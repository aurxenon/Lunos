#pragma once

#include <ArchSpecific/Types.h>

inline void iowriteb(u16 port, u8 value)
{
    asm volatile("outb %0, %1;" :: "a"(value), "Nd"(port));
}

inline u8 ioreadb(u16 port)
{
    u8 value;
    asm volatile("inb %1, %0;" : "=a"(value) : "Nd"(port));
    return value;
}

inline void iowritew(u16 port, u16 value) {
    asm volatile("outw %0,%w1": :"a" (value), "Nd" (port));
}

inline u16 ioreadw(u16 port)
{
    u16 value;
    asm volatile("inw %1, %0;" : "=a"(value) : "Nd"(port));
    return value;
}

inline void iowritedw(u16 port, u32 value) {
    asm volatile("outl %0,%w1": :"a" (value), "Nd" (port));
}

inline u32 ioreaddw(u16 port)
{
    u32 value;
    asm volatile("inl %1, %0;" : "=a"(value) : "Nd"(port));
    return value;
}