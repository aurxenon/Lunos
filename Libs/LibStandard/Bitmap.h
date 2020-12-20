#pragma once

#ifdef KERNEL_INCLUDES
#include <ArchSpecific/Types.h>
#include <System/KMalloc.h>
#elif defined(TESTING_INCLUDES)
#include <cstddef>
#include <stdlib.h>

typedef uint8_t u8;
typedef uint32_t u32;
#endif

namespace LibStandard {

class Bitmap {
    public:
        Bitmap(u8 *preallocatedBuffer, u32 numBytes);
        Bitmap(u32 numBytes);
        #ifndef KERNEL_INCLUDES
        ~Bitmap();
        #endif

        bool getBit(u32 index);
        void enableBit(u32 index);
        void disableBit(u32 index);
    private:
        u8 *m_buffer;
        u32 m_size;
        bool m_needsToBeFreed;
};

}