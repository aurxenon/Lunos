#include <iostream>

#include <LibStandard/Bitmap.h>

#include "TestCommon.h"

const int NUM_TESTS_TO_PERFORM = 4;

bool check_enableBit();
bool check_disableBit();
bool check_overflow();
bool check_overflowRead();

TestInfo testsToPerform[] = {
    TestInfo("enableBit", &check_enableBit),
    TestInfo("disableBit", &check_disableBit),
    TestInfo("enableBit & disableBit overflow", &check_overflow),
    TestInfo("getBit overflow", &check_overflowRead)
};

int main() {
    std::cout << "- | LibStandard Bitmap Tests | -" << std::endl;

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

bool check_enableBit() {
    const size_t EXPECTED_BIT_STATE = true;
    LibStandard::Bitmap bitmap(2);

    bitmap.enableBit(14);
    
    return (bitmap.getBit(14) == EXPECTED_BIT_STATE) ? true : false;
}

bool check_disableBit() {
    const size_t EXPECTED_BIT_STATE = false;
    u8 bitmapArea[] = {0xFF, 0xFF};
    LibStandard::Bitmap bitmap(bitmapArea, 2);

    bitmap.disableBit(14);
    
    return (bitmap.getBit(14) == EXPECTED_BIT_STATE) ? true : false;
}

bool check_overflow() {
    const u8 EXPECTED_BIT_STATE = 0xFF;
    u8 bitmapArea[] = {0xFF, 0xFF, 0xFF};
    LibStandard::Bitmap bitmap(bitmapArea, 2);

    bitmap.disableBit(17);
    
    return (bitmapArea[2] == EXPECTED_BIT_STATE) ? true : false;
}

bool check_overflowRead() {
    const size_t EXPECTED_BIT_STATE = false;
    u8 bitmapArea[] = {0xFF, 0xFF, 0xFF};
    LibStandard::Bitmap bitmap(bitmapArea, 2);
    
    return (bitmap.getBit(17) == EXPECTED_BIT_STATE) ? true : false;
}