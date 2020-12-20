#pragma once

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

inline u32 read_cr2() {
    u32 value;
    __asm __volatile__(
        "movl %%cr2, %0":"=r"(value)::"memory" 
    );
    return value;
}