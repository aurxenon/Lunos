#pragma once

#include <ArchSpecific/Types.h>
#include <Log/KLog.h>
#include <System/KMalloc.h>

#include "PIC.h"
#include "CPU.h"

#define IDT_NUM_ENTRIES 256

#define KERNEL_MODE_SELECTOR  8
#define KERNEL_MODE_TYPE_ATTR 142

#define _s_(a)   #a

#define Exception(i) \
    extern "C" void __asm_Exception_ISR ## i (); \
    __asm( \
        ".globl __asm_Exception_ISR" _s_(i) "\n" \
        "__asm_Exception_ISR" _s_(i) ":\n" \
        "   call ExceptionHandler" _s_(i) "\n" \
        "   iret\n" \
    ); \
    extern "C" void ExceptionHandler ## i () \
    { \
        klog() << " Caught Exception " << interruptDescriptions[i]; \
        while(true) { \
            asm("nop"); \
        } \
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

void AddISR(int index, void (*ISR)());

/*
* LoadIDT:
*   Loads the IDT array into the processor
* Arguments:
* Return:
*/
inline void LoadIDT()
{
    extern IDTPtr interruptTablePtr;
    __asm __volatile__("lidt %0"::"m"(interruptTablePtr));
}

inline void DisableInterrupts() {
    asm volatile("cli");
}

inline void EnableInterrupts() {
    asm volatile("sti");
}

void InitializeInterrupts();