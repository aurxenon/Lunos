#pragma once

#ifdef KERNEL_INCLUDES
#include <ArchSpecific/Types.h>
#include <System/KMalloc.h>
#endif

#include "string.h"

//template<class charT>

typedef class basic_string {
    public:
        basic_string(const char *cstring) {
            len = strlen(cstring);
            chars = strncpy((char*)kmalloce(len), cstring, len);
        }
        basic_string(const char *cstring, size_t cstrlen) {
            len = cstrlen;
            chars = strncpy((char*)kmalloce(len), cstring, len);
        }
        basic_string operator=(const char* cstring) {
            return basic_string(cstring);
        }
        char operator[](int index) {
            return chars[index];
        }
        basic_string& operator+(basic_string concatString) {
            size_t new_len = len + concatString.size();
            char *new_chars = (char*)kmalloce(new_len);
            strcpy(new_chars, chars);
            strcpy(new_chars + new_len, concatString.c_str());
            return *this;
        }
        basic_string& operator+(char *concatString) {
            size_t new_len = len + strlen(concatString);
            char *new_chars = (char*)kmalloce(new_len);
            strcpy(new_chars, chars);
            strcpy(new_chars + new_len, concatString);
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
        const char *c_str();
        int compare(const basic_string& str);

    private:
        char *chars;
        size_t len;
} string;