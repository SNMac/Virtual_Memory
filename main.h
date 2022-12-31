/**
 * @file
 * @brief
 * @date 2022/11/05
 * @author SNMac
 */

#ifndef INC_2022_OS_PROJ2_MAIN_H
#define INC_2022_OS_PROJ2_MAIN_H

#include <vector>
#include <unistd.h>

/* User child priority = 0 ~ 19 */
#define MAIN_PRIORITY_MIN 0
#define MAIN_PRIORITY_MAX 19

#define RAM_SIZE 0x4000  // 64KB
#define PAGE_SIZE 1024  // 1KB, 10bits for page offset
#define PAGE_TABLE_ENTRY_NUM ((RAM_SIZE << 2) / PAGE_SIZE)
#define PAGE_FRAME_NUM_BITSHIFT 10
#define PAGE_OFFSET_BITMASK 0x3ff
#define PAGE_OFFSET_MAX 0x3fc

/* One-level paging macro */
#define PAGE_TABLE_INDEX_BITSHIFT 10

/* Two-level paging macro */
#define PAGE_DIRECTORY_ENTRY_NUM 16  // 4bits for page directory
#define PAGE_TABLE_2ND_ENTRY_NUM 4  // 2bits for page table
#define PAGE_DIRECTORY_INDEX_BITSHIFT 12
#define PAGE_TABLE_2ND_INDEX_BITSHIFT 10
#define PAGE_TABLE_2ND_INDEX_BITMASK 0x3  // lower 2bits

#define PAGE_ONE_LEVEL 1
#define PAGE_TWO_LEVEL 2
#define PAGE_DIRECTORY_ENTRY_INVALID 0
#define PAGE_DIRECTORY_ENTRY_VALID 1
#define PAGE_TABLE_ENTRY_INVALID 0
#define PAGE_TABLE_ENTRY_VALID 1
#define PAGE_TABLE_ENTRY_NOTPRESENT 0
#define PAGE_TABLE_ENTRY_PRESENT 1
#define PAGE_FRAME_EVICTION (PAGE_TABLE_ENTRY_NUM >> 4)
#define FREE_FRAME_VALID 0

#define MAIN_OUTPUT_TICK 3000

struct Paging {
    int rwb_bias;  // Read/Write bias
    std::vector<int> pageFrames_RAM;  // for output
    std::vector<int> pageFrames_Disk;  // for output
    int swapInCount;  // for output
    int swapOutCount;  // for output
    int pageTbl[PAGE_TABLE_ENTRY_NUM][3];
    // [][0] = page table entry valid bit, [][1] = page table entry present bit, [][2] = page frame number
    int pageDir[PAGE_DIRECTORY_ENTRY_NUM][2];
    // [][0] = page directory entry valid bit, [][1] = page table index
    int pageTbl2nd[PAGE_DIRECTORY_ENTRY_NUM][PAGE_TABLE_2ND_ENTRY_NUM][3];
    // [][][0] = page table entry valid bit, [][][1] = page table entry present bit, [][][2] = page frame number
    bool pageTbl2ndValid[PAGE_DIRECTORY_ENTRY_NUM];  // page table valid array
};

void createChildren(int num);
void receivedCPUmsg(pid_t msgpid, int msgCPU, const int msgVA[], const int msgdata[], const bool msgisWrite[]);
void receivedIOmsg(int msgIO);
int MMU(pid_t pid, int v_addr);  // RAM Management Unit
void pageFrameSwapOut();  // move page frame RAM -> Disk
void pageFrameSwapIn(pid_t pid, int pageTblIndex, int pageFrameNum);  // move page frame Disk -> RAM (One-level paging)
void pageFrameSwapIn(pid_t pid, int pageTblNum, int pageTblIndex, int pageFrameNum);  // move page frame Disk -> RAM (Two-level paging)
void signal_handler(int signo);

#endif //INC_2022_OS_PROJ2_MAIN_H
