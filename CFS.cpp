/**
 * @file
 * @brief
 * @date 2022/11/08
 * @author SNMac
 */

#include "CFS.h"

void CFS::insertReadyQ(pid_t pid, int priority) {
    pidWeights.insert(std::pair<pid_t, int>(pid, sched_prio_to_weight[priority]));
    pidVruntime.insert(std::pair<pid_t, unsigned long long>(pid, 0));
    readyQ.insert(std::pair<int, pid_t>(0, pid));
}

std::string CFS::IOJob(bool& IO_bounded) {
    std::string ret;
    pid_t pid;
    for (int i = 0; i < waitQ.size(); ) {
        if (--waitQ[i].second == 0) {
            pid = waitQ[i].first;
            ret += "\n<<< IO burst finished) Child PID : " + std::to_string(pid) + " -> ReadyQ >>>\n";
            readyQ.insert(std::pair<unsigned long long, pid_t>(pidVruntime[pid], pid));
            waitQ.erase(waitQ.begin() + i);
            if (IO_bounded) {
                IO_bounded = false;
                setNowPID();
            }
        } else {
            i++;
        }
    }
    return ret + '\n';
}

std::string CFS::ReadyQtoWaitQ(int IO_burst) {
    std::string ret;
    std::multimap<unsigned long long, pid_t>::iterator it;
    for (it = readyQ.begin(); it != readyQ.end(); it++) {
        if (it->second == now_pid) {
            readyQ.erase(it);
            break;
        }
    }
    waitQ.emplace_back(now_pid, IO_burst);
    ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitQ for " + std::to_string(IO_burst) + " >>>\n\n";
    return ret;
}

std::string CFS::ReadyQtoInactiveQ() {
    std::string ret;
    std::multimap<unsigned long long, pid_t>::iterator it;
    for (it = readyQ.begin(); it != readyQ.end(); it++) {
        if (it->second == now_pid) {
            readyQ.erase(it);
            break;
        }
    }
    inactiveQ.push_back(now_pid);
    ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> InactiveQ >>>\n\n";
    return ret;
}

std::string CFS::swapQ() {
    while(!inactiveQ.empty()) {
        pid_t pid = inactiveQ.front();
        readyQ.insert(std::pair<unsigned long long, pid_t>(pidVruntime[pid], pid));
        inactiveQ.pop_front();
    }
    return "\n<<< Queue swapping) InactiveQ <-> ReadyQ >>>\n\n";
}

std::string CFS::updateVruntime(int CPUTime) {
    pidVruntime[now_pid] += CPUTime * ((double)CFS_NICE_0_LOAD / (double)pidWeights[now_pid]);
    return "PID : " + std::to_string(now_pid) + ") update vruntime : " + std::to_string(pidVruntime[now_pid]) + '\n';
}

int CFS::setRemain_ts() {
    pid_t pid = now_pid;
    int totalWeight = 0;
    for (auto it : pidWeights)
        totalWeight += it.second;
    return CFS_TARGET_LATENCY * ((double)pidWeights[pid] / (double)totalWeight);
}

std::string CFS::outputDump() {
    std::string ret = "ReadyQ : ";

    /* readyQ dump */
    for (auto it : readyQ)
        ret += std::to_string(it.second) + " -> ";
    ret += "EndOfQ\nvruntime : ";

    /* vruntime hash map dump */
    for (auto it : pidVruntime)
        ret += "(PID : " + std::to_string(it.first) + ", " + std::to_string(it.second) + ")" + " -> ";
    ret += "EndOfQ\nInactiveQ : ";

    /* inactiveQ dump */
    for (auto it : inactiveQ)
        ret += std::to_string(it) + " -> ";
    ret += "EndOfQ\nWaitQ : ";

    /* waitQ dump */
    for (auto it : waitQ)
        ret += std::to_string(it.first) + " -> ";
    ret += "EndOfQ\n";

    return ret;
}