#pragma once

#include <ArchSpecific/Types.h>
#include <Log/KLog.h>
#include <System/KMalloc.h>

#define PAGE_DIR_ENTRIES 1024
#define PAGE_TBL_ENTRIES 1024
#define UNINITIALIZED_DIR_ENTRY 0b00000000000000000000000000000010 //the page directory entry is not present in the cpu
#define UNINITIALIZED_TBL_ENTRY 0b00000000000000000000000000000011 //page table entry is r/w, and is present in memory
#define PAGING_ENABLE 0b10000000000000000000000000000001 //enables PG and PE

#define GDT_MAX_ENTRIES 256
#define GDT_NUM_ENTRIES 5
#define GDT_GRANULARITY 0xCF
#define GDT_RING0_CODE  0x9A
#define GDT_RING0_DATA  0x92
#define GDT_RING3_CODE  0xFA
#define GDT_RING3_DATA  0xF2

struct GDTEntry {
    u16 limit_low;           // The lower 16 bits of the limit.
    u16 base_low;            // The lower 16 bits of the base.
    u8 base_middle;         // The next 8 bits of the base.
    u8 access;              // Access flags, determine what ring this segment can be used in.
    u8 granularity;
    u8 base_high;           // The last 8 bits of the base.
} __attribute__((packed));

struct GDTPtr
{
   u16 size;               // The upper 16 bits of all selector limits.
   void* address;                // The address of the first GDTEntry struct.
} __attribute__((packed));

/////////////////////////////

/*
    Turns on paging.
*/
void initializePaging();

/*
    Sets up Global Descriptor Table
*/
void InitializeSegmentation();

inline void write_cr3(u32 value) {
    __asm __volatile__(
        "movl %0, %%cr3" ::"r"(value):"memory" 
    );
}

inline void write_cr0(u32 value) {
    __asm __volatile__(
        "movl %0, %%cr0" ::"r"(value):"memory" 
    );
}

inline u32 read_cr0() {
    u32 value;
    __asm __volatile__(
        "movl %%cr0, %0":"=r"(value)::"memory" 
    );
    return value;
}