
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

#define _ckd_static     static inline
#if __GNUC__
#define _ckd_funcconst  _ckd_static __attribute__((__warn_unused_result__)) __attribute__((__const__))
#if __GNUC__ >= 10
#define _ckd_access_w(...)  __attribute__((__access__(__write_only__, __VA_ARGS__)))
#endif
#elif __STDC_VERSION__ >  20230000L
#define _ckd_funcconst  _ckd_static [[__nodiscard__]]
#else
#define _ckd_funcconst _ckd_static
#endif

#ifndef _ckd_access_w
#define _ckd_access_w(...)  /**/
#endif

#define ckd_overflow(x)  ((x)._oveRflow)
#define ckd_value(x)     ((x)._vaLue)

// ]]]
// Type specific [[[


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    signed char _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_schar_t;

#define _ckd_schar  signed char
#define _ckd_cschar ckd_schar_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_schar_t type that holds signed char variable type.
_ckd_funcconst ckd_schar_t ckd_mk_schar_t(signed char value, bool overflow) {
    return (ckd_schar_t){value, overflow};
}

#define _ckd_max_schar  (SCHAR_MAX)
#define _ckd_min_schar  (SCHAR_MIN)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    unsigned char _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_uchar_t;

#define _ckd_uchar  unsigned char
#define _ckd_cuchar ckd_uchar_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_uchar_t type that holds unsigned char variable type.
_ckd_funcconst ckd_uchar_t ckd_mk_uchar_t(unsigned char value, bool overflow) {
    return (ckd_uchar_t){value, overflow};
}

#define _ckd_max_uchar  (UCHAR_MAX)
#define _ckd_min_uchar  (0)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    short _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_shrt_t;

#define _ckd_shrt  short
#define _ckd_cshrt ckd_shrt_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_shrt_t type that holds short variable type.
_ckd_funcconst ckd_shrt_t ckd_mk_shrt_t(short value, bool overflow) {
    return (ckd_shrt_t){value, overflow};
}

#define _ckd_max_shrt  (SHRT_MAX)
#define _ckd_min_shrt  (SHRT_MIN)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    unsigned short _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_ushrt_t;

#define _ckd_ushrt  unsigned short
#define _ckd_cushrt ckd_ushrt_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_ushrt_t type that holds unsigned short variable type.
_ckd_funcconst ckd_ushrt_t ckd_mk_ushrt_t(unsigned short value, bool overflow) {
    return (ckd_ushrt_t){value, overflow};
}

#define _ckd_max_ushrt  (USHRT_MAX)
#define _ckd_min_ushrt  (0)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    int _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_int_t;

#define _ckd_int  int
#define _ckd_cint ckd_int_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_int_t type that holds int variable type.
_ckd_funcconst ckd_int_t ckd_mk_int_t(int value, bool overflow) {
    return (ckd_int_t){value, overflow};
}

#define _ckd_max_int  (INT_MAX)
#define _ckd_min_int  (INT_MIN)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    unsigned int _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_uint_t;

#define _ckd_uint  unsigned int
#define _ckd_cuint ckd_uint_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_uint_t type that holds unsigned int variable type.
_ckd_funcconst ckd_uint_t ckd_mk_uint_t(unsigned int value, bool overflow) {
    return (ckd_uint_t){value, overflow};
}

#define _ckd_max_uint  (UINT_MAX)
#define _ckd_min_uint  (0)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    long _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_long_t;

#define _ckd_long  long
#define _ckd_clong ckd_long_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_long_t type that holds long variable type.
_ckd_funcconst ckd_long_t ckd_mk_long_t(long value, bool overflow) {
    return (ckd_long_t){value, overflow};
}

#define _ckd_max_long  (LONG_MAX)
#define _ckd_min_long  (LONG_MIN)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    unsigned long _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_ulong_t;

#define _ckd_ulong  unsigned long
#define _ckd_culong ckd_ulong_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_ulong_t type that holds unsigned long variable type.
_ckd_funcconst ckd_ulong_t ckd_mk_ulong_t(unsigned long value, bool overflow) {
    return (ckd_ulong_t){value, overflow};
}

#define _ckd_max_ulong  (ULONG_MAX)
#define _ckd_min_ulong  (0)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    long long _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_llong_t;

#define _ckd_llong  long long
#define _ckd_cllong ckd_llong_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_llong_t type that holds long long variable type.
_ckd_funcconst ckd_llong_t ckd_mk_llong_t(long long value, bool overflow) {
    return (ckd_llong_t){value, overflow};
}

#define _ckd_max_llong  (LLONG_MAX)
#define _ckd_min_llong  (LLONG_MIN)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    unsigned long long _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_ullong_t;

#define _ckd_ullong  unsigned long long
#define _ckd_cullong ckd_ullong_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_ullong_t type that holds unsigned long long variable type.
_ckd_funcconst ckd_ullong_t ckd_mk_ullong_t(unsigned long long value, bool overflow) {
    return (ckd_ullong_t){value, overflow};
}

#define _ckd_max_ullong  (ULLONG_MAX)
#define _ckd_min_ullong  (0)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    __int128 _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_int128_t;

#define _ckd_int128  __int128
#define _ckd_cint128 ckd_int128_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_int128_t type that holds __int128 variable type.
_ckd_funcconst ckd_int128_t ckd_mk_int128_t(__int128 value, bool overflow) {
    return (ckd_int128_t){value, overflow};
}

#define _ckd_max_int128  (INT128_MAX)
#define _ckd_min_int128  (INT128_MIN)


/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    unsigned __int128 _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_uint128_t;

#define _ckd_uint128  unsigned __int128
#define _ckd_cuint128 ckd_uint128_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_uint128_t type that holds unsigned __int128 variable type.
_ckd_funcconst ckd_uint128_t ckd_mk_uint128_t(unsigned __int128 value, bool overflow) {
    return (ckd_uint128_t){value, overflow};
}

#define _ckd_max_uint128  (UINT128_MAX)
#define _ckd_min_uint128  (0)


// ]]]
// Type specific operation [[[


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type signed char or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_schar(signed char *res, signed char a, signed char b, bool others) {
    const signed char max = _ckd_max_schar; (void)max;
    const signed char min = _ckd_min_schar; (void)min;
    // Stores the result of calculation.
    signed char r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_schar.
_ckd_funcconst _ckd_cschar _ckd_add_2_schar(signed char a, signed char b, bool others) {
    _ckd_cschar tmp;
    ckd_overflow(tmp) = _ckd_add_3_schar(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type signed char or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_schar(signed char *res, signed char a, signed char b, bool others) {
    const signed char max = _ckd_max_schar; (void)max;
    const signed char min = _ckd_min_schar; (void)min;
    // Stores the result of calculation.
    signed char r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_schar.
_ckd_funcconst _ckd_cschar _ckd_sub_2_schar(signed char a, signed char b, bool others) {
    _ckd_cschar tmp;
    ckd_overflow(tmp) = _ckd_sub_3_schar(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type signed char or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_schar(signed char *res, signed char a, signed char b, bool others) {
    const signed char max = _ckd_max_schar; (void)max;
    const signed char min = _ckd_min_schar; (void)min;
    // Stores the result of calculation.
    signed char r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_schar.
_ckd_funcconst _ckd_cschar _ckd_mul_2_schar(signed char a, signed char b, bool others) {
    _ckd_cschar tmp;
    ckd_overflow(tmp) = _ckd_mul_3_schar(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type signed char or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_schar(signed char *res, signed char a, signed char b, bool others) {
    const signed char max = _ckd_max_schar; (void)max;
    const signed char min = _ckd_min_schar; (void)min;
    // Stores the result of calculation.
    signed char r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_schar != 0 && _ckd_min_schar < -_ckd_max_schar
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_schar.
_ckd_funcconst _ckd_cschar _ckd_div_2_schar(signed char a, signed char b, bool others) {
    _ckd_cschar tmp;
    ckd_overflow(tmp) = _ckd_div_3_schar(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned char or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_uchar(unsigned char *res, unsigned char a, unsigned char b, bool others) {
    const unsigned char max = _ckd_max_uchar; (void)max;
    const unsigned char min = _ckd_min_uchar; (void)min;
    // Stores the result of calculation.
    unsigned char r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = r < (a | b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_uchar.
_ckd_funcconst _ckd_cuchar _ckd_add_2_uchar(unsigned char a, unsigned char b, bool others) {
    _ckd_cuchar tmp;
    ckd_overflow(tmp) = _ckd_add_3_uchar(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned char or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_uchar(unsigned char *res, unsigned char a, unsigned char b, bool others) {
    const unsigned char max = _ckd_max_uchar; (void)max;
    const unsigned char min = _ckd_min_uchar; (void)min;
    // Stores the result of calculation.
    unsigned char r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = a < min + b;
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_uchar.
_ckd_funcconst _ckd_cuchar _ckd_sub_2_uchar(unsigned char a, unsigned char b, bool others) {
    _ckd_cuchar tmp;
    ckd_overflow(tmp) = _ckd_sub_3_uchar(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned char or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_uchar(unsigned char *res, unsigned char a, unsigned char b, bool others) {
    const unsigned char max = _ckd_max_uchar; (void)max;
    const unsigned char min = _ckd_min_uchar; (void)min;
    // Stores the result of calculation.
    unsigned char r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_uchar.
_ckd_funcconst _ckd_cuchar _ckd_mul_2_uchar(unsigned char a, unsigned char b, bool others) {
    _ckd_cuchar tmp;
    ckd_overflow(tmp) = _ckd_mul_3_uchar(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned char or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_uchar(unsigned char *res, unsigned char a, unsigned char b, bool others) {
    const unsigned char max = _ckd_max_uchar; (void)max;
    const unsigned char min = _ckd_min_uchar; (void)min;
    // Stores the result of calculation.
    unsigned char r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_uchar != 0 && _ckd_min_uchar < -_ckd_max_uchar
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_uchar.
_ckd_funcconst _ckd_cuchar _ckd_div_2_uchar(unsigned char a, unsigned char b, bool others) {
    _ckd_cuchar tmp;
    ckd_overflow(tmp) = _ckd_div_3_uchar(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type short or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_shrt(short *res, short a, short b, bool others) {
    const short max = _ckd_max_shrt; (void)max;
    const short min = _ckd_min_shrt; (void)min;
    // Stores the result of calculation.
    short r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_shrt.
_ckd_funcconst _ckd_cshrt _ckd_add_2_shrt(short a, short b, bool others) {
    _ckd_cshrt tmp;
    ckd_overflow(tmp) = _ckd_add_3_shrt(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type short or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_shrt(short *res, short a, short b, bool others) {
    const short max = _ckd_max_shrt; (void)max;
    const short min = _ckd_min_shrt; (void)min;
    // Stores the result of calculation.
    short r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_shrt.
_ckd_funcconst _ckd_cshrt _ckd_sub_2_shrt(short a, short b, bool others) {
    _ckd_cshrt tmp;
    ckd_overflow(tmp) = _ckd_sub_3_shrt(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type short or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_shrt(short *res, short a, short b, bool others) {
    const short max = _ckd_max_shrt; (void)max;
    const short min = _ckd_min_shrt; (void)min;
    // Stores the result of calculation.
    short r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_shrt.
_ckd_funcconst _ckd_cshrt _ckd_mul_2_shrt(short a, short b, bool others) {
    _ckd_cshrt tmp;
    ckd_overflow(tmp) = _ckd_mul_3_shrt(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type short or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_shrt(short *res, short a, short b, bool others) {
    const short max = _ckd_max_shrt; (void)max;
    const short min = _ckd_min_shrt; (void)min;
    // Stores the result of calculation.
    short r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_shrt != 0 && _ckd_min_shrt < -_ckd_max_shrt
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_shrt.
_ckd_funcconst _ckd_cshrt _ckd_div_2_shrt(short a, short b, bool others) {
    _ckd_cshrt tmp;
    ckd_overflow(tmp) = _ckd_div_3_shrt(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned short or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_ushrt(unsigned short *res, unsigned short a, unsigned short b, bool others) {
    const unsigned short max = _ckd_max_ushrt; (void)max;
    const unsigned short min = _ckd_min_ushrt; (void)min;
    // Stores the result of calculation.
    unsigned short r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = r < (a | b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_ushrt.
_ckd_funcconst _ckd_cushrt _ckd_add_2_ushrt(unsigned short a, unsigned short b, bool others) {
    _ckd_cushrt tmp;
    ckd_overflow(tmp) = _ckd_add_3_ushrt(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned short or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_ushrt(unsigned short *res, unsigned short a, unsigned short b, bool others) {
    const unsigned short max = _ckd_max_ushrt; (void)max;
    const unsigned short min = _ckd_min_ushrt; (void)min;
    // Stores the result of calculation.
    unsigned short r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = a < min + b;
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_ushrt.
_ckd_funcconst _ckd_cushrt _ckd_sub_2_ushrt(unsigned short a, unsigned short b, bool others) {
    _ckd_cushrt tmp;
    ckd_overflow(tmp) = _ckd_sub_3_ushrt(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned short or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_ushrt(unsigned short *res, unsigned short a, unsigned short b, bool others) {
    const unsigned short max = _ckd_max_ushrt; (void)max;
    const unsigned short min = _ckd_min_ushrt; (void)min;
    // Stores the result of calculation.
    unsigned short r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_ushrt.
_ckd_funcconst _ckd_cushrt _ckd_mul_2_ushrt(unsigned short a, unsigned short b, bool others) {
    _ckd_cushrt tmp;
    ckd_overflow(tmp) = _ckd_mul_3_ushrt(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned short or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_ushrt(unsigned short *res, unsigned short a, unsigned short b, bool others) {
    const unsigned short max = _ckd_max_ushrt; (void)max;
    const unsigned short min = _ckd_min_ushrt; (void)min;
    // Stores the result of calculation.
    unsigned short r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_ushrt != 0 && _ckd_min_ushrt < -_ckd_max_ushrt
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_ushrt.
_ckd_funcconst _ckd_cushrt _ckd_div_2_ushrt(unsigned short a, unsigned short b, bool others) {
    _ckd_cushrt tmp;
    ckd_overflow(tmp) = _ckd_div_3_ushrt(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type int or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_int(int *res, int a, int b, bool others) {
    const int max = _ckd_max_int; (void)max;
    const int min = _ckd_min_int; (void)min;
    // Stores the result of calculation.
    int r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_int.
_ckd_funcconst _ckd_cint _ckd_add_2_int(int a, int b, bool others) {
    _ckd_cint tmp;
    ckd_overflow(tmp) = _ckd_add_3_int(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type int or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_int(int *res, int a, int b, bool others) {
    const int max = _ckd_max_int; (void)max;
    const int min = _ckd_min_int; (void)min;
    // Stores the result of calculation.
    int r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_int.
_ckd_funcconst _ckd_cint _ckd_sub_2_int(int a, int b, bool others) {
    _ckd_cint tmp;
    ckd_overflow(tmp) = _ckd_sub_3_int(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type int or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_int(int *res, int a, int b, bool others) {
    const int max = _ckd_max_int; (void)max;
    const int min = _ckd_min_int; (void)min;
    // Stores the result of calculation.
    int r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_int.
_ckd_funcconst _ckd_cint _ckd_mul_2_int(int a, int b, bool others) {
    _ckd_cint tmp;
    ckd_overflow(tmp) = _ckd_mul_3_int(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type int or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_int(int *res, int a, int b, bool others) {
    const int max = _ckd_max_int; (void)max;
    const int min = _ckd_min_int; (void)min;
    // Stores the result of calculation.
    int r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_int != 0 && _ckd_min_int < -_ckd_max_int
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_int.
_ckd_funcconst _ckd_cint _ckd_div_2_int(int a, int b, bool others) {
    _ckd_cint tmp;
    ckd_overflow(tmp) = _ckd_div_3_int(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned int or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_uint(unsigned int *res, unsigned int a, unsigned int b, bool others) {
    const unsigned int max = _ckd_max_uint; (void)max;
    const unsigned int min = _ckd_min_uint; (void)min;
    // Stores the result of calculation.
    unsigned int r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = r < (a | b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_uint.
_ckd_funcconst _ckd_cuint _ckd_add_2_uint(unsigned int a, unsigned int b, bool others) {
    _ckd_cuint tmp;
    ckd_overflow(tmp) = _ckd_add_3_uint(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned int or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_uint(unsigned int *res, unsigned int a, unsigned int b, bool others) {
    const unsigned int max = _ckd_max_uint; (void)max;
    const unsigned int min = _ckd_min_uint; (void)min;
    // Stores the result of calculation.
    unsigned int r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = a < min + b;
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_uint.
_ckd_funcconst _ckd_cuint _ckd_sub_2_uint(unsigned int a, unsigned int b, bool others) {
    _ckd_cuint tmp;
    ckd_overflow(tmp) = _ckd_sub_3_uint(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned int or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_uint(unsigned int *res, unsigned int a, unsigned int b, bool others) {
    const unsigned int max = _ckd_max_uint; (void)max;
    const unsigned int min = _ckd_min_uint; (void)min;
    // Stores the result of calculation.
    unsigned int r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_uint.
_ckd_funcconst _ckd_cuint _ckd_mul_2_uint(unsigned int a, unsigned int b, bool others) {
    _ckd_cuint tmp;
    ckd_overflow(tmp) = _ckd_mul_3_uint(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned int or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_uint(unsigned int *res, unsigned int a, unsigned int b, bool others) {
    const unsigned int max = _ckd_max_uint; (void)max;
    const unsigned int min = _ckd_min_uint; (void)min;
    // Stores the result of calculation.
    unsigned int r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_uint != 0 && _ckd_min_uint < -_ckd_max_uint
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_uint.
_ckd_funcconst _ckd_cuint _ckd_div_2_uint(unsigned int a, unsigned int b, bool others) {
    _ckd_cuint tmp;
    ckd_overflow(tmp) = _ckd_div_3_uint(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_long(long *res, long a, long b, bool others) {
    const long max = _ckd_max_long; (void)max;
    const long min = _ckd_min_long; (void)min;
    // Stores the result of calculation.
    long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_long.
_ckd_funcconst _ckd_clong _ckd_add_2_long(long a, long b, bool others) {
    _ckd_clong tmp;
    ckd_overflow(tmp) = _ckd_add_3_long(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_long(long *res, long a, long b, bool others) {
    const long max = _ckd_max_long; (void)max;
    const long min = _ckd_min_long; (void)min;
    // Stores the result of calculation.
    long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_long.
_ckd_funcconst _ckd_clong _ckd_sub_2_long(long a, long b, bool others) {
    _ckd_clong tmp;
    ckd_overflow(tmp) = _ckd_sub_3_long(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_long(long *res, long a, long b, bool others) {
    const long max = _ckd_max_long; (void)max;
    const long min = _ckd_min_long; (void)min;
    // Stores the result of calculation.
    long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_long.
_ckd_funcconst _ckd_clong _ckd_mul_2_long(long a, long b, bool others) {
    _ckd_clong tmp;
    ckd_overflow(tmp) = _ckd_mul_3_long(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_long(long *res, long a, long b, bool others) {
    const long max = _ckd_max_long; (void)max;
    const long min = _ckd_min_long; (void)min;
    // Stores the result of calculation.
    long r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_long != 0 && _ckd_min_long < -_ckd_max_long
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_long.
_ckd_funcconst _ckd_clong _ckd_div_2_long(long a, long b, bool others) {
    _ckd_clong tmp;
    ckd_overflow(tmp) = _ckd_div_3_long(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_ulong(unsigned long *res, unsigned long a, unsigned long b, bool others) {
    const unsigned long max = _ckd_max_ulong; (void)max;
    const unsigned long min = _ckd_min_ulong; (void)min;
    // Stores the result of calculation.
    unsigned long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = r < (a | b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_ulong.
_ckd_funcconst _ckd_culong _ckd_add_2_ulong(unsigned long a, unsigned long b, bool others) {
    _ckd_culong tmp;
    ckd_overflow(tmp) = _ckd_add_3_ulong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_ulong(unsigned long *res, unsigned long a, unsigned long b, bool others) {
    const unsigned long max = _ckd_max_ulong; (void)max;
    const unsigned long min = _ckd_min_ulong; (void)min;
    // Stores the result of calculation.
    unsigned long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = a < min + b;
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_ulong.
_ckd_funcconst _ckd_culong _ckd_sub_2_ulong(unsigned long a, unsigned long b, bool others) {
    _ckd_culong tmp;
    ckd_overflow(tmp) = _ckd_sub_3_ulong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_ulong(unsigned long *res, unsigned long a, unsigned long b, bool others) {
    const unsigned long max = _ckd_max_ulong; (void)max;
    const unsigned long min = _ckd_min_ulong; (void)min;
    // Stores the result of calculation.
    unsigned long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_ulong.
_ckd_funcconst _ckd_culong _ckd_mul_2_ulong(unsigned long a, unsigned long b, bool others) {
    _ckd_culong tmp;
    ckd_overflow(tmp) = _ckd_mul_3_ulong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_ulong(unsigned long *res, unsigned long a, unsigned long b, bool others) {
    const unsigned long max = _ckd_max_ulong; (void)max;
    const unsigned long min = _ckd_min_ulong; (void)min;
    // Stores the result of calculation.
    unsigned long r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_ulong != 0 && _ckd_min_ulong < -_ckd_max_ulong
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_ulong.
_ckd_funcconst _ckd_culong _ckd_div_2_ulong(unsigned long a, unsigned long b, bool others) {
    _ckd_culong tmp;
    ckd_overflow(tmp) = _ckd_div_3_ulong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type long long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_llong(long long *res, long long a, long long b, bool others) {
    const long long max = _ckd_max_llong; (void)max;
    const long long min = _ckd_min_llong; (void)min;
    // Stores the result of calculation.
    long long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_llong.
_ckd_funcconst _ckd_cllong _ckd_add_2_llong(long long a, long long b, bool others) {
    _ckd_cllong tmp;
    ckd_overflow(tmp) = _ckd_add_3_llong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type long long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_llong(long long *res, long long a, long long b, bool others) {
    const long long max = _ckd_max_llong; (void)max;
    const long long min = _ckd_min_llong; (void)min;
    // Stores the result of calculation.
    long long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_llong.
_ckd_funcconst _ckd_cllong _ckd_sub_2_llong(long long a, long long b, bool others) {
    _ckd_cllong tmp;
    ckd_overflow(tmp) = _ckd_sub_3_llong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type long long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_llong(long long *res, long long a, long long b, bool others) {
    const long long max = _ckd_max_llong; (void)max;
    const long long min = _ckd_min_llong; (void)min;
    // Stores the result of calculation.
    long long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_llong.
_ckd_funcconst _ckd_cllong _ckd_mul_2_llong(long long a, long long b, bool others) {
    _ckd_cllong tmp;
    ckd_overflow(tmp) = _ckd_mul_3_llong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type long long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_llong(long long *res, long long a, long long b, bool others) {
    const long long max = _ckd_max_llong; (void)max;
    const long long min = _ckd_min_llong; (void)min;
    // Stores the result of calculation.
    long long r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_llong != 0 && _ckd_min_llong < -_ckd_max_llong
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_llong.
_ckd_funcconst _ckd_cllong _ckd_div_2_llong(long long a, long long b, bool others) {
    _ckd_cllong tmp;
    ckd_overflow(tmp) = _ckd_div_3_llong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned long long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_ullong(unsigned long long *res, unsigned long long a, unsigned long long b, bool others) {
    const unsigned long long max = _ckd_max_ullong; (void)max;
    const unsigned long long min = _ckd_min_ullong; (void)min;
    // Stores the result of calculation.
    unsigned long long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = r < (a | b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_ullong.
_ckd_funcconst _ckd_cullong _ckd_add_2_ullong(unsigned long long a, unsigned long long b, bool others) {
    _ckd_cullong tmp;
    ckd_overflow(tmp) = _ckd_add_3_ullong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned long long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_ullong(unsigned long long *res, unsigned long long a, unsigned long long b, bool others) {
    const unsigned long long max = _ckd_max_ullong; (void)max;
    const unsigned long long min = _ckd_min_ullong; (void)min;
    // Stores the result of calculation.
    unsigned long long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = a < min + b;
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_ullong.
_ckd_funcconst _ckd_cullong _ckd_sub_2_ullong(unsigned long long a, unsigned long long b, bool others) {
    _ckd_cullong tmp;
    ckd_overflow(tmp) = _ckd_sub_3_ullong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned long long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_ullong(unsigned long long *res, unsigned long long a, unsigned long long b, bool others) {
    const unsigned long long max = _ckd_max_ullong; (void)max;
    const unsigned long long min = _ckd_min_ullong; (void)min;
    // Stores the result of calculation.
    unsigned long long r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_ullong.
_ckd_funcconst _ckd_cullong _ckd_mul_2_ullong(unsigned long long a, unsigned long long b, bool others) {
    _ckd_cullong tmp;
    ckd_overflow(tmp) = _ckd_mul_3_ullong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned long long or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_ullong(unsigned long long *res, unsigned long long a, unsigned long long b, bool others) {
    const unsigned long long max = _ckd_max_ullong; (void)max;
    const unsigned long long min = _ckd_min_ullong; (void)min;
    // Stores the result of calculation.
    unsigned long long r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if _ckd_min_ullong != 0 && _ckd_min_ullong < -_ckd_max_ullong
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_ullong.
_ckd_funcconst _ckd_cullong _ckd_div_2_ullong(unsigned long long a, unsigned long long b, bool others) {
    _ckd_cullong tmp;
    ckd_overflow(tmp) = _ckd_div_3_ullong(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type __int128 or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_int128(__int128 *res, __int128 a, __int128 b, bool others) {
    const __int128 max = _ckd_max_int128; (void)max;
    const __int128 min = _ckd_min_int128; (void)min;
    // Stores the result of calculation.
    __int128 r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_int128.
_ckd_funcconst _ckd_cint128 _ckd_add_2_int128(__int128 a, __int128 b, bool others) {
    _ckd_cint128 tmp;
    ckd_overflow(tmp) = _ckd_add_3_int128(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type __int128 or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_int128(__int128 *res, __int128 a, __int128 b, bool others) {
    const __int128 max = _ckd_max_int128; (void)max;
    const __int128 min = _ckd_min_int128; (void)min;
    // Stores the result of calculation.
    __int128 r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_int128.
_ckd_funcconst _ckd_cint128 _ckd_sub_2_int128(__int128 a, __int128 b, bool others) {
    _ckd_cint128 tmp;
    ckd_overflow(tmp) = _ckd_sub_3_int128(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type __int128 or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_int128(__int128 *res, __int128 a, __int128 b, bool others) {
    const __int128 max = _ckd_max_int128; (void)max;
    const __int128 min = _ckd_min_int128; (void)min;
    // Stores the result of calculation.
    __int128 r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_int128.
_ckd_funcconst _ckd_cint128 _ckd_mul_2_int128(__int128 a, __int128 b, bool others) {
    _ckd_cint128 tmp;
    ckd_overflow(tmp) = _ckd_mul_3_int128(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type __int128 or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_int128(__int128 *res, __int128 a, __int128 b, bool others) {
    const __int128 max = _ckd_max_int128; (void)max;
    const __int128 min = _ckd_min_int128; (void)min;
    // Stores the result of calculation.
    __int128 r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if True
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_int128.
_ckd_funcconst _ckd_cint128 _ckd_div_2_int128(__int128 a, __int128 b, bool others) {
    _ckd_cint128 tmp;
    ckd_overflow(tmp) = _ckd_div_3_int128(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a add b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned __int128 or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_add_3_uint128(unsigned __int128 *res, unsigned __int128 a, unsigned __int128 b, bool others) {
    const unsigned __int128 max = _ckd_max_uint128; (void)max;
    const unsigned __int128 min = _ckd_min_uint128; (void)min;
    // Stores the result of calculation.
    unsigned __int128 r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_add_overflow(a, b, &r);
#else // __GNUC__
    r = a + b;
    o = r < (a | b);
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_add_3_uint128.
_ckd_funcconst _ckd_cuint128 _ckd_add_2_uint128(unsigned __int128 a, unsigned __int128 b, bool others) {
    _ckd_cuint128 tmp;
    ckd_overflow(tmp) = _ckd_add_3_uint128(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a sub b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned __int128 or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_sub_3_uint128(unsigned __int128 *res, unsigned __int128 a, unsigned __int128 b, bool others) {
    const unsigned __int128 max = _ckd_max_uint128; (void)max;
    const unsigned __int128 min = _ckd_min_uint128; (void)min;
    // Stores the result of calculation.
    unsigned __int128 r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_sub_overflow(a, b, &r);
#else // __GNUC__
    r = a - b;
    o = a < min + b;
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_sub_3_uint128.
_ckd_funcconst _ckd_cuint128 _ckd_sub_2_uint128(unsigned __int128 a, unsigned __int128 b, bool others) {
    _ckd_cuint128 tmp;
    ckd_overflow(tmp) = _ckd_sub_3_uint128(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a mul b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned __int128 or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_mul_3_uint128(unsigned __int128 *res, unsigned __int128 a, unsigned __int128 b, bool others) {
    const unsigned __int128 max = _ckd_max_uint128; (void)max;
    const unsigned __int128 min = _ckd_min_uint128; (void)min;
    // Stores the result of calculation.
    unsigned __int128 r;
    // Stores if the calculation overflowed.
    bool o = 0;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_mul_overflow(a, b, &r);
#else // __GNUC__
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
#endif // __GNUC__
*res = r;
    return others || o;
}

/// Wrapper around _ckd_mul_3_uint128.
_ckd_funcconst _ckd_cuint128 _ckd_mul_2_uint128(unsigned __int128 a, unsigned __int128 b, bool others) {
    _ckd_cuint128 tmp;
    ckd_overflow(tmp) = _ckd_mul_3_uint128(&ckd_value(tmp), a, b, others);
    return tmp;
}


/**
 * Calculates a div b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type unsigned __int128 or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_div_3_uint128(unsigned __int128 *res, unsigned __int128 a, unsigned __int128 b, bool others) {
    const unsigned __int128 max = _ckd_max_uint128; (void)max;
    const unsigned __int128 min = _ckd_min_uint128; (void)min;
    // Stores the result of calculation.
    unsigned __int128 r;
    // Stores if the calculation overflowed.
    bool o = 0;
    #if False
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
*res = r;
    return others || o;
}

/// Wrapper around _ckd_div_3_uint128.
_ckd_funcconst _ckd_cuint128 _ckd_div_2_uint128(unsigned __int128 a, unsigned __int128 b, bool others) {
    _ckd_cuint128 tmp;
    ckd_overflow(tmp) = _ckd_div_3_uint128(&ckd_value(tmp), a, b, others);
    return tmp;
}


// ]]]
// Standard integer types aliases [[[

#if !defined(ckd_int8_t) && UINT8_MAX == ULLONG_MAX && UINT8_MIN == 0
#define ckd_uint8_t ckd_ullong_t
#endif
#if !defined(ckd_int8_t) && INT8_MAX == LLONG_MAX && INT8_MIN == LLONG_MIN
#define ckd_int8_t ckd_llong_t
#endif
#if !defined(ckd_int8_t) && UINT8_MAX == ULONG_MAX && UINT8_MIN == 0
#define ckd_uint8_t ckd_ulong_t
#endif
#if !defined(ckd_int8_t) && INT8_MAX == LONG_MAX && INT8_MIN == LONG_MIN
#define ckd_int8_t ckd_long_t
#endif
#if !defined(ckd_int8_t) && UINT8_MAX == UINT_MAX && UINT8_MIN == 0
#define ckd_uint8_t ckd_uint_t
#endif
#if !defined(ckd_int8_t) && INT8_MAX == INT_MAX && INT8_MIN == INT_MIN
#define ckd_int8_t ckd_int_t
#endif
#if !defined(ckd_int8_t) && UINT8_MAX == USHRT_MAX && UINT8_MIN == 0
#define ckd_uint8_t ckd_ushrt_t
#endif
#if !defined(ckd_int8_t) && INT8_MAX == SHRT_MAX && INT8_MIN == SHRT_MIN
#define ckd_int8_t ckd_shrt_t
#endif
#if !defined(ckd_int8_t) && UINT8_MAX == UCHAR_MAX && UINT8_MIN == 0
#define ckd_uint8_t ckd_uchar_t
#endif
#if !defined(ckd_int8_t) && INT8_MAX == SCHAR_MAX && INT8_MIN == SCHAR_MIN
#define ckd_int8_t ckd_schar_t
#endif
#if !defined(ckd_int16_t) && UINT16_MAX == ULLONG_MAX && UINT16_MIN == 0
#define ckd_uint16_t ckd_ullong_t
#endif
#if !defined(ckd_int16_t) && INT16_MAX == LLONG_MAX && INT16_MIN == LLONG_MIN
#define ckd_int16_t ckd_llong_t
#endif
#if !defined(ckd_int16_t) && UINT16_MAX == ULONG_MAX && UINT16_MIN == 0
#define ckd_uint16_t ckd_ulong_t
#endif
#if !defined(ckd_int16_t) && INT16_MAX == LONG_MAX && INT16_MIN == LONG_MIN
#define ckd_int16_t ckd_long_t
#endif
#if !defined(ckd_int16_t) && UINT16_MAX == UINT_MAX && UINT16_MIN == 0
#define ckd_uint16_t ckd_uint_t
#endif
#if !defined(ckd_int16_t) && INT16_MAX == INT_MAX && INT16_MIN == INT_MIN
#define ckd_int16_t ckd_int_t
#endif
#if !defined(ckd_int16_t) && UINT16_MAX == USHRT_MAX && UINT16_MIN == 0
#define ckd_uint16_t ckd_ushrt_t
#endif
#if !defined(ckd_int16_t) && INT16_MAX == SHRT_MAX && INT16_MIN == SHRT_MIN
#define ckd_int16_t ckd_shrt_t
#endif
#if !defined(ckd_int16_t) && UINT16_MAX == UCHAR_MAX && UINT16_MIN == 0
#define ckd_uint16_t ckd_uchar_t
#endif
#if !defined(ckd_int16_t) && INT16_MAX == SCHAR_MAX && INT16_MIN == SCHAR_MIN
#define ckd_int16_t ckd_schar_t
#endif
#if !defined(ckd_int32_t) && UINT32_MAX == ULLONG_MAX && UINT32_MIN == 0
#define ckd_uint32_t ckd_ullong_t
#endif
#if !defined(ckd_int32_t) && INT32_MAX == LLONG_MAX && INT32_MIN == LLONG_MIN
#define ckd_int32_t ckd_llong_t
#endif
#if !defined(ckd_int32_t) && UINT32_MAX == ULONG_MAX && UINT32_MIN == 0
#define ckd_uint32_t ckd_ulong_t
#endif
#if !defined(ckd_int32_t) && INT32_MAX == LONG_MAX && INT32_MIN == LONG_MIN
#define ckd_int32_t ckd_long_t
#endif
#if !defined(ckd_int32_t) && UINT32_MAX == UINT_MAX && UINT32_MIN == 0
#define ckd_uint32_t ckd_uint_t
#endif
#if !defined(ckd_int32_t) && INT32_MAX == INT_MAX && INT32_MIN == INT_MIN
#define ckd_int32_t ckd_int_t
#endif
#if !defined(ckd_int32_t) && UINT32_MAX == USHRT_MAX && UINT32_MIN == 0
#define ckd_uint32_t ckd_ushrt_t
#endif
#if !defined(ckd_int32_t) && INT32_MAX == SHRT_MAX && INT32_MIN == SHRT_MIN
#define ckd_int32_t ckd_shrt_t
#endif
#if !defined(ckd_int32_t) && UINT32_MAX == UCHAR_MAX && UINT32_MIN == 0
#define ckd_uint32_t ckd_uchar_t
#endif
#if !defined(ckd_int32_t) && INT32_MAX == SCHAR_MAX && INT32_MIN == SCHAR_MIN
#define ckd_int32_t ckd_schar_t
#endif
#if !defined(ckd_int64_t) && UINT64_MAX == ULLONG_MAX && UINT64_MIN == 0
#define ckd_uint64_t ckd_ullong_t
#endif
#if !defined(ckd_int64_t) && INT64_MAX == LLONG_MAX && INT64_MIN == LLONG_MIN
#define ckd_int64_t ckd_llong_t
#endif
#if !defined(ckd_int64_t) && UINT64_MAX == ULONG_MAX && UINT64_MIN == 0
#define ckd_uint64_t ckd_ulong_t
#endif
#if !defined(ckd_int64_t) && INT64_MAX == LONG_MAX && INT64_MIN == LONG_MIN
#define ckd_int64_t ckd_long_t
#endif
#if !defined(ckd_int64_t) && UINT64_MAX == UINT_MAX && UINT64_MIN == 0
#define ckd_uint64_t ckd_uint_t
#endif
#if !defined(ckd_int64_t) && INT64_MAX == INT_MAX && INT64_MIN == INT_MIN
#define ckd_int64_t ckd_int_t
#endif
#if !defined(ckd_int64_t) && UINT64_MAX == USHRT_MAX && UINT64_MIN == 0
#define ckd_uint64_t ckd_ushrt_t
#endif
#if !defined(ckd_int64_t) && INT64_MAX == SHRT_MAX && INT64_MIN == SHRT_MIN
#define ckd_int64_t ckd_shrt_t
#endif
#if !defined(ckd_int64_t) && UINT64_MAX == UCHAR_MAX && UINT64_MIN == 0
#define ckd_uint64_t ckd_uchar_t
#endif
#if !defined(ckd_int64_t) && INT64_MAX == SCHAR_MAX && INT64_MIN == SCHAR_MIN
#define ckd_int64_t ckd_schar_t
#endif

// ]]]
// Generic _ckd_overflow and _ckd_value with normal types [[[

_ckd_funcconst _ckd_schar _ckd_value_cschar(_ckd_cschar v) { return ckd_value(v); }
_ckd_funcconst _ckd_schar _ckd_value_schar(_ckd_schar v) { return v; }
_ckd_funcconst bool _ckd_overflow_cschar(_ckd_cschar v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_schar(_ckd_schar v) { return 0; }
_ckd_funcconst _ckd_uchar _ckd_value_cuchar(_ckd_cuchar v) { return ckd_value(v); }
_ckd_funcconst _ckd_uchar _ckd_value_uchar(_ckd_uchar v) { return v; }
_ckd_funcconst bool _ckd_overflow_cuchar(_ckd_cuchar v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_uchar(_ckd_uchar v) { return 0; }
_ckd_funcconst _ckd_shrt _ckd_value_cshrt(_ckd_cshrt v) { return ckd_value(v); }
_ckd_funcconst _ckd_shrt _ckd_value_shrt(_ckd_shrt v) { return v; }
_ckd_funcconst bool _ckd_overflow_cshrt(_ckd_cshrt v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_shrt(_ckd_shrt v) { return 0; }
_ckd_funcconst _ckd_ushrt _ckd_value_cushrt(_ckd_cushrt v) { return ckd_value(v); }
_ckd_funcconst _ckd_ushrt _ckd_value_ushrt(_ckd_ushrt v) { return v; }
_ckd_funcconst bool _ckd_overflow_cushrt(_ckd_cushrt v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_ushrt(_ckd_ushrt v) { return 0; }
_ckd_funcconst _ckd_int _ckd_value_cint(_ckd_cint v) { return ckd_value(v); }
_ckd_funcconst _ckd_int _ckd_value_int(_ckd_int v) { return v; }
_ckd_funcconst bool _ckd_overflow_cint(_ckd_cint v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_int(_ckd_int v) { return 0; }
_ckd_funcconst _ckd_uint _ckd_value_cuint(_ckd_cuint v) { return ckd_value(v); }
_ckd_funcconst _ckd_uint _ckd_value_uint(_ckd_uint v) { return v; }
_ckd_funcconst bool _ckd_overflow_cuint(_ckd_cuint v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_uint(_ckd_uint v) { return 0; }
_ckd_funcconst _ckd_long _ckd_value_clong(_ckd_clong v) { return ckd_value(v); }
_ckd_funcconst _ckd_long _ckd_value_long(_ckd_long v) { return v; }
_ckd_funcconst bool _ckd_overflow_clong(_ckd_clong v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_long(_ckd_long v) { return 0; }
_ckd_funcconst _ckd_ulong _ckd_value_culong(_ckd_culong v) { return ckd_value(v); }
_ckd_funcconst _ckd_ulong _ckd_value_ulong(_ckd_ulong v) { return v; }
_ckd_funcconst bool _ckd_overflow_culong(_ckd_culong v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_ulong(_ckd_ulong v) { return 0; }
_ckd_funcconst _ckd_llong _ckd_value_cllong(_ckd_cllong v) { return ckd_value(v); }
_ckd_funcconst _ckd_llong _ckd_value_llong(_ckd_llong v) { return v; }
_ckd_funcconst bool _ckd_overflow_cllong(_ckd_cllong v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_llong(_ckd_llong v) { return 0; }
_ckd_funcconst _ckd_ullong _ckd_value_cullong(_ckd_cullong v) { return ckd_value(v); }
_ckd_funcconst _ckd_ullong _ckd_value_ullong(_ckd_ullong v) { return v; }
_ckd_funcconst bool _ckd_overflow_cullong(_ckd_cullong v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_ullong(_ckd_ullong v) { return 0; }
_ckd_funcconst _ckd_int128 _ckd_value_cint128(_ckd_cint128 v) { return ckd_value(v); }
_ckd_funcconst _ckd_int128 _ckd_value_int128(_ckd_int128 v) { return v; }
_ckd_funcconst bool _ckd_overflow_cint128(_ckd_cint128 v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_int128(_ckd_int128 v) { return 0; }
_ckd_funcconst _ckd_uint128 _ckd_value_cuint128(_ckd_cuint128 v) { return ckd_value(v); }
_ckd_funcconst _ckd_uint128 _ckd_value_uint128(_ckd_uint128 v) { return v; }
_ckd_funcconst bool _ckd_overflow_cuint128(_ckd_cuint128 v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_uint128(_ckd_uint128 v) { return 0; }

/// @define _ckd_value(X)
// For any basic type returns it's value.
// For any ckd_*_t type returns ckd_value(X).
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
        _ckd_uint128:  _ckd_value_uint128 \
        )(X)

/// @define _ckd_overflow(X)
/// Same as _ckd_value, but returns ckd_overflow(0) or 0.
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
        _ckd_uint128:  _ckd_overflow_uint128 \
        )(X)

// ]]]
// Generic macros implementation [[[

struct _ckd_invalid_;
void _ckd_invalid(struct _ckd_invalid_);

#define ckd_mk(value, overflow)  _Generic((value), \
    _ckd_schar: ckd_mk_schar_t, \
    _ckd_uchar: ckd_mk_uchar_t, \
    _ckd_shrt: ckd_mk_shrt_t, \
    _ckd_ushrt: ckd_mk_ushrt_t, \
    _ckd_int: ckd_mk_int_t, \
    _ckd_uint: ckd_mk_uint_t, \
    _ckd_long: ckd_mk_long_t, \
    _ckd_ulong: ckd_mk_ulong_t, \
    _ckd_llong: ckd_mk_llong_t, \
    _ckd_ullong: ckd_mk_ullong_t, \
    _ckd_int128: ckd_mk_int128_t, \
    _ckd_uint128: ckd_mk_uint128_t \
    )(value, overflow)

/* ------------------------------------------------------------------------- */


#define _ckd_add_2(a, b)  \
    _Generic(_ckd_value(a) + _ckd_value(b), \
    _ckd_schar: _ckd_add_2_schar, \
    _ckd_uchar: _ckd_add_2_uchar, \
    _ckd_shrt: _ckd_add_2_shrt, \
    _ckd_ushrt: _ckd_add_2_ushrt, \
    _ckd_int: _ckd_add_2_int, \
    _ckd_uint: _ckd_add_2_uint, \
    _ckd_long: _ckd_add_2_long, \
    _ckd_ulong: _ckd_add_2_ulong, \
    _ckd_llong: _ckd_add_2_llong, \
    _ckd_ullong: _ckd_add_2_ullong, \
    _ckd_int128: _ckd_add_2_int128, \
    _ckd_uint128: _ckd_add_2_uint128, \
    default: _ckd_invalid)(_ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_add_3(r, a, b) \
    _Generic(_ckd_value(a) + _ckd_value(b) + *(r), \
    _ckd_schar: _ckd_add_3_schar, \
    _ckd_uchar: _ckd_add_3_uchar, \
    _ckd_shrt: _ckd_add_3_shrt, \
    _ckd_ushrt: _ckd_add_3_ushrt, \
    _ckd_int: _ckd_add_3_int, \
    _ckd_uint: _ckd_add_3_uint, \
    _ckd_long: _ckd_add_3_long, \
    _ckd_ulong: _ckd_add_3_ulong, \
    _ckd_llong: _ckd_add_3_llong, \
    _ckd_ullong: _ckd_add_3_ullong, \
    _ckd_int128: _ckd_add_3_int128, \
    _ckd_uint128: _ckd_add_3_uint128, \
    default: _ckd_invalid)((r), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_add_N(_2,_3,N,...) _ckd_add_##N
#define ckd_add(w, ...)  _ckd_add_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)


#define _ckd_sub_2(a, b)  \
    _Generic(_ckd_value(a) + _ckd_value(b), \
    _ckd_schar: _ckd_sub_2_schar, \
    _ckd_uchar: _ckd_sub_2_uchar, \
    _ckd_shrt: _ckd_sub_2_shrt, \
    _ckd_ushrt: _ckd_sub_2_ushrt, \
    _ckd_int: _ckd_sub_2_int, \
    _ckd_uint: _ckd_sub_2_uint, \
    _ckd_long: _ckd_sub_2_long, \
    _ckd_ulong: _ckd_sub_2_ulong, \
    _ckd_llong: _ckd_sub_2_llong, \
    _ckd_ullong: _ckd_sub_2_ullong, \
    _ckd_int128: _ckd_sub_2_int128, \
    _ckd_uint128: _ckd_sub_2_uint128, \
    default: _ckd_invalid)(_ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_sub_3(r, a, b) \
    _Generic(_ckd_value(a) + _ckd_value(b) + *(r), \
    _ckd_schar: _ckd_sub_3_schar, \
    _ckd_uchar: _ckd_sub_3_uchar, \
    _ckd_shrt: _ckd_sub_3_shrt, \
    _ckd_ushrt: _ckd_sub_3_ushrt, \
    _ckd_int: _ckd_sub_3_int, \
    _ckd_uint: _ckd_sub_3_uint, \
    _ckd_long: _ckd_sub_3_long, \
    _ckd_ulong: _ckd_sub_3_ulong, \
    _ckd_llong: _ckd_sub_3_llong, \
    _ckd_ullong: _ckd_sub_3_ullong, \
    _ckd_int128: _ckd_sub_3_int128, \
    _ckd_uint128: _ckd_sub_3_uint128, \
    default: _ckd_invalid)((r), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_sub_N(_2,_3,N,...) _ckd_sub_##N
#define ckd_sub(w, ...)  _ckd_sub_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)


#define _ckd_mul_2(a, b)  \
    _Generic(_ckd_value(a) + _ckd_value(b), \
    _ckd_schar: _ckd_mul_2_schar, \
    _ckd_uchar: _ckd_mul_2_uchar, \
    _ckd_shrt: _ckd_mul_2_shrt, \
    _ckd_ushrt: _ckd_mul_2_ushrt, \
    _ckd_int: _ckd_mul_2_int, \
    _ckd_uint: _ckd_mul_2_uint, \
    _ckd_long: _ckd_mul_2_long, \
    _ckd_ulong: _ckd_mul_2_ulong, \
    _ckd_llong: _ckd_mul_2_llong, \
    _ckd_ullong: _ckd_mul_2_ullong, \
    _ckd_int128: _ckd_mul_2_int128, \
    _ckd_uint128: _ckd_mul_2_uint128, \
    default: _ckd_invalid)(_ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_mul_3(r, a, b) \
    _Generic(_ckd_value(a) + _ckd_value(b) + *(r), \
    _ckd_schar: _ckd_mul_3_schar, \
    _ckd_uchar: _ckd_mul_3_uchar, \
    _ckd_shrt: _ckd_mul_3_shrt, \
    _ckd_ushrt: _ckd_mul_3_ushrt, \
    _ckd_int: _ckd_mul_3_int, \
    _ckd_uint: _ckd_mul_3_uint, \
    _ckd_long: _ckd_mul_3_long, \
    _ckd_ulong: _ckd_mul_3_ulong, \
    _ckd_llong: _ckd_mul_3_llong, \
    _ckd_ullong: _ckd_mul_3_ullong, \
    _ckd_int128: _ckd_mul_3_int128, \
    _ckd_uint128: _ckd_mul_3_uint128, \
    default: _ckd_invalid)((r), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_mul_N(_2,_3,N,...) _ckd_mul_##N
#define ckd_mul(w, ...)  _ckd_mul_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)


#define _ckd_div_2(a, b)  \
    _Generic(_ckd_value(a) + _ckd_value(b), \
    _ckd_schar: _ckd_div_2_schar, \
    _ckd_uchar: _ckd_div_2_uchar, \
    _ckd_shrt: _ckd_div_2_shrt, \
    _ckd_ushrt: _ckd_div_2_ushrt, \
    _ckd_int: _ckd_div_2_int, \
    _ckd_uint: _ckd_div_2_uint, \
    _ckd_long: _ckd_div_2_long, \
    _ckd_ulong: _ckd_div_2_ulong, \
    _ckd_llong: _ckd_div_2_llong, \
    _ckd_ullong: _ckd_div_2_ullong, \
    _ckd_int128: _ckd_div_2_int128, \
    _ckd_uint128: _ckd_div_2_uint128, \
    default: _ckd_invalid)(_ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_div_3(r, a, b) \
    _Generic(_ckd_value(a) + _ckd_value(b) + *(r), \
    _ckd_schar: _ckd_div_3_schar, \
    _ckd_uchar: _ckd_div_3_uchar, \
    _ckd_shrt: _ckd_div_3_shrt, \
    _ckd_ushrt: _ckd_div_3_ushrt, \
    _ckd_int: _ckd_div_3_int, \
    _ckd_uint: _ckd_div_3_uint, \
    _ckd_long: _ckd_div_3_long, \
    _ckd_ulong: _ckd_div_3_ulong, \
    _ckd_llong: _ckd_div_3_llong, \
    _ckd_ullong: _ckd_div_3_ullong, \
    _ckd_int128: _ckd_div_3_int128, \
    _ckd_uint128: _ckd_div_3_uint128, \
    default: _ckd_invalid)((r), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_div_N(_2,_3,N,...) _ckd_div_##N
#define ckd_div(w, ...)  _ckd_div_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)


// ]]]
// EOF [[[

#endif /* CKDINT_H_ */

// ]]]
