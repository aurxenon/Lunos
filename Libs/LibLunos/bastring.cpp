#include "bastring.h"

size_t basic_string::size() {
    return len;
}

const char *basic_string::c_str() {
    return chars;
}

int basic_string::compare(const string& str) {
    return strcmp(chars, ((basic_string)str).c_str());
}