#pragma once

#include <ArchSpecific/Types.h>
#include <Log/KLog.h>
#include <System/KMalloc.h>

#define IRQ_BASE 40

#define IDT_NUM_ENTRIES 256

#define KERNEL_MODE_SELECTOR  8
#define KERNEL_MODE_TYPE_ATTR 142

#define Exception(i) \
    void ExceptionHandler ## i () \
    { \
        klog() << " Caught Exception " << interruptDescriptions[i]; \
    }

struct IDTEntry {
    u16 offset_1; // offset bits 0..15
    u16 selector; // a code segment selector in GDT
    u8 zero;      // unused, always 0
    u8 type_attr; // type and attributes
    u16 offset_2; // offset bits 16..31
} __attribute__ ((packed));

struct IDTPtr {
    u16 size;
    void* address;
} __attribute__ ((packed));


inline void DisableInterrupts() {
    asm volatile("cli");
}

inline void EnableInterrupts() {
    asm volatile("sti");
}

void InitializeInterrupts();