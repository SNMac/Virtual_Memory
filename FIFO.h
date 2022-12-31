/**
 * @file
 * @brief
 * @date 2022/11/05
 * @author SNMac
 */

#ifndef INC_2022_OS_PROJ2_FIFO_H
#define INC_2022_OS_PROJ2_FIFO_H

#include <deque>
#include <vector>
#include <string>
#include <unistd.h>

class FIFO {
public:
    /* class variables */
    pid_t now_pid;  // current handling child's pid
    std::deque<pid_t> readyQ;
    std::vector<std::pair<pid_t, int>> waitQ;  // <pid, IO_burst>

    /* class functions specified in here */
    void insertReadyQ(pid_t pid) {readyQ.push_back(pid);}
    bool isReadyQEmpty() {return readyQ.empty();}
    bool isWaitQEmpty() {return waitQ.empty();}
    void setNowPID() {now_pid = readyQ.front();}
    pid_t getNowPID() {return now_pid;}

    /* class functions specified in .cpp */
    std::string IOJob(bool& IO_bounded);
    std::string ReadyQtoWaitQ(int IO_burst);
    std::string outputDump();
};

#endif //INC_2022_OS_PROJ2_FIFO_H
