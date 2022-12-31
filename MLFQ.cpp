/**
 * @file
 * @brief
 * @date 2022/11/12
 * @author SNMac
 */

#include "MLFQ.h"

void MLFQ::insertReadyQ(pid_t pid) {
    readyFirstQ.push_back(pid);
    childRemainTs.insert(std::pair<pid_t, int>(pid, MLFQ_FIRST_LEVEL_TIME_SLICE));
}

void MLFQ::setNowPID() {
    if (!readyFirstQ.empty()) {
        now_pid = readyFirstQ.front();
        now_level = MLFQ_FIRST_LEVEL;
    } else if (!readySecondQ.empty()) {
        now_pid = readySecondQ.front();
        now_level = MLFQ_SECOND_LEVEL;
    } else {
        now_pid = readyThirdQ.front();
        now_level = MLFQ_THIRD_LEVEL;
    }
}

std::string MLFQ::IOJob(bool& IO_bounded) {
    std::string ret;
    pid_t pid;
    for (int i = 0; i < waitFirstQ.size(); ) {
        if (--waitFirstQ[i].second == 0) {
            pid = waitFirstQ[i].first;
            ret += "\n<<< IO burst finished) Child PID : " + std::to_string(pid) + " -> ReadyFirstQ >>>\n";
            readyFirstQ.push_back(pid);
            waitFirstQ.erase(waitFirstQ.begin() + i);
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
            if (IO_bounded) {
                IO_bounded = false;
                setNowPID();
            }
        } else {
            i++;
        }
    }
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
    return ret + '\n';
}

std::string MLFQ::ReadyQtoWaitQ(int remain_ts, int IO_burst) {
    std::string ret;
    if (remain_ts == 0) {  // CPU burst == 0 && remain_ts == 0
        if (now_level == MLFQ_FIRST_LEVEL) {  // first -> second
            readyFirstQ.pop_front();
            waitSecondQ.emplace_back(now_pid, IO_burst);
            childRemainTs[now_pid] = MLFQ_SECOND_LEVEL_TIME_SLICE;
            ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitSecondQ for " + std::to_string(IO_burst) + " >>>\n\n";
        } else if (now_level == MLFQ_SECOND_LEVEL) {  // second -> third
            readySecondQ.pop_front();
            waitThirdQ.emplace_back(now_pid, IO_burst);
            childRemainTs[now_pid] = MLFQ_THIRD_LEVEL_TIME_SLICE;
            ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitThirdQ for " + std::to_string(IO_burst) + " >>>\n\n";
        } else {  // now_level == MLFQ_THIRD_LEVEL  // third -> third
            readyThirdQ.pop_front();
            waitThirdQ.emplace_back(now_pid, IO_burst);
            childRemainTs[now_pid] = MLFQ_THIRD_LEVEL_TIME_SLICE;
            ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitThirdQ for " + std::to_string(IO_burst) + " >>>\n\n";
        }
    } else {
        if (now_level == MLFQ_FIRST_LEVEL) {
            readyFirstQ.pop_front();
            waitFirstQ.emplace_back(now_pid, IO_burst);
            ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitFirstQ for " + std::to_string(IO_burst) + " >>>\n\n";
        } else if (now_level == MLFQ_SECOND_LEVEL) {
            readySecondQ.pop_front();
            waitSecondQ.emplace_back(now_pid, IO_burst);
            ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitSecondQ for " + std::to_string(IO_burst) + " >>>\n\n";
        } else {  // now_level == MLFQ_THIRD_LEVEL
            readyThirdQ.pop_front();
            waitThirdQ.emplace_back(now_pid, IO_burst);
            ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> WaitThirdQ for " + std::to_string(IO_burst) + " >>>\n\n";
        }
    }

    if (afterResetTime >= MLFQ_RESET_TIME) {
        resetPriority();
        ret += "\n<<< Resetting priority >>>\n\n";
    }
    return ret;
}

std::string MLFQ::ReadyQtoInactiveQ() {
    std::string ret;
    if (now_level == MLFQ_FIRST_LEVEL) {  // first -> second
        readyFirstQ.pop_front();
        readySecondQ.push_back(now_pid);
        childRemainTs[now_pid] = MLFQ_SECOND_LEVEL_TIME_SLICE;
        ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> ReadySecondQ >>>\n\n";
    } else if (now_level == MLFQ_SECOND_LEVEL) {  // second -> third
        readySecondQ.pop_front();
        readyThirdQ.push_back(now_pid);
        childRemainTs[now_pid] = MLFQ_THIRD_LEVEL_TIME_SLICE;
        ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> ReadyThirdQ >>>\n\n";
    } else {  // now_level == MLFQ_THIRD_LEVEL  // third -> third
        readyThirdQ.pop_front();
        readyThirdQ.push_back(now_pid);
        childRemainTs[now_pid] = MLFQ_THIRD_LEVEL_TIME_SLICE;
        ret = "\n<<< Context switching) Child PID : " + std::to_string(now_pid) + " -> ReadyThirdQ >>>\n\n";
    }

    if (afterResetTime >= MLFQ_RESET_TIME) {
        resetPriority();
        ret += "\n<<< Resetting priority >>>\n\n";
    }
    return ret;
}

void MLFQ::resetPriority() {
    /* move all IO child to waitFirstQ */
    for (auto it : waitSecondQ)
        waitFirstQ.emplace_back(it.first, it.second);
    waitSecondQ.clear();

    for (auto it : waitThirdQ)
        waitFirstQ.emplace_back(it.first, it.second);
    waitThirdQ.clear();

    /* move all CPU child to readyFirstQ */
    while(!readySecondQ.empty()) {
        pid_t pid = readySecondQ.front();
        readyFirstQ.push_back(pid);
        readySecondQ.pop_front();
    }
    while(!readyThirdQ.empty()) {
        pid_t pid = readyThirdQ.front();
        readyFirstQ.push_back(pid);
        readyThirdQ.pop_front();
    }

    for (auto& it : childRemainTs)
        it.second = MLFQ_FIRST_LEVEL_TIME_SLICE;

    afterResetTime = 0;
}

std::string MLFQ::outputDump() {
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