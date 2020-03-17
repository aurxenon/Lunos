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
        basic_string operator =(const char* cstring) {
            basic_string cppstring(cstring);
            return cppstring;
        }
        char operator[](int index) {
            return chars[index];
        }
        char operator==(basic_string bstr) {
            if (strcmp(chars, bstr.c_str()) == 0) {
                return true;
            } else {
                return false;
            }
        }
        char operator==(const char *cstr) {
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