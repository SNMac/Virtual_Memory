/**
 * @file
 * @brief
 * @date 2022/11/03
 * @author SNMac
 */

#ifndef INC_2022_OS_PROJ2_SCHEDULER_H
#define INC_2022_OS_PROJ2_SCHEDULER_H

#include <string>
#include <unordered_map>
#include <unistd.h>

#include "FIFO.h"
#include "RR.h"
#include "MLQ.h"
#include "MLFQ.h"
#include "CFS.h"

#define SCHEDULER_FIFO 1
#define SCHEDULER_RR 2
#define SCHEDULER_MLQ 3
#define SCHEDULER_MLFQ 4
#define SCHEDULER_CFS 5

class Scheduler {
    /* class variables */
    int sched;  // current scheduler
    int tick_count;  // total time tick
    int remain_ts;  // remain time slice
    FIFO* fifo;
    RR* rr;
    MLQ* mlq;
    MLFQ* mlfq;
    CFS* cfs;
public:
    std::unordered_map<pid_t, int> pidCPU;  // <pid, CPU time>
    bool IO_bounded = false;  // indicate readyQ is empty or not

    /* class functions specified in here */
    int getTickCount() {return tick_count;}
    int getRemain_ts() {return remain_ts;}

    /* class functions specified in .cpp */
    ~Scheduler();  // destructor
    bool setScheduler(const std::string& schedName);
    std::string getScheduler();
    void insertReadyQ(pid_t pid, int priority);  // initial push children to readyQ
    bool isReadyQEmpty();
    bool isWaitQEmpty();
    bool isInactiveQEmpty();
    void setNowPID();  // set current handling child
    pid_t getNowPID();  // get current handling child
    void IOJob();  // decrease all IO burst in waitQ, send to readyQ which used up its IO burst
    std::string ReadyQtoWaitQ(int IO_burst);  // current handling child used up its CPU burst
    std::string ReadyQtoInactiveQ();  // current handling child used up assigned time slice
    std::string swapQ();  // swap inactiveQ and readyQ
    void setRemain_ts();  // get time slice of current handling child
    void decRemain_ts();
    void addCPUtime(pid_t pid);  // calculate child's total CPU time
    void incTick_count();  // calculate total time tick
    std::string outputDump();
};

#endif //INC_2022_OS_PROJ2_SCHEDULER_H
