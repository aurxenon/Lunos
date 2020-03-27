#include "bastring.h"

size_t basic_string::size() {
    return len;
}

const char *basic_string::c_str() {
    return chars;
}

basic_string& basic_string::prepend(const char* cString) {
    size_t cStringLength = strlen(cString);
    resizeAt(cStringLength + len, cStringLength);
    strcpy(chars, cString);
    return *this;
}

basic_string& basic_string::prepend(const char character) {
    resizeAt(len + 1, 1);
    chars[0] = character;
    return *this;
}

void basic_string::resize(size_t newSize) {
    resizeAt(newSize, 0);
}

void basic_string::resizeAt(size_t newSize, size_t index) {
    if (len > 0) {
        len = newSize;
        char *new_chars = (char*)kmalloce(newSize);
        strncpy(new_chars + index, chars, len);
        chars = new_chars;
    } else {
        len = newSize;
        chars = (char*)kmalloce(newSize);
    }
}

int basic_string::compare(const string& str) {
    return strcmp(chars, ((basic_string)str).c_str());
}

void basic_string::instantiate(const basic_string& stringCopy) {
    len = 0;
    chars = (char*)&emptyString;
    if (stringCopy.len == 0) {
        return;
    }
    len = stringCopy.len;
    chars = strncpy((char*)kmalloce(stringCopy.len), stringCopy.chars, len);
}

void basic_string::instantiate(const char *cstring, size_t stringLength) {
    len = 0;
    chars = (char*)&emptyString;
    if (stringLength == 0) {
        return;
    }
    len = stringLength;
    chars = strncpy((char*)kmalloce(stringLength), cstring, stringLength);
}