#pragma once

struct TestInfo {
    TestInfo(const char* name, bool (*function)(void)) 
        : testedFunctionName(name), testFunction(function) {}
    const char* testedFunctionName;
    bool (*testFunction)(void);
};