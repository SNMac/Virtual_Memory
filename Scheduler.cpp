/**
 * @file
 * @brief
 * @date 2022/11/02
 * @author SNMac
 */

#include <iostream>

#include "Scheduler.h"

Scheduler::~Scheduler() {
    if (sched == SCHEDULER_FIFO) {
        delete fifo;
    } else if (sched == SCHEDULER_RR) {
        delete rr;
    } else if (sched == SCHEDULER_MLQ) {
        delete mlq;
    } else if (sched == SCHEDULER_MLFQ) {
        delete mlfq;
    } else if (sched == SCHEDULER_CFS) {
        delete cfs;
    }
}

bool Scheduler::setScheduler(const std::string& schedName) {
    if (schedName == "FIFO") {
        sched = SCHEDULER_FIFO;
        fifo = new FIFO;
    } else if (schedName == "RR") {
        sched = SCHEDULER_RR;
        rr = new RR;
    } else if (schedName == "MLQ") {
        sched = SCHEDULER_MLQ;
        mlq = new MLQ;
    } else if (schedName == "MLFQ") {
        sched = SCHEDULER_MLFQ;
        mlfq = new MLFQ;
    } else if (schedName == "CFS") {
        sched = SCHEDULER_CFS;
        cfs = new CFS;
    } else {  // Undefined scheduler
        return false;
    }
    return true;
}

std::string Scheduler::getScheduler() {
    if (sched == SCHEDULER_FIFO) {
        return "FIFO";
    } else if (sched == SCHEDULER_RR) {
        return "RR";
    } else if (sched == SCHEDULER_MLQ) {
        return "MLQ";
    } else if (sched == SCHEDULER_MLFQ) {
        return "MLFQ";
    } else if (sched == SCHEDULER_CFS) {
        return "CFS";
    }
}

void Scheduler::insertReadyQ(pid_t pid, int priority) {
    pidCPU.insert(std::pair<pid_t, int>(pid, 0));
    if (sched == SCHEDULER_FIFO) {
        fifo->insertReadyQ(pid);
    } else if (sched == SCHEDULER_RR) {
        rr->insertReadyQ(pid);
    } else if (sched == SCHEDULER_MLQ) {
        mlq->insertReadyQ(pid, priority);
    } else if (sched == SCHEDULER_MLFQ) {
        mlfq->insertReadyQ(pid);
    } else if (sched == SCHEDULER_CFS) {
        cfs->insertReadyQ(pid ,priority);
    }
}

bool Scheduler::isReadyQEmpty() {
    if (sched == SCHEDULER_FIFO) {
        return fifo->isReadyQEmpty();
    } else if (sched == SCHEDULER_RR) {
        return rr->isReadyQEmpty();
    } else if (sched == SCHEDULER_MLQ) {
        return mlq->isReadyQEmpty();
    } else if (sched == SCHEDULER_MLFQ) {
        return mlfq->isReadyQEmpty();
    } else if (sched == SCHEDULER_CFS) {
        return cfs->isReadyQEmpty();
    }
}

bool Scheduler::isWaitQEmpty() {
    if (sched == SCHEDULER_FIFO) {
        return fifo->isWaitQEmpty();
    } else if (sched == SCHEDULER_RR) {
        return rr->isWaitQEmpty();
    } else if (sched == SCHEDULER_MLQ) {
        return mlq->isWaitQEmpty();
    } else if (sched == SCHEDULER_MLFQ) {
        return mlfq->isWaitQEmpty();
    } else if (sched == SCHEDULER_CFS) {
        return cfs->isWaitQEmpty();
    }
}

bool Scheduler::isInactiveQEmpty() {
    if (sched == SCHEDULER_FIFO) {  // doesn't have inactiveQ
        return true;
    } else if (sched == SCHEDULER_RR) {
        return rr->inactiveQ.empty();
    } else if (sched == SCHEDULER_MLQ) {  // doesn't have inactiveQ
        return true;
    } else if (sched == SCHEDULER_MLFQ) {  // doesn't have inactiveQ
        return true;
    } else if (sched == SCHEDULER_CFS) {
        return cfs->inactiveQ.empty();
    }
}

void Scheduler::setNowPID() {
    if (sched == SCHEDULER_FIFO) {
        fifo->setNowPID();
    } else if (sched == SCHEDULER_RR) {
        rr->setNowPID();
    } else if (sched == SCHEDULER_MLQ) {
        mlq->setNowPID();
    } else if (sched == SCHEDULER_MLFQ) {
        mlfq->setNowPID();
    } else if (sched == SCHEDULER_CFS) {
        cfs->setNowPID();
    }
}

pid_t Scheduler::getNowPID() {
    if (sched == SCHEDULER_FIFO) {
        return fifo->getNowPID();
    } else if (sched == SCHEDULER_RR) {
        return rr->getNowPID();
    } else if (sched == SCHEDULER_MLQ) {
        return mlq->getNowPID();
    } else if (sched == SCHEDULER_MLFQ) {
        return mlfq->getNowPID();
    } else if (sched == SCHEDULER_CFS) {
        return cfs->getNowPID();
    }
}

void Scheduler::IOJob() {
    std::cout << "< IO job on going >\n";
    if (sched == SCHEDULER_FIFO) {
        std::cout << fifo->IOJob(IO_bounded);
    } else if (sched == SCHEDULER_RR) {
        std::cout << rr->IOJob(IO_bounded);
    } else if (sched == SCHEDULER_MLQ) {
        pid_t old_pid = getNowPID();
        std::cout << mlq->IOJob(IO_bounded);
        if (old_pid != getNowPID())
            setRemain_ts();
    } else if (sched == SCHEDULER_MLFQ) {
        std::cout << mlfq->IOJob(IO_bounded);
    } else if (sched == SCHEDULER_CFS) {
        std::cout << cfs->IOJob(IO_bounded);
    }
}

std::string Scheduler::ReadyQtoWaitQ(int IO_burst) {
    std::string dump;
    if (sched == SCHEDULER_FIFO) {
        dump = fifo->ReadyQtoWaitQ(IO_burst);
        std::cout << dump;
    } else if (sched == SCHEDULER_RR) {
        dump = rr->ReadyQtoWaitQ(IO_burst);
        std::cout << dump;
    } else if (sched == SCHEDULER_MLQ) {
        dump = mlq->ReadyQtoWaitQ(IO_burst);
        std::cout << dump;
    } else if (sched == SCHEDULER_MLFQ) {
        dump = mlfq->ReadyQtoWaitQ(remain_ts, IO_burst);
        std::cout << dump;
    } else if (sched == SCHEDULER_CFS) {
        dump = cfs->ReadyQtoWaitQ(IO_burst);
        std::cout << dump;
    }
    return dump + '\n';
}

std::string Scheduler::ReadyQtoInactiveQ() {
    std::string dump;
    if (sched == SCHEDULER_RR) {
        dump = rr->ReadyQtoInactiveQ();
        std::cout << dump;
    } else if (sched == SCHEDULER_MLQ) {
        dump = mlq->ReadyQtoInactiveQ();
        std::cout << dump;
    } else if (sched == SCHEDULER_MLFQ) {  // decreasing current child priority level
        dump = mlfq->ReadyQtoInactiveQ();
        std::cout << dump;
    } else if (sched == SCHEDULER_CFS) {
        dump = cfs->ReadyQtoInactiveQ();
        std::cout << dump;
    }
    return dump + '\n';
}

std::string Scheduler::swapQ() {
    std::string dump;
    if (sched == SCHEDULER_RR) {
        dump = rr->swapQ();
        std::cout << dump;
    } else if (sched == SCHEDULER_CFS) {
        dump = cfs->swapQ();
        std::cout << dump;
    }
    return dump + '\n';
}

void Scheduler::setRemain_ts() {
    if (sched == SCHEDULER_FIFO) {
        remain_ts = 10000;
    } else if (sched == SCHEDULER_RR) {
        remain_ts = rr->setRemain_ts();
    } else if (sched == SCHEDULER_MLQ) {
        remain_ts = mlq->setRemain_ts();
    } else if (sched == SCHEDULER_MLFQ) {
        remain_ts = mlfq->setRemain_ts();
    } else if (sched == SCHEDULER_CFS) {
        remain_ts = cfs->setRemain_ts();
    }
    std::cout << "TimeSlice : " << remain_ts << '\n';
}

void Scheduler::decRemain_ts() {
    remain_ts--;
    if (sched == SCHEDULER_MLFQ)  // decrease time slice
        mlfq->decRemain_ts();
}

void Scheduler::addCPUtime(pid_t pid) {
    pidCPU[pid]++;
    if (sched == SCHEDULER_CFS)
        std::cout << cfs->updateVruntime(pidCPU[pid]);
}

void Scheduler::incTick_count() {
    tick_count++;
    if (sched == SCHEDULER_MLFQ)
        mlfq->afterResetTime++;
}

std::string Scheduler::outputDump() {
    if (sched == SCHEDULER_FIFO) {
        return fifo->outputDump() + '\n';
    } else if (sched == SCHEDULER_RR) {
        return rr->outputDump() + '\n';
    } else if (sched == SCHEDULER_MLQ) {
        return mlq->outputDump() + '\n';
    } else if (sched == SCHEDULER_MLFQ) {
        return mlfq->outputDump() + '\n';
    } else if (sched == SCHEDULER_CFS) {
        return cfs->outputDump() + '\n';
    }
}