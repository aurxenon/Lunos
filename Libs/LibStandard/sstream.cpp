#include "sstream.h"

namespace LibStandard {

string to_string(int num) {
    return numToString<int>(num, 10);
}

}