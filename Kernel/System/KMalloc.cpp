#include "KMalloc.h"

static u8 kmalloce_space[KMALLOCE_SIZE];
static void *kmalloce_ptr = &kmalloce_space[0];

void *kmalloce(size_t size) {
    uintptr_t space_remaining = ((uintptr_t)((&kmalloce_space[0] + KMALLOCE_SIZE) - (uintptr_t)kmalloce_ptr));

    if (size > KMALLOCE_SIZE || size > space_remaining) {
        return NULL;
    } else {
        void *ptr = (void*)((char*)kmalloce_ptr + size); //ugly hack so that i can add size to void pointer without gcc complaining
        void *used_ptr = kmalloce_ptr; //this is the pointer that gets returned, it points to the block of free space
        kmalloce_ptr = ptr;

        return used_ptr;
    }
}

//stub
void *kmalloc(size_t size) {
    return NULL;
}