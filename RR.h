/**
 * @file
 * @brief
 * @date 2022/11/14
 * @author SNMac
 */

#ifndef INC_2022_OS_PROJ2_RR_H
#define INC_2022_OS_PROJ2_RR_H

#include <deque>
#include <vector>
#include <string>
#include <unistd.h>

#define RR_TIME_SLICE 50

class RR {
public:
    /* class variables */
    pid_t now_pid;
    std::deque<pid_t> readyQ;
    std::deque<pid_t> inactiveQ;
    std::vector<std::pair<pid_t, int>> waitQ;

    /* class functions specified in here */
    void insertReadyQ(pid_t pid) {readyQ.push_back(pid);}
    bool isReadyQEmpty() {return readyQ.empty();}
    bool isWaitQEmpty() {return waitQ.empty();}
    void setNowPID() {now_pid = readyQ.front();}
    pid_t getNowPID() {return now_pid;}
    std::string swapQ() {
        readyQ.swap(inactiveQ);
        return "\n<<< Queue swapping) InactiveQ <-> ReadyQ >>>\n\n";
    }
    int setRemain_ts() {return RR_TIME_SLICE;}

    /* class functions specified in .cpp */
    std::string IOJob(bool& IO_bounded);
    std::string ReadyQtoWaitQ(int IO_burst);
    std::string ReadyQtoInactiveQ();
    std::string outputDump();
};

#endif //INC_2022_OS_PROJ2_RR_H
