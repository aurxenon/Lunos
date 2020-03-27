#pragma once

#include "ConvertNums.h"
#include "bastring.h"

extern "C" {
    char *itoa(int value, char *buffer, int base);
}