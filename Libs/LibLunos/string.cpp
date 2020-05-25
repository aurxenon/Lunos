#include "string.h"

extern "C" {
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

    //FIXME this doesn't conform to the C standard
    int strcmp(const char *str1, const char *str2) {
        int i;
        for (i = 0; (str1[i] == str2[i] && str1[i] != '\0'); i++);
        if (i == (int)strlen(str1) && i == (int)strlen(str2)) {
            return 0;
        }
        return i;
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