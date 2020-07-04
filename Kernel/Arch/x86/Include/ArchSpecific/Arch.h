#pragma once

#include "Types.h"

#define TSS_SS0        0x10 //refers to kernel data segment in GDT (sizeof(GDTEntry) * data segment index)
#define TSS_IOPB       0xFFFF
#define TSS_GDT_OFFSET 0x28
#define TSS_GDT_ACCESS 0x89

#define FLAGS_KERNEL_IOPL 0b1110011111111111

//need to move this to a more permanent place at some point
#define offsetof(st, m) \
    __builtin_offsetof(st, m)

struct TrapFrame {
    u32 gs;
    u32 fs;
    u32 es;
    u32 ds;
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 esp;
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;
    u32 eip;
    u32 cs;
    u32 eflags;
} __attribute__ ((packed));

struct TSS {
    u32 link;
    u32 esp0;
    u16 ss0;
    u16 __ss0h;
    u32 esp1;
    u16 ss1;
    u16 __ss1h;
    u32 esp2;
    u16 ss2;
    u16 __ss2h;
    u32 cr3;
    u32 eip;
    u32 eflags;
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;
    u16 es;
    u16 __esh;
    u16 cs;
    u16 __csh;
    u16 ss;
    u16 __ssh;
    u16 ds;
    u16 __dsh;
    u16 fs;
    u16 __fsh;
    u16 gs;
    u16 __gsh;
    u16 ldtr;
    u16 __ldtrh;
    u16 trace;
    u16 io_map_addr;
} __attribute__ ((packed));

inline void LoadTSS(u16 descriptor)
{
    __asm __volatile__("ltr %0"::"r"(descriptor));
}

inline void set_iopl() {
    //stub
    //flagsRegister &= FLAGS_KERNEL_IOPL;
}