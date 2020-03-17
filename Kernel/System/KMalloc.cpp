#include "KMalloc.h"

u8 kmalloce_space[KMALLOCE_SIZE];
void *kmalloce_ptr = &kmalloce_space[0];

void *kmalloce(size_t size) {
    uintptr_t space_remaining = ((uintptr_t)((kmalloce_space + KMALLOCE_SIZE) - (uintptr_t)kmalloce_ptr));

    if (size > KMALLOCE_SIZE || size > space_remaining) {
        return NULL;
    } else {
        void *ptr = kmalloce_ptr + size;
        kmalloce_ptr = ptr;

        return ptr;
    }
}

//stub
void *kmalloc(size_t size) {
    return NULL;
}