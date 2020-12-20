#pragma once

#ifdef KERNEL_INCLUDES
#include <ArchSpecific/Types.h>
#elif defined(TESTING_INCLUDES)
#include <cstddef>
#include <stdlib.h>

typedef uint8_t u8;
#endif

#ifndef KERNEL_INCLUDES
namespace LibStandard {
#elif defined(KERNEL_INCLUDES)
extern "C" {
#endif
    size_t strlen(const char *str);
    char *strcpy(const char *dest, const char *src);
    char *strncpy(const char *dest, const char *src, size_t len);
    int strcmp(const char *str1, const char *str2);
    int strncmp(const char *str1, const char *str2, size_t len);
    void *memcpy(void *dest, const void *src, size_t len);
    void *memset(void *dest, int c, size_t len);
}