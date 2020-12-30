#include <iostream>

#include <LibStandard/SinglyLinkedList.h>

#include "TestCommon.h"

const int NUM_TESTS_TO_PERFORM = 3;

bool check_getNext();
bool check_addNode();
bool check_removeNode();

TestInfo testsToPerform[] = {
    TestInfo("getNext", &check_getNext),
    TestInfo("addNode", &check_addNode),
    TestInfo("removeNode", &check_removeNode)
};

int main() {
    std::cout << "- | LibStandard SinglyLinkedList Tests | -" << std::endl;

    for (int i = 0; i < NUM_TESTS_TO_PERFORM; i++) {
        std::cout << "Testing function " << testsToPerform[i].testedFunctionName << "...";
        bool passed = (*(testsToPerform[i].testFunction))();
        if (passed) {
            std::cout << " PASSED";
        } else {
            std::cout << " ----->FAILED";
        }
        std::cout << std::endl;
    }

    return 0;
}

class IntSinglyLinkedNode : public LibStandard::SinglyLinkedNode {
    public:
        IntSinglyLinkedNode(int newInt) {
            m_int = newInt;
        }

        int getInt() {
            return m_int;
        }

        void setInt(int newInt) {
            m_int = newInt;
        }
    private:
        int m_int;
};

bool check_getNext() {
    IntSinglyLinkedNode newIntNode1(10);
    IntSinglyLinkedNode newIntNode2(11);

    newIntNode1.setNext(&newIntNode2);

    return (newIntNode1.getNext() == &newIntNode2 ? true : false);
}

bool check_addNode() {
    LibStandard::SinglyLinkedList<IntSinglyLinkedNode> linkedList = LibStandard::SinglyLinkedList<IntSinglyLinkedNode>();
    IntSinglyLinkedNode newIntNode1(10);
    IntSinglyLinkedNode newIntNode2(11);
    linkedList.addNode(&newIntNode1);
    linkedList.addNode(&newIntNode2);

    return (linkedList.getStart()->getNext() == &newIntNode1 ? true : false);
}
bool check_removeNode() {
    LibStandard::SinglyLinkedList<IntSinglyLinkedNode> linkedList = LibStandard::SinglyLinkedList<IntSinglyLinkedNode>();
    IntSinglyLinkedNode newIntNode1(10);
    IntSinglyLinkedNode newIntNode2(11);
    linkedList.addNode(&newIntNode1);
    linkedList.addNode(&newIntNode2);
    linkedList.removeNode(&newIntNode2);

    return (linkedList.getStart()->getNext() == nullptr ? true : false);
}