#pragma once

#include <ArchSpecific/Types.h>

#define PAGE_DIR_ENTRIES 1024
#define PAGE_TBL_ENTRIES 1024
#define UNINITIALIZED_DIR_ENTRY 0b00000000000000000000000000000010 //the page directory entry is not present in the cpu
#define UNINITIALIZED_TBL_ENTRY 0b00000000000000000000000000000011 //page table entry is r/w, and is present in memory
#define PAGING_ENABLE 0b10000000000000000000000000000001 //enables PG and PE


//
//turns on paging
//
void initializePaging();

void write_cr3(u32 value);
void write_cr0(u32 value);
u32 read_cr0();