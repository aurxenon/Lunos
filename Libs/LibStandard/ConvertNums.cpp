#include "ConvertNums.h"

namespace LibStandard {

//converted from osdev itoa implementation
//this will hopefully only ever be populated with non floating point numbers
template<typename T>
string numToString(T value, int base) {
    string convertedNum;
    
    if (base < 2 || base > 36)
    {
        return convertedNum;
    }
    
    //if number is negative and base 10 add a minus sign in front
    if (value < 0 && base == 10)
    {
         convertedNum = convertedNum + '-';
    }

    //does most of the converting
    do
    {
        convertedNum.prepend("zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base]);
        value /= base;
    } while (value);
    
    return convertedNum;
}

template string numToString(int value, int base);

}