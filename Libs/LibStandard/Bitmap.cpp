#include "Bitmap.h"

#ifdef KERNEL_INCLUDES
#define malloc kmalloce
#endif

#ifdef TESTING_INCLUDES
#include <iostream>
#include <iomanip>
#endif

namespace LibStandard {

Bitmap::Bitmap(u8 *preallocatedBuffer, u32 numBytes) {
    m_buffer = preallocatedBuffer;
    m_size = numBytes;
    m_needsToBeFreed = false;
}

Bitmap::Bitmap(u32 numBytes) {
    m_buffer = (u8*)malloc(numBytes);
    m_size = numBytes;
    m_needsToBeFreed = true;
}

#ifndef KERNEL_INCLUDES
Bitmap::~Bitmap() {
    if (m_needsToBeFreed) {
        free(m_buffer);
    }
}
#endif

bool Bitmap::getBit(u32 index) {
    if (index <= (m_size * 8)) {
        u8 bitToRead = (1 << (index % 8));
        return 0 != (m_buffer[index / 8] & bitToRead);
    }
    return false;
}

void Bitmap::enableBit(u32 index) {
    if (index <= (m_size * 8)) {
        u8 bitToRead = (1 << (index % 8));
        m_buffer[index / 8] |= bitToRead;
    }
}

void Bitmap::disableBit(u32 index) {
    if (index <= (m_size * 8)) {
        u8 bitToRead = (1 << (index % 8));
        m_buffer[index / 8] &= ~bitToRead;
    }
}

}