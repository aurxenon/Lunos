#include "CString.h"

#ifndef KERNEL_INCLUDES
namespace LibStandard {
#elif defined(KERNEL_INCLUDES)
extern "C" {
#endif
    size_t strlen(const char *str) {
        size_t i;
        for (i = 0; str[i] != '\0'; i++) {}
        return i;
    }

    char *strcpy(const char *dest, const char *src) {
        size_t srclen = strlen(src);
        return strncpy(dest, src, srclen);
    }

    char *strncpy(const char *dest, const char *src, size_t len) {
        return (char*)memcpy((void*)dest, src, len);
    }

    int strcmp(const char* str1, const char* str2) {
        return strncmp(str1, str2, strlen(str1));
    }

    int strncmp(const char* str1, const char* str2, size_t len) {
        if((u8*)str1 == (u8*)str2) {
            return 0;
        }

        for (size_t i = 0; i < len; i++) {
            if (str1[i] != str2[i]) {
                return str1[i] - str2[i];
            }
        }

        return 0;
    }

    void *memcpy(void *dest, const void *src, size_t len) {
        char *cpysrc = (char*)src;
        char *cpydest = (char*)dest;

        for (size_t i = 0; i < len; i++) {
            cpydest[i] = cpysrc[i];
        }
        return dest;
    }

    void *memset(void *dest, int c, size_t len) {
        u8* fillDest = (u8*)dest;
        u8 fillC = (u8)c;
        for (size_t i = 0; i < len; i++) {
            fillDest[i] = fillC;
        }
        return fillDest;
    }

}