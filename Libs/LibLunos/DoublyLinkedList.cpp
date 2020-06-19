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
* DoublyLinkedList::push_front:
*   Adds a new node to the front of the list
* Arguments:
*   node - the node to be placed at the front of the list
* Return:
*/
template <class T>
void DoublyLinkedList<T>::push_front(DoublyLinkedNode<T>* node) {
    m_items->setPrevNode(node);
    node->setNextNode(m_items);
    m_items = node;
    m_numElements++;
}

/*
* DoublyLinkedList::pop_front:
*   Removes node from the front of the list and returns it
* Arguments:
* Return:
*   firstNode - the node that was previously at the beginning of the list
*/
template <class T>
DoublyLinkedNode<T>* DoublyLinkedList<T>::pop_front() {
    DoublyLinkedNode<T>* firstNode = m_items;
    m_items = m_items->getNextNode();
    m_numElements--;
    return firstNode;
}

/*
* DoublyLinkedList::push_back:
*   Adds supplied node to the end of the list
* Arguments:
*   node - the node to be added to the end of the list
* Return:
*/
template <class T>
void DoublyLinkedList<T>::push_back(DoublyLinkedNode<T>* node) {
    DoublyLinkedNode<T>* prevBack = m_back;
    prevBack->setNextNode(node);
    node->setPrevNode(prevBack);
    m_back = node;
    m_numElements++;
}

/*
* DoublyLinkedList::pop_back:
*   Removes last node from the list and returns it
* Arguments:
* Return:
*   endNode - the last node in the list
*/
template <class T>
DoublyLinkedNode<T>* DoublyLinkedList<T>::pop_back() {
    DoublyLinkedNode<T> *endNode = m_back;
    m_back = m_back->getPrevNode();
    m_numElements--;
    return endNode;
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
DoublyLinkedNode<T>* DoublyLinkedList<T>::operator[](int index) {
    if (index >= m_numElements) {
        return nullptr;
    }
    
    DoublyLinkedNode<T>* node = m_items;
    
    for (int i = 0; i <= index; i++) {
        node = node->getNextNode();
    }

    return node;
}


/*
    DoublyLinkedNode
*/


/*
* DoublyLinkedNode::DoublyLinkedNode:
*   Constructs a new node that contains an object of type T
* Arguments:
*   item - object of type T that's to be stored
* Return:
*/
template <class T>
DoublyLinkedNode<T>::DoublyLinkedNode(T item) {
    m_contents = item;
}

/*
* DoublyLinkedNode::getNextNode:
*   Returns a pointer to the next node in the linked list after this node
* Arguments:
* Return:
*   m_nextNode - pointer to the next node in the linked list after this one
*/
template <class T>
DoublyLinkedNode<T>* DoublyLinkedNode<T>::getNextNode() {
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
DoublyLinkedNode<T>* DoublyLinkedNode<T>::getPrevNode() {
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
void DoublyLinkedNode<T>::setNextNode(DoublyLinkedNode* nextNode) {
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
void DoublyLinkedNode<T>::setPrevNode(DoublyLinkedNode* prevNode) {
    m_prevNode = prevNode;
}

/*
* DoublyLinkedNode::getContents:
*   Returns the contents stored in the node
* Arguments:
* Return:
*   m_contents - the contents of this node
*/
template <class T>
T DoublyLinkedNode<T>::getContents() {
    return m_contents;
}

/*
* DoublyLinkedNode::setContents:
*   Change the contents stored in the node
* Arguments:
*   newContents - the new contents of this node
* Return:
*/
template <class T>
void DoublyLinkedNode<T>::setContents(T newContents) {
    m_contents = newContents;
}