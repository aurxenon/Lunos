#include "stdlib.h"

namespace LibStandard {

char *itoa(int value, char *buffer, int base) {
    strcpy(buffer, numToString<int>(value, base).c_str());
    return buffer;
}

}