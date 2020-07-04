#pragma once

#include <ArchSpecific/Types.h>
#include <System/KMalloc.h>

namespace std {
    typedef long unsigned int size_t;
}
 
void* operator new(std::size_t size);
void* operator new[](std::size_t size);

void operator delete(void* ptr);
void operator delete[](void* ptr);