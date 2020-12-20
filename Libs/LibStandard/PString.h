#pragma once

#ifdef KERNEL_INCLUDES
#include <ArchSpecific/Types.h>
#include <System/KMalloc.h>
#endif

#include "CString.h"

namespace LibStandard {

const char emptyString = '\0';

//template<class charT>
typedef class basic_string {
    public:

        /* Constructors */

        basic_string();
        basic_string(const char *cstring);
        basic_string(const char *cstring, size_t cstrlen);
        //
        //creates a copy of a C++ string
        //
        basic_string(const basic_string& stringCopy);

        /* Various operator overloads for easy string manipulation and comparisons */

        //
        //copies data from a string into the C++ string being operated on
        //
        basic_string operator=(const char* cstring);
        basic_string operator=(basic_string equalString);
        //
        //grabs a single character from a C++ string, array style
        //
        char operator[](int index);
        //
        //adds a string to the C++ string being operated on and returns the combined string
        //
        basic_string& operator+(basic_string concatString);
        basic_string& operator+(char *concatString);
        //
        //adds a single character to a C++ string and returns the new string
        //
        basic_string& operator+(char concatChar);
        //
        //compares 2 string's and returns if the contents are equal or not
        //
        bool operator==(basic_string bstr);
        bool operator==(const char *cstr);

        /* Utility functions */

        size_t size();

        //propietary addition to Lunos, adds a string to the beginning of the string being operated on
        basic_string& prepend(const char* cstring);
        basic_string& prepend(const char character);

        void resize(size_t newSize);
        const char *c_str();
        int compare(const basic_string& str);

    private:
        //
        //makes a new string buffer of the given size and places 
        //old string into the new buffer at the given index
        //if the string is empty, it simply allocates a new buffer
        //and size according to the arguments
        //
        void resizeAt(size_t newSize, size_t index);

        //
        //does most of the work in creating a new
        //
        void instantiate(const basic_string& stringCopy);
        void instantiate(const char *cstring, size_t stringLength);


        char *m_chars;
        size_t m_len;
} string;

}

#ifdef KERNEL_INCLUDES
using namespace LibStandard;
#endif