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
        
        void push_back(T value) {
            num++;
            autoresize();
            vectorBlock[size()] = value;
        }

        void pop_back() {
            vectorBlock[num - 1] = nullptr;
            num--;
        }
        
        void erase() {
            for (int i = 0; i < num; i++) {
                vectorBlock[i] = nullptr;
            }
            num = 0;
        }
        
        size_t size() {
            return num;
        }
        
        size_t capacity() {
            return vectorCapacity;
        }
        
        T& at(size_t index) {
            autoresize();
            return vectorBlock[index];
        }
        
        T& front() {
            return vectorBlock[0];
        }
        
        T& back() {
            return vectorBlock[num - 1];
        }
        
        T* data() {
            return vectorBlock;
        }
        
        void resize(size_t new_len) {
            T* newVectorBlock = (T*)kmalloce(sizeof(T) * new_len);

            if (new_len >= vectorCapacity) {
                memcpy(newVectorBlock, vectorBlock, vectorCapacity);
            } else {
                memcpy(newVectorBlock, vectorBlock, new_len);
                num = new_len;
            }
            vectorCapacity = new_len;
        }
        
        void autoresize() {
            if (num > (int)(vectorCapacity * 0.80)) {
                resize((size_t)vectorCapacity * 1.8);
            }
        }
        
        void clear() {
            resize(0);
            vectorBlock[0] = nullptr;
        }
        
        bool empty() {
            if (num > 0) {
                return false;
            } else {
                return true;
            }
        }
        
        T& operator[](size_t index) {
            autoresize();
            return vectorBlock[index];
        }

        //using Iterator=VectorIterator;
    private:
        size_t num;
        size_t vectorCapacity;
        T* vectorBlock;
};