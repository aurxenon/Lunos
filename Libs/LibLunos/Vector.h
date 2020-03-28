#pragma once

#include "Iterator.h"
#include "string.h"

#ifdef KERNEL_INCLUDES
#include <System/KMalloc.h>
#endif

template<class T>
class Vector {
    public:
        Vector () {
            vectorBlock = (T*)kmalloce(sizeof(T));
            num = 0;
            vectorCapacity = 0;
        }
        Vector (size_t numItems) {
            vectorBlock = (T*)kmalloce(sizeof(T) * numItems);
            num = numItems;
            vectorCapacity = numItems;
        }
        Vector (size_t numItems, T item) {
            vectorBlock = (T*)kmalloce(sizeof(T) * numItems);
            for (size_t i = 0; i < numItems; i++) {
                vectorBlock[i] = item;
            }
            num = numItems;
            vectorCapacity = numItems;
        }
        void push_back(T value);
        void pop_back();
        void erase();
        size_t size();
        size_t capacity();
        T& at(size_t n);
        T& front();
        T& back();
        T* data();
        void resize(size_t new_len);
        void autoresize();
        void clear();
        bool empty();

        T& operator[](size_t index);

        //using Iterator=VectorIterator;
    private:
        size_t num;
        size_t vectorCapacity;
        T* vectorBlock;
};