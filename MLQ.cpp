/**
 * @file
 * @brief
 * @date 2022/11/16
 * @author SNMac
 */

#include "MLQ.h"

void MLQ::insertReadyQ(pid_t pid, int priority) {
    if (priority <= 5) {  // 0 ~ 5
        readyFirstQ.push_back(pid);
    } else if (priority <= 12) {  // 6 ~ 12
        readySecondQ.push_back(pid);
    } else {  // 13 ~ 19
        readyThirdQ.push_back(pid);
    }
}

void MLQ::setNowPID() {
    if (!readyFirstQ.empty()) {
        now_pid = readyFirstQ.front();
        now_level = MLQ_FIRST_LEVEL;
    } else if (!readySecondQ.empty()) {
        now_pid = readySecondQ.front();
        now_level = MLQ_SECOND_LEVEL;
    } else {
        now_pid = readyThirdQ.front();
        now_level = MLQ_THIRD_LEVEL;
    }
}

std::string MLQ::IOJob(bool& IO_bounded) {
    std::string ret;
    pid_t pid;
    pid_t old_pid = now_pid;
    bool isContextSwitched = false;
    for (int i = 0; i < waitThirdQ.size(); ) {
        if (--waitThirdQ[i].second == 0) {
            pid = waitThirdQ[i].first;
            ret += "\n<<< IO burst finished) Child PID : " + std::to_string(pid) + " -> ReadyThirdQ >>>\n";
            readyThirdQ.push_back(pid);
            waitThirdQ.erase(waitThirdQ.begin() + i);
            if (IO_bounded) {
                IO_bounded = false;
                setNowPID();
            }
        } else {
            i++;
        }
    }
    for (int i = 0; i < waitSecondQ.size(); ) {
        if (--waitSecondQ[i].second == 0) {
            pid = waitSecondQ[i].first;
            ret += "\n<<< IO burst finished) Child PID : " + std::to_string(pid) + " -> ReadySecondQ >>>\n";
            readySecondQ.push_back(pid);
            waitSecondQ.erase(waitSecondQ.begin() + i);
            if (IO_bounded)
                IO_bounded = false;
            setNowPID();
            if (old_pid != now_pid)
                isContextSwitched = true;
        } else {
            i++;
        }
    }
    for (int i = 0; i < waitFirstQ.size(); ) {
        if (--waitFirstQ[i].second == 0) {
            pid = waitFirstQ[i].first;
            ret += "\n<<< IO burst finished) Child PID : " + std::to_string(pid) + " -> ReadyFirstQ >>>\n";
            readyFirstQ.push_back(pid);
            waitFirstQ.erase(waitFirstQ.begin() + i);
            if (IO_bounded)
                IO_bounded = false;
            setNowPID();
            if (old_pid != now_pid)
                isContextSwitched = true;
        } else {
            i++;
        }
    }

    if (isContextSwitched)
        ret += "\n<<< Context switching by priority) Child PID : " + std::to_string(old_pid) + " -> " + std::to_string(now_pid) + " >>>\n";
    return ret + '\n';
}

std::string MLQ::ReadyQtoWaitQ(int IO_burst) {
    std::string ret;
    if (now_level == MLQ_FIRST_LEVEL) {
        readyFirstQ.pop_front();
        waitFirstQ.emplace_back(now_pid, IO_burst);
        ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitFirstQ for " + std::to_string(IO_burst) + " >>>\n\n";
    } else if (now_level == MLQ_SECOND_LEVEL) {
        readySecondQ.pop_front();
        waitSecondQ.emplace_back(now_pid, IO_burst);
        ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitSecondQ for " + std::to_string(IO_burst) + " >>>\n\n";
    } else {  // now_level == MLQ_THIRD_LEVEL
        readyThirdQ.pop_front();
        waitThirdQ.emplace_back(now_pid, IO_burst);
        ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitThirdQ for " + std::to_string(IO_burst) + " >>>\n\n";
    }
    return ret;
}

std::string MLQ::ReadyQtoInactiveQ() {
    std::string ret;
    if (now_level == MLQ_FIRST_LEVEL) {
        readyFirstQ.pop_front();
        readyFirstQ.push_back(now_pid);
        ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> ReadyFirstQ >>>\n\n";
    } else if (now_level == MLQ_SECOND_LEVEL) {
        readySecondQ.pop_front();
        readySecondQ.push_back(now_pid);
        ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> ReadySecondQ >>>\n\n";
    } else {  // now_level == MLQ_THIRD_LEVEL  // third -> third
        readyThirdQ.pop_front();
        readyThirdQ.push_back(now_pid);
        ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> ReadyThirdQ >>>\n\n";
    }
    return ret;
}

int MLQ::setRemain_ts() {
    if (now_level == MLQ_FIRST_LEVEL) {
        return MLQ_FIRST_LEVEL_TIME_SLICE;
    } else if (now_level == MLQ_SECOND_LEVEL) {
        return MLQ_SECOND_LEVEL_TIME_SLICE;
    } else {  // now_level == MLQ_THIRD_LEVEL
        return MLQ_THIRD_LEVEL_TIME_SLICE;
    }
}

std::string MLQ::outputDump() {
    std::string ret = "ReadyFirstQ : ";

    /* readyQ dump */
    for (auto it : readyFirstQ)
        ret += std::to_string(it) + " -> ";
    ret += "EndOfQ\nReadySecondQ : ";
    for (auto it : readySecondQ)
        ret += std::to_string(it) + " -> ";
    ret += "EndOfQ\nReadyThirdQ : ";
    for (auto it : readyThirdQ)
        ret += std::to_string(it) + " -> ";
    ret += "EndOfQ\nWaitFirstQ : ";

    /* waitQ dump */
    for (auto it : waitFirstQ)
        ret += std::to_string(it.first) + " -> ";
    ret += "EndOfQ\nWaitSecondQ : ";
    for (auto it : waitSecondQ)
        ret += std::to_string(it.first) + " -> ";
    ret += "EndOfQ\nWaitThirdQ : ";
    for (auto it : waitThirdQ)
        ret += std::to_string(it.first) + " -> ";
    ret += "EndOfQ\n";

    return ret;
}