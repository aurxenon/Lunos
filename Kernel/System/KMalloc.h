#pragma once

#include <ArchSpecific/Types.h>
#include <ArchSpecific/Limits.h>

#define KMALLOCE_SIZE 4096 * 4 //4096 bytes of space kmalloce can allocate from

void kmalloc_init();

//
//stupid simple watermark allocator
//
void *kmalloce(size_t size); //eternally maps a memory space for the calling code

void *kmalloc(size_t size);