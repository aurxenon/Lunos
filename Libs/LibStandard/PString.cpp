#include "PString.h"

#ifdef KERNEL_INCLUDES
#define malloc kmalloce
#endif

namespace LibStandard {
/*
Constructors and also string initializers
*/

basic_string::basic_string() {
    instantiate(&emptyString, 0);
}

basic_string::basic_string(const basic_string& stringCopy) {
    instantiate(stringCopy);
}

basic_string::basic_string(const char *cstring) {
    instantiate(cstring, strlen(cstring));
}

basic_string::basic_string(const char *cstring, size_t cstrlen) {
    instantiate(cstring, cstrlen);
}

//initializes m_len and m_chars, then fills them using the stringCopy
void basic_string::instantiate(const basic_string& stringCopy) {
    m_len = 0;
    m_chars = (char*)&emptyString;
    if (stringCopy.m_len == 0) {
        return;
    }
    m_len = stringCopy.m_len;
    m_chars = strncpy((char*)malloc(stringCopy.m_len), stringCopy.m_chars, m_len);
}

//initializes m_len and m_chars, then fills them using the C-style string and length
void basic_string::instantiate(const char *cstring, size_t stringLength) {
    m_len = 0;
    m_chars = (char*)(&emptyString);
    if (stringLength == 0) {
        return;
    }
    m_len = stringLength;
    m_chars = strncpy((char*)malloc(stringLength), cstring, stringLength);
}

/*
Operator overloads
*/

basic_string basic_string::operator=(const char* cstring) {
    instantiate(cstring, strlen(cstring));
    return *this;
}

basic_string basic_string::operator=(basic_string equalString) {
    instantiate(equalString);
    return *this;
}

char basic_string::operator[](int index) {
    return m_chars[index];
}

basic_string& basic_string::operator+(basic_string concatString) {
    size_t new_len = m_len + concatString.m_len;
    resize(new_len);
    strncpy(m_chars + new_len, concatString.m_chars, concatString.m_len);
    return *this;
}

basic_string& basic_string::operator+(char *concatString) {
    size_t new_len = m_len + strlen(concatString);
    resize(new_len);
    strncpy(m_chars + new_len, concatString, strlen(concatString));
    return *this;
}

basic_string& basic_string::operator+(char concatChar) {
    resize(m_len + 1);
    m_chars[m_len - 1] = concatChar;
    return *this;
}

bool basic_string::operator==(basic_string bstr) {
    if (strcmp(m_chars, bstr.c_str()) == 0) {
        return true;
    } else {
        return false;
    }
}

bool basic_string::operator==(const char *cstr) {
    if (strcmp(m_chars, cstr) == 0) {
        return true;
    } else {
        return false;
    }
}

/*
Various string utilities
*/

size_t basic_string::size() {
    return m_len;
}

const char *basic_string::c_str() {
    return m_chars;
}

//creates a new string that's the same size as the passed in string and the
//string being operated on, then copies the passed in string into the buffer
//immediately before the string being operated on
basic_string& basic_string::prepend(const char* cstring) {
    size_t cstringLength = strlen(cstring);

    resizeAt(cstringLength + m_len, cstringLength);
    //after resizing, place the C-style string in the space before the buffer before the original string
    strcpy(m_chars, cstring);
    
    return *this;
}

basic_string& basic_string::prepend(const char character) {
    resizeAt(m_len + 1, 1);

    m_chars[0] = character;
    
    return *this;
}

void basic_string::resize(size_t newSize) {
    resizeAt(newSize, 0);
}

//this creates a whole new string, and then copies the string being operated on
//into the new string at the index specified
void basic_string::resizeAt(size_t newSize, size_t index) {
    //if the string length is greater than zero
    if (m_len > 0) {
        m_len = newSize;
        char *new_chars = (char*)malloc(newSize);
        if ((m_len + index) > newSize) {
            strncpy(new_chars + index, m_chars, m_len - index);
        } else {
            strncpy(new_chars + index, m_chars, m_len);
        }
        m_chars = new_chars;
    } else {
        m_len = newSize;
        m_chars = (char*)malloc(newSize);
    }
}

int basic_string::compare(const string& str) {
    return strcmp(m_chars, ((basic_string)str).c_str());
}

}