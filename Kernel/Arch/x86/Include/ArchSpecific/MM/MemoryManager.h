#pragma once

#include <ArchSpecific/Types.h>

#define PAGE_DIR_ENTRIES 1024
#define PAGE_TBL_ENTRIES 1024
#define UNINITIALIZED_DIR_ENTRY 0b00000000000000000000000000000010 //the page directory entry is not present in the cpu
#define UNINITIALIZED_TBL_ENTRY 0b00000000000000000000000000000011 //page table entry is r/w, and is present in memory
#define PAGING_ENABLE 0b10000000000000000000000000000001 //enables PG and PE

struct gdt_entry_t
{
   u16 limit_low;           // The lower 16 bits of the limit.
   u16 base_low;            // The lower 16 bits of the base.
   u8  base_middle;         // The next 8 bits of the base.
   u8  access;              // Access flags, determine what ring this segment can be used in.
   u8  granularity;
   u8  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

struct gdt_ptr_t
{
   u16 limit;               // The upper 16 bits of all selector limits.
   u32 base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));

/*
    Turns on paging.
*/
void initializePaging();

/*
    Sets up Global Descriptor Table
*/
void InitializeSegmentation();
void GDTSetCallGate(i32 num, u32 base, u32 limit, u8 access, u8 granularity);
void LoadGDT(u32 gdt_pointer);

void write_cr3(u32 value);
void write_cr0(u32 value);
u32 read_cr0();

