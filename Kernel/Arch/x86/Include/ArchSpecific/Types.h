#pragma once

//typedef _Bool bool;
#define true 1
#define false 0

typedef __builtin_va_list va_list;

/*unsigned types*/

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long int u64;

typedef u8 uint8_t;
typedef u16 uint16_t;
typedef u32 uint32_t;
typedef u64 uint64_t;

typedef u16 uint_least16_t;
typedef u32 uint_least32_t;

typedef u32 uintptr_t;
typedef u32 size_t;
typedef u64 uintmax_t;

/*signed types*/

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long int i64;

typedef i8 int8_t;
typedef i16 int16_t;
typedef i32 int32_t;
typedef i64 int64_t;

typedef i32 ptrdiff_t;
typedef long intptr_t;
typedef u64 intmax_t;

typedef i32 ssize_t;