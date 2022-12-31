/**
 * @file
 * @brief
 * @date 2022/11/07
 * @author SNMac
 */

#include "FIFO.h"

std::string FIFO::IOJob(bool& IO_bounded) {
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

std::string FIFO::ReadyQtoWaitQ(int IO_burst) {
    std::string ret;
    readyQ.pop_front();
    waitQ.emplace_back(now_pid, IO_burst);
    ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitQ for " + std::to_string(IO_burst) + " >>>\n\n";
    return ret;
}

std::string FIFO::outputDump() {
    std::string ret = "ReadyQ : ";

    /* readyQ dump */
    for (auto it : readyQ)
        ret += std::to_string(it) + " -> ";
    ret += "EndOfQ\nWaitQ : ";

    /* waitQ dump */
    for (auto it : waitQ)
        ret += std::to_string(it.first) + " -> ";
    ret += "EndOfQ\n";

    return ret;
}