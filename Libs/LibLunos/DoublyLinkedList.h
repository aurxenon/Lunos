#pragma once

#include <ArchSpecific/Types.h>

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

        void push_front(DoublyLinkedNode<T>* node);
        DoublyLinkedNode<T>* pop_front();

        void push_back(DoublyLinkedNode<T>* node);
        DoublyLinkedNode<T>* pop_back();

        DoublyLinkedNode<T>* operator[](int index);
    private:
        T* m_items;
        T* m_back;
        size_t m_numElements;
};

template <class T>
class DoublyLinkedNode {
    public:
        DoublyLinkedNode(T item);

        DoublyLinkedNode* getNextNode();
        DoublyLinkedNode* getPrevNode();

        void setNextNode(DoublyLinkedNode* nextNode);
        void setPrevNode(DoublyLinkedNode* prevNode);

        T getContents();
        void setContents(T newContents);
    private:
        T m_contents;
        DoublyLinkedNode *m_nextNode;
        DoublyLinkedNode *m_prevNode;
};