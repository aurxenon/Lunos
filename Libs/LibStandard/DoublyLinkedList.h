#pragma once

#if defined KERNEL_INCLUDES
#include <ArchSpecific/Types.h>
#include <Log/KLog.h>
#elif defined(TESTING_INCLUDES)
#include <stddef.h>
#endif

namespace LibStandard {

template <class T>
class DoublyLinkedNode;

template <class T>
class DoublyLinkedList {
    public:
        DoublyLinkedList() {
            m_items = nullptr;
            m_back = nullptr;
            m_numElements = 0;
        }

        T* front();
        T* end();

        size_t size();

        void push_front(T* node);
        void push_back(T* node);

        void remove(T* node);
        void remove(int index);

        T& operator[](int index);
    private:
        T* m_items;
        T* m_back;
        size_t m_numElements;
};

template <class T>
class DoublyLinkedNode {
    public:
        DoublyLinkedNode() {}

        T* getNextNode();
        T* getPrevNode();

        void setNextNode(T* nextNode);
        void setPrevNode(T* prevNode);
    private:
        T* m_nextNode;
        T* m_prevNode;
};

}