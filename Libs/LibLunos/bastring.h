#pragma once

#ifdef KERNEL_INCLUDES
#include <ArchSpecific/Types.h>
#include <System/KMalloc.h>
#endif

#include "string.h"

const char emptyString = '\0';

//template<class charT>

//this already needs to be refactored tbh
typedef class basic_string {
    public:
        basic_string() {
            instantiate(&emptyString, 0);
        }
        basic_string(const basic_string& stringCopy) {
            instantiate(stringCopy);
        }
        basic_string(const char *cstring) {
            instantiate(cstring, strlen(cstring));
        }
        basic_string(const char *cstring, size_t cstrlen) {
            instantiate(cstring, cstrlen);
        }
        basic_string operator=(const char* cstring) {
            instantiate(cstring, strlen(cstring));
            return *this;
        }
        basic_string operator=(basic_string equalString) {
            basic_string stringCopy = basic_string(equalString);
            instantiate(stringCopy);
            return *this;
        }
        char operator[](int index) {
            return chars[index];
        }
        basic_string& operator+(basic_string concatString) {
            size_t new_len = len + concatString.len;
            resize(new_len);
            strncpy(chars + new_len, concatString.chars, concatString.len);
            return *this;
        }
        basic_string& operator+(char *concatString) {
            size_t new_len = len + strlen(concatString);
            resize(new_len);
            strncpy(chars + new_len, concatString, strlen(concatString));
            return *this;
        }
        basic_string& operator+(char concatChar) {
            resize(len + 1);
            chars[len - 1] = concatChar;
            return *this;
        }
        bool operator==(basic_string bstr) {
            if (strcmp(chars, bstr.c_str()) == 0) {
                return true;
            } else {
                return false;
            }
        }
        bool operator==(const char *cstr) {
            if (strcmp(chars, cstr) == 0) {
                return true;
            } else {
                return false;
            }
        }

        size_t size();

        //propietary addition to Lunos, adds a string to the very beginning of this string
        basic_string& prepend(const char* cString);
        basic_string& prepend(const char character);

        void resize(size_t newSize);
        const char *c_str();
        int compare(const basic_string& str);

    private:
        void resizeAt(size_t newSize, size_t index);
        void instantiate(const basic_string& stringCopy);
        void instantiate(const char *cstring, size_t stringLength);
        char *chars;
        size_t len;
} string;