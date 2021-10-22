
// vim: ft=c tabstop=4 expandtab shiftwidth=4 softtabstop=4 autoindent foldmethod=marker foldmarker=[[[,]]]
/*
 * @file
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * SPDX-License-Identifier: MIT + Beerware
 */
// Header [[[
#ifndef CKDINT_H_
#define CKDINT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#ifdef __SIZEOF_INT128__
#ifndef INT128_MAX
#define INT128_MAX   ((__int128)(((unsigned __int128) 1 << ((__SIZEOF_INT128__ * __CHAR_BIT__) - 1)) - 1))
#endif
#ifndef INT128_MIN
#define INT128_MIN   (-INT128_MAX - 1)
#endif
#ifndef UINT128_MAX
#define UINT128_MAX  ((2 * (unsigned __int128) INT128_MAX) + 1)
#endif
#endif // __SIZEOF_INT128__

#ifndef _ckd_static
#define _ckd_static     static inline
#endif
#if __GNUC__
#define _ckd_funcconst  _ckd_static __attribute__((__warn_unused_result__)) __attribute__((__const__))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ > 20230000L
#define _ckd_funcconst  _ckd_static [[__nodiscard__]]
#else
#define _ckd_funcconst  _ckd_static
#endif

// ]]]
// Declare checked integer types [[[
/// @brief A checked integer type for storing value of type signed char.
typedef struct _ckd_schar_t {
    /// @brief The stored value.
    signed char _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_schar_t;

#define _ckd_schar   signed char
#define _ckd_cschar  ckd_schar_t


/// @brief A checked integer type for storing value of type unsigned char.
typedef struct _ckd_uchar_t {
    /// @brief The stored value.
    unsigned char _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_uchar_t;

#define _ckd_uchar   unsigned char
#define _ckd_cuchar  ckd_uchar_t


/// @brief A checked integer type for storing value of type short.
typedef struct _ckd_shrt_t {
    /// @brief The stored value.
    short _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_shrt_t;

#define _ckd_shrt   short
#define _ckd_cshrt  ckd_shrt_t


/// @brief A checked integer type for storing value of type unsigned short.
typedef struct _ckd_ushrt_t {
    /// @brief The stored value.
    unsigned short _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_ushrt_t;

#define _ckd_ushrt   unsigned short
#define _ckd_cushrt  ckd_ushrt_t


/// @brief A checked integer type for storing value of type int.
typedef struct _ckd_int_t {
    /// @brief The stored value.
    int _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_int_t;

#define _ckd_int   int
#define _ckd_cint  ckd_int_t


/// @brief A checked integer type for storing value of type unsigned int.
typedef struct _ckd_uint_t {
    /// @brief The stored value.
    unsigned int _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_uint_t;

#define _ckd_uint   unsigned int
#define _ckd_cuint  ckd_uint_t


/// @brief A checked integer type for storing value of type long.
typedef struct _ckd_long_t {
    /// @brief The stored value.
    long _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_long_t;

#define _ckd_long   long
#define _ckd_clong  ckd_long_t


/// @brief A checked integer type for storing value of type unsigned long.
typedef struct _ckd_ulong_t {
    /// @brief The stored value.
    unsigned long _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_ulong_t;

#define _ckd_ulong   unsigned long
#define _ckd_culong  ckd_ulong_t


/// @brief A checked integer type for storing value of type long long.
typedef struct _ckd_llong_t {
    /// @brief The stored value.
    long long _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_llong_t;

#define _ckd_llong   long long
#define _ckd_cllong  ckd_llong_t


/// @brief A checked integer type for storing value of type unsigned long long.
typedef struct _ckd_ullong_t {
    /// @brief The stored value.
    unsigned long long _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_ullong_t;

#define _ckd_ullong   unsigned long long
#define _ckd_cullong  ckd_ullong_t


/// @brief A checked integer type for storing value of type __int128.
typedef struct _ckd_int128_t {
    /// @brief The stored value.
    __int128 _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_int128_t;

#define _ckd_int128   __int128
#define _ckd_cint128  ckd_int128_t


/// @brief A checked integer type for storing value of type unsigned __int128.
typedef struct _ckd_uint128_t {
    /// @brief The stored value.
    unsigned __int128 _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_uint128_t;

#define _ckd_uint128   unsigned __int128
#define _ckd_cuint128  ckd_uint128_t

// ]]]
// Standard integer types aliases [[[

#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == SCHAR_MAX && INTMAX_MIN == SCHAR_MIN
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_schar_t.
 */
#define ckd_intmax_t  ckd_schar_t
#endif
#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == UCHAR_MAX && INTMAX_MIN == 0
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_uchar_t.
 */
#define ckd_intmax_t  ckd_uchar_t
#endif
#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == SHRT_MAX && INTMAX_MIN == SHRT_MIN
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_shrt_t.
 */
#define ckd_intmax_t  ckd_shrt_t
#endif
#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == USHRT_MAX && INTMAX_MIN == 0
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_ushrt_t.
 */
#define ckd_intmax_t  ckd_ushrt_t
#endif
#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == INT_MAX && INTMAX_MIN == INT_MIN
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_int_t.
 */
#define ckd_intmax_t  ckd_int_t
#endif
#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == UINT_MAX && INTMAX_MIN == 0
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_uint_t.
 */
#define ckd_intmax_t  ckd_uint_t
#endif
#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == LONG_MAX && INTMAX_MIN == LONG_MIN
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_long_t.
 */
#define ckd_intmax_t  ckd_long_t
#endif
#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == ULONG_MAX && INTMAX_MIN == 0
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_ulong_t.
 */
#define ckd_intmax_t  ckd_ulong_t
#endif
#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == LLONG_MAX && INTMAX_MIN == LLONG_MIN
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_llong_t.
 */
#define ckd_intmax_t  ckd_llong_t
#endif
#if !defined(ckd_intmax_t) && defined(INTMAX_MAX) && INTMAX_MAX == ULLONG_MAX && INTMAX_MIN == 0
/**
 * @define ckd_intmax_t
 * @brief Check integer type ckd_intmax_t is an alias to ckd_ullong_t.
 */
#define ckd_intmax_t  ckd_ullong_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_schar_t.
 */
#define ckd_uintmax_t  ckd_schar_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_uchar_t.
 */
#define ckd_uintmax_t  ckd_uchar_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_shrt_t.
 */
#define ckd_uintmax_t  ckd_shrt_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_ushrt_t.
 */
#define ckd_uintmax_t  ckd_ushrt_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_int_t.
 */
#define ckd_uintmax_t  ckd_int_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_uint_t.
 */
#define ckd_uintmax_t  ckd_uint_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_long_t.
 */
#define ckd_uintmax_t  ckd_long_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_ulong_t.
 */
#define ckd_uintmax_t  ckd_ulong_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_llong_t.
 */
#define ckd_uintmax_t  ckd_llong_t
#endif
#if !defined(ckd_uintmax_t) && defined(UINTMAX_MAX) && UINTMAX_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uintmax_t
 * @brief Check integer type ckd_uintmax_t is an alias to ckd_ullong_t.
 */
#define ckd_uintmax_t  ckd_ullong_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_schar_t.
 */
#define ckd_size_t  ckd_schar_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_uchar_t.
 */
#define ckd_size_t  ckd_uchar_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_shrt_t.
 */
#define ckd_size_t  ckd_shrt_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_ushrt_t.
 */
#define ckd_size_t  ckd_ushrt_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_int_t.
 */
#define ckd_size_t  ckd_int_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_uint_t.
 */
#define ckd_size_t  ckd_uint_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_long_t.
 */
#define ckd_size_t  ckd_long_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_ulong_t.
 */
#define ckd_size_t  ckd_ulong_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_llong_t.
 */
#define ckd_size_t  ckd_llong_t
#endif
#if !defined(ckd_size_t) && defined(SIZE_MAX) && SIZE_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_size_t
 * @brief Check integer type ckd_size_t is an alias to ckd_ullong_t.
 */
#define ckd_size_t  ckd_ullong_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == SCHAR_MAX && INTPTR_MIN == SCHAR_MIN
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_schar_t.
 */
#define ckd_intptr_t  ckd_schar_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == UCHAR_MAX && INTPTR_MIN == 0
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_uchar_t.
 */
#define ckd_intptr_t  ckd_uchar_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == SHRT_MAX && INTPTR_MIN == SHRT_MIN
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_shrt_t.
 */
#define ckd_intptr_t  ckd_shrt_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == USHRT_MAX && INTPTR_MIN == 0
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_ushrt_t.
 */
#define ckd_intptr_t  ckd_ushrt_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == INT_MAX && INTPTR_MIN == INT_MIN
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_int_t.
 */
#define ckd_intptr_t  ckd_int_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == UINT_MAX && INTPTR_MIN == 0
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_uint_t.
 */
#define ckd_intptr_t  ckd_uint_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == LONG_MAX && INTPTR_MIN == LONG_MIN
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_long_t.
 */
#define ckd_intptr_t  ckd_long_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == ULONG_MAX && INTPTR_MIN == 0
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_ulong_t.
 */
#define ckd_intptr_t  ckd_ulong_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == LLONG_MAX && INTPTR_MIN == LLONG_MIN
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_llong_t.
 */
#define ckd_intptr_t  ckd_llong_t
#endif
#if !defined(ckd_intptr_t) && defined(INTPTR_MAX) && INTPTR_MAX == ULLONG_MAX && INTPTR_MIN == 0
/**
 * @define ckd_intptr_t
 * @brief Check integer type ckd_intptr_t is an alias to ckd_ullong_t.
 */
#define ckd_intptr_t  ckd_ullong_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_schar_t.
 */
#define ckd_uintptr_t  ckd_schar_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_uchar_t.
 */
#define ckd_uintptr_t  ckd_uchar_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_shrt_t.
 */
#define ckd_uintptr_t  ckd_shrt_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_ushrt_t.
 */
#define ckd_uintptr_t  ckd_ushrt_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_int_t.
 */
#define ckd_uintptr_t  ckd_int_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_uint_t.
 */
#define ckd_uintptr_t  ckd_uint_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_long_t.
 */
#define ckd_uintptr_t  ckd_long_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_ulong_t.
 */
#define ckd_uintptr_t  ckd_ulong_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_llong_t.
 */
#define ckd_uintptr_t  ckd_llong_t
#endif
#if !defined(ckd_uintptr_t) && defined(UINTPTR_MAX) && UINTPTR_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uintptr_t
 * @brief Check integer type ckd_uintptr_t is an alias to ckd_ullong_t.
 */
#define ckd_uintptr_t  ckd_ullong_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == SCHAR_MAX && INT8_MIN == SCHAR_MIN
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_schar_t.
 */
#define ckd_int8_t  ckd_schar_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == UCHAR_MAX && INT8_MIN == 0
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_uchar_t.
 */
#define ckd_int8_t  ckd_uchar_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == SHRT_MAX && INT8_MIN == SHRT_MIN
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_shrt_t.
 */
#define ckd_int8_t  ckd_shrt_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == USHRT_MAX && INT8_MIN == 0
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_ushrt_t.
 */
#define ckd_int8_t  ckd_ushrt_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == INT_MAX && INT8_MIN == INT_MIN
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_int_t.
 */
#define ckd_int8_t  ckd_int_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == UINT_MAX && INT8_MIN == 0
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_uint_t.
 */
#define ckd_int8_t  ckd_uint_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == LONG_MAX && INT8_MIN == LONG_MIN
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_long_t.
 */
#define ckd_int8_t  ckd_long_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == ULONG_MAX && INT8_MIN == 0
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_ulong_t.
 */
#define ckd_int8_t  ckd_ulong_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == LLONG_MAX && INT8_MIN == LLONG_MIN
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_llong_t.
 */
#define ckd_int8_t  ckd_llong_t
#endif
#if !defined(ckd_int8_t) && defined(INT8_MAX) && INT8_MAX == ULLONG_MAX && INT8_MIN == 0
/**
 * @define ckd_int8_t
 * @brief Check integer type ckd_int8_t is an alias to ckd_ullong_t.
 */
#define ckd_int8_t  ckd_ullong_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_schar_t.
 */
#define ckd_uint8_t  ckd_schar_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_uchar_t.
 */
#define ckd_uint8_t  ckd_uchar_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_shrt_t.
 */
#define ckd_uint8_t  ckd_shrt_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint8_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_int_t.
 */
#define ckd_uint8_t  ckd_int_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_uint_t.
 */
#define ckd_uint8_t  ckd_uint_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_long_t.
 */
#define ckd_uint8_t  ckd_long_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_ulong_t.
 */
#define ckd_uint8_t  ckd_ulong_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_llong_t.
 */
#define ckd_uint8_t  ckd_llong_t
#endif
#if !defined(ckd_uint8_t) && defined(UINT8_MAX) && UINT8_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint8_t
 * @brief Check integer type ckd_uint8_t is an alias to ckd_ullong_t.
 */
#define ckd_uint8_t  ckd_ullong_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == SCHAR_MAX && INT_LEAST8_MIN == SCHAR_MIN
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_schar_t.
 */
#define ckd_int_least8_t  ckd_schar_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == UCHAR_MAX && INT_LEAST8_MIN == 0
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_uchar_t.
 */
#define ckd_int_least8_t  ckd_uchar_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == SHRT_MAX && INT_LEAST8_MIN == SHRT_MIN
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_shrt_t.
 */
#define ckd_int_least8_t  ckd_shrt_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == USHRT_MAX && INT_LEAST8_MIN == 0
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_ushrt_t.
 */
#define ckd_int_least8_t  ckd_ushrt_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == INT_MAX && INT_LEAST8_MIN == INT_MIN
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_int_t.
 */
#define ckd_int_least8_t  ckd_int_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == UINT_MAX && INT_LEAST8_MIN == 0
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_uint_t.
 */
#define ckd_int_least8_t  ckd_uint_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == LONG_MAX && INT_LEAST8_MIN == LONG_MIN
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_long_t.
 */
#define ckd_int_least8_t  ckd_long_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == ULONG_MAX && INT_LEAST8_MIN == 0
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_ulong_t.
 */
#define ckd_int_least8_t  ckd_ulong_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == LLONG_MAX && INT_LEAST8_MIN == LLONG_MIN
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_llong_t.
 */
#define ckd_int_least8_t  ckd_llong_t
#endif
#if !defined(ckd_int_least8_t) && defined(INT_LEAST8_MAX) && INT_LEAST8_MAX == ULLONG_MAX && INT_LEAST8_MIN == 0
/**
 * @define ckd_int_least8_t
 * @brief Check integer type ckd_int_least8_t is an alias to ckd_ullong_t.
 */
#define ckd_int_least8_t  ckd_ullong_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_schar_t.
 */
#define ckd_uint_least8_t  ckd_schar_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_uchar_t.
 */
#define ckd_uint_least8_t  ckd_uchar_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_shrt_t.
 */
#define ckd_uint_least8_t  ckd_shrt_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint_least8_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_int_t.
 */
#define ckd_uint_least8_t  ckd_int_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_uint_t.
 */
#define ckd_uint_least8_t  ckd_uint_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_long_t.
 */
#define ckd_uint_least8_t  ckd_long_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_ulong_t.
 */
#define ckd_uint_least8_t  ckd_ulong_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_llong_t.
 */
#define ckd_uint_least8_t  ckd_llong_t
#endif
#if !defined(ckd_uint_least8_t) && defined(UINT_LEAST8_MAX) && UINT_LEAST8_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint_least8_t
 * @brief Check integer type ckd_uint_least8_t is an alias to ckd_ullong_t.
 */
#define ckd_uint_least8_t  ckd_ullong_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == SCHAR_MAX && INT_FAST8_MIN == SCHAR_MIN
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_schar_t.
 */
#define ckd_int_fast8_t  ckd_schar_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == UCHAR_MAX && INT_FAST8_MIN == 0
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_uchar_t.
 */
#define ckd_int_fast8_t  ckd_uchar_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == SHRT_MAX && INT_FAST8_MIN == SHRT_MIN
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_shrt_t.
 */
#define ckd_int_fast8_t  ckd_shrt_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == USHRT_MAX && INT_FAST8_MIN == 0
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_ushrt_t.
 */
#define ckd_int_fast8_t  ckd_ushrt_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == INT_MAX && INT_FAST8_MIN == INT_MIN
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_int_t.
 */
#define ckd_int_fast8_t  ckd_int_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == UINT_MAX && INT_FAST8_MIN == 0
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_uint_t.
 */
#define ckd_int_fast8_t  ckd_uint_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == LONG_MAX && INT_FAST8_MIN == LONG_MIN
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_long_t.
 */
#define ckd_int_fast8_t  ckd_long_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == ULONG_MAX && INT_FAST8_MIN == 0
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_ulong_t.
 */
#define ckd_int_fast8_t  ckd_ulong_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == LLONG_MAX && INT_FAST8_MIN == LLONG_MIN
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_llong_t.
 */
#define ckd_int_fast8_t  ckd_llong_t
#endif
#if !defined(ckd_int_fast8_t) && defined(INT_FAST8_MAX) && INT_FAST8_MAX == ULLONG_MAX && INT_FAST8_MIN == 0
/**
 * @define ckd_int_fast8_t
 * @brief Check integer type ckd_int_fast8_t is an alias to ckd_ullong_t.
 */
#define ckd_int_fast8_t  ckd_ullong_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_schar_t.
 */
#define ckd_uint_fast8_t  ckd_schar_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_uchar_t.
 */
#define ckd_uint_fast8_t  ckd_uchar_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_shrt_t.
 */
#define ckd_uint_fast8_t  ckd_shrt_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint_fast8_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_int_t.
 */
#define ckd_uint_fast8_t  ckd_int_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_uint_t.
 */
#define ckd_uint_fast8_t  ckd_uint_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_long_t.
 */
#define ckd_uint_fast8_t  ckd_long_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_ulong_t.
 */
#define ckd_uint_fast8_t  ckd_ulong_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_llong_t.
 */
#define ckd_uint_fast8_t  ckd_llong_t
#endif
#if !defined(ckd_uint_fast8_t) && defined(UINT_FAST8_MAX) && UINT_FAST8_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint_fast8_t
 * @brief Check integer type ckd_uint_fast8_t is an alias to ckd_ullong_t.
 */
#define ckd_uint_fast8_t  ckd_ullong_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == SCHAR_MAX && INT16_MIN == SCHAR_MIN
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_schar_t.
 */
#define ckd_int16_t  ckd_schar_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == UCHAR_MAX && INT16_MIN == 0
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_uchar_t.
 */
#define ckd_int16_t  ckd_uchar_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == SHRT_MAX && INT16_MIN == SHRT_MIN
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_shrt_t.
 */
#define ckd_int16_t  ckd_shrt_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == USHRT_MAX && INT16_MIN == 0
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_ushrt_t.
 */
#define ckd_int16_t  ckd_ushrt_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == INT_MAX && INT16_MIN == INT_MIN
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_int_t.
 */
#define ckd_int16_t  ckd_int_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == UINT_MAX && INT16_MIN == 0
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_uint_t.
 */
#define ckd_int16_t  ckd_uint_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == LONG_MAX && INT16_MIN == LONG_MIN
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_long_t.
 */
#define ckd_int16_t  ckd_long_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == ULONG_MAX && INT16_MIN == 0
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_ulong_t.
 */
#define ckd_int16_t  ckd_ulong_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == LLONG_MAX && INT16_MIN == LLONG_MIN
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_llong_t.
 */
#define ckd_int16_t  ckd_llong_t
#endif
#if !defined(ckd_int16_t) && defined(INT16_MAX) && INT16_MAX == ULLONG_MAX && INT16_MIN == 0
/**
 * @define ckd_int16_t
 * @brief Check integer type ckd_int16_t is an alias to ckd_ullong_t.
 */
#define ckd_int16_t  ckd_ullong_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_schar_t.
 */
#define ckd_uint16_t  ckd_schar_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_uchar_t.
 */
#define ckd_uint16_t  ckd_uchar_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_shrt_t.
 */
#define ckd_uint16_t  ckd_shrt_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint16_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_int_t.
 */
#define ckd_uint16_t  ckd_int_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_uint_t.
 */
#define ckd_uint16_t  ckd_uint_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_long_t.
 */
#define ckd_uint16_t  ckd_long_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_ulong_t.
 */
#define ckd_uint16_t  ckd_ulong_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_llong_t.
 */
#define ckd_uint16_t  ckd_llong_t
#endif
#if !defined(ckd_uint16_t) && defined(UINT16_MAX) && UINT16_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint16_t
 * @brief Check integer type ckd_uint16_t is an alias to ckd_ullong_t.
 */
#define ckd_uint16_t  ckd_ullong_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == SCHAR_MAX && INT_LEAST16_MIN == SCHAR_MIN
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_schar_t.
 */
#define ckd_int_least16_t  ckd_schar_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == UCHAR_MAX && INT_LEAST16_MIN == 0
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_uchar_t.
 */
#define ckd_int_least16_t  ckd_uchar_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == SHRT_MAX && INT_LEAST16_MIN == SHRT_MIN
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_shrt_t.
 */
#define ckd_int_least16_t  ckd_shrt_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == USHRT_MAX && INT_LEAST16_MIN == 0
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_ushrt_t.
 */
#define ckd_int_least16_t  ckd_ushrt_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == INT_MAX && INT_LEAST16_MIN == INT_MIN
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_int_t.
 */
#define ckd_int_least16_t  ckd_int_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == UINT_MAX && INT_LEAST16_MIN == 0
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_uint_t.
 */
#define ckd_int_least16_t  ckd_uint_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == LONG_MAX && INT_LEAST16_MIN == LONG_MIN
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_long_t.
 */
#define ckd_int_least16_t  ckd_long_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == ULONG_MAX && INT_LEAST16_MIN == 0
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_ulong_t.
 */
#define ckd_int_least16_t  ckd_ulong_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == LLONG_MAX && INT_LEAST16_MIN == LLONG_MIN
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_llong_t.
 */
#define ckd_int_least16_t  ckd_llong_t
#endif
#if !defined(ckd_int_least16_t) && defined(INT_LEAST16_MAX) && INT_LEAST16_MAX == ULLONG_MAX && INT_LEAST16_MIN == 0
/**
 * @define ckd_int_least16_t
 * @brief Check integer type ckd_int_least16_t is an alias to ckd_ullong_t.
 */
#define ckd_int_least16_t  ckd_ullong_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_schar_t.
 */
#define ckd_uint_least16_t  ckd_schar_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_uchar_t.
 */
#define ckd_uint_least16_t  ckd_uchar_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_shrt_t.
 */
#define ckd_uint_least16_t  ckd_shrt_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint_least16_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_int_t.
 */
#define ckd_uint_least16_t  ckd_int_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_uint_t.
 */
#define ckd_uint_least16_t  ckd_uint_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_long_t.
 */
#define ckd_uint_least16_t  ckd_long_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_ulong_t.
 */
#define ckd_uint_least16_t  ckd_ulong_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_llong_t.
 */
#define ckd_uint_least16_t  ckd_llong_t
#endif
#if !defined(ckd_uint_least16_t) && defined(UINT_LEAST16_MAX) && UINT_LEAST16_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint_least16_t
 * @brief Check integer type ckd_uint_least16_t is an alias to ckd_ullong_t.
 */
#define ckd_uint_least16_t  ckd_ullong_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == SCHAR_MAX && INT_FAST16_MIN == SCHAR_MIN
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_schar_t.
 */
#define ckd_int_fast16_t  ckd_schar_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == UCHAR_MAX && INT_FAST16_MIN == 0
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_uchar_t.
 */
#define ckd_int_fast16_t  ckd_uchar_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == SHRT_MAX && INT_FAST16_MIN == SHRT_MIN
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_shrt_t.
 */
#define ckd_int_fast16_t  ckd_shrt_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == USHRT_MAX && INT_FAST16_MIN == 0
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_ushrt_t.
 */
#define ckd_int_fast16_t  ckd_ushrt_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == INT_MAX && INT_FAST16_MIN == INT_MIN
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_int_t.
 */
#define ckd_int_fast16_t  ckd_int_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == UINT_MAX && INT_FAST16_MIN == 0
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_uint_t.
 */
#define ckd_int_fast16_t  ckd_uint_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == LONG_MAX && INT_FAST16_MIN == LONG_MIN
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_long_t.
 */
#define ckd_int_fast16_t  ckd_long_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == ULONG_MAX && INT_FAST16_MIN == 0
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_ulong_t.
 */
#define ckd_int_fast16_t  ckd_ulong_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == LLONG_MAX && INT_FAST16_MIN == LLONG_MIN
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_llong_t.
 */
#define ckd_int_fast16_t  ckd_llong_t
#endif
#if !defined(ckd_int_fast16_t) && defined(INT_FAST16_MAX) && INT_FAST16_MAX == ULLONG_MAX && INT_FAST16_MIN == 0
/**
 * @define ckd_int_fast16_t
 * @brief Check integer type ckd_int_fast16_t is an alias to ckd_ullong_t.
 */
#define ckd_int_fast16_t  ckd_ullong_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_schar_t.
 */
#define ckd_uint_fast16_t  ckd_schar_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_uchar_t.
 */
#define ckd_uint_fast16_t  ckd_uchar_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_shrt_t.
 */
#define ckd_uint_fast16_t  ckd_shrt_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint_fast16_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_int_t.
 */
#define ckd_uint_fast16_t  ckd_int_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_uint_t.
 */
#define ckd_uint_fast16_t  ckd_uint_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_long_t.
 */
#define ckd_uint_fast16_t  ckd_long_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_ulong_t.
 */
#define ckd_uint_fast16_t  ckd_ulong_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_llong_t.
 */
#define ckd_uint_fast16_t  ckd_llong_t
#endif
#if !defined(ckd_uint_fast16_t) && defined(UINT_FAST16_MAX) && UINT_FAST16_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint_fast16_t
 * @brief Check integer type ckd_uint_fast16_t is an alias to ckd_ullong_t.
 */
#define ckd_uint_fast16_t  ckd_ullong_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == SCHAR_MAX && INT32_MIN == SCHAR_MIN
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_schar_t.
 */
#define ckd_int32_t  ckd_schar_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == UCHAR_MAX && INT32_MIN == 0
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_uchar_t.
 */
#define ckd_int32_t  ckd_uchar_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == SHRT_MAX && INT32_MIN == SHRT_MIN
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_shrt_t.
 */
#define ckd_int32_t  ckd_shrt_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == USHRT_MAX && INT32_MIN == 0
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_ushrt_t.
 */
#define ckd_int32_t  ckd_ushrt_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == INT_MAX && INT32_MIN == INT_MIN
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_int_t.
 */
#define ckd_int32_t  ckd_int_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == UINT_MAX && INT32_MIN == 0
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_uint_t.
 */
#define ckd_int32_t  ckd_uint_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == LONG_MAX && INT32_MIN == LONG_MIN
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_long_t.
 */
#define ckd_int32_t  ckd_long_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == ULONG_MAX && INT32_MIN == 0
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_ulong_t.
 */
#define ckd_int32_t  ckd_ulong_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == LLONG_MAX && INT32_MIN == LLONG_MIN
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_llong_t.
 */
#define ckd_int32_t  ckd_llong_t
#endif
#if !defined(ckd_int32_t) && defined(INT32_MAX) && INT32_MAX == ULLONG_MAX && INT32_MIN == 0
/**
 * @define ckd_int32_t
 * @brief Check integer type ckd_int32_t is an alias to ckd_ullong_t.
 */
#define ckd_int32_t  ckd_ullong_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_schar_t.
 */
#define ckd_uint32_t  ckd_schar_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_uchar_t.
 */
#define ckd_uint32_t  ckd_uchar_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_shrt_t.
 */
#define ckd_uint32_t  ckd_shrt_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint32_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_int_t.
 */
#define ckd_uint32_t  ckd_int_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_uint_t.
 */
#define ckd_uint32_t  ckd_uint_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_long_t.
 */
#define ckd_uint32_t  ckd_long_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_ulong_t.
 */
#define ckd_uint32_t  ckd_ulong_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_llong_t.
 */
#define ckd_uint32_t  ckd_llong_t
#endif
#if !defined(ckd_uint32_t) && defined(UINT32_MAX) && UINT32_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint32_t
 * @brief Check integer type ckd_uint32_t is an alias to ckd_ullong_t.
 */
#define ckd_uint32_t  ckd_ullong_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == SCHAR_MAX && INT_LEAST32_MIN == SCHAR_MIN
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_schar_t.
 */
#define ckd_int_least32_t  ckd_schar_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == UCHAR_MAX && INT_LEAST32_MIN == 0
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_uchar_t.
 */
#define ckd_int_least32_t  ckd_uchar_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == SHRT_MAX && INT_LEAST32_MIN == SHRT_MIN
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_shrt_t.
 */
#define ckd_int_least32_t  ckd_shrt_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == USHRT_MAX && INT_LEAST32_MIN == 0
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_ushrt_t.
 */
#define ckd_int_least32_t  ckd_ushrt_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == INT_MAX && INT_LEAST32_MIN == INT_MIN
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_int_t.
 */
#define ckd_int_least32_t  ckd_int_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == UINT_MAX && INT_LEAST32_MIN == 0
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_uint_t.
 */
#define ckd_int_least32_t  ckd_uint_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == LONG_MAX && INT_LEAST32_MIN == LONG_MIN
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_long_t.
 */
#define ckd_int_least32_t  ckd_long_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == ULONG_MAX && INT_LEAST32_MIN == 0
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_ulong_t.
 */
#define ckd_int_least32_t  ckd_ulong_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == LLONG_MAX && INT_LEAST32_MIN == LLONG_MIN
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_llong_t.
 */
#define ckd_int_least32_t  ckd_llong_t
#endif
#if !defined(ckd_int_least32_t) && defined(INT_LEAST32_MAX) && INT_LEAST32_MAX == ULLONG_MAX && INT_LEAST32_MIN == 0
/**
 * @define ckd_int_least32_t
 * @brief Check integer type ckd_int_least32_t is an alias to ckd_ullong_t.
 */
#define ckd_int_least32_t  ckd_ullong_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_schar_t.
 */
#define ckd_uint_least32_t  ckd_schar_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_uchar_t.
 */
#define ckd_uint_least32_t  ckd_uchar_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_shrt_t.
 */
#define ckd_uint_least32_t  ckd_shrt_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint_least32_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_int_t.
 */
#define ckd_uint_least32_t  ckd_int_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_uint_t.
 */
#define ckd_uint_least32_t  ckd_uint_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_long_t.
 */
#define ckd_uint_least32_t  ckd_long_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_ulong_t.
 */
#define ckd_uint_least32_t  ckd_ulong_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_llong_t.
 */
#define ckd_uint_least32_t  ckd_llong_t
#endif
#if !defined(ckd_uint_least32_t) && defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint_least32_t
 * @brief Check integer type ckd_uint_least32_t is an alias to ckd_ullong_t.
 */
#define ckd_uint_least32_t  ckd_ullong_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == SCHAR_MAX && INT_FAST32_MIN == SCHAR_MIN
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_schar_t.
 */
#define ckd_int_fast32_t  ckd_schar_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == UCHAR_MAX && INT_FAST32_MIN == 0
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_uchar_t.
 */
#define ckd_int_fast32_t  ckd_uchar_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == SHRT_MAX && INT_FAST32_MIN == SHRT_MIN
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_shrt_t.
 */
#define ckd_int_fast32_t  ckd_shrt_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == USHRT_MAX && INT_FAST32_MIN == 0
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_ushrt_t.
 */
#define ckd_int_fast32_t  ckd_ushrt_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == INT_MAX && INT_FAST32_MIN == INT_MIN
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_int_t.
 */
#define ckd_int_fast32_t  ckd_int_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == UINT_MAX && INT_FAST32_MIN == 0
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_uint_t.
 */
#define ckd_int_fast32_t  ckd_uint_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == LONG_MAX && INT_FAST32_MIN == LONG_MIN
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_long_t.
 */
#define ckd_int_fast32_t  ckd_long_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == ULONG_MAX && INT_FAST32_MIN == 0
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_ulong_t.
 */
#define ckd_int_fast32_t  ckd_ulong_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == LLONG_MAX && INT_FAST32_MIN == LLONG_MIN
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_llong_t.
 */
#define ckd_int_fast32_t  ckd_llong_t
#endif
#if !defined(ckd_int_fast32_t) && defined(INT_FAST32_MAX) && INT_FAST32_MAX == ULLONG_MAX && INT_FAST32_MIN == 0
/**
 * @define ckd_int_fast32_t
 * @brief Check integer type ckd_int_fast32_t is an alias to ckd_ullong_t.
 */
#define ckd_int_fast32_t  ckd_ullong_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_schar_t.
 */
#define ckd_uint_fast32_t  ckd_schar_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_uchar_t.
 */
#define ckd_uint_fast32_t  ckd_uchar_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_shrt_t.
 */
#define ckd_uint_fast32_t  ckd_shrt_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint_fast32_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_int_t.
 */
#define ckd_uint_fast32_t  ckd_int_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_uint_t.
 */
#define ckd_uint_fast32_t  ckd_uint_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_long_t.
 */
#define ckd_uint_fast32_t  ckd_long_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_ulong_t.
 */
#define ckd_uint_fast32_t  ckd_ulong_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_llong_t.
 */
#define ckd_uint_fast32_t  ckd_llong_t
#endif
#if !defined(ckd_uint_fast32_t) && defined(UINT_FAST32_MAX) && UINT_FAST32_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint_fast32_t
 * @brief Check integer type ckd_uint_fast32_t is an alias to ckd_ullong_t.
 */
#define ckd_uint_fast32_t  ckd_ullong_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == SCHAR_MAX && INT64_MIN == SCHAR_MIN
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_schar_t.
 */
#define ckd_int64_t  ckd_schar_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == UCHAR_MAX && INT64_MIN == 0
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_uchar_t.
 */
#define ckd_int64_t  ckd_uchar_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == SHRT_MAX && INT64_MIN == SHRT_MIN
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_shrt_t.
 */
#define ckd_int64_t  ckd_shrt_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == USHRT_MAX && INT64_MIN == 0
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_ushrt_t.
 */
#define ckd_int64_t  ckd_ushrt_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == INT_MAX && INT64_MIN == INT_MIN
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_int_t.
 */
#define ckd_int64_t  ckd_int_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == UINT_MAX && INT64_MIN == 0
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_uint_t.
 */
#define ckd_int64_t  ckd_uint_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == LONG_MAX && INT64_MIN == LONG_MIN
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_long_t.
 */
#define ckd_int64_t  ckd_long_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == ULONG_MAX && INT64_MIN == 0
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_ulong_t.
 */
#define ckd_int64_t  ckd_ulong_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == LLONG_MAX && INT64_MIN == LLONG_MIN
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_llong_t.
 */
#define ckd_int64_t  ckd_llong_t
#endif
#if !defined(ckd_int64_t) && defined(INT64_MAX) && INT64_MAX == ULLONG_MAX && INT64_MIN == 0
/**
 * @define ckd_int64_t
 * @brief Check integer type ckd_int64_t is an alias to ckd_ullong_t.
 */
#define ckd_int64_t  ckd_ullong_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_schar_t.
 */
#define ckd_uint64_t  ckd_schar_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_uchar_t.
 */
#define ckd_uint64_t  ckd_uchar_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_shrt_t.
 */
#define ckd_uint64_t  ckd_shrt_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint64_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_int_t.
 */
#define ckd_uint64_t  ckd_int_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_uint_t.
 */
#define ckd_uint64_t  ckd_uint_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_long_t.
 */
#define ckd_uint64_t  ckd_long_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_ulong_t.
 */
#define ckd_uint64_t  ckd_ulong_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_llong_t.
 */
#define ckd_uint64_t  ckd_llong_t
#endif
#if !defined(ckd_uint64_t) && defined(UINT64_MAX) && UINT64_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint64_t
 * @brief Check integer type ckd_uint64_t is an alias to ckd_ullong_t.
 */
#define ckd_uint64_t  ckd_ullong_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == SCHAR_MAX && INT_LEAST64_MIN == SCHAR_MIN
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_schar_t.
 */
#define ckd_int_least64_t  ckd_schar_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == UCHAR_MAX && INT_LEAST64_MIN == 0
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_uchar_t.
 */
#define ckd_int_least64_t  ckd_uchar_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == SHRT_MAX && INT_LEAST64_MIN == SHRT_MIN
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_shrt_t.
 */
#define ckd_int_least64_t  ckd_shrt_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == USHRT_MAX && INT_LEAST64_MIN == 0
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_ushrt_t.
 */
#define ckd_int_least64_t  ckd_ushrt_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == INT_MAX && INT_LEAST64_MIN == INT_MIN
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_int_t.
 */
#define ckd_int_least64_t  ckd_int_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == UINT_MAX && INT_LEAST64_MIN == 0
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_uint_t.
 */
#define ckd_int_least64_t  ckd_uint_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == LONG_MAX && INT_LEAST64_MIN == LONG_MIN
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_long_t.
 */
#define ckd_int_least64_t  ckd_long_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == ULONG_MAX && INT_LEAST64_MIN == 0
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_ulong_t.
 */
#define ckd_int_least64_t  ckd_ulong_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == LLONG_MAX && INT_LEAST64_MIN == LLONG_MIN
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_llong_t.
 */
#define ckd_int_least64_t  ckd_llong_t
#endif
#if !defined(ckd_int_least64_t) && defined(INT_LEAST64_MAX) && INT_LEAST64_MAX == ULLONG_MAX && INT_LEAST64_MIN == 0
/**
 * @define ckd_int_least64_t
 * @brief Check integer type ckd_int_least64_t is an alias to ckd_ullong_t.
 */
#define ckd_int_least64_t  ckd_ullong_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_schar_t.
 */
#define ckd_uint_least64_t  ckd_schar_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_uchar_t.
 */
#define ckd_uint_least64_t  ckd_uchar_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_shrt_t.
 */
#define ckd_uint_least64_t  ckd_shrt_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint_least64_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_int_t.
 */
#define ckd_uint_least64_t  ckd_int_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_uint_t.
 */
#define ckd_uint_least64_t  ckd_uint_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_long_t.
 */
#define ckd_uint_least64_t  ckd_long_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_ulong_t.
 */
#define ckd_uint_least64_t  ckd_ulong_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_llong_t.
 */
#define ckd_uint_least64_t  ckd_llong_t
#endif
#if !defined(ckd_uint_least64_t) && defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint_least64_t
 * @brief Check integer type ckd_uint_least64_t is an alias to ckd_ullong_t.
 */
#define ckd_uint_least64_t  ckd_ullong_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == SCHAR_MAX && INT_FAST64_MIN == SCHAR_MIN
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_schar_t.
 */
#define ckd_int_fast64_t  ckd_schar_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == UCHAR_MAX && INT_FAST64_MIN == 0
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_uchar_t.
 */
#define ckd_int_fast64_t  ckd_uchar_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == SHRT_MAX && INT_FAST64_MIN == SHRT_MIN
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_shrt_t.
 */
#define ckd_int_fast64_t  ckd_shrt_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == USHRT_MAX && INT_FAST64_MIN == 0
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_ushrt_t.
 */
#define ckd_int_fast64_t  ckd_ushrt_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == INT_MAX && INT_FAST64_MIN == INT_MIN
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_int_t.
 */
#define ckd_int_fast64_t  ckd_int_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == UINT_MAX && INT_FAST64_MIN == 0
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_uint_t.
 */
#define ckd_int_fast64_t  ckd_uint_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == LONG_MAX && INT_FAST64_MIN == LONG_MIN
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_long_t.
 */
#define ckd_int_fast64_t  ckd_long_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == ULONG_MAX && INT_FAST64_MIN == 0
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_ulong_t.
 */
#define ckd_int_fast64_t  ckd_ulong_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == LLONG_MAX && INT_FAST64_MIN == LLONG_MIN
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_llong_t.
 */
#define ckd_int_fast64_t  ckd_llong_t
#endif
#if !defined(ckd_int_fast64_t) && defined(INT_FAST64_MAX) && INT_FAST64_MAX == ULLONG_MAX && INT_FAST64_MIN == 0
/**
 * @define ckd_int_fast64_t
 * @brief Check integer type ckd_int_fast64_t is an alias to ckd_ullong_t.
 */
#define ckd_int_fast64_t  ckd_ullong_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == SCHAR_MAX && 0 == SCHAR_MIN
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_schar_t.
 */
#define ckd_uint_fast64_t  ckd_schar_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == UCHAR_MAX && 0 == 0
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_uchar_t.
 */
#define ckd_uint_fast64_t  ckd_uchar_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == SHRT_MAX && 0 == SHRT_MIN
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_shrt_t.
 */
#define ckd_uint_fast64_t  ckd_shrt_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == USHRT_MAX && 0 == 0
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_ushrt_t.
 */
#define ckd_uint_fast64_t  ckd_ushrt_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == INT_MAX && 0 == INT_MIN
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_int_t.
 */
#define ckd_uint_fast64_t  ckd_int_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == UINT_MAX && 0 == 0
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_uint_t.
 */
#define ckd_uint_fast64_t  ckd_uint_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == LONG_MAX && 0 == LONG_MIN
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_long_t.
 */
#define ckd_uint_fast64_t  ckd_long_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == ULONG_MAX && 0 == 0
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_ulong_t.
 */
#define ckd_uint_fast64_t  ckd_ulong_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == LLONG_MAX && 0 == LLONG_MIN
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_llong_t.
 */
#define ckd_uint_fast64_t  ckd_llong_t
#endif
#if !defined(ckd_uint_fast64_t) && defined(UINT_FAST64_MAX) && UINT_FAST64_MAX == ULLONG_MAX && 0 == 0
/**
 * @define ckd_uint_fast64_t
 * @brief Check integer type ckd_uint_fast64_t is an alias to ckd_ullong_t.
 */
#define ckd_uint_fast64_t  ckd_ullong_t
#endif

// ]]]
// Check integer accessors [[[

/**
 * @define bool ckd_overflow(ckd_type_t x);
 * @brief If ckd_type is a checked integer type, the ckd_overflow macro indicates if x was computed
using an operation that overflowed or suffered truncation or misinterpretation of sign.
 * @param x One of checked integer types.
 * @return The ckd_overflow macro returns true if overflow, truncation, or misinterpretation of sign
 * occurred when x was computed and false otherwise.
 */
#define ckd_overflow(x)  ((x)._oveRflow)

/**
 * @define type ckd_value(ckd_type x);
 * @brief If ckd_type is a checked integer type, the ckd_value macro indicates the value of x.
 * If the overflow flag is set to false, the value correctly represents the mathematical value of whatever
 * operation(s) produced x. Otherwise, the value of x is converted as if by assignment to the type of x.
 * @param x One of checked integer types.
 * @return The ckd_value macro returns the value of x.
 */
#define ckd_value(x)     ((x)._vaLue)

// ]]]
// ckd_mk_* functions [[[

/**
 * @brief These functions construct a checked integer type ckd_schar_t
 * given an unchecked integer of type signed char and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_schar_t ckd_mk_schar_t(signed char value, bool overflow) {
    const ckd_schar_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uchar_t
 * given an unchecked integer of type unsigned char and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uchar_t ckd_mk_uchar_t(unsigned char value, bool overflow) {
    const ckd_uchar_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_shrt_t
 * given an unchecked integer of type short and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_shrt_t ckd_mk_shrt_t(short value, bool overflow) {
    const ckd_shrt_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_ushrt_t
 * given an unchecked integer of type unsigned short and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_ushrt_t ckd_mk_ushrt_t(unsigned short value, bool overflow) {
    const ckd_ushrt_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int_t
 * given an unchecked integer of type int and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int_t ckd_mk_int_t(int value, bool overflow) {
    const ckd_int_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint_t
 * given an unchecked integer of type unsigned int and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint_t ckd_mk_uint_t(unsigned int value, bool overflow) {
    const ckd_uint_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_long_t
 * given an unchecked integer of type long and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_long_t ckd_mk_long_t(long value, bool overflow) {
    const ckd_long_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_ulong_t
 * given an unchecked integer of type unsigned long and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_ulong_t ckd_mk_ulong_t(unsigned long value, bool overflow) {
    const ckd_ulong_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_llong_t
 * given an unchecked integer of type long long and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_llong_t ckd_mk_llong_t(long long value, bool overflow) {
    const ckd_llong_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_ullong_t
 * given an unchecked integer of type unsigned long long and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_ullong_t ckd_mk_ullong_t(unsigned long long value, bool overflow) {
    const ckd_ullong_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int128_t
 * given an unchecked integer of type __int128 and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int128_t ckd_mk_int128_t(__int128 value, bool overflow) {
    const ckd_int128_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint128_t
 * given an unchecked integer of type unsigned __int128 and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint128_t ckd_mk_uint128_t(unsigned __int128 value, bool overflow) {
    const ckd_uint128_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_intmax_t
 * given an unchecked integer of type intmax_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_intmax_t ckd_mk_intmax_t(intmax_t value, bool overflow) {
    const ckd_intmax_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uintmax_t
 * given an unchecked integer of type uintmax_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uintmax_t ckd_mk_uintmax_t(uintmax_t value, bool overflow) {
    const ckd_uintmax_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_size_t
 * given an unchecked integer of type size_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_size_t ckd_mk_size_t(size_t value, bool overflow) {
    const ckd_size_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_intptr_t
 * given an unchecked integer of type intptr_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_intptr_t ckd_mk_intptr_t(intptr_t value, bool overflow) {
    const ckd_intptr_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uintptr_t
 * given an unchecked integer of type uintptr_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uintptr_t ckd_mk_uintptr_t(uintptr_t value, bool overflow) {
    const ckd_uintptr_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int8_t
 * given an unchecked integer of type int8_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int8_t ckd_mk_int8_t(int8_t value, bool overflow) {
    const ckd_int8_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint8_t
 * given an unchecked integer of type uint8_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint8_t ckd_mk_uint8_t(uint8_t value, bool overflow) {
    const ckd_uint8_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int_least8_t
 * given an unchecked integer of type int_least8_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int_least8_t ckd_mk_int_least8_t(int_least8_t value, bool overflow) {
    const ckd_int_least8_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint_least8_t
 * given an unchecked integer of type uint_least8_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint_least8_t ckd_mk_uint_least8_t(uint_least8_t value, bool overflow) {
    const ckd_uint_least8_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int_fast8_t
 * given an unchecked integer of type int_fast8_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int_fast8_t ckd_mk_int_fast8_t(int_fast8_t value, bool overflow) {
    const ckd_int_fast8_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint_fast8_t
 * given an unchecked integer of type uint_fast8_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint_fast8_t ckd_mk_uint_fast8_t(uint_fast8_t value, bool overflow) {
    const ckd_uint_fast8_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int16_t
 * given an unchecked integer of type int16_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int16_t ckd_mk_int16_t(int16_t value, bool overflow) {
    const ckd_int16_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint16_t
 * given an unchecked integer of type uint16_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint16_t ckd_mk_uint16_t(uint16_t value, bool overflow) {
    const ckd_uint16_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int_least16_t
 * given an unchecked integer of type int_least16_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int_least16_t ckd_mk_int_least16_t(int_least16_t value, bool overflow) {
    const ckd_int_least16_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint_least16_t
 * given an unchecked integer of type uint_least16_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint_least16_t ckd_mk_uint_least16_t(uint_least16_t value, bool overflow) {
    const ckd_uint_least16_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int_fast16_t
 * given an unchecked integer of type int_fast16_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int_fast16_t ckd_mk_int_fast16_t(int_fast16_t value, bool overflow) {
    const ckd_int_fast16_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint_fast16_t
 * given an unchecked integer of type uint_fast16_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint_fast16_t ckd_mk_uint_fast16_t(uint_fast16_t value, bool overflow) {
    const ckd_uint_fast16_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int32_t
 * given an unchecked integer of type int32_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int32_t ckd_mk_int32_t(int32_t value, bool overflow) {
    const ckd_int32_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint32_t
 * given an unchecked integer of type uint32_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint32_t ckd_mk_uint32_t(uint32_t value, bool overflow) {
    const ckd_uint32_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int_least32_t
 * given an unchecked integer of type int_least32_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int_least32_t ckd_mk_int_least32_t(int_least32_t value, bool overflow) {
    const ckd_int_least32_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint_least32_t
 * given an unchecked integer of type uint_least32_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint_least32_t ckd_mk_uint_least32_t(uint_least32_t value, bool overflow) {
    const ckd_uint_least32_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int_fast32_t
 * given an unchecked integer of type int_fast32_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int_fast32_t ckd_mk_int_fast32_t(int_fast32_t value, bool overflow) {
    const ckd_int_fast32_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint_fast32_t
 * given an unchecked integer of type uint_fast32_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint_fast32_t ckd_mk_uint_fast32_t(uint_fast32_t value, bool overflow) {
    const ckd_uint_fast32_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int64_t
 * given an unchecked integer of type int64_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int64_t ckd_mk_int64_t(int64_t value, bool overflow) {
    const ckd_int64_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint64_t
 * given an unchecked integer of type uint64_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint64_t ckd_mk_uint64_t(uint64_t value, bool overflow) {
    const ckd_uint64_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int_least64_t
 * given an unchecked integer of type int_least64_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int_least64_t ckd_mk_int_least64_t(int_least64_t value, bool overflow) {
    const ckd_int_least64_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint_least64_t
 * given an unchecked integer of type uint_least64_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint_least64_t ckd_mk_uint_least64_t(uint_least64_t value, bool overflow) {
    const ckd_uint_least64_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_int_fast64_t
 * given an unchecked integer of type int_fast64_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_int_fast64_t ckd_mk_int_fast64_t(int_fast64_t value, bool overflow) {
    const ckd_int_fast64_t tmp = {value, overflow}; return tmp;
}


/**
 * @brief These functions construct a checked integer type ckd_uint_fast64_t
 * given an unchecked integer of type uint_fast64_t and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_uint_fast64_t ckd_mk_uint_fast64_t(uint_fast64_t value, bool overflow) {
    const ckd_uint_fast64_t tmp = {value, overflow}; return tmp;
}

// ]]]
// Macro helpers [[[

struct _ckd_invalid_;
void _ckd_invalid(struct _ckd_invalid_);

_ckd_funcconst _ckd_schar _ckd_value_cschar(_ckd_cschar v) { return ckd_value(v); }
_ckd_funcconst _ckd_schar _ckd_value_schar(_ckd_schar v) { return v; }
_ckd_funcconst bool _ckd_overflow_cschar(_ckd_cschar v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_schar(_ckd_schar v) { (void)v; return 0; }
_ckd_funcconst _ckd_uchar _ckd_value_cuchar(_ckd_cuchar v) { return ckd_value(v); }
_ckd_funcconst _ckd_uchar _ckd_value_uchar(_ckd_uchar v) { return v; }
_ckd_funcconst bool _ckd_overflow_cuchar(_ckd_cuchar v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_uchar(_ckd_uchar v) { (void)v; return 0; }
_ckd_funcconst _ckd_shrt _ckd_value_cshrt(_ckd_cshrt v) { return ckd_value(v); }
_ckd_funcconst _ckd_shrt _ckd_value_shrt(_ckd_shrt v) { return v; }
_ckd_funcconst bool _ckd_overflow_cshrt(_ckd_cshrt v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_shrt(_ckd_shrt v) { (void)v; return 0; }
_ckd_funcconst _ckd_ushrt _ckd_value_cushrt(_ckd_cushrt v) { return ckd_value(v); }
_ckd_funcconst _ckd_ushrt _ckd_value_ushrt(_ckd_ushrt v) { return v; }
_ckd_funcconst bool _ckd_overflow_cushrt(_ckd_cushrt v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_ushrt(_ckd_ushrt v) { (void)v; return 0; }
_ckd_funcconst _ckd_int _ckd_value_cint(_ckd_cint v) { return ckd_value(v); }
_ckd_funcconst _ckd_int _ckd_value_int(_ckd_int v) { return v; }
_ckd_funcconst bool _ckd_overflow_cint(_ckd_cint v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_int(_ckd_int v) { (void)v; return 0; }
_ckd_funcconst _ckd_uint _ckd_value_cuint(_ckd_cuint v) { return ckd_value(v); }
_ckd_funcconst _ckd_uint _ckd_value_uint(_ckd_uint v) { return v; }
_ckd_funcconst bool _ckd_overflow_cuint(_ckd_cuint v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_uint(_ckd_uint v) { (void)v; return 0; }
_ckd_funcconst _ckd_long _ckd_value_clong(_ckd_clong v) { return ckd_value(v); }
_ckd_funcconst _ckd_long _ckd_value_long(_ckd_long v) { return v; }
_ckd_funcconst bool _ckd_overflow_clong(_ckd_clong v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_long(_ckd_long v) { (void)v; return 0; }
_ckd_funcconst _ckd_ulong _ckd_value_culong(_ckd_culong v) { return ckd_value(v); }
_ckd_funcconst _ckd_ulong _ckd_value_ulong(_ckd_ulong v) { return v; }
_ckd_funcconst bool _ckd_overflow_culong(_ckd_culong v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_ulong(_ckd_ulong v) { (void)v; return 0; }
_ckd_funcconst _ckd_llong _ckd_value_cllong(_ckd_cllong v) { return ckd_value(v); }
_ckd_funcconst _ckd_llong _ckd_value_llong(_ckd_llong v) { return v; }
_ckd_funcconst bool _ckd_overflow_cllong(_ckd_cllong v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_llong(_ckd_llong v) { (void)v; return 0; }
_ckd_funcconst _ckd_ullong _ckd_value_cullong(_ckd_cullong v) { return ckd_value(v); }
_ckd_funcconst _ckd_ullong _ckd_value_ullong(_ckd_ullong v) { return v; }
_ckd_funcconst bool _ckd_overflow_cullong(_ckd_cullong v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_ullong(_ckd_ullong v) { (void)v; return 0; }
_ckd_funcconst _ckd_int128 _ckd_value_cint128(_ckd_cint128 v) { return ckd_value(v); }
_ckd_funcconst _ckd_int128 _ckd_value_int128(_ckd_int128 v) { return v; }
_ckd_funcconst bool _ckd_overflow_cint128(_ckd_cint128 v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_int128(_ckd_int128 v) { (void)v; return 0; }
_ckd_funcconst _ckd_uint128 _ckd_value_cuint128(_ckd_cuint128 v) { return ckd_value(v); }
_ckd_funcconst _ckd_uint128 _ckd_value_uint128(_ckd_uint128 v) { return v; }
_ckd_funcconst bool _ckd_overflow_cuint128(_ckd_cuint128 v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_uint128(_ckd_uint128 v) { (void)v; return 0; }

/**
 * @define _ckd_value(X)
 * @brief For any basic type returns it's value.
 * For any ckd_*_t type returns ckd_value(X).
 * @param X Any integer type or checked integer type.
 * @return Value of the integer or the value hold inside checked integer type.
 */
#define _ckd_value(X) \
        _Generic((X), \
        _ckd_cschar: _ckd_value_cschar, \
        _ckd_schar:  _ckd_value_schar, \
        _ckd_cuchar: _ckd_value_cuchar, \
        _ckd_uchar:  _ckd_value_uchar, \
        _ckd_cshrt: _ckd_value_cshrt, \
        _ckd_shrt:  _ckd_value_shrt, \
        _ckd_cushrt: _ckd_value_cushrt, \
        _ckd_ushrt:  _ckd_value_ushrt, \
        _ckd_cint: _ckd_value_cint, \
        _ckd_int:  _ckd_value_int, \
        _ckd_cuint: _ckd_value_cuint, \
        _ckd_uint:  _ckd_value_uint, \
        _ckd_clong: _ckd_value_clong, \
        _ckd_long:  _ckd_value_long, \
        _ckd_culong: _ckd_value_culong, \
        _ckd_ulong:  _ckd_value_ulong, \
        _ckd_cllong: _ckd_value_cllong, \
        _ckd_llong:  _ckd_value_llong, \
        _ckd_cullong: _ckd_value_cullong, \
        _ckd_ullong:  _ckd_value_ullong, \
        _ckd_cint128: _ckd_value_cint128, \
        _ckd_int128:  _ckd_value_int128, \
        _ckd_cuint128: _ckd_value_cuint128, \
        _ckd_uint128:  _ckd_value_uint128)(X)

/**
 * @define _ckd_overflow(X)
 * @param X Any integer type or checked integer type.
 * @return 0 for integer types, the overflow flat for checked integer types.
 */
#define _ckd_overflow(X) \
        _Generic((X), \
        _ckd_cschar: _ckd_overflow_cschar, \
        _ckd_schar:  _ckd_overflow_schar, \
        _ckd_cuchar: _ckd_overflow_cuchar, \
        _ckd_uchar:  _ckd_overflow_uchar, \
        _ckd_cshrt: _ckd_overflow_cshrt, \
        _ckd_shrt:  _ckd_overflow_shrt, \
        _ckd_cushrt: _ckd_overflow_cushrt, \
        _ckd_ushrt:  _ckd_overflow_ushrt, \
        _ckd_cint: _ckd_overflow_cint, \
        _ckd_int:  _ckd_overflow_int, \
        _ckd_cuint: _ckd_overflow_cuint, \
        _ckd_uint:  _ckd_overflow_uint, \
        _ckd_clong: _ckd_overflow_clong, \
        _ckd_long:  _ckd_overflow_long, \
        _ckd_culong: _ckd_overflow_culong, \
        _ckd_ulong:  _ckd_overflow_ulong, \
        _ckd_cllong: _ckd_overflow_cllong, \
        _ckd_llong:  _ckd_overflow_llong, \
        _ckd_cullong: _ckd_overflow_cullong, \
        _ckd_ullong:  _ckd_overflow_ullong, \
        _ckd_cint128: _ckd_overflow_cint128, \
        _ckd_int128:  _ckd_overflow_int128, \
        _ckd_cuint128: _ckd_overflow_cuint128, \
        _ckd_uint128:  _ckd_overflow_uint128)(X)

/**
 * @define _ckd_getctype(X)
 * @param X Any integer type or checked integer type.
 * @return ckd_mk_TYPE_t function pointer type associated with _ckd_value(X).
 * @see _ckd_value
 */
#define _ckd_getctype(X) \
    _Generic((X), \
    _ckd_schar:  ckd_mk_schar_t, \
    _ckd_cschar: ckd_mk_schar_t, \
    _ckd_uchar:  ckd_mk_uchar_t, \
    _ckd_cuchar: ckd_mk_uchar_t, \
    _ckd_shrt:  ckd_mk_shrt_t, \
    _ckd_cshrt: ckd_mk_shrt_t, \
    _ckd_ushrt:  ckd_mk_ushrt_t, \
    _ckd_cushrt: ckd_mk_ushrt_t, \
    _ckd_int:  ckd_mk_int_t, \
    _ckd_cint: ckd_mk_int_t, \
    _ckd_uint:  ckd_mk_uint_t, \
    _ckd_cuint: ckd_mk_uint_t, \
    _ckd_long:  ckd_mk_long_t, \
    _ckd_clong: ckd_mk_long_t, \
    _ckd_ulong:  ckd_mk_ulong_t, \
    _ckd_culong: ckd_mk_ulong_t, \
    _ckd_llong:  ckd_mk_llong_t, \
    _ckd_cllong: ckd_mk_llong_t, \
    _ckd_ullong:  ckd_mk_ullong_t, \
    _ckd_cullong: ckd_mk_ullong_t, \
    _ckd_int128:  ckd_mk_int128_t, \
    _ckd_cint128: ckd_mk_int128_t, \
    _ckd_uint128:  ckd_mk_uint128_t, \
    _ckd_cuint128: ckd_mk_uint128_t)

// ]]]
// Generic macros implementation [[[

/// @brief ckd_add overflow for 2 arguments.
/// @see ckd_add
#define _ckd_add_2(a, b)  ({ \
        __auto_type _tMp = _ckd_getctype(_ckd_value(a) + _ckd_value(b))(0, 0); \
        ckd_overflow(_tMp) = __builtin_add_overflow(_ckd_value(a), _ckd_value(b), &ckd_value(_tMp)) || _ckd_overflow(a) || _ckd_overflow(b); \
        _tMp; \
        })
/// @brief ckd_add overflow for 3 arguments.
/// @see ckd_add
#define _ckd_add_3(r, a, b) \
        (__builtin_add_overflow(_ckd_value(a), _ckd_value(b), r) || _ckd_overflow(a) || _ckd_overflow(b))
/// @brief Macro overload on number of arguments for ckd_add
/// @see ckd_add
#define _ckd_add_N(_2,_3,N,...)  _ckd_add_##N
/**
 * @define ckd_add(...)
 * @brief `bool ckd_add(type1 *result, type2 a, type3 b);` or `ckd_type_t ckd_add(type1 a, type2 b);`
 * @param a Any checked or unchecked integer type other than plain char, bool, or an enumeration type.
 * @param b Any checked or unchecked integer type other than plain char, bool, or an enumeration type.
 * @param result Modifiable lvalue of any integer type.
 * @return In the first-form return false if type1 is sufficient to hold the mathematical result of
 * the computation, which is then stored in *result... Otherwise, these macros return true.. In this
 * case, *result is the mathematical result reduced by modular arithmetic on two’s-complement
 * representation with silent wrap-around on overflow. If *result is a checked integer type then its
 * overflow flag will equal the macro’s return value.
 * The macros of the second-form return a checked integer type that indicates the result of the
 * computation as well as an overflow flag.
 *
 * These macros perform operation add of the mathematical values of a and b.
 * In the first form, they store the result of the operation in *result, and in the second form, they return
 * the result as a checked integer.  Each operation is performed as if both operands were represented in a
 * signed integer type with infinite range, and the result was then converted from this integer type to a
 * particular type.  For the first form, this particular type is type1. For the second form, this type is the
 * type that would have been used had the operands undergone usual arithmetic conversion. (Section 6.3.1.8)
 */
#define ckd_add(w, ...)  _ckd_add_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)


/// @brief ckd_sub overflow for 2 arguments.
/// @see ckd_sub
#define _ckd_sub_2(a, b)  ({ \
        __auto_type _tMp = _ckd_getctype(_ckd_value(a) + _ckd_value(b))(0, 0); \
        ckd_overflow(_tMp) = __builtin_sub_overflow(_ckd_value(a), _ckd_value(b), &ckd_value(_tMp)) || _ckd_overflow(a) || _ckd_overflow(b); \
        _tMp; \
        })
/// @brief ckd_sub overflow for 3 arguments.
/// @see ckd_sub
#define _ckd_sub_3(r, a, b) \
        (__builtin_sub_overflow(_ckd_value(a), _ckd_value(b), r) || _ckd_overflow(a) || _ckd_overflow(b))
/// @brief Macro overload on number of arguments for ckd_sub
/// @see ckd_sub
#define _ckd_sub_N(_2,_3,N,...)  _ckd_sub_##N
/**
 * @define ckd_sub(...)
 * @brief `bool ckd_sub(type1 *result, type2 a, type3 b);` or `ckd_type_t ckd_sub(type1 a, type2 b);`
 * @param a Any checked or unchecked integer type other than plain char, bool, or an enumeration type.
 * @param b Any checked or unchecked integer type other than plain char, bool, or an enumeration type.
 * @param result Modifiable lvalue of any integer type.
 * @return In the first-form return false if type1 is sufficient to hold the mathematical result of
 * the computation, which is then stored in *result... Otherwise, these macros return true.. In this
 * case, *result is the mathematical result reduced by modular arithmetic on two’s-complement
 * representation with silent wrap-around on overflow. If *result is a checked integer type then its
 * overflow flag will equal the macro’s return value.
 * The macros of the second-form return a checked integer type that indicates the result of the
 * computation as well as an overflow flag.
 *
 * These macros perform operation sub of the mathematical values of a and b.
 * In the first form, they store the result of the operation in *result, and in the second form, they return
 * the result as a checked integer.  Each operation is performed as if both operands were represented in a
 * signed integer type with infinite range, and the result was then converted from this integer type to a
 * particular type.  For the first form, this particular type is type1. For the second form, this type is the
 * type that would have been used had the operands undergone usual arithmetic conversion. (Section 6.3.1.8)
 */
#define ckd_sub(w, ...)  _ckd_sub_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)


/// @brief ckd_mul overflow for 2 arguments.
/// @see ckd_mul
#define _ckd_mul_2(a, b)  ({ \
        __auto_type _tMp = _ckd_getctype(_ckd_value(a) + _ckd_value(b))(0, 0); \
        ckd_overflow(_tMp) = __builtin_mul_overflow(_ckd_value(a), _ckd_value(b), &ckd_value(_tMp)) || _ckd_overflow(a) || _ckd_overflow(b); \
        _tMp; \
        })
/// @brief ckd_mul overflow for 3 arguments.
/// @see ckd_mul
#define _ckd_mul_3(r, a, b) \
        (__builtin_mul_overflow(_ckd_value(a), _ckd_value(b), r) || _ckd_overflow(a) || _ckd_overflow(b))
/// @brief Macro overload on number of arguments for ckd_mul
/// @see ckd_mul
#define _ckd_mul_N(_2,_3,N,...)  _ckd_mul_##N
/**
 * @define ckd_mul(...)
 * @brief `bool ckd_mul(type1 *result, type2 a, type3 b);` or `ckd_type_t ckd_mul(type1 a, type2 b);`
 * @param a Any checked or unchecked integer type other than plain char, bool, or an enumeration type.
 * @param b Any checked or unchecked integer type other than plain char, bool, or an enumeration type.
 * @param result Modifiable lvalue of any integer type.
 * @return In the first-form return false if type1 is sufficient to hold the mathematical result of
 * the computation, which is then stored in *result... Otherwise, these macros return true.. In this
 * case, *result is the mathematical result reduced by modular arithmetic on two’s-complement
 * representation with silent wrap-around on overflow. If *result is a checked integer type then its
 * overflow flag will equal the macro’s return value.
 * The macros of the second-form return a checked integer type that indicates the result of the
 * computation as well as an overflow flag.
 *
 * These macros perform operation mul of the mathematical values of a and b.
 * In the first form, they store the result of the operation in *result, and in the second form, they return
 * the result as a checked integer.  Each operation is performed as if both operands were represented in a
 * signed integer type with infinite range, and the result was then converted from this integer type to a
 * particular type.  For the first form, this particular type is type1. For the second form, this type is the
 * type that would have been used had the operands undergone usual arithmetic conversion. (Section 6.3.1.8)
 */
#define ckd_mul(w, ...)  _ckd_mul_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)

// ]]]
// EOF [[[

#endif /* CKDINT_H_ */

// ]]]
