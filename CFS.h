/**
 * @file
 * @brief
 * @date 2022/11/08
 * @author SNMac
 */

#ifndef INC_2022_OS_PROJ2_CFS_H
#define INC_2022_OS_PROJ2_CFS_H

#include <unordered_map>
#include <map>
#include <deque>
#include <vector>
#include <string>
#include <unistd.h>

#define CFS_TARGET_LATENCY 600
#define CFS_NICE_0_LOAD 64

class CFS {
public:
    /* class variables */
    pid_t now_pid;  // current handling child's pid
    const int sched_prio_to_weight[20] = {  // 64 * 1.15^(-priority)
            259, 225, 196, 170, 148,
            129, 112, 97, 85, 74,
            64, 56, 48, 42, 37,
            32, 28, 24, 21, 18
    };
    std::unordered_map<pid_t, int> pidWeights;  // <pid, weight>, hash map
    std::unordered_map<pid_t, unsigned long long> pidVruntime;  // <pid, vruntime>, hash map
    std::multimap<unsigned long long, pid_t> readyQ;  // <vruntime, pid>, red-black tree
    std::deque<pid_t> inactiveQ;
    std::vector<std::pair<pid_t, int>> waitQ;  // <pid, IO_burst>

    /* class functions specified in here */
    bool isReadyQEmpty() {return readyQ.empty();}
    bool isWaitQEmpty() {return waitQ.empty();}
    void setNowPID() {now_pid = readyQ.begin()->second;}
    pid_t getNowPID() {return now_pid;}

    /* class functions specified in .cpp */
    void insertReadyQ(pid_t pid, int priority);
    std::string IOJob(bool& IO_bounded);
    std::string ReadyQtoWaitQ(int IO_burst);
    std::string ReadyQtoInactiveQ();
    std::string swapQ();
    std::string updateVruntime(int CPUTime);
    int setRemain_ts();  // calculate actual time slice
    std::string outputDump();
};

#endif //INC_2022_OS_PROJ2_CFS_H
