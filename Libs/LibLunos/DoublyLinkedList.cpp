#include "DoublyLinkedList.h"

/*
* DoublyLinkedList::front:
*   Returns the node at the return of the list
* Arguments:
* Return:
*   m_items - node at the beginning of the list
*/
template <class T>
T* DoublyLinkedList<T>::front() {
    return m_items;
}

/*
* DoublyLinkedList::end:
*   Returns the node at the end of the list
* Arguments:
* Return:
*   m_back - node at the end of the list
*/
template <class T>
T* DoublyLinkedList<T>::end() {
    return m_back;
}

/*
* DoublyLinkedList::size:
*   Returns number of elements in the linked list
* Arguments:
* Return:
*   m_numElements - number of elements stored in the linked list
*/
template <class T>
size_t DoublyLinkedList<T>::size() {
    return m_numElements;
}

/*
* DoublyLinkedList::push_front:
*   Adds a new node to the front of the list
* Arguments:
*   node - the node to be placed at the front of the list
* Return:
*/
template <class T>
void DoublyLinkedList<T>::push_front(T* node) {
    node->setNextNode(nullptr);
    node->setPrevNode(nullptr);

    if (m_numElements == 0) {
        m_items = node;
        m_back = node;
    } else if (m_numElements == 1) {
        m_items = node;
        m_items->setNextNode(m_back);
        m_back->setPrevNode(m_items);
    } else {
        node->setNextNode(m_items);
        m_items->setPrevNode(node);
        m_items = node;
    }
    m_numElements++;
}

/*
* DoublyLinkedList::push_back:
*   Adds supplied node to the end of the list
* Arguments:
*   node - the node to be added to the end of the list
* Return:
*/
template <class T>
void DoublyLinkedList<T>::push_back(T* node) {
    node->setNextNode(nullptr);
    node->setPrevNode(nullptr);

    if (m_numElements == 0) {
        m_items = node;
        m_back = node;
    } else if (m_numElements == 1) {
        m_back = node;
        m_back->setPrevNode(m_items);
        m_items->setNextNode(m_back);
    } else {
        node->setPrevNode(m_back);
        m_back->setNextNode(node);
        m_back = node;
    }
    m_numElements++;
}

/*
* DoublyLinkedList::remove:
*   Removes node from doubly linked list
* Arguments:
*   node - the node to be removed from the list
* Return:
*/
template <class T>
void DoublyLinkedList<T>::remove(T* node) {
    if (m_numElements == 1) {
        m_back = nullptr;
        m_items = nullptr;
        node->setNextNode(nullptr);
        node->setPrevNode(nullptr);
    } else {
        if (node == m_items) {
            m_items = m_items->getNextNode();
        } else if (node == m_back) {
            m_back = m_back->getPrevNode();
        }
        T* nodeBehind = node->getPrevNode();
        T* nodeAhead = node->getNextNode();

        nodeBehind->setNextNode(nodeAhead);
        nodeAhead->setPrevNode(nodeBehind);

        node->setNextNode(nullptr);
        node->setPrevNode(nullptr);
    }
    m_numElements--;
}

/*
* DoublyLinkedList::operator[]:
*   Grab pointer to the node at the specified index
* Arguments:
*   index - place in list where node is stored
* Return:
*   node - node located at the index in the list
*/
template <class T>
T& DoublyLinkedList<T>::operator[](int index) {
    T* node = m_items;
    
    for (int i = 0; i <= index; i++) {
        node = node->getNextNode();
    }

    return *node;
}


/*
    DoublyLinkedNode
*/

/*
* DoublyLinkedNode::getNextNode:
*   Returns a pointer to the next node in the linked list after this node
* Arguments:
* Return:
*   m_nextNode - pointer to the next node in the linked list after this one
*/
template <class T>
T* DoublyLinkedNode<T>::getNextNode() {
    return m_nextNode;
}

/*
* DoublyLinkedNode::getPrevNode:
*   Returns a pointer to the preceeding node in the linked list before this node
* Arguments:
* Return:
*   m_prevNode -pointer to the previous node in the linked list before this one
*/
template <class T>
T* DoublyLinkedNode<T>::getPrevNode() {
    return m_prevNode;
}

/*
* DoublyLinkedNode::setNextNode:
*   Replaces the next node being pointed to for a different node
* Arguments:
*   nextNode - the next node that this node should point at
* Return:
*/
template <class T>
void DoublyLinkedNode<T>::setNextNode(T* nextNode) {
    m_nextNode = nextNode;
}

/*
* DoublyLinkedNode::setPrevNode:
*   Sets the previous node in the list that this node should point at
* Arguments:
*   prevNode - the prior node in the linked list
* Return:
*/
template <class T>
void DoublyLinkedNode<T>::setPrevNode(T* prevNode) {
    m_prevNode = prevNode;
}

//very very VERY hacky
#include <System/Process/Process.h>

template class DoublyLinkedList<Process>;