/**
 * @file
 * @brief
 * @date 2022/11/03
 * @author SNMac
 */

#include <iostream>
#include <random>
#include <csignal>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "Child.h"

Child* child;

Child::Child(int bias) {
    child = this;
    my_pid = getpid();
#ifdef SWAP_TEST
    CPU_burst = CHILD_BURST_MAX;
    IO_burst = CHILD_BURST_MIN;
#else
    CPU_burst = uniformRNG(CHILD_BURST_MIN, CHILD_BURST_MAX);
    IO_burst = uniformRNG(CHILD_BURST_MIN, CHILD_BURST_MAX);
#endif
    key = MSG_QUEUE_KEY;
    msgq = msgget(key, IPC_CREAT | 0666);
    msg.pid = my_pid;
    new_sa.sa_handler = Child::signal_handler;
    nowHeap = CHILD_VADDR_HEAP_START;
    nowStack = CHILD_VADDR_STACK_START;
    rwb_bias = bias;
}

void Child::DoSomeJob() {
    if (sigaction(SIGUSR1, &new_sa, &old_sa) == -1) {
        perror("sigaction(SIGUSR1)");
        exit(EXIT_FAILURE);
    }

    while(true);
}

void Child::sendMsg(bool isIOJob) {
    msg.mtype = 1;
    msg.CPU_burst = CPU_burst;
    msg.IO_burst = IO_burst;
    msg.isIOJob = isIOJob;
    if (writtenAddr.empty()) {  // initial memory access
        /* memory write */
        for (int i = 0; i < CHILD_MEMORY_ACCESS_NUM; i++) {
#ifdef SWAP_TEST
            /* write data at heap */
            writtenAddr.insert(nowHeap);
            msg.v_addr[i] = nowHeap;
            msg.data[i] = uniformRNG(0, CHILD_DATA_MAX);
            msg.isWrite[i] = true;
            nowHeap += 4;
#else
            if (i <= rwb_bias / 2) {
                /* write data at heap */
                writtenAddr.insert(nowHeap);
                msg.v_addr[i] = nowHeap;
                msg.data[i] = uniformRNG(0, CHILD_DATA_MAX);
                msg.isWrite[i] = true;
                nowHeap += 4;
            } else {
                /* write data at stack */
                writtenAddr.insert(nowStack);
                msg.v_addr[i] = nowStack;
                msg.data[i] = uniformRNG(0, CHILD_DATA_MAX);
                msg.isWrite[i] = true;
                nowStack -= 4;
            }
#endif
        }
    } else {
        /* memory write */
        for (int i = 0; i < rwb_bias; i++) {
#ifdef SWAP_TEST
            if (i < rwb_bias) {
#else
            if (i < rwb_bias / 2) {
#endif
                /* write data at heap */
                int v_addr;
#ifdef SWAP_TEST
                v_addr = nowHeap;
                nowHeap += 4;
                writtenAddr.insert(v_addr);
#else
                if (uniformRNG(1, CHILD_MEMORY_ACCESS_NUM) <= rwb_bias) {
                    if (nowHeap < CHILD_VADDR_HEAP_END)  // check remain capacity of heap
                        nowHeap += 4;
                    v_addr = nowHeap;
                    writtenAddr.insert(v_addr);
                } else {
                    v_addr = uniformRNG(CHILD_VADDR_HEAP_START, nowHeap) & 0xfffc;
                }
#endif
                msg.v_addr[i] = v_addr;
                msg.data[i] = uniformRNG(0, CHILD_DATA_MAX);
                msg.isWrite[i] = true;
            } else {
                /* write data at stack */
                int v_addr;
                if (uniformRNG(1, CHILD_MEMORY_ACCESS_NUM) <= rwb_bias) {
                    if (nowStack > CHILD_VADDR_STACK_END)  // check remain capacity of stack
                        nowStack -= 4;
                    v_addr = nowStack;
                    writtenAddr.insert(v_addr);
                } else {
                    v_addr = uniformRNG(nowStack, CHILD_VADDR_STACK_START) & 0xfffc;
                }

                msg.v_addr[i] = v_addr;
                msg.data[i] = uniformRNG(0, CHILD_DATA_MAX);
                msg.isWrite[i] = true;
            }
        }
        /* memory read */
        for (int i = rwb_bias; i < CHILD_MEMORY_ACCESS_NUM; i++) {
            auto it = writtenAddr.begin();
            std::advance(it, uniformRNG(0, writtenAddr.size() - 1));  // find already written virtual address
            msg.v_addr[i] = *it;
            msg.data[i] = 0;
            msg.isWrite[i] = false;
        }
    }
    msgsnd(msgq, &msg, sizeof(struct msgblock) - sizeof(long), 0);
}

void Child::signal_handler(int signo) {
    std::cout << "SIGUSR1(" << signo << ") ~> Child(" << child->my_pid << ")\n";
    child->CPU_burst--;
    std::cout << "Child PID : " << child->my_pid << ") remain CPU burst : " << child->CPU_burst << '\n';
    if (child->CPU_burst == 0) {  // switch to IO burst
        child->sendMsg(true);
#ifdef SWAP_TEST
        child->CPU_burst = CHILD_BURST_MAX;  // reset CPU burst time
        child->IO_burst = CHILD_BURST_MIN;  // reset IO burst time
#else
        child->CPU_burst = uniformRNG(CHILD_BURST_MIN, CHILD_BURST_MAX);  // reset CPU burst time
        child->IO_burst = uniformRNG(CHILD_BURST_MIN, CHILD_BURST_MAX);  // reset IO burst time
#endif
    } else {
        child->sendMsg(false);
    }
}

int uniformRNG(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}