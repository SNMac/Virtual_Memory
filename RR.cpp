/**
 * @file
 * @brief
 * @date 2022/11/14
 * @author SNMac
 */

#include "RR.h"

std::string RR::IOJob(bool& IO_bounded) {
    std::string ret;
    pid_t pid;
    for (int i = 0; i < waitQ.size(); ) {
        if (--waitQ[i].second == 0) {
            pid = waitQ[i].first;
            ret += "\n<<< IO burst finished) Child PID : " + std::to_string(pid) + " -> ReadyQ >>>\n";
            readyQ.push_back(pid);
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

std::string RR::ReadyQtoWaitQ(int IO_burst) {
    std::string ret;
    readyQ.pop_front();
    waitQ.emplace_back(now_pid, IO_burst);
    ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitQ for " + std::to_string(IO_burst) + " >>>\n\n";
    return ret;
}

std::string RR::ReadyQtoInactiveQ() {
    std::string ret;
    readyQ.pop_front();
    inactiveQ.push_back(now_pid);
    ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> InactiveQ >>>\n\n";
    return ret;
}

std::string RR::outputDump() {
    std::string ret = "ReadyQ : ";

    /* readyQ dump */
    for (auto it : readyQ)
        ret += std::to_string(it) + " -> ";
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