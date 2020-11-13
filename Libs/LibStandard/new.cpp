#include "new.h"

#ifdef KERNEL_INCLUDES
void* operator new(std::size_t size)
{
    return kmalloce(size);
}
 
void* operator new[](std::size_t size)
{
    return kmalloce(size);
}

void operator delete(void* ptr)
{
    return;
}

void operator delete[](void* ptr)
{
    return;
}
#endif