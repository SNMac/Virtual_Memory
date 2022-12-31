/**
 * @file
 * @brief
 * @date 2022/11/05
 * @author SNMac
 */

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <experimental/filesystem>
#include <unordered_map>
#include <algorithm>
#include <csignal>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "main.h"
#include "Scheduler.h"
#include "Child.h"

using namespace std;
namespace fs = experimental::filesystem;

string schedName;
Scheduler sched;
unordered_map<pid_t, int> children;
int msgq;

int page_level;
int RAM[RAM_SIZE];
pid_t freeFrame[PAGE_TABLE_ENTRY_NUM];
int freeFrameCount = PAGE_TABLE_ENTRY_NUM;
unordered_map<pid_t, struct Paging> PCB;
vector<pair<pid_t, int>> LRU_OneLevel;  // <pid, pfn>
vector<tuple<pid_t, int, int>> LRU_TwoLevel;  // <pid, tblNum, pfn>
string diskDir;

/* for output of the program */
ofstream output;
chrono::steady_clock::time_point programStart;

int main() {
    cout << "Scheduler : FIFO, RR, MLQ, MLFQ, CFS\n";
    cout << "Scheduler? >> ";
    cin >> schedName;
    if (!sched.setScheduler(schedName)) {
        cerr << "Undefined scheduler\n";
        exit(EXIT_SUCCESS);
    }

    cout << "Paging level : 1, 2\n";
    cout << "Paging level? >> ";
    cin >> page_level;
    if (page_level != PAGE_ONE_LEVEL && page_level != PAGE_TWO_LEVEL) {
        cerr << "Undefined paging level\n";
        exit(EXIT_SUCCESS);
    }

    /* for memory swapping */
    diskDir = fs::current_path().string() + "/Disk_for_swapping";
    fs::create_directory(diskDir);
    for (const auto& entry : fs::directory_iterator(diskDir))  // delete previous swapping files
        fs::remove_all(entry);

    fill_n(RAM, RAM_SIZE, 0);
    fill_n(freeFrame, PAGE_TABLE_ENTRY_NUM, FREE_FRAME_VALID);

    /* for output file */
    if (page_level == PAGE_ONE_LEVEL) {
        output.open(sched.getScheduler() + "_OneLevel_schedule_dump.txt");
    } else {
        output.open(sched.getScheduler() + "_TwoLevel_schedule_dump.txt");
    }

    /* create child process */
    createChildren(CHILD_PROCESS_NUM);

    /* for message queue */
    int key = MSG_QUEUE_KEY;
    msgq = msgget(key, IPC_CREAT | 0666);
    struct msgblock msg{};

    /* for signal handling */
    struct sigaction old_sa{};
    struct sigaction new_sa{};
    new_sa.sa_handler = signal_handler;
    if (sigaction(SIGALRM, &new_sa, &old_sa) == -1) {
        perror("sigaction(SIGALRM)");
        exit(EXIT_FAILURE);
    }

    sched.setNowPID();  // setting target child
    sched.setRemain_ts();  // setting time slice

    /* for execution time */
    programStart = chrono::steady_clock::now();

    /* for periodic signaling */
    struct itimerval new_itimer{};
    struct itimerval old_itimer{};
    new_itimer.it_interval.tv_sec = 0;
    new_itimer.it_interval.tv_usec = 50000;  // 50ms
    new_itimer.it_value.tv_sec = 0;
    new_itimer.it_value.tv_usec = 50000;  // 50ms
    if (setitimer(ITIMER_REAL, &new_itimer, &old_itimer) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    while(true) {  // check IPC message queue
        if(msgrcv(msgq, &msg, sizeof(struct msgblock) - sizeof(long), 0, IPC_NOWAIT) != -1) {  // IPC message received
            receivedCPUmsg(msg.pid, msg.CPU_burst, msg.v_addr, msg.data, msg.isWrite);
            if (msg.isIOJob) {  // child requested IO time
                receivedIOmsg(msg.IO_burst);
            } else if (sched.getRemain_ts() == 0) {  // used all time slice
                output << sched.ReadyQtoInactiveQ();
                if (sched.isReadyQEmpty())  // readyQ is empty
                    output << sched.swapQ();  // swap inactiveQ and readyQ
                sched.setNowPID();  // change target child
                sched.setRemain_ts();  // reset time slice for target child
            }
        }
    }
}
void createChildren(int num) {
    pid_t ch_pid;
    int rwb_bias = CHILD_WRITE;
    for (int i = 0; i < num; i++) {
        /* create child using fork() */
        if ((ch_pid = fork()) < 0) {  // fork failed
            perror("fork");
        } else if (ch_pid == 0) {  // fork success, child
            Child child(rwb_bias);
            child.DoSomeJob();
            exit(EXIT_SUCCESS);
        } else {  // fork success, parent
            int priority = uniformRNG(MAIN_PRIORITY_MIN, MAIN_PRIORITY_MAX);
            sched.insertReadyQ(ch_pid, priority);
            children.insert(pair<pid_t, int>(ch_pid, priority));
            struct Paging page{};
            if (page_level == PAGE_TWO_LEVEL)
                fill_n(page.pageTbl2ndValid, PAGE_DIRECTORY_ENTRY_NUM, true);
            page.rwb_bias = rwb_bias;
            PCB.insert(pair<pid_t, struct Paging>(ch_pid, page));
#ifdef SWAP_TEST
            if (children.size() >= 2) {
                rwb_bias = CHILD_READ;
            } else if (children.size() >= 1) {
                rwb_bias = CHILD_BOTH;
            }
#else
            if (children.size() >= 7) {
                rwb_bias = CHILD_READ;
            } else if (children.size() >= 3) {
                rwb_bias = CHILD_BOTH;
            }
#endif
            cout << "forked) PID : " << ch_pid << ", priority : " << priority << '\n';
            output << "forked) PID : " << ch_pid << ", priority : " << priority << '\n';
        }
    }
    output << "\n\n";
}

void receivedCPUmsg(pid_t msgpid, int msgCPU, const int msgVA[], const int msgdata[], const bool msgisWrite[]) {
    /* child send CPU burst for output */
    bool isContextSwitched = false;

    if (sched.getScheduler() == "MLQ") {
        if (msgpid != sched.getNowPID())  // Context switched by priority
            isContextSwitched = true;
    }
    output << "at time : " << sched.getTickCount() << ", current PID : " << msgpid
           << ", remaining CPU burst : " << msgCPU;
    if (sched.getScheduler() != "FIFO") {
        if (isContextSwitched) {  // for MLQ
            output << ", remaining time slice : " << 0 << '\n';
        } else {
            output << ", remaining time slice : " << sched.getRemain_ts() << '\n';
        }
    } else {
        output << '\n';
    }

    /* RAM access */
    for (int i = 0; i < CHILD_MEMORY_ACCESS_NUM; i++) {
        int p_addr = MMU(msgpid, msgVA[i]);  // translate VA to PA
        int arr_addr = p_addr >> 2;  // PA to array index
        if (msgisWrite[i]) {
            RAM[arr_addr] = msgdata[i];

            cout << "RAM[0x" << hex;
            cout.width(4); cout.fill('0');
            cout << p_addr << "] write <- 0x";
            cout.width(8); cout.fill('0');
            cout << RAM[arr_addr] << "\n\n" << dec;

            output << "RAM[0x" << hex;
            output.width(4); output.fill('0');
            output << p_addr << "] write <- 0x";
            output.width(8); output.fill('0');
            output << RAM[arr_addr] << "\n\n" << dec;
        } else {
            cout << "RAM[0x" << hex;
            cout.width(4); cout.fill('0');
            cout << p_addr << "] read -> 0x";
            cout.width(8); cout.fill('0');
            cout << RAM[arr_addr] << "\n\n" << dec;

            output << "RAM[0x" << hex;
            output.width(4); output.fill('0');
            output << p_addr << "] read -> 0x";
            output.width(8); output.fill('0');
            output << RAM[arr_addr] << "\n\n" << dec;
        }
    }

    output << sched.outputDump() << "\n\n";

    if (isContextSwitched)
        output << "\n<<< Context switched by priority) Child PID : " << msgpid << " -> " << sched.getNowPID() << " >>>\n\n\n";
}

void receivedIOmsg(int msgIO) {
    output << sched.ReadyQtoWaitQ(msgIO);
    if (sched.isReadyQEmpty()) {  // readyQ is empty
        if (!sched.isInactiveQEmpty()) {  // inactiveQ has child
            output << sched.swapQ();  // swap inactiveQ and readyQ
            sched.setNowPID();  // change target child
            sched.setRemain_ts();  // reset time slice to target child
        }
    } else {  // readyQ has child
        sched.setNowPID();  // change target child
        sched.setRemain_ts();  // reset time slice to target child
    }
}

int MMU(pid_t pid, int v_addr) {
    if (freeFrameCount == 0)  // all page frame is used
        pageFrameSwapOut();

    /* address translation */
    int pageTblIndex, pageFrameNum, pageOffset, p_addr;
    if (page_level == PAGE_ONE_LEVEL) {  // One-level
        pageTblIndex = v_addr >> PAGE_TABLE_INDEX_BITSHIFT;
        if (PCB[pid].pageTbl[pageTblIndex][0] == PAGE_TABLE_ENTRY_INVALID) {  // page table entry is invalid
            for (int i = 0; i < PAGE_TABLE_ENTRY_NUM; i++) {
                if (freeFrame[i] == FREE_FRAME_VALID) {
                    PCB[pid].pageTbl[pageTblIndex][0] = PAGE_TABLE_ENTRY_VALID;
                    PCB[pid].pageTbl[pageTblIndex][1] = PAGE_TABLE_ENTRY_PRESENT;
                    PCB[pid].pageTbl[pageTblIndex][2] = i;
                    freeFrame[i] = pid;
                    freeFrameCount--;
                    output << "<<< Initial) PageTable[" << to_string(pageTblIndex) << "] <- page frame " << i << " >>>\n";
                    break;
                }
            }
        }
        if (PCB[pid].pageTbl[pageTblIndex][1] == PAGE_TABLE_ENTRY_NOTPRESENT) {  // page fault
            cout << "<<< Page fault occurred >>>\n";
            output << "<<< Page fault occurred >>>\n";
            pageFrameSwapIn(pid, pageTblIndex, PCB[pid].pageTbl[pageTblIndex][2]);
        }
        pageFrameNum = PCB[pid].pageTbl[pageTblIndex][2];
        output << "<<< PageTable[" << to_string(pageTblIndex) << "] -> page frame " << pageFrameNum << " >>>\n";

        for (int i = 0; i < LRU_OneLevel.size(); ) {  // for LRU page swapping-out
            if (LRU_OneLevel[i].second == pageFrameNum) {
                LRU_OneLevel.erase(LRU_OneLevel.begin() + i);
                break;
            } else {
                i++;
            }
        }
        LRU_OneLevel.emplace_back(pid, pageFrameNum);

    } else {  // Two-level
        int pageDirIndex, pageTblNum;
        pageDirIndex = v_addr >> PAGE_DIRECTORY_INDEX_BITSHIFT;
        pageTblIndex = (v_addr >> PAGE_TABLE_2ND_INDEX_BITSHIFT) & PAGE_TABLE_2ND_INDEX_BITMASK;
        if (PCB[pid].pageDir[pageDirIndex][0] == PAGE_DIRECTORY_ENTRY_INVALID) {  // page directory entry is invalid
            for (int i = 0; i < PAGE_DIRECTORY_ENTRY_NUM; i++) {
                if (PCB[pid].pageTbl2ndValid[i]) {
                    PCB[pid].pageTbl2ndValid[i] = false;
                    PCB[pid].pageDir[pageDirIndex][0] = PAGE_DIRECTORY_ENTRY_VALID;
                    PCB[pid].pageDir[pageDirIndex][1] = i;
                    output << "<<< Initial) PageDirectory[" << to_string(pageDirIndex) << "] <- PageTable[" << i << "] >>>\n";
                    break;
                }
            }
        }
        pageTblNum = PCB[pid].pageDir[pageDirIndex][1];
        output << "<<< PageDirectory[" << to_string(pageDirIndex) << "] -> PageTable[" << pageTblNum << "] >>>\n";

        if (PCB[pid].pageTbl2nd[pageTblNum][pageTblIndex][0] == PAGE_TABLE_ENTRY_INVALID) {  // 2nd level page table entry is invalid
            for (int i = 0; i < PAGE_TABLE_ENTRY_NUM; i++) {
                if (freeFrame[i] == FREE_FRAME_VALID) {
                    PCB[pid].pageTbl2nd[pageTblNum][pageTblIndex][0] = PAGE_TABLE_ENTRY_VALID;
                    PCB[pid].pageTbl2nd[pageTblNum][pageTblIndex][1] = PAGE_TABLE_ENTRY_PRESENT;
                    PCB[pid].pageTbl2nd[pageTblNum][pageTblIndex][2] = i;
                    freeFrame[i] = pid;
                    freeFrameCount--;
                    output << "<<< Initial) PageTable[" << pageTblNum << "][" << to_string(pageTblIndex) << "] <- page frame " << i << " >>>\n";
                    break;
                }
            }
        }
        if (PCB[pid].pageTbl2nd[pageTblNum][pageTblIndex][1] == PAGE_TABLE_ENTRY_NOTPRESENT) {  // page fault
            cout << "<<< Page fault occurred >>>\n";
            output << "<<< Page fault occurred >>>\n";
            pageFrameSwapIn(pid, pageTblNum, pageTblIndex, PCB[pid].pageTbl2nd[pageTblNum][pageTblIndex][2]);
        }
        pageFrameNum = PCB[pid].pageTbl2nd[pageTblNum][pageTblIndex][2];
        output << "<<< PageTable[" << pageTblNum << "][" << to_string(pageTblIndex) << "] -> page frame " << pageFrameNum << " >>>\n";

        for (int i = 0; i < LRU_TwoLevel.size(); ) {  // for LRU page swapping-out
            if (get<2>(LRU_TwoLevel[i]) == pageFrameNum) {
                LRU_TwoLevel.erase(LRU_TwoLevel.begin() + i);
                break;
            } else {
                i++;
            }
        }
        LRU_TwoLevel.emplace_back(pid, pageTblNum, pageFrameNum);
    }

    pageOffset = v_addr & PAGE_OFFSET_BITMASK;
    p_addr = (pageFrameNum << PAGE_FRAME_NUM_BITSHIFT) | pageOffset;

    cout << "MMU) Virtual Address 0x" << hex;
    cout.width(4); cout.fill('0');
    cout << v_addr << " -> Physical Address 0x";
    cout.width(4); cout.fill('0');
    cout << p_addr << dec << '\n';

    output << "MMU) Virtual Address 0x" << hex;
    output.width(4); output.fill('0');
    output << v_addr << " -> Physical Address 0x";
    output.width(4); output.fill('0');
    output << p_addr << dec << '\n';

    return p_addr;
}

void pageFrameSwapOut() {
    pid_t evictPID;
    int evictPageFrameNum;

    for (int i = 0; i < PAGE_FRAME_EVICTION; i++) {
        if (page_level == PAGE_ONE_LEVEL) {
            evictPID = LRU_OneLevel.front().first;
            evictPageFrameNum = LRU_OneLevel.front().second;
            LRU_OneLevel.erase(LRU_OneLevel.begin());
            string pageFrameDir = diskDir + '/' + to_string(evictPageFrameNum) + '_' + to_string(evictPID);
            ofstream swapOut(pageFrameDir);

            for (int evictPageOffset = 0; evictPageOffset <= PAGE_OFFSET_MAX; evictPageOffset += 0x4) {
                int memIndex = ((evictPageFrameNum << PAGE_FRAME_NUM_BITSHIFT) | evictPageOffset) >> 2;
                swapOut << to_string(RAM[memIndex]);  // RAM contents
                if (evictPageOffset != PAGE_OFFSET_MAX)
                    swapOut << '\n';
            }
            swapOut << flush;
            swapOut.close();
            for (auto& it : PCB[evictPID].pageTbl) {
                if (it[2] == evictPageFrameNum) {
                    it[1] = PAGE_TABLE_ENTRY_NOTPRESENT;
                    break;
                }
            }
            cout << "<<< Swap-out) RAM(" << evictPageFrameNum << ") -> Disk_for_swapping(" << evictPageFrameNum << '_' << evictPID << ") >>>\n";
            output << "<<< Swap-out) RAM(" << evictPageFrameNum << ") -> Disk_for_swapping(" << evictPageFrameNum << '_' << evictPID << ") >>>\n";
        } else {  // Two-level
            evictPID = get<0>(LRU_TwoLevel.front());
            int evictPageTblNum = get<1>(LRU_TwoLevel.front());
            evictPageFrameNum = get<2>(LRU_TwoLevel.front());
            LRU_TwoLevel.erase(LRU_TwoLevel.begin());
            string pageFrameDir = diskDir + '/' + to_string(evictPageFrameNum) + '_' + to_string(evictPID) + '_' + to_string(evictPageTblNum);
            ofstream swapOut(pageFrameDir);

            for (int evictPageOffset = 0; evictPageOffset <= PAGE_OFFSET_MAX; evictPageOffset += 0x4) {
                int memIndex = ((evictPageFrameNum << PAGE_FRAME_NUM_BITSHIFT) | evictPageOffset) >> 2;
                swapOut << to_string(RAM[memIndex]);  // RAM contents
                if (evictPageOffset != PAGE_OFFSET_MAX)
                    swapOut << '\n';
            }
            swapOut << flush;
            swapOut.close();
            for (auto& it : PCB[evictPID].pageTbl2nd[evictPageTblNum]) {
                if (it[2] == evictPageFrameNum) {
                    it[1] = PAGE_TABLE_ENTRY_NOTPRESENT;
                    break;
                }
            }
            cout << "<<< Swap-out) RAM(" << evictPageFrameNum << ") -> Disk_for_swapping(" << evictPageFrameNum << '_' << evictPID << '_' << evictPageTblNum << ") >>>\n";
            output << "<<< Swap-out) RAM(" << evictPageFrameNum << ") -> Disk_for_swapping(" << evictPageFrameNum << '_' << evictPID << '_' << evictPageTblNum << ") >>>\n";
        }
        PCB[evictPID].swapOutCount++;
        freeFrame[evictPageFrameNum] = FREE_FRAME_VALID;
        freeFrameCount++;
    }
}

void pageFrameSwapIn(pid_t pid, int pageTblIndex, int pageFrameNum) {  // for One-level paging
    int newPageFrame;
    string pageFrameDir = diskDir + '/' + to_string(pageFrameNum) + '_' + to_string(pid);
    ifstream swapIn(pageFrameDir);
    string pageFrameContent;

    if (swapIn.is_open()) {
        /* assign new page frame */
        for (int i = 0; i < PAGE_TABLE_ENTRY_NUM; i++) {
            if (freeFrame[i] == FREE_FRAME_VALID) {
                PCB[pid].pageTbl[pageTblIndex][1] = PAGE_TABLE_ENTRY_PRESENT;
                PCB[pid].pageTbl[pageTblIndex][2] = i;
                freeFrame[i] = pid;
                freeFrameCount--;
                newPageFrame = i;
                break;
            }
        }

        /* read page frame */
        int newPageOffset = 0;
        int lineNum = 0;
        while(swapIn) {
            lineNum++;
            if (lineNum > PAGE_SIZE >> 2)
                break;
            getline(swapIn, pageFrameContent);
            int memIndex = ((newPageFrame << PAGE_FRAME_NUM_BITSHIFT) | newPageOffset) >> 2;
            RAM[memIndex] = stoi(pageFrameContent);  // RAM contents
            newPageOffset += 4;
        }
        swapIn.close();
        fs::remove(pageFrameDir);
    } else {
        cerr << "Undefined swapping file\n";
        exit(EXIT_FAILURE);
    }
    PCB[pid].swapInCount++;
    cout << "<<< Swap-in) RAM(" << newPageFrame << ") <- Disk_for_swapping(" << pageFrameNum << '_' << pid << ") >>>\n";
    output << "<<< Swap-in) RAM(" << newPageFrame << ") <- Disk_for_swapping(" << pageFrameNum << '_' << pid << ") >>>\n";
    output << "<<< Changing) PageTable[" << to_string(pageTblIndex) << "] <- page frame " << newPageFrame << " >>>\n";
}

void pageFrameSwapIn(pid_t pid, int pageTblNum, int pageTblIndex, int pageFrameNum) {  // for Two-level paging
    int newPageFrame;
    string pageFrameDir = diskDir + '/' + to_string(pageFrameNum) + '_' + to_string(pid) + '_' + to_string(pageTblNum);
    ifstream swapIn(pageFrameDir);
    string pageFrameContent;

    if (swapIn.is_open()) {
        /* assign new page frame */
        for (int i = 0; i < PAGE_TABLE_ENTRY_NUM; i++) {
            if (freeFrame[i] == FREE_FRAME_VALID) {
                PCB[pid].pageTbl2nd[pageTblNum][pageTblIndex][1] = PAGE_TABLE_ENTRY_PRESENT;
                PCB[pid].pageTbl2nd[pageTblNum][pageTblIndex][2] = i;
                freeFrame[i] = pid;
                freeFrameCount--;
                newPageFrame = i;
                break;
            }
        }

        /* read page frame */
        int newPageOffset = 0;
        int lineNum = 0;
        while(swapIn) {
            lineNum++;
            if (lineNum > PAGE_SIZE >> 2)
                break;
            getline(swapIn, pageFrameContent);
            int memIndex = ((newPageFrame << PAGE_FRAME_NUM_BITSHIFT) | newPageOffset) >> 2;
            RAM[memIndex] = stoi(pageFrameContent);  // RAM contents
            newPageOffset += 4;
        }
        swapIn.close();
        fs::remove(pageFrameDir);
    } else {
        cerr << "Undefined swapping file\n";
        exit(EXIT_FAILURE);
    }
    PCB[pid].swapInCount++;
    cout << "<<< Swap-in) RAM(" << newPageFrame << ") <- Disk_for_swapping(" << pageFrameNum << '_' << pid << ") >>>\n";
    output << "<<< Swap-in) RAM(" << newPageFrame << ") <- Disk_for_swapping(" << pageFrameNum << '_' << pid << ") >>>\n";
    output << "<<< Initial) PageTable[" << pageTblNum << "][" << to_string(pageTblIndex) << "] <- page frame " << newPageFrame << " >>>\n";
}

void signal_handler(int signo) {
    cout << "SIGALRM(" << signo << ") ~> Parent(" << getpid() << ")\n";
    sched.incTick_count();

    /* end of execution */
    if (sched.getTickCount() > MAIN_OUTPUT_TICK) {
        auto programEnd = chrono::steady_clock::now();
        auto programTime = chrono::duration<double>(programEnd - programStart);
        if (msgctl(msgq, IPC_RMID, nullptr) == -1) {
            perror("msgctl");
            exit(EXIT_FAILURE);
        }
        for (auto it : children)  // kill children
            kill(it.first, SIGTERM);
        cout << fixed;
        cout.precision(4);
        cout << "Execution time : " << programTime.count() << " seconds" << '\n';
        cout << "Scheduler : " << sched.getScheduler() << '\n';
        cout << "Paging level : " << page_level << endl;

        output << "\n<<< End Of Execution >>>\n\n";

        output << fixed;
        output.precision(4);
        output << "Execution time : " << programTime.count() << " seconds\n";
        output << "Scheduler : " << sched.getScheduler() << '\n';
        output << "Paging level : " << page_level << "\n\n\n";

        /* find page frame number in RAM */
        for (int i = 0; i < PAGE_TABLE_ENTRY_NUM; i++) {
            if (freeFrame[i] != FREE_FRAME_VALID)
                PCB[freeFrame[i]].pageFrames_RAM.push_back(i);
        }

        /* find page frame number in Disk */
        if (page_level == PAGE_ONE_LEVEL) {
            for (const auto& entry : fs::directory_iterator(diskDir)) {
                string fname = entry.path().filename();
                size_t index = fname.find('_');
                int fnamePID = stoi(fname.substr(index + 1));
                int fnamePageFrame = stoi(fname.substr(0, index));
                PCB[fnamePID].pageFrames_Disk.push_back(fnamePageFrame);
            }
        } else {  // Two-level
            for (const auto& entry : fs::directory_iterator(diskDir)) {
                string fname = entry.path().filename();
                size_t index = fname.find('_');
                size_t index2nd = fname.find('_', index + 1);
                int fnamePID = stoi(fname.substr(index + 1, index2nd - index - 1));
                int fnamePageFrame = stoi(fname.substr(0, index));
                PCB[fnamePID].pageFrames_Disk.push_back(fnamePageFrame);
            }
        }

        int total_pageTblSize = 0;
        int total_RAMUsage = 0;
        int total_DiskUsage = 0;
        int total_swapInCount = 0;
        int total_swapOutCount = 0;
        for (auto it : children) {
            /* calculate page table memory usage */
            // One-level paging : PAGE_TABLE_ENTRY_NUM * 4bytes
            // Two-level paging : PAGE_DIRECTORY_ENTRY_NUM * 4bytes +
            //                      <# of valid page table> * PAGE_TABLE_2ND_ENTRY_NUM * 4bytes
            int childPageTblSize;
            if (page_level == PAGE_ONE_LEVEL) {  // One-level
                childPageTblSize = PAGE_TABLE_ENTRY_NUM * 4;
            } else {  // Two-level
                int pageTblCount = 0;
                for (const auto valid : PCB[it.first].pageTbl2ndValid) {
                    if (!valid)
                        pageTblCount++;
                }
                childPageTblSize = PAGE_DIRECTORY_ENTRY_NUM * 4 + pageTblCount * PAGE_TABLE_2ND_ENTRY_NUM * 4;
            }
            total_pageTblSize += childPageTblSize;

            /* calculate RAM usage */
            int childRAMUsage = PCB[it.first].pageFrames_RAM.size() * PAGE_SIZE;
            total_RAMUsage += childRAMUsage;

            /* calculate Disk usage */
            int childDiskUsage = PCB[it.first].pageFrames_Disk.size() * PAGE_SIZE;
            total_DiskUsage += childDiskUsage;

            /* calculate memory(RAM + Disk) usage */
            int childMemUsage = childRAMUsage + childDiskUsage;

            /* calculate # of swapping */
            int childSwapInCount = PCB[it.first].swapInCount;
            int childSwapOutCount = PCB[it.first].swapOutCount;
            total_swapInCount += childSwapInCount;
            total_swapOutCount += childSwapOutCount;

            output.precision(2);
            output << "PID : " << it.first << ")\n";
            output << "Priority : " << it.second << ", CPU time : " << sched.pidCPU[it.first]
                   << ", Page table size : " << childPageTblSize
                   << "bytes, RAM usage : " << (double)childRAMUsage / 1024.0
                   << "KB, Disk usage : " << (double)childDiskUsage / 1024.0
                   << "KB, Memory usage : " << (double)childMemUsage / 1024.0
                   << "KB, # of Swap-in : " << childSwapInCount << ", # of Swap-out : " << childSwapOutCount << '\n';

            output << "Page frames presented in RAM : ";
            for (auto pfn : PCB[it.first].pageFrames_RAM)
                output << pfn << ' ';
            output << '\n';

            output << "Page frames presented in Disk : ";
            for (auto pfn : PCB[it.first].pageFrames_Disk)
                output << pfn << ' ';
            output << '\n';

            output << "Memory access bias : ";
            if (PCB[it.first].rwb_bias == CHILD_READ) {
                output << "READ";
            } else if (PCB[it.first].rwb_bias == CHILD_WRITE) {
                output << "WRITE";
            } else {
                output << "BOTH";
            }
            output << "\n\n";
        }

        output << "Total page table size : " << (double)total_pageTblSize / 1024.0 << "KB\n";
        output << "Total RAM usage : " << (double)total_RAMUsage / 1024.0 << "KB\n";
        output << "Total Disk usage : " << (double)total_DiskUsage / 1024.0 << "KB\n";
        double total_UsedMemory = (double)(total_RAMUsage + total_DiskUsage) / 1024.0;
        output << "Total memory usage : " << total_UsedMemory << "KB\n";
        output << "Total # of Swap-in : " << total_swapInCount << '\n';
        output << "Total # of Swap-out : " << total_swapOutCount << '\n' << flush;

        exit(EXIT_SUCCESS);
    }

    /* continue execution */
    pid_t ch_pid;
    if (!sched.isReadyQEmpty()) {  // readyQ has child
        ch_pid = sched.getNowPID();
        sched.addCPUtime(ch_pid);
        kill(ch_pid, SIGUSR1);
        if (sched.getScheduler() != "FIFO")  // RR, MLQ, MLFQ, CFS
            sched.decRemain_ts();
    } else {  // readyQ is empty
        sched.IO_bounded = true;
    }

    if (!sched.isWaitQEmpty())  // waitQ has child
        sched.IOJob();
}