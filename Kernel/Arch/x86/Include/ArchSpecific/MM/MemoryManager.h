#pragma once

#include <ArchSpecific/Types.h>
#include <Log/KLog.h>
#include <System/KMalloc.h>
#include <ArchSpecific/multiboot.h>
#include <LibStandard/Bitmap.h>
#include <LibStandard/CString.h>

#include "PageTable.h"
#include "PageDirectory.h"
#include "CPU.h"

#define PAGING_ENABLE 0b10000000000000000000000000000001 //enables PG and PE

#define GDT_MAX_ENTRIES    256
#define GDT_NUM_ENTRIES    5
#define GDT_STANDARD_FLAGS 0xCF
#define GDT_RING0_CODE     0x9A
#define GDT_RING0_DATA     0x92
#define GDT_RING3_CODE     0xFA
#define GDT_RING3_DATA     0xF2

#define GDT_RING0_DATA_SELECTOR  (2 << 3) | 0 //2 represents kernel data in gdt, 0 represents ring 0
#define GDT_RING0_CODE_SELECTOR  (1 << 3) | 0 //1 represents kernel code in gdt, 0 represents ring 0

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
void InitializeMemoryManager(void* kernelPageArea, multiboot_info_t* mbd);
void CreateKernelPages(void* kernelPageArea);

void RegisterGDTEntry(int index, u32 limit, u32 base, u8 access, u8 flags);
void LoadGDT();

/*
    Sets up Global Descriptor Table
*/
void InitializeSegmentation();