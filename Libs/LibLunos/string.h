#ifdef KERNEL_INCLUDES
#include <ArchSpecific/Types.h>
#endif

extern "C" {
    size_t strlen(const char *str);
    char *strcpy(const char *dest, const char *src);
    char *strncpy(const char *dest, const char *src, size_t len);
    int strcmp(const char *str1, const char *str2);
    void *memcpy(void *dest, const void *src, size_t len);
    void *memset(void *dest, int c, size_t len);
}