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