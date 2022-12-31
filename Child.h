/**
 * @file
 * @brief
 * @date 2022/11/03
 * @author SNMac
 */

#ifndef INC_2022_OS_PROJ2_CHILD_H
#define INC_2022_OS_PROJ2_CHILD_H

//#define SWAP_TEST

#include <set>
#include <unistd.h>

#ifdef SWAP_TEST
    #define CHILD_PROCESS_NUM 3
#else
    #define CHILD_PROCESS_NUM 10
#endif

#define CHILD_BURST_MIN 10
#define CHILD_BURST_MAX 200

#define CHILD_MEMORY_ACCESS_NUM 20  // # of memory access per tick
#define CHILD_READ 5
#define CHILD_BOTH 10
#define CHILD_WRITE 15

#define CHILD_VADDR_HEAP_START 0x0000
#define CHILD_VADDR_HEAP_END 0x7ff0
#define CHILD_VADDR_STACK_START 0xfff0
#define CHILD_VADDR_STACK_END 0x8000
#define CHILD_DATA_MAX 0xffffffff

#define MSG_QUEUE_KEY 0x12345

struct msgblock {  // message structure
    long mtype;
    int pid;
    int CPU_burst;
    int IO_burst;
    bool isIOJob;
    int v_addr[CHILD_MEMORY_ACCESS_NUM];
    int data[CHILD_MEMORY_ACCESS_NUM];
    bool isWrite[CHILD_MEMORY_ACCESS_NUM];
};

class Child {
    /* class variables */
    pid_t my_pid;
    int CPU_burst;
    int IO_burst;
    int key;
    int msgq;
    struct msgblock msg{};
    struct sigaction old_sa{};
    struct sigaction new_sa{};
    std::set<int> writtenAddr;
    int nowHeap;
    int nowStack;
    int rwb_bias;  // memory access bias (Read or Write or Both)

public:
    /* class functions specified in .cpp */
    Child(int bias);
    void DoSomeJob();
    void sendMsg(bool isIOJob);
    static void signal_handler(int signo);
};

int uniformRNG(int min, int max);  // random number generator

#endif //INC_2022_OS_PROJ2_CHILD_H
