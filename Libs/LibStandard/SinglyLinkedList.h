#pragma once

namespace LibStandard {

class SinglyLinkedNode;

template<class NodeType>
class SinglyLinkedList {
    public:
        /*
        * SinglyLinkedList::SinglyLinkedList:
        *   Creates a new singly linked list
        * Arguments:
        * Return:
        */
        SinglyLinkedList() {
            m_start = nullptr;
        }

        /*
        * SinglyLinkedList::removeNode:
        *   Removes a linked list node from the linked list
        * Arguments:
        *   nodeToRemove - the node to be removed from the linked list
        * Return:
        *   bool - true if node was successfully found and removed, otherwise false
        */
        bool removeNode(NodeType* nodeToRemove) {
            if (m_start == nodeToRemove) {
                m_start = (NodeType*)nodeToRemove->getNext();
                return true;
            }
            NodeType* searchNode = m_start;
            while (searchNode != nullptr) {
                if (searchNode->getNext() == nodeToRemove) {
                    searchNode->setNext(nodeToRemove->getNext());
                    return true;
                }
                searchNode = (NodeType*)(searchNode->getNext());
            }
            return false;
        }

        /*
        * SinglyLinkedList::addNode:
        *   Adds a new node to the front of the linked list
        * Arguments:
        *   nodeToAdd - the node to be added to the front of the linked list
        * Return:
        */
        void addNode(NodeType* nodeToAdd) {
            nodeToAdd->setNext(nullptr);
            if (m_start == nullptr) {
                m_start = nodeToAdd;
            } else {
                nodeToAdd->setNext(m_start);
                m_start = nodeToAdd;
            }
        }

        /*
        * SinglyLinkedList::getStart:
        *   Returns first node in linked list
        * Arguments:
        * Return:
        *   NodeType* - first node in linked list
        */
        NodeType* getStart() {
            return m_start;
        }

    private:
        NodeType* m_start;
};

class SinglyLinkedNode {
    public:

        /*
        * SinglyLinkedList::SinglyLinkedNode:
        *   Creates a new singly linked list
        * Arguments:
        * Return:
        */
        SinglyLinkedNode() {
            m_next = nullptr;
        }

        /*
        * SinglyLinkedList::getNext:
        *   Gets next node after this node in the linked list
        * Arguments:
        * Return:
        *   SinglyLinkedNode* - next node in the linked list
        */
        SinglyLinkedNode* getNext() {
            return m_next;
        }

        /*
        * SinglyLinkedList::setNext:
        *   Sets the next node in the linked list after this node
        * Arguments:
        *   nextNode - the next node that's in the linked list after this node
        * Return:
        */
        void setNext(SinglyLinkedNode* nextNode) {
            m_next = nextNode;
        }
    private:
        SinglyLinkedNode* m_next;        
};

}