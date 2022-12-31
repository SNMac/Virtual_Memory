/**
 * @file
 * @brief
 * @date 2022/11/16
 * @author SNMac
 */

#ifndef INC_2022_OS_PROJ2_MLQ_H
#define INC_2022_OS_PROJ2_MLQ_H

#include <deque>
#include <vector>
#include <string>
#include <unistd.h>

#define MLQ_FIRST_LEVEL_TIME_SLICE 50
#define MLQ_SECOND_LEVEL_TIME_SLICE 75
#define MLQ_THIRD_LEVEL_TIME_SLICE 100
#define MLQ_FIRST_LEVEL 1
#define MLQ_SECOND_LEVEL 2
#define MLQ_THIRD_LEVEL 3

class MLQ {
public:
    /* class variables */
    pid_t now_pid;  // current handling child's pid
    int now_level;  // current handling child's priority level
    std::deque<pid_t> readyFirstQ;  // first priority readyQ
    std::deque<pid_t> readySecondQ;  // second priority readyQ
    std::deque<pid_t> readyThirdQ;  // third priority readyQ
    std::vector<std::pair<pid_t, int>> waitFirstQ;  // <pid, IO_burst>, first priority waitQ
    std::vector<std::pair<pid_t, int>> waitSecondQ;  // <pid, IO_burst>, second priority waitQ
    std::vector<std::pair<pid_t, int>> waitThirdQ;  // <pid, IO_burst>, third priority waitQ

    /* class functions specified in here */
    bool isReadyQEmpty() {return readyFirstQ.empty() & readySecondQ.empty() & readyThirdQ.empty();}
    bool isWaitQEmpty() {return waitFirstQ.empty() & waitSecondQ.empty() & waitThirdQ.empty();}
    pid_t getNowPID() {return now_pid;}

    /* class functions specified in .cpp */
    void insertReadyQ(pid_t pid, int priority);
    void setNowPID();
    std::string IOJob(bool& IO_bounded);
    std::string ReadyQtoWaitQ(int IO_burst);
    std::string ReadyQtoInactiveQ();
    int setRemain_ts();
    std::string outputDump();
};

#endif //INC_2022_OS_PROJ2_MLQ_H
