#include <iostream>

#include <LibStandard/CString.h>

#include "TestCommon.h"

const int NUM_TESTS_TO_PERFORM = 7;

bool check_strlen();
bool check_strcpy();
bool check_strncpy();
bool check_strcmp();
bool check_strncmp();
bool check_memcpy();
bool check_memset();

TestInfo testsToPerform[] = {
    TestInfo("strlen", &check_strlen),
    TestInfo("strcpy", &check_strcpy),
    TestInfo("strncpy", &check_strncpy),
    TestInfo("strcmp", &check_strcmp),
    TestInfo("strncmp", &check_strncmp),
    TestInfo("memcpy", &check_memcpy),
    TestInfo("memset", &check_memset)
};

int main() {
    std::cout << "- | LibStandard CString Tests | -" << std::endl;

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

bool check_strlen() {
    const size_t EXPECTED_STRLEN_RESULT = 6;
    const char* strlenTestString = "abcdef";

    size_t strlenResult = LibStandard::strlen(strlenTestString);

    return (strlenResult == EXPECTED_STRLEN_RESULT) ? true : false;
}

bool check_strcpy() {
    const bool EXPECTED_STRCPY_RESULT = true;
    const bool strcpyTestString1Size = 7;
    
    const char* strcpyTestString1 = "abcdef";
    const char* strcpyTestString2 = (const char*)malloc(strcpyTestString1Size);
    bool strcpyResult = true;

    LibStandard::strcpy(strcpyTestString2, strcpyTestString1);

    if (strcmp(strcpyTestString1, strcpyTestString2) != 0) {
        strcpyResult = false;
    }

    free((void*)strcpyTestString2);

    return (strcpyResult == EXPECTED_STRCPY_RESULT) ? true : false;
}

bool check_strncpy() {
    const bool EXPECTED_STRNCPY_RESULT = true;
    const bool strncpyTestString1Size = 3;
    
    const char* strncpyTestString1 = "abcdef";
    const char* strncpyTestString2 = (const char*)malloc(strncpyTestString1Size);
    bool strncpyResult = true;

    LibStandard::strncpy(strncpyTestString2, strncpyTestString1, strncpyTestString1Size);

    if (strcmp(strncpyTestString1, strncpyTestString2) != 0) {
        strncpyResult = false;
    }

    free((void*)strncpyTestString2);

    return (strncpyResult == EXPECTED_STRNCPY_RESULT) ? true : false;
}

bool check_strcmp() {
    const char* strcmpTestString1 = "abcdef";
    const char* strcmpTestString2 = "abcdef";
    const char* strcmpTestString3 = "bcdefg";
    const char* strcmpTestString4 = "abcde";

    if (LibStandard::strcmp(strcmpTestString1, strcmpTestString2) != 
            strcmp(strcmpTestString1, strcmpTestString2)) {
        return false;
    }
    if (LibStandard::strcmp(strcmpTestString1, strcmpTestString3) != 
            strcmp(strcmpTestString1, strcmpTestString3)) {
        return false;
    }
    if (LibStandard::strcmp(strcmpTestString1, strcmpTestString4) != 
            strcmp(strcmpTestString1, strcmpTestString4)) {
        return false;
    }

    return true;
}

bool check_strncmp() {
    const char* strcmpTestString1 = "abcdef";
    const size_t STRCMP_TEST_STRING1_LENGTH = 7;
    const char* strcmpTestString2 = "abcdef";
    const char* strcmpTestString3 = "bcdefg";
    const char* strcmpTestString4 = "abcde";
    const size_t STRCMP_TEST_STRING4_LENGTH = 6;

    if (LibStandard::strncmp(strcmpTestString1, strcmpTestString2, STRCMP_TEST_STRING1_LENGTH) != 
            strncmp(strcmpTestString1, strcmpTestString2, STRCMP_TEST_STRING1_LENGTH)) {
        return false;
    }
    if (LibStandard::strncmp(strcmpTestString1, strcmpTestString3, STRCMP_TEST_STRING1_LENGTH) != 
            strncmp(strcmpTestString1, strcmpTestString3, STRCMP_TEST_STRING1_LENGTH)) {
        return false;
    }
    if (LibStandard::strncmp(strcmpTestString1, strcmpTestString4, STRCMP_TEST_STRING1_LENGTH) != 
            strncmp(strcmpTestString1, strcmpTestString4, STRCMP_TEST_STRING1_LENGTH)) {
        return false;
    }
    if (LibStandard::strncmp(strcmpTestString1, strcmpTestString4, STRCMP_TEST_STRING4_LENGTH) != 
            strncmp(strcmpTestString1, strcmpTestString4, STRCMP_TEST_STRING4_LENGTH)) {
        return false;
    }

    return true;
}

bool check_memcpy() {
    const int NUM_ITEMS = 5;
    int memSpot1[NUM_ITEMS] = {1, 2, 3, 4, 5};
    int* memSpot2 = (int*)malloc(sizeof(int) * 5);

    bool memEqual = true;

    LibStandard::memcpy(memSpot2, memSpot1, NUM_ITEMS * sizeof(int));

    if (memcmp(memSpot1, memSpot2, NUM_ITEMS * sizeof(int)) != 0) {
        memEqual = false;
    }

    free(memSpot2);

    return memEqual;
}

bool check_memset() {
    const int NUM_ITEMS = 5;
    const int FILL_ITEM = 3;
    void* fillSpace = malloc(NUM_ITEMS);
    
    bool filledMem = true;

    LibStandard::memset(fillSpace, FILL_ITEM, NUM_ITEMS);

    for (int i = 0; i < NUM_ITEMS; i++) {
        if (((char*)(fillSpace))[i] != (char)FILL_ITEM) {
            filledMem = false;
        }
    }

    free(fillSpace);

    return filledMem;
}