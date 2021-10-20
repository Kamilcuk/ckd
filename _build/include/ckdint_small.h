
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


#define _ckd_ONLYSAMETYPES  1

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
#elif __STDC_VERSION__ >  20230000L
#define _ckd_funcconst  _ckd_static [[__nodiscard__]]
#else
#define _ckd_funcconst _ckd_static
#endif

#define ckd_inexact(x)  ((x)._ineXact)
#define ckd_value(x)    ((x)._vaLue)

// ]]]
// Type specific [[[


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    signed char _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_schar_t;

#define _ckd_type_schar  signed char
#define _ckd_type_cschar ckd_schar_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_schar_t type that holds signed char variable type.
_ckd_funcconst ckd_schar_t ckd_mk_schar_t(signed char value, bool inexact) {
    return (ckd_schar_t){value, inexact};
}

#define _ckd_max_schar  (SCHAR_MAX)
#define _ckd_min_schar  (SCHAR_MIN)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    unsigned char _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_uchar_t;

#define _ckd_type_uchar  unsigned char
#define _ckd_type_cuchar ckd_uchar_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_uchar_t type that holds unsigned char variable type.
_ckd_funcconst ckd_uchar_t ckd_mk_uchar_t(unsigned char value, bool inexact) {
    return (ckd_uchar_t){value, inexact};
}

#define _ckd_max_uchar  (UCHAR_MAX)
#define _ckd_min_uchar  (0)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    short _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_shrt_t;

#define _ckd_type_shrt  short
#define _ckd_type_cshrt ckd_shrt_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_shrt_t type that holds short variable type.
_ckd_funcconst ckd_shrt_t ckd_mk_shrt_t(short value, bool inexact) {
    return (ckd_shrt_t){value, inexact};
}

#define _ckd_max_shrt  (SHRT_MAX)
#define _ckd_min_shrt  (SHRT_MIN)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    unsigned short _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_ushrt_t;

#define _ckd_type_ushrt  unsigned short
#define _ckd_type_cushrt ckd_ushrt_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_ushrt_t type that holds unsigned short variable type.
_ckd_funcconst ckd_ushrt_t ckd_mk_ushrt_t(unsigned short value, bool inexact) {
    return (ckd_ushrt_t){value, inexact};
}

#define _ckd_max_ushrt  (USHRT_MAX)
#define _ckd_min_ushrt  (0)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    int _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_int_t;

#define _ckd_type_int  int
#define _ckd_type_cint ckd_int_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_int_t type that holds int variable type.
_ckd_funcconst ckd_int_t ckd_mk_int_t(int value, bool inexact) {
    return (ckd_int_t){value, inexact};
}

#define _ckd_max_int  (INT_MAX)
#define _ckd_min_int  (INT_MIN)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    unsigned int _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_uint_t;

#define _ckd_type_uint  unsigned int
#define _ckd_type_cuint ckd_uint_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_uint_t type that holds unsigned int variable type.
_ckd_funcconst ckd_uint_t ckd_mk_uint_t(unsigned int value, bool inexact) {
    return (ckd_uint_t){value, inexact};
}

#define _ckd_max_uint  (UINT_MAX)
#define _ckd_min_uint  (0)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    long _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_long_t;

#define _ckd_type_long  long
#define _ckd_type_clong ckd_long_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_long_t type that holds long variable type.
_ckd_funcconst ckd_long_t ckd_mk_long_t(long value, bool inexact) {
    return (ckd_long_t){value, inexact};
}

#define _ckd_max_long  (LONG_MAX)
#define _ckd_min_long  (LONG_MIN)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    unsigned long _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_ulong_t;

#define _ckd_type_ulong  unsigned long
#define _ckd_type_culong ckd_ulong_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_ulong_t type that holds unsigned long variable type.
_ckd_funcconst ckd_ulong_t ckd_mk_ulong_t(unsigned long value, bool inexact) {
    return (ckd_ulong_t){value, inexact};
}

#define _ckd_max_ulong  (ULONG_MAX)
#define _ckd_min_ulong  (0)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    long long _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_llong_t;

#define _ckd_type_llong  long long
#define _ckd_type_cllong ckd_llong_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_llong_t type that holds long long variable type.
_ckd_funcconst ckd_llong_t ckd_mk_llong_t(long long value, bool inexact) {
    return (ckd_llong_t){value, inexact};
}

#define _ckd_max_llong  (LLONG_MAX)
#define _ckd_min_llong  (LLONG_MIN)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    unsigned long long _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_ullong_t;

#define _ckd_type_ullong  unsigned long long
#define _ckd_type_cullong ckd_ullong_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_ullong_t type that holds unsigned long long variable type.
_ckd_funcconst ckd_ullong_t ckd_mk_ullong_t(unsigned long long value, bool inexact) {
    return (ckd_ullong_t){value, inexact};
}

#define _ckd_max_ullong  (ULLONG_MAX)
#define _ckd_min_ullong  (0)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    __int128 _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_int128_t;

#define _ckd_type_int128  __int128
#define _ckd_type_cint128 ckd_int128_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_int128_t type that holds __int128 variable type.
_ckd_funcconst ckd_int128_t ckd_mk_int128_t(__int128 value, bool inexact) {
    return (ckd_int128_t){value, inexact};
}

#define _ckd_max_int128  (INT128_MAX)
#define _ckd_min_int128  (INT128_MIN)


/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    unsigned __int128 _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_uint128_t;

#define _ckd_type_uint128  unsigned __int128
#define _ckd_type_cuint128 ckd_uint128_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_uint128_t type that holds unsigned __int128 variable type.
_ckd_funcconst ckd_uint128_t ckd_mk_uint128_t(unsigned __int128 value, bool inexact) {
    return (ckd_uint128_t){value, inexact};
}

#define _ckd_max_uint128  (UINT128_MAX)
#define _ckd_min_uint128  (0)


// ]]]
// Type specific operation [[[


_ckd_static bool _ckd_add_3_schar_schar_schar_in(signed char *r, signed char a, signed char b) {
    const signed char max = _ckd_max_schar; (void)max;
    const signed char min = _ckd_min_schar; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_schar_schar_schar_in(signed char *r, signed char a, signed char b) {
    const signed char max = _ckd_max_schar; (void)max;
    const signed char min = _ckd_min_schar; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_schar_schar_schar_in(signed char *r, signed char a, signed char b) {
    const signed char max = _ckd_max_schar; (void)max;
    const signed char min = _ckd_min_schar; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_schar_schar_schar_in(signed char *r, signed char a, signed char b) {
    const signed char max = _ckd_max_schar; (void)max;
    const signed char min = _ckd_min_schar; (void)min;
    #if _ckd_min_schar != 0 && _ckd_min_schar < -_ckd_max_schar
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_uchar_uchar_uchar_in(unsigned char *r, unsigned char a, unsigned char b) {
    const unsigned char max = _ckd_max_uchar; (void)max;
    const unsigned char min = _ckd_min_uchar; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_uchar_uchar_uchar_in(unsigned char *r, unsigned char a, unsigned char b) {
    const unsigned char max = _ckd_max_uchar; (void)max;
    const unsigned char min = _ckd_min_uchar; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_uchar_uchar_uchar_in(unsigned char *r, unsigned char a, unsigned char b) {
    const unsigned char max = _ckd_max_uchar; (void)max;
    const unsigned char min = _ckd_min_uchar; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_uchar_uchar_uchar_in(unsigned char *r, unsigned char a, unsigned char b) {
    const unsigned char max = _ckd_max_uchar; (void)max;
    const unsigned char min = _ckd_min_uchar; (void)min;
    #if _ckd_min_uchar != 0 && _ckd_min_uchar < -_ckd_max_uchar
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_shrt_shrt_shrt_in(short *r, short a, short b) {
    const short max = _ckd_max_shrt; (void)max;
    const short min = _ckd_min_shrt; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_shrt_shrt_shrt_in(short *r, short a, short b) {
    const short max = _ckd_max_shrt; (void)max;
    const short min = _ckd_min_shrt; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_shrt_shrt_shrt_in(short *r, short a, short b) {
    const short max = _ckd_max_shrt; (void)max;
    const short min = _ckd_min_shrt; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_shrt_shrt_shrt_in(short *r, short a, short b) {
    const short max = _ckd_max_shrt; (void)max;
    const short min = _ckd_min_shrt; (void)min;
    #if _ckd_min_shrt != 0 && _ckd_min_shrt < -_ckd_max_shrt
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_ushrt_ushrt_ushrt_in(unsigned short *r, unsigned short a, unsigned short b) {
    const unsigned short max = _ckd_max_ushrt; (void)max;
    const unsigned short min = _ckd_min_ushrt; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_ushrt_ushrt_ushrt_in(unsigned short *r, unsigned short a, unsigned short b) {
    const unsigned short max = _ckd_max_ushrt; (void)max;
    const unsigned short min = _ckd_min_ushrt; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_ushrt_ushrt_ushrt_in(unsigned short *r, unsigned short a, unsigned short b) {
    const unsigned short max = _ckd_max_ushrt; (void)max;
    const unsigned short min = _ckd_min_ushrt; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_ushrt_ushrt_ushrt_in(unsigned short *r, unsigned short a, unsigned short b) {
    const unsigned short max = _ckd_max_ushrt; (void)max;
    const unsigned short min = _ckd_min_ushrt; (void)min;
    #if _ckd_min_ushrt != 0 && _ckd_min_ushrt < -_ckd_max_ushrt
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_int_int_int_in(int *r, int a, int b) {
    const int max = _ckd_max_int; (void)max;
    const int min = _ckd_min_int; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_int_int_int_in(int *r, int a, int b) {
    const int max = _ckd_max_int; (void)max;
    const int min = _ckd_min_int; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_int_int_int_in(int *r, int a, int b) {
    const int max = _ckd_max_int; (void)max;
    const int min = _ckd_min_int; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_int_int_int_in(int *r, int a, int b) {
    const int max = _ckd_max_int; (void)max;
    const int min = _ckd_min_int; (void)min;
    #if _ckd_min_int != 0 && _ckd_min_int < -_ckd_max_int
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_uint_uint_uint_in(unsigned int *r, unsigned int a, unsigned int b) {
    const unsigned int max = _ckd_max_uint; (void)max;
    const unsigned int min = _ckd_min_uint; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_uint_uint_uint_in(unsigned int *r, unsigned int a, unsigned int b) {
    const unsigned int max = _ckd_max_uint; (void)max;
    const unsigned int min = _ckd_min_uint; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_uint_uint_uint_in(unsigned int *r, unsigned int a, unsigned int b) {
    const unsigned int max = _ckd_max_uint; (void)max;
    const unsigned int min = _ckd_min_uint; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_uint_uint_uint_in(unsigned int *r, unsigned int a, unsigned int b) {
    const unsigned int max = _ckd_max_uint; (void)max;
    const unsigned int min = _ckd_min_uint; (void)min;
    #if _ckd_min_uint != 0 && _ckd_min_uint < -_ckd_max_uint
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_long_long_long_in(long *r, long a, long b) {
    const long max = _ckd_max_long; (void)max;
    const long min = _ckd_min_long; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_long_long_long_in(long *r, long a, long b) {
    const long max = _ckd_max_long; (void)max;
    const long min = _ckd_min_long; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_long_long_long_in(long *r, long a, long b) {
    const long max = _ckd_max_long; (void)max;
    const long min = _ckd_min_long; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_long_long_long_in(long *r, long a, long b) {
    const long max = _ckd_max_long; (void)max;
    const long min = _ckd_min_long; (void)min;
    #if _ckd_min_long != 0 && _ckd_min_long < -_ckd_max_long
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_ulong_ulong_ulong_in(unsigned long *r, unsigned long a, unsigned long b) {
    const unsigned long max = _ckd_max_ulong; (void)max;
    const unsigned long min = _ckd_min_ulong; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_ulong_ulong_ulong_in(unsigned long *r, unsigned long a, unsigned long b) {
    const unsigned long max = _ckd_max_ulong; (void)max;
    const unsigned long min = _ckd_min_ulong; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_ulong_ulong_ulong_in(unsigned long *r, unsigned long a, unsigned long b) {
    const unsigned long max = _ckd_max_ulong; (void)max;
    const unsigned long min = _ckd_min_ulong; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_ulong_ulong_ulong_in(unsigned long *r, unsigned long a, unsigned long b) {
    const unsigned long max = _ckd_max_ulong; (void)max;
    const unsigned long min = _ckd_min_ulong; (void)min;
    #if _ckd_min_ulong != 0 && _ckd_min_ulong < -_ckd_max_ulong
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_llong_llong_llong_in(long long *r, long long a, long long b) {
    const long long max = _ckd_max_llong; (void)max;
    const long long min = _ckd_min_llong; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_llong_llong_llong_in(long long *r, long long a, long long b) {
    const long long max = _ckd_max_llong; (void)max;
    const long long min = _ckd_min_llong; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_llong_llong_llong_in(long long *r, long long a, long long b) {
    const long long max = _ckd_max_llong; (void)max;
    const long long min = _ckd_min_llong; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_llong_llong_llong_in(long long *r, long long a, long long b) {
    const long long max = _ckd_max_llong; (void)max;
    const long long min = _ckd_min_llong; (void)min;
    #if _ckd_min_llong != 0 && _ckd_min_llong < -_ckd_max_llong
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_ullong_ullong_ullong_in(unsigned long long *r, unsigned long long a, unsigned long long b) {
    const unsigned long long max = _ckd_max_ullong; (void)max;
    const unsigned long long min = _ckd_min_ullong; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_ullong_ullong_ullong_in(unsigned long long *r, unsigned long long a, unsigned long long b) {
    const unsigned long long max = _ckd_max_ullong; (void)max;
    const unsigned long long min = _ckd_min_ullong; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_ullong_ullong_ullong_in(unsigned long long *r, unsigned long long a, unsigned long long b) {
    const unsigned long long max = _ckd_max_ullong; (void)max;
    const unsigned long long min = _ckd_min_ullong; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_ullong_ullong_ullong_in(unsigned long long *r, unsigned long long a, unsigned long long b) {
    const unsigned long long max = _ckd_max_ullong; (void)max;
    const unsigned long long min = _ckd_min_ullong; (void)min;
    #if _ckd_min_ullong != 0 && _ckd_min_ullong < -_ckd_max_ullong
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_int128_int128_int128_in(__int128 *r, __int128 a, __int128 b) {
    const __int128 max = _ckd_max_int128; (void)max;
    const __int128 min = _ckd_min_int128; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_int128_int128_int128_in(__int128 *r, __int128 a, __int128 b) {
    const __int128 max = _ckd_max_int128; (void)max;
    const __int128 min = _ckd_min_int128; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_int128_int128_int128_in(__int128 *r, __int128 a, __int128 b) {
    const __int128 max = _ckd_max_int128; (void)max;
    const __int128 min = _ckd_min_int128; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_int128_int128_int128_in(__int128 *r, __int128 a, __int128 b) {
    const __int128 max = _ckd_max_int128; (void)max;
    const __int128 min = _ckd_min_int128; (void)min;
    #if True
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


_ckd_static bool _ckd_add_3_uint128_uint128_uint128_in(unsigned __int128 *r, unsigned __int128 a, unsigned __int128 b) {
    const unsigned __int128 max = _ckd_max_uint128; (void)max;
    const unsigned __int128 min = _ckd_min_uint128; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_add_overflow(a, b, r);
#else // __GNUC__
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
#endif // __GNUC__
}


_ckd_static bool _ckd_sub_3_uint128_uint128_uint128_in(unsigned __int128 *r, unsigned __int128 a, unsigned __int128 b) {
    const unsigned __int128 max = _ckd_max_uint128; (void)max;
    const unsigned __int128 min = _ckd_min_uint128; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_sub_overflow(a, b, r);
#else // __GNUC__
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
#endif // __GNUC__
}


_ckd_static bool _ckd_mul_3_uint128_uint128_uint128_in(unsigned __int128 *r, unsigned __int128 a, unsigned __int128 b) {
    const unsigned __int128 max = _ckd_max_uint128; (void)max;
    const unsigned __int128 min = _ckd_min_uint128; (void)min;
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_mul_overflow(a, b, r);
#else // __GNUC__
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
#endif // __GNUC__
}


_ckd_static bool _ckd_div_3_uint128_uint128_uint128_in(unsigned __int128 *r, unsigned __int128 a, unsigned __int128 b) {
    const unsigned __int128 max = _ckd_max_uint128; (void)max;
    const unsigned __int128 min = _ckd_min_uint128; (void)min;
    #if False
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
}


// ]]]
// Each type with every type operations [[[



// Operation add on schar and schar -> schar
_ckd_static bool _ckd_add_3_schar_schar_schar(_ckd_type_schar *r, _ckd_type_schar a, _ckd_type_schar b) {
    return _ckd_add_3_schar_schar_schar_in(r, a, b);
}
_ckd_funcconst ckd_schar_t _ckd_add_2_schar_schar_schar(_ckd_type_schar a, _ckd_type_schar b) {
    ckd_schar_t r; r._ineXact = _ckd_add_3_schar_schar_schar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_schar_cschar_schar(_ckd_type_schar *r, _ckd_type_cschar a, _ckd_type_schar b) {
    return _ckd_add_3_schar_schar_schar(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_schar_t _ckd_add_2_schar_cschar_schar(_ckd_type_cschar a, _ckd_type_schar b) {
    ckd_schar_t r; r._ineXact = _ckd_add_3_schar_cschar_schar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_schar_schar_cschar(_ckd_type_schar *r, _ckd_type_schar a, _ckd_type_cschar b) {
    return _ckd_add_3_schar_schar_schar(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_schar_t _ckd_add_2_schar_schar_cschar(_ckd_type_schar a, _ckd_type_cschar b) {
    ckd_schar_t r; r._ineXact = _ckd_add_3_schar_schar_cschar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_schar_cschar_cschar(_ckd_type_schar *r, _ckd_type_cschar a, _ckd_type_cschar b) {
    return _ckd_add_3_schar_schar_schar(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_schar_t _ckd_add_2_schar_cschar_cschar(_ckd_type_cschar a, _ckd_type_cschar b) {
    ckd_schar_t r; r._ineXact = _ckd_add_3_schar_cschar_cschar(&r._vaLue, a, b); return r;
}
// Operation add on uchar and uchar -> uchar
_ckd_static bool _ckd_add_3_uchar_uchar_uchar(_ckd_type_uchar *r, _ckd_type_uchar a, _ckd_type_uchar b) {
    return _ckd_add_3_uchar_uchar_uchar_in(r, a, b);
}
_ckd_funcconst ckd_uchar_t _ckd_add_2_uchar_uchar_uchar(_ckd_type_uchar a, _ckd_type_uchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_add_3_uchar_uchar_uchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_uchar_cuchar_uchar(_ckd_type_uchar *r, _ckd_type_cuchar a, _ckd_type_uchar b) {
    return _ckd_add_3_uchar_uchar_uchar(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uchar_t _ckd_add_2_uchar_cuchar_uchar(_ckd_type_cuchar a, _ckd_type_uchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_add_3_uchar_cuchar_uchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_uchar_uchar_cuchar(_ckd_type_uchar *r, _ckd_type_uchar a, _ckd_type_cuchar b) {
    return _ckd_add_3_uchar_uchar_uchar(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uchar_t _ckd_add_2_uchar_uchar_cuchar(_ckd_type_uchar a, _ckd_type_cuchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_add_3_uchar_uchar_cuchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_uchar_cuchar_cuchar(_ckd_type_uchar *r, _ckd_type_cuchar a, _ckd_type_cuchar b) {
    return _ckd_add_3_uchar_uchar_uchar(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uchar_t _ckd_add_2_uchar_cuchar_cuchar(_ckd_type_cuchar a, _ckd_type_cuchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_add_3_uchar_cuchar_cuchar(&r._vaLue, a, b); return r;
}
// Operation add on shrt and shrt -> shrt
_ckd_static bool _ckd_add_3_shrt_shrt_shrt(_ckd_type_shrt *r, _ckd_type_shrt a, _ckd_type_shrt b) {
    return _ckd_add_3_shrt_shrt_shrt_in(r, a, b);
}
_ckd_funcconst ckd_shrt_t _ckd_add_2_shrt_shrt_shrt(_ckd_type_shrt a, _ckd_type_shrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_add_3_shrt_shrt_shrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_shrt_cshrt_shrt(_ckd_type_shrt *r, _ckd_type_cshrt a, _ckd_type_shrt b) {
    return _ckd_add_3_shrt_shrt_shrt(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_shrt_t _ckd_add_2_shrt_cshrt_shrt(_ckd_type_cshrt a, _ckd_type_shrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_add_3_shrt_cshrt_shrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_shrt_shrt_cshrt(_ckd_type_shrt *r, _ckd_type_shrt a, _ckd_type_cshrt b) {
    return _ckd_add_3_shrt_shrt_shrt(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_shrt_t _ckd_add_2_shrt_shrt_cshrt(_ckd_type_shrt a, _ckd_type_cshrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_add_3_shrt_shrt_cshrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_shrt_cshrt_cshrt(_ckd_type_shrt *r, _ckd_type_cshrt a, _ckd_type_cshrt b) {
    return _ckd_add_3_shrt_shrt_shrt(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_shrt_t _ckd_add_2_shrt_cshrt_cshrt(_ckd_type_cshrt a, _ckd_type_cshrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_add_3_shrt_cshrt_cshrt(&r._vaLue, a, b); return r;
}
// Operation add on ushrt and ushrt -> ushrt
_ckd_static bool _ckd_add_3_ushrt_ushrt_ushrt(_ckd_type_ushrt *r, _ckd_type_ushrt a, _ckd_type_ushrt b) {
    return _ckd_add_3_ushrt_ushrt_ushrt_in(r, a, b);
}
_ckd_funcconst ckd_ushrt_t _ckd_add_2_ushrt_ushrt_ushrt(_ckd_type_ushrt a, _ckd_type_ushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_add_3_ushrt_ushrt_ushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_ushrt_cushrt_ushrt(_ckd_type_ushrt *r, _ckd_type_cushrt a, _ckd_type_ushrt b) {
    return _ckd_add_3_ushrt_ushrt_ushrt(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ushrt_t _ckd_add_2_ushrt_cushrt_ushrt(_ckd_type_cushrt a, _ckd_type_ushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_add_3_ushrt_cushrt_ushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_ushrt_ushrt_cushrt(_ckd_type_ushrt *r, _ckd_type_ushrt a, _ckd_type_cushrt b) {
    return _ckd_add_3_ushrt_ushrt_ushrt(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ushrt_t _ckd_add_2_ushrt_ushrt_cushrt(_ckd_type_ushrt a, _ckd_type_cushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_add_3_ushrt_ushrt_cushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_ushrt_cushrt_cushrt(_ckd_type_ushrt *r, _ckd_type_cushrt a, _ckd_type_cushrt b) {
    return _ckd_add_3_ushrt_ushrt_ushrt(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ushrt_t _ckd_add_2_ushrt_cushrt_cushrt(_ckd_type_cushrt a, _ckd_type_cushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_add_3_ushrt_cushrt_cushrt(&r._vaLue, a, b); return r;
}
// Operation add on int and int -> int
_ckd_static bool _ckd_add_3_int_int_int(_ckd_type_int *r, _ckd_type_int a, _ckd_type_int b) {
    return _ckd_add_3_int_int_int_in(r, a, b);
}
_ckd_funcconst ckd_int_t _ckd_add_2_int_int_int(_ckd_type_int a, _ckd_type_int b) {
    ckd_int_t r; r._ineXact = _ckd_add_3_int_int_int(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_int_cint_int(_ckd_type_int *r, _ckd_type_cint a, _ckd_type_int b) {
    return _ckd_add_3_int_int_int(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_int_t _ckd_add_2_int_cint_int(_ckd_type_cint a, _ckd_type_int b) {
    ckd_int_t r; r._ineXact = _ckd_add_3_int_cint_int(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_int_int_cint(_ckd_type_int *r, _ckd_type_int a, _ckd_type_cint b) {
    return _ckd_add_3_int_int_int(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_int_t _ckd_add_2_int_int_cint(_ckd_type_int a, _ckd_type_cint b) {
    ckd_int_t r; r._ineXact = _ckd_add_3_int_int_cint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_int_cint_cint(_ckd_type_int *r, _ckd_type_cint a, _ckd_type_cint b) {
    return _ckd_add_3_int_int_int(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_int_t _ckd_add_2_int_cint_cint(_ckd_type_cint a, _ckd_type_cint b) {
    ckd_int_t r; r._ineXact = _ckd_add_3_int_cint_cint(&r._vaLue, a, b); return r;
}
// Operation add on uint and uint -> uint
_ckd_static bool _ckd_add_3_uint_uint_uint(_ckd_type_uint *r, _ckd_type_uint a, _ckd_type_uint b) {
    return _ckd_add_3_uint_uint_uint_in(r, a, b);
}
_ckd_funcconst ckd_uint_t _ckd_add_2_uint_uint_uint(_ckd_type_uint a, _ckd_type_uint b) {
    ckd_uint_t r; r._ineXact = _ckd_add_3_uint_uint_uint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_uint_cuint_uint(_ckd_type_uint *r, _ckd_type_cuint a, _ckd_type_uint b) {
    return _ckd_add_3_uint_uint_uint(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uint_t _ckd_add_2_uint_cuint_uint(_ckd_type_cuint a, _ckd_type_uint b) {
    ckd_uint_t r; r._ineXact = _ckd_add_3_uint_cuint_uint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_uint_uint_cuint(_ckd_type_uint *r, _ckd_type_uint a, _ckd_type_cuint b) {
    return _ckd_add_3_uint_uint_uint(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uint_t _ckd_add_2_uint_uint_cuint(_ckd_type_uint a, _ckd_type_cuint b) {
    ckd_uint_t r; r._ineXact = _ckd_add_3_uint_uint_cuint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_uint_cuint_cuint(_ckd_type_uint *r, _ckd_type_cuint a, _ckd_type_cuint b) {
    return _ckd_add_3_uint_uint_uint(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uint_t _ckd_add_2_uint_cuint_cuint(_ckd_type_cuint a, _ckd_type_cuint b) {
    ckd_uint_t r; r._ineXact = _ckd_add_3_uint_cuint_cuint(&r._vaLue, a, b); return r;
}
// Operation add on long and long -> long
_ckd_static bool _ckd_add_3_long_long_long(_ckd_type_long *r, _ckd_type_long a, _ckd_type_long b) {
    return _ckd_add_3_long_long_long_in(r, a, b);
}
_ckd_funcconst ckd_long_t _ckd_add_2_long_long_long(_ckd_type_long a, _ckd_type_long b) {
    ckd_long_t r; r._ineXact = _ckd_add_3_long_long_long(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_long_clong_long(_ckd_type_long *r, _ckd_type_clong a, _ckd_type_long b) {
    return _ckd_add_3_long_long_long(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_long_t _ckd_add_2_long_clong_long(_ckd_type_clong a, _ckd_type_long b) {
    ckd_long_t r; r._ineXact = _ckd_add_3_long_clong_long(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_long_long_clong(_ckd_type_long *r, _ckd_type_long a, _ckd_type_clong b) {
    return _ckd_add_3_long_long_long(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_long_t _ckd_add_2_long_long_clong(_ckd_type_long a, _ckd_type_clong b) {
    ckd_long_t r; r._ineXact = _ckd_add_3_long_long_clong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_long_clong_clong(_ckd_type_long *r, _ckd_type_clong a, _ckd_type_clong b) {
    return _ckd_add_3_long_long_long(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_long_t _ckd_add_2_long_clong_clong(_ckd_type_clong a, _ckd_type_clong b) {
    ckd_long_t r; r._ineXact = _ckd_add_3_long_clong_clong(&r._vaLue, a, b); return r;
}
// Operation add on ulong and ulong -> ulong
_ckd_static bool _ckd_add_3_ulong_ulong_ulong(_ckd_type_ulong *r, _ckd_type_ulong a, _ckd_type_ulong b) {
    return _ckd_add_3_ulong_ulong_ulong_in(r, a, b);
}
_ckd_funcconst ckd_ulong_t _ckd_add_2_ulong_ulong_ulong(_ckd_type_ulong a, _ckd_type_ulong b) {
    ckd_ulong_t r; r._ineXact = _ckd_add_3_ulong_ulong_ulong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_ulong_culong_ulong(_ckd_type_ulong *r, _ckd_type_culong a, _ckd_type_ulong b) {
    return _ckd_add_3_ulong_ulong_ulong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ulong_t _ckd_add_2_ulong_culong_ulong(_ckd_type_culong a, _ckd_type_ulong b) {
    ckd_ulong_t r; r._ineXact = _ckd_add_3_ulong_culong_ulong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_ulong_ulong_culong(_ckd_type_ulong *r, _ckd_type_ulong a, _ckd_type_culong b) {
    return _ckd_add_3_ulong_ulong_ulong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ulong_t _ckd_add_2_ulong_ulong_culong(_ckd_type_ulong a, _ckd_type_culong b) {
    ckd_ulong_t r; r._ineXact = _ckd_add_3_ulong_ulong_culong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_ulong_culong_culong(_ckd_type_ulong *r, _ckd_type_culong a, _ckd_type_culong b) {
    return _ckd_add_3_ulong_ulong_ulong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ulong_t _ckd_add_2_ulong_culong_culong(_ckd_type_culong a, _ckd_type_culong b) {
    ckd_ulong_t r; r._ineXact = _ckd_add_3_ulong_culong_culong(&r._vaLue, a, b); return r;
}
// Operation add on llong and llong -> llong
_ckd_static bool _ckd_add_3_llong_llong_llong(_ckd_type_llong *r, _ckd_type_llong a, _ckd_type_llong b) {
    return _ckd_add_3_llong_llong_llong_in(r, a, b);
}
_ckd_funcconst ckd_llong_t _ckd_add_2_llong_llong_llong(_ckd_type_llong a, _ckd_type_llong b) {
    ckd_llong_t r; r._ineXact = _ckd_add_3_llong_llong_llong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_llong_cllong_llong(_ckd_type_llong *r, _ckd_type_cllong a, _ckd_type_llong b) {
    return _ckd_add_3_llong_llong_llong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_llong_t _ckd_add_2_llong_cllong_llong(_ckd_type_cllong a, _ckd_type_llong b) {
    ckd_llong_t r; r._ineXact = _ckd_add_3_llong_cllong_llong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_llong_llong_cllong(_ckd_type_llong *r, _ckd_type_llong a, _ckd_type_cllong b) {
    return _ckd_add_3_llong_llong_llong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_llong_t _ckd_add_2_llong_llong_cllong(_ckd_type_llong a, _ckd_type_cllong b) {
    ckd_llong_t r; r._ineXact = _ckd_add_3_llong_llong_cllong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_llong_cllong_cllong(_ckd_type_llong *r, _ckd_type_cllong a, _ckd_type_cllong b) {
    return _ckd_add_3_llong_llong_llong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_llong_t _ckd_add_2_llong_cllong_cllong(_ckd_type_cllong a, _ckd_type_cllong b) {
    ckd_llong_t r; r._ineXact = _ckd_add_3_llong_cllong_cllong(&r._vaLue, a, b); return r;
}
// Operation add on ullong and ullong -> ullong
_ckd_static bool _ckd_add_3_ullong_ullong_ullong(_ckd_type_ullong *r, _ckd_type_ullong a, _ckd_type_ullong b) {
    return _ckd_add_3_ullong_ullong_ullong_in(r, a, b);
}
_ckd_funcconst ckd_ullong_t _ckd_add_2_ullong_ullong_ullong(_ckd_type_ullong a, _ckd_type_ullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_add_3_ullong_ullong_ullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_ullong_cullong_ullong(_ckd_type_ullong *r, _ckd_type_cullong a, _ckd_type_ullong b) {
    return _ckd_add_3_ullong_ullong_ullong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ullong_t _ckd_add_2_ullong_cullong_ullong(_ckd_type_cullong a, _ckd_type_ullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_add_3_ullong_cullong_ullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_ullong_ullong_cullong(_ckd_type_ullong *r, _ckd_type_ullong a, _ckd_type_cullong b) {
    return _ckd_add_3_ullong_ullong_ullong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ullong_t _ckd_add_2_ullong_ullong_cullong(_ckd_type_ullong a, _ckd_type_cullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_add_3_ullong_ullong_cullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_ullong_cullong_cullong(_ckd_type_ullong *r, _ckd_type_cullong a, _ckd_type_cullong b) {
    return _ckd_add_3_ullong_ullong_ullong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ullong_t _ckd_add_2_ullong_cullong_cullong(_ckd_type_cullong a, _ckd_type_cullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_add_3_ullong_cullong_cullong(&r._vaLue, a, b); return r;
}
// Operation add on int128 and int128 -> int128
_ckd_static bool _ckd_add_3_int128_int128_int128(_ckd_type_int128 *r, _ckd_type_int128 a, _ckd_type_int128 b) {
    return _ckd_add_3_int128_int128_int128_in(r, a, b);
}
_ckd_funcconst ckd_int128_t _ckd_add_2_int128_int128_int128(_ckd_type_int128 a, _ckd_type_int128 b) {
    ckd_int128_t r; r._ineXact = _ckd_add_3_int128_int128_int128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_int128_cint128_int128(_ckd_type_int128 *r, _ckd_type_cint128 a, _ckd_type_int128 b) {
    return _ckd_add_3_int128_int128_int128(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_int128_t _ckd_add_2_int128_cint128_int128(_ckd_type_cint128 a, _ckd_type_int128 b) {
    ckd_int128_t r; r._ineXact = _ckd_add_3_int128_cint128_int128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_int128_int128_cint128(_ckd_type_int128 *r, _ckd_type_int128 a, _ckd_type_cint128 b) {
    return _ckd_add_3_int128_int128_int128(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_int128_t _ckd_add_2_int128_int128_cint128(_ckd_type_int128 a, _ckd_type_cint128 b) {
    ckd_int128_t r; r._ineXact = _ckd_add_3_int128_int128_cint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_int128_cint128_cint128(_ckd_type_int128 *r, _ckd_type_cint128 a, _ckd_type_cint128 b) {
    return _ckd_add_3_int128_int128_int128(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_int128_t _ckd_add_2_int128_cint128_cint128(_ckd_type_cint128 a, _ckd_type_cint128 b) {
    ckd_int128_t r; r._ineXact = _ckd_add_3_int128_cint128_cint128(&r._vaLue, a, b); return r;
}
// Operation add on uint128 and uint128 -> uint128
_ckd_static bool _ckd_add_3_uint128_uint128_uint128(_ckd_type_uint128 *r, _ckd_type_uint128 a, _ckd_type_uint128 b) {
    return _ckd_add_3_uint128_uint128_uint128_in(r, a, b);
}
_ckd_funcconst ckd_uint128_t _ckd_add_2_uint128_uint128_uint128(_ckd_type_uint128 a, _ckd_type_uint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_add_3_uint128_uint128_uint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_uint128_cuint128_uint128(_ckd_type_uint128 *r, _ckd_type_cuint128 a, _ckd_type_uint128 b) {
    return _ckd_add_3_uint128_uint128_uint128(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uint128_t _ckd_add_2_uint128_cuint128_uint128(_ckd_type_cuint128 a, _ckd_type_uint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_add_3_uint128_cuint128_uint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_uint128_uint128_cuint128(_ckd_type_uint128 *r, _ckd_type_uint128 a, _ckd_type_cuint128 b) {
    return _ckd_add_3_uint128_uint128_uint128(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uint128_t _ckd_add_2_uint128_uint128_cuint128(_ckd_type_uint128 a, _ckd_type_cuint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_add_3_uint128_uint128_cuint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_add_3_uint128_cuint128_cuint128(_ckd_type_uint128 *r, _ckd_type_cuint128 a, _ckd_type_cuint128 b) {
    return _ckd_add_3_uint128_uint128_uint128(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uint128_t _ckd_add_2_uint128_cuint128_cuint128(_ckd_type_cuint128 a, _ckd_type_cuint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_add_3_uint128_cuint128_cuint128(&r._vaLue, a, b); return r;
}
// Operation sub on schar and schar -> schar
_ckd_static bool _ckd_sub_3_schar_schar_schar(_ckd_type_schar *r, _ckd_type_schar a, _ckd_type_schar b) {
    return _ckd_sub_3_schar_schar_schar_in(r, a, b);
}
_ckd_funcconst ckd_schar_t _ckd_sub_2_schar_schar_schar(_ckd_type_schar a, _ckd_type_schar b) {
    ckd_schar_t r; r._ineXact = _ckd_sub_3_schar_schar_schar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_schar_cschar_schar(_ckd_type_schar *r, _ckd_type_cschar a, _ckd_type_schar b) {
    return _ckd_sub_3_schar_schar_schar(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_schar_t _ckd_sub_2_schar_cschar_schar(_ckd_type_cschar a, _ckd_type_schar b) {
    ckd_schar_t r; r._ineXact = _ckd_sub_3_schar_cschar_schar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_schar_schar_cschar(_ckd_type_schar *r, _ckd_type_schar a, _ckd_type_cschar b) {
    return _ckd_sub_3_schar_schar_schar(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_schar_t _ckd_sub_2_schar_schar_cschar(_ckd_type_schar a, _ckd_type_cschar b) {
    ckd_schar_t r; r._ineXact = _ckd_sub_3_schar_schar_cschar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_schar_cschar_cschar(_ckd_type_schar *r, _ckd_type_cschar a, _ckd_type_cschar b) {
    return _ckd_sub_3_schar_schar_schar(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_schar_t _ckd_sub_2_schar_cschar_cschar(_ckd_type_cschar a, _ckd_type_cschar b) {
    ckd_schar_t r; r._ineXact = _ckd_sub_3_schar_cschar_cschar(&r._vaLue, a, b); return r;
}
// Operation sub on uchar and uchar -> uchar
_ckd_static bool _ckd_sub_3_uchar_uchar_uchar(_ckd_type_uchar *r, _ckd_type_uchar a, _ckd_type_uchar b) {
    return _ckd_sub_3_uchar_uchar_uchar_in(r, a, b);
}
_ckd_funcconst ckd_uchar_t _ckd_sub_2_uchar_uchar_uchar(_ckd_type_uchar a, _ckd_type_uchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_sub_3_uchar_uchar_uchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_uchar_cuchar_uchar(_ckd_type_uchar *r, _ckd_type_cuchar a, _ckd_type_uchar b) {
    return _ckd_sub_3_uchar_uchar_uchar(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uchar_t _ckd_sub_2_uchar_cuchar_uchar(_ckd_type_cuchar a, _ckd_type_uchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_sub_3_uchar_cuchar_uchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_uchar_uchar_cuchar(_ckd_type_uchar *r, _ckd_type_uchar a, _ckd_type_cuchar b) {
    return _ckd_sub_3_uchar_uchar_uchar(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uchar_t _ckd_sub_2_uchar_uchar_cuchar(_ckd_type_uchar a, _ckd_type_cuchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_sub_3_uchar_uchar_cuchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_uchar_cuchar_cuchar(_ckd_type_uchar *r, _ckd_type_cuchar a, _ckd_type_cuchar b) {
    return _ckd_sub_3_uchar_uchar_uchar(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uchar_t _ckd_sub_2_uchar_cuchar_cuchar(_ckd_type_cuchar a, _ckd_type_cuchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_sub_3_uchar_cuchar_cuchar(&r._vaLue, a, b); return r;
}
// Operation sub on shrt and shrt -> shrt
_ckd_static bool _ckd_sub_3_shrt_shrt_shrt(_ckd_type_shrt *r, _ckd_type_shrt a, _ckd_type_shrt b) {
    return _ckd_sub_3_shrt_shrt_shrt_in(r, a, b);
}
_ckd_funcconst ckd_shrt_t _ckd_sub_2_shrt_shrt_shrt(_ckd_type_shrt a, _ckd_type_shrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_sub_3_shrt_shrt_shrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_shrt_cshrt_shrt(_ckd_type_shrt *r, _ckd_type_cshrt a, _ckd_type_shrt b) {
    return _ckd_sub_3_shrt_shrt_shrt(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_shrt_t _ckd_sub_2_shrt_cshrt_shrt(_ckd_type_cshrt a, _ckd_type_shrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_sub_3_shrt_cshrt_shrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_shrt_shrt_cshrt(_ckd_type_shrt *r, _ckd_type_shrt a, _ckd_type_cshrt b) {
    return _ckd_sub_3_shrt_shrt_shrt(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_shrt_t _ckd_sub_2_shrt_shrt_cshrt(_ckd_type_shrt a, _ckd_type_cshrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_sub_3_shrt_shrt_cshrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_shrt_cshrt_cshrt(_ckd_type_shrt *r, _ckd_type_cshrt a, _ckd_type_cshrt b) {
    return _ckd_sub_3_shrt_shrt_shrt(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_shrt_t _ckd_sub_2_shrt_cshrt_cshrt(_ckd_type_cshrt a, _ckd_type_cshrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_sub_3_shrt_cshrt_cshrt(&r._vaLue, a, b); return r;
}
// Operation sub on ushrt and ushrt -> ushrt
_ckd_static bool _ckd_sub_3_ushrt_ushrt_ushrt(_ckd_type_ushrt *r, _ckd_type_ushrt a, _ckd_type_ushrt b) {
    return _ckd_sub_3_ushrt_ushrt_ushrt_in(r, a, b);
}
_ckd_funcconst ckd_ushrt_t _ckd_sub_2_ushrt_ushrt_ushrt(_ckd_type_ushrt a, _ckd_type_ushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_sub_3_ushrt_ushrt_ushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_ushrt_cushrt_ushrt(_ckd_type_ushrt *r, _ckd_type_cushrt a, _ckd_type_ushrt b) {
    return _ckd_sub_3_ushrt_ushrt_ushrt(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ushrt_t _ckd_sub_2_ushrt_cushrt_ushrt(_ckd_type_cushrt a, _ckd_type_ushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_sub_3_ushrt_cushrt_ushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_ushrt_ushrt_cushrt(_ckd_type_ushrt *r, _ckd_type_ushrt a, _ckd_type_cushrt b) {
    return _ckd_sub_3_ushrt_ushrt_ushrt(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ushrt_t _ckd_sub_2_ushrt_ushrt_cushrt(_ckd_type_ushrt a, _ckd_type_cushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_sub_3_ushrt_ushrt_cushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_ushrt_cushrt_cushrt(_ckd_type_ushrt *r, _ckd_type_cushrt a, _ckd_type_cushrt b) {
    return _ckd_sub_3_ushrt_ushrt_ushrt(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ushrt_t _ckd_sub_2_ushrt_cushrt_cushrt(_ckd_type_cushrt a, _ckd_type_cushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_sub_3_ushrt_cushrt_cushrt(&r._vaLue, a, b); return r;
}
// Operation sub on int and int -> int
_ckd_static bool _ckd_sub_3_int_int_int(_ckd_type_int *r, _ckd_type_int a, _ckd_type_int b) {
    return _ckd_sub_3_int_int_int_in(r, a, b);
}
_ckd_funcconst ckd_int_t _ckd_sub_2_int_int_int(_ckd_type_int a, _ckd_type_int b) {
    ckd_int_t r; r._ineXact = _ckd_sub_3_int_int_int(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_int_cint_int(_ckd_type_int *r, _ckd_type_cint a, _ckd_type_int b) {
    return _ckd_sub_3_int_int_int(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_int_t _ckd_sub_2_int_cint_int(_ckd_type_cint a, _ckd_type_int b) {
    ckd_int_t r; r._ineXact = _ckd_sub_3_int_cint_int(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_int_int_cint(_ckd_type_int *r, _ckd_type_int a, _ckd_type_cint b) {
    return _ckd_sub_3_int_int_int(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_int_t _ckd_sub_2_int_int_cint(_ckd_type_int a, _ckd_type_cint b) {
    ckd_int_t r; r._ineXact = _ckd_sub_3_int_int_cint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_int_cint_cint(_ckd_type_int *r, _ckd_type_cint a, _ckd_type_cint b) {
    return _ckd_sub_3_int_int_int(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_int_t _ckd_sub_2_int_cint_cint(_ckd_type_cint a, _ckd_type_cint b) {
    ckd_int_t r; r._ineXact = _ckd_sub_3_int_cint_cint(&r._vaLue, a, b); return r;
}
// Operation sub on uint and uint -> uint
_ckd_static bool _ckd_sub_3_uint_uint_uint(_ckd_type_uint *r, _ckd_type_uint a, _ckd_type_uint b) {
    return _ckd_sub_3_uint_uint_uint_in(r, a, b);
}
_ckd_funcconst ckd_uint_t _ckd_sub_2_uint_uint_uint(_ckd_type_uint a, _ckd_type_uint b) {
    ckd_uint_t r; r._ineXact = _ckd_sub_3_uint_uint_uint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_uint_cuint_uint(_ckd_type_uint *r, _ckd_type_cuint a, _ckd_type_uint b) {
    return _ckd_sub_3_uint_uint_uint(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uint_t _ckd_sub_2_uint_cuint_uint(_ckd_type_cuint a, _ckd_type_uint b) {
    ckd_uint_t r; r._ineXact = _ckd_sub_3_uint_cuint_uint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_uint_uint_cuint(_ckd_type_uint *r, _ckd_type_uint a, _ckd_type_cuint b) {
    return _ckd_sub_3_uint_uint_uint(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uint_t _ckd_sub_2_uint_uint_cuint(_ckd_type_uint a, _ckd_type_cuint b) {
    ckd_uint_t r; r._ineXact = _ckd_sub_3_uint_uint_cuint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_uint_cuint_cuint(_ckd_type_uint *r, _ckd_type_cuint a, _ckd_type_cuint b) {
    return _ckd_sub_3_uint_uint_uint(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uint_t _ckd_sub_2_uint_cuint_cuint(_ckd_type_cuint a, _ckd_type_cuint b) {
    ckd_uint_t r; r._ineXact = _ckd_sub_3_uint_cuint_cuint(&r._vaLue, a, b); return r;
}
// Operation sub on long and long -> long
_ckd_static bool _ckd_sub_3_long_long_long(_ckd_type_long *r, _ckd_type_long a, _ckd_type_long b) {
    return _ckd_sub_3_long_long_long_in(r, a, b);
}
_ckd_funcconst ckd_long_t _ckd_sub_2_long_long_long(_ckd_type_long a, _ckd_type_long b) {
    ckd_long_t r; r._ineXact = _ckd_sub_3_long_long_long(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_long_clong_long(_ckd_type_long *r, _ckd_type_clong a, _ckd_type_long b) {
    return _ckd_sub_3_long_long_long(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_long_t _ckd_sub_2_long_clong_long(_ckd_type_clong a, _ckd_type_long b) {
    ckd_long_t r; r._ineXact = _ckd_sub_3_long_clong_long(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_long_long_clong(_ckd_type_long *r, _ckd_type_long a, _ckd_type_clong b) {
    return _ckd_sub_3_long_long_long(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_long_t _ckd_sub_2_long_long_clong(_ckd_type_long a, _ckd_type_clong b) {
    ckd_long_t r; r._ineXact = _ckd_sub_3_long_long_clong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_long_clong_clong(_ckd_type_long *r, _ckd_type_clong a, _ckd_type_clong b) {
    return _ckd_sub_3_long_long_long(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_long_t _ckd_sub_2_long_clong_clong(_ckd_type_clong a, _ckd_type_clong b) {
    ckd_long_t r; r._ineXact = _ckd_sub_3_long_clong_clong(&r._vaLue, a, b); return r;
}
// Operation sub on ulong and ulong -> ulong
_ckd_static bool _ckd_sub_3_ulong_ulong_ulong(_ckd_type_ulong *r, _ckd_type_ulong a, _ckd_type_ulong b) {
    return _ckd_sub_3_ulong_ulong_ulong_in(r, a, b);
}
_ckd_funcconst ckd_ulong_t _ckd_sub_2_ulong_ulong_ulong(_ckd_type_ulong a, _ckd_type_ulong b) {
    ckd_ulong_t r; r._ineXact = _ckd_sub_3_ulong_ulong_ulong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_ulong_culong_ulong(_ckd_type_ulong *r, _ckd_type_culong a, _ckd_type_ulong b) {
    return _ckd_sub_3_ulong_ulong_ulong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ulong_t _ckd_sub_2_ulong_culong_ulong(_ckd_type_culong a, _ckd_type_ulong b) {
    ckd_ulong_t r; r._ineXact = _ckd_sub_3_ulong_culong_ulong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_ulong_ulong_culong(_ckd_type_ulong *r, _ckd_type_ulong a, _ckd_type_culong b) {
    return _ckd_sub_3_ulong_ulong_ulong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ulong_t _ckd_sub_2_ulong_ulong_culong(_ckd_type_ulong a, _ckd_type_culong b) {
    ckd_ulong_t r; r._ineXact = _ckd_sub_3_ulong_ulong_culong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_ulong_culong_culong(_ckd_type_ulong *r, _ckd_type_culong a, _ckd_type_culong b) {
    return _ckd_sub_3_ulong_ulong_ulong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ulong_t _ckd_sub_2_ulong_culong_culong(_ckd_type_culong a, _ckd_type_culong b) {
    ckd_ulong_t r; r._ineXact = _ckd_sub_3_ulong_culong_culong(&r._vaLue, a, b); return r;
}
// Operation sub on llong and llong -> llong
_ckd_static bool _ckd_sub_3_llong_llong_llong(_ckd_type_llong *r, _ckd_type_llong a, _ckd_type_llong b) {
    return _ckd_sub_3_llong_llong_llong_in(r, a, b);
}
_ckd_funcconst ckd_llong_t _ckd_sub_2_llong_llong_llong(_ckd_type_llong a, _ckd_type_llong b) {
    ckd_llong_t r; r._ineXact = _ckd_sub_3_llong_llong_llong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_llong_cllong_llong(_ckd_type_llong *r, _ckd_type_cllong a, _ckd_type_llong b) {
    return _ckd_sub_3_llong_llong_llong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_llong_t _ckd_sub_2_llong_cllong_llong(_ckd_type_cllong a, _ckd_type_llong b) {
    ckd_llong_t r; r._ineXact = _ckd_sub_3_llong_cllong_llong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_llong_llong_cllong(_ckd_type_llong *r, _ckd_type_llong a, _ckd_type_cllong b) {
    return _ckd_sub_3_llong_llong_llong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_llong_t _ckd_sub_2_llong_llong_cllong(_ckd_type_llong a, _ckd_type_cllong b) {
    ckd_llong_t r; r._ineXact = _ckd_sub_3_llong_llong_cllong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_llong_cllong_cllong(_ckd_type_llong *r, _ckd_type_cllong a, _ckd_type_cllong b) {
    return _ckd_sub_3_llong_llong_llong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_llong_t _ckd_sub_2_llong_cllong_cllong(_ckd_type_cllong a, _ckd_type_cllong b) {
    ckd_llong_t r; r._ineXact = _ckd_sub_3_llong_cllong_cllong(&r._vaLue, a, b); return r;
}
// Operation sub on ullong and ullong -> ullong
_ckd_static bool _ckd_sub_3_ullong_ullong_ullong(_ckd_type_ullong *r, _ckd_type_ullong a, _ckd_type_ullong b) {
    return _ckd_sub_3_ullong_ullong_ullong_in(r, a, b);
}
_ckd_funcconst ckd_ullong_t _ckd_sub_2_ullong_ullong_ullong(_ckd_type_ullong a, _ckd_type_ullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_sub_3_ullong_ullong_ullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_ullong_cullong_ullong(_ckd_type_ullong *r, _ckd_type_cullong a, _ckd_type_ullong b) {
    return _ckd_sub_3_ullong_ullong_ullong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ullong_t _ckd_sub_2_ullong_cullong_ullong(_ckd_type_cullong a, _ckd_type_ullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_sub_3_ullong_cullong_ullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_ullong_ullong_cullong(_ckd_type_ullong *r, _ckd_type_ullong a, _ckd_type_cullong b) {
    return _ckd_sub_3_ullong_ullong_ullong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ullong_t _ckd_sub_2_ullong_ullong_cullong(_ckd_type_ullong a, _ckd_type_cullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_sub_3_ullong_ullong_cullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_ullong_cullong_cullong(_ckd_type_ullong *r, _ckd_type_cullong a, _ckd_type_cullong b) {
    return _ckd_sub_3_ullong_ullong_ullong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ullong_t _ckd_sub_2_ullong_cullong_cullong(_ckd_type_cullong a, _ckd_type_cullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_sub_3_ullong_cullong_cullong(&r._vaLue, a, b); return r;
}
// Operation sub on int128 and int128 -> int128
_ckd_static bool _ckd_sub_3_int128_int128_int128(_ckd_type_int128 *r, _ckd_type_int128 a, _ckd_type_int128 b) {
    return _ckd_sub_3_int128_int128_int128_in(r, a, b);
}
_ckd_funcconst ckd_int128_t _ckd_sub_2_int128_int128_int128(_ckd_type_int128 a, _ckd_type_int128 b) {
    ckd_int128_t r; r._ineXact = _ckd_sub_3_int128_int128_int128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_int128_cint128_int128(_ckd_type_int128 *r, _ckd_type_cint128 a, _ckd_type_int128 b) {
    return _ckd_sub_3_int128_int128_int128(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_int128_t _ckd_sub_2_int128_cint128_int128(_ckd_type_cint128 a, _ckd_type_int128 b) {
    ckd_int128_t r; r._ineXact = _ckd_sub_3_int128_cint128_int128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_int128_int128_cint128(_ckd_type_int128 *r, _ckd_type_int128 a, _ckd_type_cint128 b) {
    return _ckd_sub_3_int128_int128_int128(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_int128_t _ckd_sub_2_int128_int128_cint128(_ckd_type_int128 a, _ckd_type_cint128 b) {
    ckd_int128_t r; r._ineXact = _ckd_sub_3_int128_int128_cint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_int128_cint128_cint128(_ckd_type_int128 *r, _ckd_type_cint128 a, _ckd_type_cint128 b) {
    return _ckd_sub_3_int128_int128_int128(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_int128_t _ckd_sub_2_int128_cint128_cint128(_ckd_type_cint128 a, _ckd_type_cint128 b) {
    ckd_int128_t r; r._ineXact = _ckd_sub_3_int128_cint128_cint128(&r._vaLue, a, b); return r;
}
// Operation sub on uint128 and uint128 -> uint128
_ckd_static bool _ckd_sub_3_uint128_uint128_uint128(_ckd_type_uint128 *r, _ckd_type_uint128 a, _ckd_type_uint128 b) {
    return _ckd_sub_3_uint128_uint128_uint128_in(r, a, b);
}
_ckd_funcconst ckd_uint128_t _ckd_sub_2_uint128_uint128_uint128(_ckd_type_uint128 a, _ckd_type_uint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_sub_3_uint128_uint128_uint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_uint128_cuint128_uint128(_ckd_type_uint128 *r, _ckd_type_cuint128 a, _ckd_type_uint128 b) {
    return _ckd_sub_3_uint128_uint128_uint128(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uint128_t _ckd_sub_2_uint128_cuint128_uint128(_ckd_type_cuint128 a, _ckd_type_uint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_sub_3_uint128_cuint128_uint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_uint128_uint128_cuint128(_ckd_type_uint128 *r, _ckd_type_uint128 a, _ckd_type_cuint128 b) {
    return _ckd_sub_3_uint128_uint128_uint128(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uint128_t _ckd_sub_2_uint128_uint128_cuint128(_ckd_type_uint128 a, _ckd_type_cuint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_sub_3_uint128_uint128_cuint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_sub_3_uint128_cuint128_cuint128(_ckd_type_uint128 *r, _ckd_type_cuint128 a, _ckd_type_cuint128 b) {
    return _ckd_sub_3_uint128_uint128_uint128(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uint128_t _ckd_sub_2_uint128_cuint128_cuint128(_ckd_type_cuint128 a, _ckd_type_cuint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_sub_3_uint128_cuint128_cuint128(&r._vaLue, a, b); return r;
}
// Operation mul on schar and schar -> schar
_ckd_static bool _ckd_mul_3_schar_schar_schar(_ckd_type_schar *r, _ckd_type_schar a, _ckd_type_schar b) {
    return _ckd_mul_3_schar_schar_schar_in(r, a, b);
}
_ckd_funcconst ckd_schar_t _ckd_mul_2_schar_schar_schar(_ckd_type_schar a, _ckd_type_schar b) {
    ckd_schar_t r; r._ineXact = _ckd_mul_3_schar_schar_schar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_schar_cschar_schar(_ckd_type_schar *r, _ckd_type_cschar a, _ckd_type_schar b) {
    return _ckd_mul_3_schar_schar_schar(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_schar_t _ckd_mul_2_schar_cschar_schar(_ckd_type_cschar a, _ckd_type_schar b) {
    ckd_schar_t r; r._ineXact = _ckd_mul_3_schar_cschar_schar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_schar_schar_cschar(_ckd_type_schar *r, _ckd_type_schar a, _ckd_type_cschar b) {
    return _ckd_mul_3_schar_schar_schar(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_schar_t _ckd_mul_2_schar_schar_cschar(_ckd_type_schar a, _ckd_type_cschar b) {
    ckd_schar_t r; r._ineXact = _ckd_mul_3_schar_schar_cschar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_schar_cschar_cschar(_ckd_type_schar *r, _ckd_type_cschar a, _ckd_type_cschar b) {
    return _ckd_mul_3_schar_schar_schar(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_schar_t _ckd_mul_2_schar_cschar_cschar(_ckd_type_cschar a, _ckd_type_cschar b) {
    ckd_schar_t r; r._ineXact = _ckd_mul_3_schar_cschar_cschar(&r._vaLue, a, b); return r;
}
// Operation mul on uchar and uchar -> uchar
_ckd_static bool _ckd_mul_3_uchar_uchar_uchar(_ckd_type_uchar *r, _ckd_type_uchar a, _ckd_type_uchar b) {
    return _ckd_mul_3_uchar_uchar_uchar_in(r, a, b);
}
_ckd_funcconst ckd_uchar_t _ckd_mul_2_uchar_uchar_uchar(_ckd_type_uchar a, _ckd_type_uchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_mul_3_uchar_uchar_uchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_uchar_cuchar_uchar(_ckd_type_uchar *r, _ckd_type_cuchar a, _ckd_type_uchar b) {
    return _ckd_mul_3_uchar_uchar_uchar(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uchar_t _ckd_mul_2_uchar_cuchar_uchar(_ckd_type_cuchar a, _ckd_type_uchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_mul_3_uchar_cuchar_uchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_uchar_uchar_cuchar(_ckd_type_uchar *r, _ckd_type_uchar a, _ckd_type_cuchar b) {
    return _ckd_mul_3_uchar_uchar_uchar(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uchar_t _ckd_mul_2_uchar_uchar_cuchar(_ckd_type_uchar a, _ckd_type_cuchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_mul_3_uchar_uchar_cuchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_uchar_cuchar_cuchar(_ckd_type_uchar *r, _ckd_type_cuchar a, _ckd_type_cuchar b) {
    return _ckd_mul_3_uchar_uchar_uchar(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uchar_t _ckd_mul_2_uchar_cuchar_cuchar(_ckd_type_cuchar a, _ckd_type_cuchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_mul_3_uchar_cuchar_cuchar(&r._vaLue, a, b); return r;
}
// Operation mul on shrt and shrt -> shrt
_ckd_static bool _ckd_mul_3_shrt_shrt_shrt(_ckd_type_shrt *r, _ckd_type_shrt a, _ckd_type_shrt b) {
    return _ckd_mul_3_shrt_shrt_shrt_in(r, a, b);
}
_ckd_funcconst ckd_shrt_t _ckd_mul_2_shrt_shrt_shrt(_ckd_type_shrt a, _ckd_type_shrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_mul_3_shrt_shrt_shrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_shrt_cshrt_shrt(_ckd_type_shrt *r, _ckd_type_cshrt a, _ckd_type_shrt b) {
    return _ckd_mul_3_shrt_shrt_shrt(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_shrt_t _ckd_mul_2_shrt_cshrt_shrt(_ckd_type_cshrt a, _ckd_type_shrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_mul_3_shrt_cshrt_shrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_shrt_shrt_cshrt(_ckd_type_shrt *r, _ckd_type_shrt a, _ckd_type_cshrt b) {
    return _ckd_mul_3_shrt_shrt_shrt(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_shrt_t _ckd_mul_2_shrt_shrt_cshrt(_ckd_type_shrt a, _ckd_type_cshrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_mul_3_shrt_shrt_cshrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_shrt_cshrt_cshrt(_ckd_type_shrt *r, _ckd_type_cshrt a, _ckd_type_cshrt b) {
    return _ckd_mul_3_shrt_shrt_shrt(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_shrt_t _ckd_mul_2_shrt_cshrt_cshrt(_ckd_type_cshrt a, _ckd_type_cshrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_mul_3_shrt_cshrt_cshrt(&r._vaLue, a, b); return r;
}
// Operation mul on ushrt and ushrt -> ushrt
_ckd_static bool _ckd_mul_3_ushrt_ushrt_ushrt(_ckd_type_ushrt *r, _ckd_type_ushrt a, _ckd_type_ushrt b) {
    return _ckd_mul_3_ushrt_ushrt_ushrt_in(r, a, b);
}
_ckd_funcconst ckd_ushrt_t _ckd_mul_2_ushrt_ushrt_ushrt(_ckd_type_ushrt a, _ckd_type_ushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_mul_3_ushrt_ushrt_ushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_ushrt_cushrt_ushrt(_ckd_type_ushrt *r, _ckd_type_cushrt a, _ckd_type_ushrt b) {
    return _ckd_mul_3_ushrt_ushrt_ushrt(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ushrt_t _ckd_mul_2_ushrt_cushrt_ushrt(_ckd_type_cushrt a, _ckd_type_ushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_mul_3_ushrt_cushrt_ushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_ushrt_ushrt_cushrt(_ckd_type_ushrt *r, _ckd_type_ushrt a, _ckd_type_cushrt b) {
    return _ckd_mul_3_ushrt_ushrt_ushrt(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ushrt_t _ckd_mul_2_ushrt_ushrt_cushrt(_ckd_type_ushrt a, _ckd_type_cushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_mul_3_ushrt_ushrt_cushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_ushrt_cushrt_cushrt(_ckd_type_ushrt *r, _ckd_type_cushrt a, _ckd_type_cushrt b) {
    return _ckd_mul_3_ushrt_ushrt_ushrt(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ushrt_t _ckd_mul_2_ushrt_cushrt_cushrt(_ckd_type_cushrt a, _ckd_type_cushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_mul_3_ushrt_cushrt_cushrt(&r._vaLue, a, b); return r;
}
// Operation mul on int and int -> int
_ckd_static bool _ckd_mul_3_int_int_int(_ckd_type_int *r, _ckd_type_int a, _ckd_type_int b) {
    return _ckd_mul_3_int_int_int_in(r, a, b);
}
_ckd_funcconst ckd_int_t _ckd_mul_2_int_int_int(_ckd_type_int a, _ckd_type_int b) {
    ckd_int_t r; r._ineXact = _ckd_mul_3_int_int_int(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_int_cint_int(_ckd_type_int *r, _ckd_type_cint a, _ckd_type_int b) {
    return _ckd_mul_3_int_int_int(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_int_t _ckd_mul_2_int_cint_int(_ckd_type_cint a, _ckd_type_int b) {
    ckd_int_t r; r._ineXact = _ckd_mul_3_int_cint_int(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_int_int_cint(_ckd_type_int *r, _ckd_type_int a, _ckd_type_cint b) {
    return _ckd_mul_3_int_int_int(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_int_t _ckd_mul_2_int_int_cint(_ckd_type_int a, _ckd_type_cint b) {
    ckd_int_t r; r._ineXact = _ckd_mul_3_int_int_cint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_int_cint_cint(_ckd_type_int *r, _ckd_type_cint a, _ckd_type_cint b) {
    return _ckd_mul_3_int_int_int(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_int_t _ckd_mul_2_int_cint_cint(_ckd_type_cint a, _ckd_type_cint b) {
    ckd_int_t r; r._ineXact = _ckd_mul_3_int_cint_cint(&r._vaLue, a, b); return r;
}
// Operation mul on uint and uint -> uint
_ckd_static bool _ckd_mul_3_uint_uint_uint(_ckd_type_uint *r, _ckd_type_uint a, _ckd_type_uint b) {
    return _ckd_mul_3_uint_uint_uint_in(r, a, b);
}
_ckd_funcconst ckd_uint_t _ckd_mul_2_uint_uint_uint(_ckd_type_uint a, _ckd_type_uint b) {
    ckd_uint_t r; r._ineXact = _ckd_mul_3_uint_uint_uint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_uint_cuint_uint(_ckd_type_uint *r, _ckd_type_cuint a, _ckd_type_uint b) {
    return _ckd_mul_3_uint_uint_uint(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uint_t _ckd_mul_2_uint_cuint_uint(_ckd_type_cuint a, _ckd_type_uint b) {
    ckd_uint_t r; r._ineXact = _ckd_mul_3_uint_cuint_uint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_uint_uint_cuint(_ckd_type_uint *r, _ckd_type_uint a, _ckd_type_cuint b) {
    return _ckd_mul_3_uint_uint_uint(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uint_t _ckd_mul_2_uint_uint_cuint(_ckd_type_uint a, _ckd_type_cuint b) {
    ckd_uint_t r; r._ineXact = _ckd_mul_3_uint_uint_cuint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_uint_cuint_cuint(_ckd_type_uint *r, _ckd_type_cuint a, _ckd_type_cuint b) {
    return _ckd_mul_3_uint_uint_uint(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uint_t _ckd_mul_2_uint_cuint_cuint(_ckd_type_cuint a, _ckd_type_cuint b) {
    ckd_uint_t r; r._ineXact = _ckd_mul_3_uint_cuint_cuint(&r._vaLue, a, b); return r;
}
// Operation mul on long and long -> long
_ckd_static bool _ckd_mul_3_long_long_long(_ckd_type_long *r, _ckd_type_long a, _ckd_type_long b) {
    return _ckd_mul_3_long_long_long_in(r, a, b);
}
_ckd_funcconst ckd_long_t _ckd_mul_2_long_long_long(_ckd_type_long a, _ckd_type_long b) {
    ckd_long_t r; r._ineXact = _ckd_mul_3_long_long_long(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_long_clong_long(_ckd_type_long *r, _ckd_type_clong a, _ckd_type_long b) {
    return _ckd_mul_3_long_long_long(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_long_t _ckd_mul_2_long_clong_long(_ckd_type_clong a, _ckd_type_long b) {
    ckd_long_t r; r._ineXact = _ckd_mul_3_long_clong_long(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_long_long_clong(_ckd_type_long *r, _ckd_type_long a, _ckd_type_clong b) {
    return _ckd_mul_3_long_long_long(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_long_t _ckd_mul_2_long_long_clong(_ckd_type_long a, _ckd_type_clong b) {
    ckd_long_t r; r._ineXact = _ckd_mul_3_long_long_clong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_long_clong_clong(_ckd_type_long *r, _ckd_type_clong a, _ckd_type_clong b) {
    return _ckd_mul_3_long_long_long(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_long_t _ckd_mul_2_long_clong_clong(_ckd_type_clong a, _ckd_type_clong b) {
    ckd_long_t r; r._ineXact = _ckd_mul_3_long_clong_clong(&r._vaLue, a, b); return r;
}
// Operation mul on ulong and ulong -> ulong
_ckd_static bool _ckd_mul_3_ulong_ulong_ulong(_ckd_type_ulong *r, _ckd_type_ulong a, _ckd_type_ulong b) {
    return _ckd_mul_3_ulong_ulong_ulong_in(r, a, b);
}
_ckd_funcconst ckd_ulong_t _ckd_mul_2_ulong_ulong_ulong(_ckd_type_ulong a, _ckd_type_ulong b) {
    ckd_ulong_t r; r._ineXact = _ckd_mul_3_ulong_ulong_ulong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_ulong_culong_ulong(_ckd_type_ulong *r, _ckd_type_culong a, _ckd_type_ulong b) {
    return _ckd_mul_3_ulong_ulong_ulong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ulong_t _ckd_mul_2_ulong_culong_ulong(_ckd_type_culong a, _ckd_type_ulong b) {
    ckd_ulong_t r; r._ineXact = _ckd_mul_3_ulong_culong_ulong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_ulong_ulong_culong(_ckd_type_ulong *r, _ckd_type_ulong a, _ckd_type_culong b) {
    return _ckd_mul_3_ulong_ulong_ulong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ulong_t _ckd_mul_2_ulong_ulong_culong(_ckd_type_ulong a, _ckd_type_culong b) {
    ckd_ulong_t r; r._ineXact = _ckd_mul_3_ulong_ulong_culong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_ulong_culong_culong(_ckd_type_ulong *r, _ckd_type_culong a, _ckd_type_culong b) {
    return _ckd_mul_3_ulong_ulong_ulong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ulong_t _ckd_mul_2_ulong_culong_culong(_ckd_type_culong a, _ckd_type_culong b) {
    ckd_ulong_t r; r._ineXact = _ckd_mul_3_ulong_culong_culong(&r._vaLue, a, b); return r;
}
// Operation mul on llong and llong -> llong
_ckd_static bool _ckd_mul_3_llong_llong_llong(_ckd_type_llong *r, _ckd_type_llong a, _ckd_type_llong b) {
    return _ckd_mul_3_llong_llong_llong_in(r, a, b);
}
_ckd_funcconst ckd_llong_t _ckd_mul_2_llong_llong_llong(_ckd_type_llong a, _ckd_type_llong b) {
    ckd_llong_t r; r._ineXact = _ckd_mul_3_llong_llong_llong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_llong_cllong_llong(_ckd_type_llong *r, _ckd_type_cllong a, _ckd_type_llong b) {
    return _ckd_mul_3_llong_llong_llong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_llong_t _ckd_mul_2_llong_cllong_llong(_ckd_type_cllong a, _ckd_type_llong b) {
    ckd_llong_t r; r._ineXact = _ckd_mul_3_llong_cllong_llong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_llong_llong_cllong(_ckd_type_llong *r, _ckd_type_llong a, _ckd_type_cllong b) {
    return _ckd_mul_3_llong_llong_llong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_llong_t _ckd_mul_2_llong_llong_cllong(_ckd_type_llong a, _ckd_type_cllong b) {
    ckd_llong_t r; r._ineXact = _ckd_mul_3_llong_llong_cllong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_llong_cllong_cllong(_ckd_type_llong *r, _ckd_type_cllong a, _ckd_type_cllong b) {
    return _ckd_mul_3_llong_llong_llong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_llong_t _ckd_mul_2_llong_cllong_cllong(_ckd_type_cllong a, _ckd_type_cllong b) {
    ckd_llong_t r; r._ineXact = _ckd_mul_3_llong_cllong_cllong(&r._vaLue, a, b); return r;
}
// Operation mul on ullong and ullong -> ullong
_ckd_static bool _ckd_mul_3_ullong_ullong_ullong(_ckd_type_ullong *r, _ckd_type_ullong a, _ckd_type_ullong b) {
    return _ckd_mul_3_ullong_ullong_ullong_in(r, a, b);
}
_ckd_funcconst ckd_ullong_t _ckd_mul_2_ullong_ullong_ullong(_ckd_type_ullong a, _ckd_type_ullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_mul_3_ullong_ullong_ullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_ullong_cullong_ullong(_ckd_type_ullong *r, _ckd_type_cullong a, _ckd_type_ullong b) {
    return _ckd_mul_3_ullong_ullong_ullong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ullong_t _ckd_mul_2_ullong_cullong_ullong(_ckd_type_cullong a, _ckd_type_ullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_mul_3_ullong_cullong_ullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_ullong_ullong_cullong(_ckd_type_ullong *r, _ckd_type_ullong a, _ckd_type_cullong b) {
    return _ckd_mul_3_ullong_ullong_ullong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ullong_t _ckd_mul_2_ullong_ullong_cullong(_ckd_type_ullong a, _ckd_type_cullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_mul_3_ullong_ullong_cullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_ullong_cullong_cullong(_ckd_type_ullong *r, _ckd_type_cullong a, _ckd_type_cullong b) {
    return _ckd_mul_3_ullong_ullong_ullong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ullong_t _ckd_mul_2_ullong_cullong_cullong(_ckd_type_cullong a, _ckd_type_cullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_mul_3_ullong_cullong_cullong(&r._vaLue, a, b); return r;
}
// Operation mul on int128 and int128 -> int128
_ckd_static bool _ckd_mul_3_int128_int128_int128(_ckd_type_int128 *r, _ckd_type_int128 a, _ckd_type_int128 b) {
    return _ckd_mul_3_int128_int128_int128_in(r, a, b);
}
_ckd_funcconst ckd_int128_t _ckd_mul_2_int128_int128_int128(_ckd_type_int128 a, _ckd_type_int128 b) {
    ckd_int128_t r; r._ineXact = _ckd_mul_3_int128_int128_int128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_int128_cint128_int128(_ckd_type_int128 *r, _ckd_type_cint128 a, _ckd_type_int128 b) {
    return _ckd_mul_3_int128_int128_int128(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_int128_t _ckd_mul_2_int128_cint128_int128(_ckd_type_cint128 a, _ckd_type_int128 b) {
    ckd_int128_t r; r._ineXact = _ckd_mul_3_int128_cint128_int128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_int128_int128_cint128(_ckd_type_int128 *r, _ckd_type_int128 a, _ckd_type_cint128 b) {
    return _ckd_mul_3_int128_int128_int128(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_int128_t _ckd_mul_2_int128_int128_cint128(_ckd_type_int128 a, _ckd_type_cint128 b) {
    ckd_int128_t r; r._ineXact = _ckd_mul_3_int128_int128_cint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_int128_cint128_cint128(_ckd_type_int128 *r, _ckd_type_cint128 a, _ckd_type_cint128 b) {
    return _ckd_mul_3_int128_int128_int128(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_int128_t _ckd_mul_2_int128_cint128_cint128(_ckd_type_cint128 a, _ckd_type_cint128 b) {
    ckd_int128_t r; r._ineXact = _ckd_mul_3_int128_cint128_cint128(&r._vaLue, a, b); return r;
}
// Operation mul on uint128 and uint128 -> uint128
_ckd_static bool _ckd_mul_3_uint128_uint128_uint128(_ckd_type_uint128 *r, _ckd_type_uint128 a, _ckd_type_uint128 b) {
    return _ckd_mul_3_uint128_uint128_uint128_in(r, a, b);
}
_ckd_funcconst ckd_uint128_t _ckd_mul_2_uint128_uint128_uint128(_ckd_type_uint128 a, _ckd_type_uint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_mul_3_uint128_uint128_uint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_uint128_cuint128_uint128(_ckd_type_uint128 *r, _ckd_type_cuint128 a, _ckd_type_uint128 b) {
    return _ckd_mul_3_uint128_uint128_uint128(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uint128_t _ckd_mul_2_uint128_cuint128_uint128(_ckd_type_cuint128 a, _ckd_type_uint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_mul_3_uint128_cuint128_uint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_uint128_uint128_cuint128(_ckd_type_uint128 *r, _ckd_type_uint128 a, _ckd_type_cuint128 b) {
    return _ckd_mul_3_uint128_uint128_uint128(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uint128_t _ckd_mul_2_uint128_uint128_cuint128(_ckd_type_uint128 a, _ckd_type_cuint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_mul_3_uint128_uint128_cuint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_mul_3_uint128_cuint128_cuint128(_ckd_type_uint128 *r, _ckd_type_cuint128 a, _ckd_type_cuint128 b) {
    return _ckd_mul_3_uint128_uint128_uint128(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uint128_t _ckd_mul_2_uint128_cuint128_cuint128(_ckd_type_cuint128 a, _ckd_type_cuint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_mul_3_uint128_cuint128_cuint128(&r._vaLue, a, b); return r;
}
// Operation div on schar and schar -> schar
_ckd_static bool _ckd_div_3_schar_schar_schar(_ckd_type_schar *r, _ckd_type_schar a, _ckd_type_schar b) {
    return _ckd_div_3_schar_schar_schar_in(r, a, b);
}
_ckd_funcconst ckd_schar_t _ckd_div_2_schar_schar_schar(_ckd_type_schar a, _ckd_type_schar b) {
    ckd_schar_t r; r._ineXact = _ckd_div_3_schar_schar_schar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_schar_cschar_schar(_ckd_type_schar *r, _ckd_type_cschar a, _ckd_type_schar b) {
    return _ckd_div_3_schar_schar_schar(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_schar_t _ckd_div_2_schar_cschar_schar(_ckd_type_cschar a, _ckd_type_schar b) {
    ckd_schar_t r; r._ineXact = _ckd_div_3_schar_cschar_schar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_schar_schar_cschar(_ckd_type_schar *r, _ckd_type_schar a, _ckd_type_cschar b) {
    return _ckd_div_3_schar_schar_schar(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_schar_t _ckd_div_2_schar_schar_cschar(_ckd_type_schar a, _ckd_type_cschar b) {
    ckd_schar_t r; r._ineXact = _ckd_div_3_schar_schar_cschar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_schar_cschar_cschar(_ckd_type_schar *r, _ckd_type_cschar a, _ckd_type_cschar b) {
    return _ckd_div_3_schar_schar_schar(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_schar_t _ckd_div_2_schar_cschar_cschar(_ckd_type_cschar a, _ckd_type_cschar b) {
    ckd_schar_t r; r._ineXact = _ckd_div_3_schar_cschar_cschar(&r._vaLue, a, b); return r;
}
// Operation div on uchar and uchar -> uchar
_ckd_static bool _ckd_div_3_uchar_uchar_uchar(_ckd_type_uchar *r, _ckd_type_uchar a, _ckd_type_uchar b) {
    return _ckd_div_3_uchar_uchar_uchar_in(r, a, b);
}
_ckd_funcconst ckd_uchar_t _ckd_div_2_uchar_uchar_uchar(_ckd_type_uchar a, _ckd_type_uchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_div_3_uchar_uchar_uchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_uchar_cuchar_uchar(_ckd_type_uchar *r, _ckd_type_cuchar a, _ckd_type_uchar b) {
    return _ckd_div_3_uchar_uchar_uchar(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uchar_t _ckd_div_2_uchar_cuchar_uchar(_ckd_type_cuchar a, _ckd_type_uchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_div_3_uchar_cuchar_uchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_uchar_uchar_cuchar(_ckd_type_uchar *r, _ckd_type_uchar a, _ckd_type_cuchar b) {
    return _ckd_div_3_uchar_uchar_uchar(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uchar_t _ckd_div_2_uchar_uchar_cuchar(_ckd_type_uchar a, _ckd_type_cuchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_div_3_uchar_uchar_cuchar(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_uchar_cuchar_cuchar(_ckd_type_uchar *r, _ckd_type_cuchar a, _ckd_type_cuchar b) {
    return _ckd_div_3_uchar_uchar_uchar(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uchar_t _ckd_div_2_uchar_cuchar_cuchar(_ckd_type_cuchar a, _ckd_type_cuchar b) {
    ckd_uchar_t r; r._ineXact = _ckd_div_3_uchar_cuchar_cuchar(&r._vaLue, a, b); return r;
}
// Operation div on shrt and shrt -> shrt
_ckd_static bool _ckd_div_3_shrt_shrt_shrt(_ckd_type_shrt *r, _ckd_type_shrt a, _ckd_type_shrt b) {
    return _ckd_div_3_shrt_shrt_shrt_in(r, a, b);
}
_ckd_funcconst ckd_shrt_t _ckd_div_2_shrt_shrt_shrt(_ckd_type_shrt a, _ckd_type_shrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_div_3_shrt_shrt_shrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_shrt_cshrt_shrt(_ckd_type_shrt *r, _ckd_type_cshrt a, _ckd_type_shrt b) {
    return _ckd_div_3_shrt_shrt_shrt(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_shrt_t _ckd_div_2_shrt_cshrt_shrt(_ckd_type_cshrt a, _ckd_type_shrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_div_3_shrt_cshrt_shrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_shrt_shrt_cshrt(_ckd_type_shrt *r, _ckd_type_shrt a, _ckd_type_cshrt b) {
    return _ckd_div_3_shrt_shrt_shrt(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_shrt_t _ckd_div_2_shrt_shrt_cshrt(_ckd_type_shrt a, _ckd_type_cshrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_div_3_shrt_shrt_cshrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_shrt_cshrt_cshrt(_ckd_type_shrt *r, _ckd_type_cshrt a, _ckd_type_cshrt b) {
    return _ckd_div_3_shrt_shrt_shrt(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_shrt_t _ckd_div_2_shrt_cshrt_cshrt(_ckd_type_cshrt a, _ckd_type_cshrt b) {
    ckd_shrt_t r; r._ineXact = _ckd_div_3_shrt_cshrt_cshrt(&r._vaLue, a, b); return r;
}
// Operation div on ushrt and ushrt -> ushrt
_ckd_static bool _ckd_div_3_ushrt_ushrt_ushrt(_ckd_type_ushrt *r, _ckd_type_ushrt a, _ckd_type_ushrt b) {
    return _ckd_div_3_ushrt_ushrt_ushrt_in(r, a, b);
}
_ckd_funcconst ckd_ushrt_t _ckd_div_2_ushrt_ushrt_ushrt(_ckd_type_ushrt a, _ckd_type_ushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_div_3_ushrt_ushrt_ushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_ushrt_cushrt_ushrt(_ckd_type_ushrt *r, _ckd_type_cushrt a, _ckd_type_ushrt b) {
    return _ckd_div_3_ushrt_ushrt_ushrt(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ushrt_t _ckd_div_2_ushrt_cushrt_ushrt(_ckd_type_cushrt a, _ckd_type_ushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_div_3_ushrt_cushrt_ushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_ushrt_ushrt_cushrt(_ckd_type_ushrt *r, _ckd_type_ushrt a, _ckd_type_cushrt b) {
    return _ckd_div_3_ushrt_ushrt_ushrt(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ushrt_t _ckd_div_2_ushrt_ushrt_cushrt(_ckd_type_ushrt a, _ckd_type_cushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_div_3_ushrt_ushrt_cushrt(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_ushrt_cushrt_cushrt(_ckd_type_ushrt *r, _ckd_type_cushrt a, _ckd_type_cushrt b) {
    return _ckd_div_3_ushrt_ushrt_ushrt(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ushrt_t _ckd_div_2_ushrt_cushrt_cushrt(_ckd_type_cushrt a, _ckd_type_cushrt b) {
    ckd_ushrt_t r; r._ineXact = _ckd_div_3_ushrt_cushrt_cushrt(&r._vaLue, a, b); return r;
}
// Operation div on int and int -> int
_ckd_static bool _ckd_div_3_int_int_int(_ckd_type_int *r, _ckd_type_int a, _ckd_type_int b) {
    return _ckd_div_3_int_int_int_in(r, a, b);
}
_ckd_funcconst ckd_int_t _ckd_div_2_int_int_int(_ckd_type_int a, _ckd_type_int b) {
    ckd_int_t r; r._ineXact = _ckd_div_3_int_int_int(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_int_cint_int(_ckd_type_int *r, _ckd_type_cint a, _ckd_type_int b) {
    return _ckd_div_3_int_int_int(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_int_t _ckd_div_2_int_cint_int(_ckd_type_cint a, _ckd_type_int b) {
    ckd_int_t r; r._ineXact = _ckd_div_3_int_cint_int(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_int_int_cint(_ckd_type_int *r, _ckd_type_int a, _ckd_type_cint b) {
    return _ckd_div_3_int_int_int(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_int_t _ckd_div_2_int_int_cint(_ckd_type_int a, _ckd_type_cint b) {
    ckd_int_t r; r._ineXact = _ckd_div_3_int_int_cint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_int_cint_cint(_ckd_type_int *r, _ckd_type_cint a, _ckd_type_cint b) {
    return _ckd_div_3_int_int_int(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_int_t _ckd_div_2_int_cint_cint(_ckd_type_cint a, _ckd_type_cint b) {
    ckd_int_t r; r._ineXact = _ckd_div_3_int_cint_cint(&r._vaLue, a, b); return r;
}
// Operation div on uint and uint -> uint
_ckd_static bool _ckd_div_3_uint_uint_uint(_ckd_type_uint *r, _ckd_type_uint a, _ckd_type_uint b) {
    return _ckd_div_3_uint_uint_uint_in(r, a, b);
}
_ckd_funcconst ckd_uint_t _ckd_div_2_uint_uint_uint(_ckd_type_uint a, _ckd_type_uint b) {
    ckd_uint_t r; r._ineXact = _ckd_div_3_uint_uint_uint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_uint_cuint_uint(_ckd_type_uint *r, _ckd_type_cuint a, _ckd_type_uint b) {
    return _ckd_div_3_uint_uint_uint(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uint_t _ckd_div_2_uint_cuint_uint(_ckd_type_cuint a, _ckd_type_uint b) {
    ckd_uint_t r; r._ineXact = _ckd_div_3_uint_cuint_uint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_uint_uint_cuint(_ckd_type_uint *r, _ckd_type_uint a, _ckd_type_cuint b) {
    return _ckd_div_3_uint_uint_uint(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uint_t _ckd_div_2_uint_uint_cuint(_ckd_type_uint a, _ckd_type_cuint b) {
    ckd_uint_t r; r._ineXact = _ckd_div_3_uint_uint_cuint(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_uint_cuint_cuint(_ckd_type_uint *r, _ckd_type_cuint a, _ckd_type_cuint b) {
    return _ckd_div_3_uint_uint_uint(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uint_t _ckd_div_2_uint_cuint_cuint(_ckd_type_cuint a, _ckd_type_cuint b) {
    ckd_uint_t r; r._ineXact = _ckd_div_3_uint_cuint_cuint(&r._vaLue, a, b); return r;
}
// Operation div on long and long -> long
_ckd_static bool _ckd_div_3_long_long_long(_ckd_type_long *r, _ckd_type_long a, _ckd_type_long b) {
    return _ckd_div_3_long_long_long_in(r, a, b);
}
_ckd_funcconst ckd_long_t _ckd_div_2_long_long_long(_ckd_type_long a, _ckd_type_long b) {
    ckd_long_t r; r._ineXact = _ckd_div_3_long_long_long(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_long_clong_long(_ckd_type_long *r, _ckd_type_clong a, _ckd_type_long b) {
    return _ckd_div_3_long_long_long(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_long_t _ckd_div_2_long_clong_long(_ckd_type_clong a, _ckd_type_long b) {
    ckd_long_t r; r._ineXact = _ckd_div_3_long_clong_long(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_long_long_clong(_ckd_type_long *r, _ckd_type_long a, _ckd_type_clong b) {
    return _ckd_div_3_long_long_long(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_long_t _ckd_div_2_long_long_clong(_ckd_type_long a, _ckd_type_clong b) {
    ckd_long_t r; r._ineXact = _ckd_div_3_long_long_clong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_long_clong_clong(_ckd_type_long *r, _ckd_type_clong a, _ckd_type_clong b) {
    return _ckd_div_3_long_long_long(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_long_t _ckd_div_2_long_clong_clong(_ckd_type_clong a, _ckd_type_clong b) {
    ckd_long_t r; r._ineXact = _ckd_div_3_long_clong_clong(&r._vaLue, a, b); return r;
}
// Operation div on ulong and ulong -> ulong
_ckd_static bool _ckd_div_3_ulong_ulong_ulong(_ckd_type_ulong *r, _ckd_type_ulong a, _ckd_type_ulong b) {
    return _ckd_div_3_ulong_ulong_ulong_in(r, a, b);
}
_ckd_funcconst ckd_ulong_t _ckd_div_2_ulong_ulong_ulong(_ckd_type_ulong a, _ckd_type_ulong b) {
    ckd_ulong_t r; r._ineXact = _ckd_div_3_ulong_ulong_ulong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_ulong_culong_ulong(_ckd_type_ulong *r, _ckd_type_culong a, _ckd_type_ulong b) {
    return _ckd_div_3_ulong_ulong_ulong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ulong_t _ckd_div_2_ulong_culong_ulong(_ckd_type_culong a, _ckd_type_ulong b) {
    ckd_ulong_t r; r._ineXact = _ckd_div_3_ulong_culong_ulong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_ulong_ulong_culong(_ckd_type_ulong *r, _ckd_type_ulong a, _ckd_type_culong b) {
    return _ckd_div_3_ulong_ulong_ulong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ulong_t _ckd_div_2_ulong_ulong_culong(_ckd_type_ulong a, _ckd_type_culong b) {
    ckd_ulong_t r; r._ineXact = _ckd_div_3_ulong_ulong_culong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_ulong_culong_culong(_ckd_type_ulong *r, _ckd_type_culong a, _ckd_type_culong b) {
    return _ckd_div_3_ulong_ulong_ulong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ulong_t _ckd_div_2_ulong_culong_culong(_ckd_type_culong a, _ckd_type_culong b) {
    ckd_ulong_t r; r._ineXact = _ckd_div_3_ulong_culong_culong(&r._vaLue, a, b); return r;
}
// Operation div on llong and llong -> llong
_ckd_static bool _ckd_div_3_llong_llong_llong(_ckd_type_llong *r, _ckd_type_llong a, _ckd_type_llong b) {
    return _ckd_div_3_llong_llong_llong_in(r, a, b);
}
_ckd_funcconst ckd_llong_t _ckd_div_2_llong_llong_llong(_ckd_type_llong a, _ckd_type_llong b) {
    ckd_llong_t r; r._ineXact = _ckd_div_3_llong_llong_llong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_llong_cllong_llong(_ckd_type_llong *r, _ckd_type_cllong a, _ckd_type_llong b) {
    return _ckd_div_3_llong_llong_llong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_llong_t _ckd_div_2_llong_cllong_llong(_ckd_type_cllong a, _ckd_type_llong b) {
    ckd_llong_t r; r._ineXact = _ckd_div_3_llong_cllong_llong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_llong_llong_cllong(_ckd_type_llong *r, _ckd_type_llong a, _ckd_type_cllong b) {
    return _ckd_div_3_llong_llong_llong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_llong_t _ckd_div_2_llong_llong_cllong(_ckd_type_llong a, _ckd_type_cllong b) {
    ckd_llong_t r; r._ineXact = _ckd_div_3_llong_llong_cllong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_llong_cllong_cllong(_ckd_type_llong *r, _ckd_type_cllong a, _ckd_type_cllong b) {
    return _ckd_div_3_llong_llong_llong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_llong_t _ckd_div_2_llong_cllong_cllong(_ckd_type_cllong a, _ckd_type_cllong b) {
    ckd_llong_t r; r._ineXact = _ckd_div_3_llong_cllong_cllong(&r._vaLue, a, b); return r;
}
// Operation div on ullong and ullong -> ullong
_ckd_static bool _ckd_div_3_ullong_ullong_ullong(_ckd_type_ullong *r, _ckd_type_ullong a, _ckd_type_ullong b) {
    return _ckd_div_3_ullong_ullong_ullong_in(r, a, b);
}
_ckd_funcconst ckd_ullong_t _ckd_div_2_ullong_ullong_ullong(_ckd_type_ullong a, _ckd_type_ullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_div_3_ullong_ullong_ullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_ullong_cullong_ullong(_ckd_type_ullong *r, _ckd_type_cullong a, _ckd_type_ullong b) {
    return _ckd_div_3_ullong_ullong_ullong(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_ullong_t _ckd_div_2_ullong_cullong_ullong(_ckd_type_cullong a, _ckd_type_ullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_div_3_ullong_cullong_ullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_ullong_ullong_cullong(_ckd_type_ullong *r, _ckd_type_ullong a, _ckd_type_cullong b) {
    return _ckd_div_3_ullong_ullong_ullong(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_ullong_t _ckd_div_2_ullong_ullong_cullong(_ckd_type_ullong a, _ckd_type_cullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_div_3_ullong_ullong_cullong(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_ullong_cullong_cullong(_ckd_type_ullong *r, _ckd_type_cullong a, _ckd_type_cullong b) {
    return _ckd_div_3_ullong_ullong_ullong(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_ullong_t _ckd_div_2_ullong_cullong_cullong(_ckd_type_cullong a, _ckd_type_cullong b) {
    ckd_ullong_t r; r._ineXact = _ckd_div_3_ullong_cullong_cullong(&r._vaLue, a, b); return r;
}
// Operation div on int128 and int128 -> int128
_ckd_static bool _ckd_div_3_int128_int128_int128(_ckd_type_int128 *r, _ckd_type_int128 a, _ckd_type_int128 b) {
    return _ckd_div_3_int128_int128_int128_in(r, a, b);
}
_ckd_funcconst ckd_int128_t _ckd_div_2_int128_int128_int128(_ckd_type_int128 a, _ckd_type_int128 b) {
    ckd_int128_t r; r._ineXact = _ckd_div_3_int128_int128_int128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_int128_cint128_int128(_ckd_type_int128 *r, _ckd_type_cint128 a, _ckd_type_int128 b) {
    return _ckd_div_3_int128_int128_int128(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_int128_t _ckd_div_2_int128_cint128_int128(_ckd_type_cint128 a, _ckd_type_int128 b) {
    ckd_int128_t r; r._ineXact = _ckd_div_3_int128_cint128_int128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_int128_int128_cint128(_ckd_type_int128 *r, _ckd_type_int128 a, _ckd_type_cint128 b) {
    return _ckd_div_3_int128_int128_int128(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_int128_t _ckd_div_2_int128_int128_cint128(_ckd_type_int128 a, _ckd_type_cint128 b) {
    ckd_int128_t r; r._ineXact = _ckd_div_3_int128_int128_cint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_int128_cint128_cint128(_ckd_type_int128 *r, _ckd_type_cint128 a, _ckd_type_cint128 b) {
    return _ckd_div_3_int128_int128_int128(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_int128_t _ckd_div_2_int128_cint128_cint128(_ckd_type_cint128 a, _ckd_type_cint128 b) {
    ckd_int128_t r; r._ineXact = _ckd_div_3_int128_cint128_cint128(&r._vaLue, a, b); return r;
}
// Operation div on uint128 and uint128 -> uint128
_ckd_static bool _ckd_div_3_uint128_uint128_uint128(_ckd_type_uint128 *r, _ckd_type_uint128 a, _ckd_type_uint128 b) {
    return _ckd_div_3_uint128_uint128_uint128_in(r, a, b);
}
_ckd_funcconst ckd_uint128_t _ckd_div_2_uint128_uint128_uint128(_ckd_type_uint128 a, _ckd_type_uint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_div_3_uint128_uint128_uint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_uint128_cuint128_uint128(_ckd_type_uint128 *r, _ckd_type_cuint128 a, _ckd_type_uint128 b) {
    return _ckd_div_3_uint128_uint128_uint128(r, ckd_value(a), b)|ckd_inexact(a);
}
_ckd_funcconst ckd_uint128_t _ckd_div_2_uint128_cuint128_uint128(_ckd_type_cuint128 a, _ckd_type_uint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_div_3_uint128_cuint128_uint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_uint128_uint128_cuint128(_ckd_type_uint128 *r, _ckd_type_uint128 a, _ckd_type_cuint128 b) {
    return _ckd_div_3_uint128_uint128_uint128(r, a, ckd_value(b))|ckd_inexact(b);
}
_ckd_funcconst ckd_uint128_t _ckd_div_2_uint128_uint128_cuint128(_ckd_type_uint128 a, _ckd_type_cuint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_div_3_uint128_uint128_cuint128(&r._vaLue, a, b); return r;
}
_ckd_static bool _ckd_div_3_uint128_cuint128_cuint128(_ckd_type_uint128 *r, _ckd_type_cuint128 a, _ckd_type_cuint128 b) {
    return _ckd_div_3_uint128_uint128_uint128(r, ckd_value(a), ckd_value(b))|ckd_inexact(a)|ckd_inexact(b);
}
_ckd_funcconst ckd_uint128_t _ckd_div_2_uint128_cuint128_cuint128(_ckd_type_cuint128 a, _ckd_type_cuint128 b) {
    ckd_uint128_t r; r._ineXact = _ckd_div_3_uint128_cuint128_cuint128(&r._vaLue, a, b); return r;
}

// ]]]
// Generic macros implementation [[[

struct _ckd_invalid_;
void _ckd_invalid(struct _ckd_invalid_);


#define ckd_mk(value, inexact)  _Generic((value), \
    signed char: ckd_mk_schar_t, \
    unsigned char: ckd_mk_uchar_t, \
    short: ckd_mk_shrt_t, \
    unsigned short: ckd_mk_ushrt_t, \
    int: ckd_mk_int_t, \
    unsigned int: ckd_mk_uint_t, \
    long: ckd_mk_long_t, \
    unsigned long: ckd_mk_ulong_t, \
    long long: ckd_mk_llong_t, \
    unsigned long long: ckd_mk_ullong_t, \
    __int128: ckd_mk_int128_t, \
    unsigned __int128: ckd_mk_uint128_t \
    )(value, inexact)


    
#define _ckd_add_2(a, b)  _Generic((a), \
    _ckd_type_schar: \
        _Generic((b), \
        _ckd_type_cschar: _ckd_add_2_schar_schar_cschar, \
        default: _ckd_add_2_schar_schar_schar), \
    _ckd_type_cschar: \
        _Generic((b), \
        _ckd_type_cschar: _ckd_add_2_schar_cschar_cschar, \
        default:  _ckd_add_2_schar_cschar_schar), \
    _ckd_type_uchar: \
        _Generic((b), \
        _ckd_type_cuchar: _ckd_add_2_uchar_uchar_cuchar, \
        default: _ckd_add_2_uchar_uchar_uchar), \
    _ckd_type_cuchar: \
        _Generic((b), \
        _ckd_type_cuchar: _ckd_add_2_uchar_cuchar_cuchar, \
        default:  _ckd_add_2_uchar_cuchar_uchar), \
    _ckd_type_shrt: \
        _Generic((b), \
        _ckd_type_cshrt: _ckd_add_2_shrt_shrt_cshrt, \
        default: _ckd_add_2_shrt_shrt_shrt), \
    _ckd_type_cshrt: \
        _Generic((b), \
        _ckd_type_cshrt: _ckd_add_2_shrt_cshrt_cshrt, \
        default:  _ckd_add_2_shrt_cshrt_shrt), \
    _ckd_type_ushrt: \
        _Generic((b), \
        _ckd_type_cushrt: _ckd_add_2_ushrt_ushrt_cushrt, \
        default: _ckd_add_2_ushrt_ushrt_ushrt), \
    _ckd_type_cushrt: \
        _Generic((b), \
        _ckd_type_cushrt: _ckd_add_2_ushrt_cushrt_cushrt, \
        default:  _ckd_add_2_ushrt_cushrt_ushrt), \
    _ckd_type_int: \
        _Generic((b), \
        _ckd_type_cint: _ckd_add_2_int_int_cint, \
        default: _ckd_add_2_int_int_int), \
    _ckd_type_cint: \
        _Generic((b), \
        _ckd_type_cint: _ckd_add_2_int_cint_cint, \
        default:  _ckd_add_2_int_cint_int), \
    _ckd_type_uint: \
        _Generic((b), \
        _ckd_type_cuint: _ckd_add_2_uint_uint_cuint, \
        default: _ckd_add_2_uint_uint_uint), \
    _ckd_type_cuint: \
        _Generic((b), \
        _ckd_type_cuint: _ckd_add_2_uint_cuint_cuint, \
        default:  _ckd_add_2_uint_cuint_uint), \
    _ckd_type_long: \
        _Generic((b), \
        _ckd_type_clong: _ckd_add_2_long_long_clong, \
        default: _ckd_add_2_long_long_long), \
    _ckd_type_clong: \
        _Generic((b), \
        _ckd_type_clong: _ckd_add_2_long_clong_clong, \
        default:  _ckd_add_2_long_clong_long), \
    _ckd_type_ulong: \
        _Generic((b), \
        _ckd_type_culong: _ckd_add_2_ulong_ulong_culong, \
        default: _ckd_add_2_ulong_ulong_ulong), \
    _ckd_type_culong: \
        _Generic((b), \
        _ckd_type_culong: _ckd_add_2_ulong_culong_culong, \
        default:  _ckd_add_2_ulong_culong_ulong), \
    _ckd_type_llong: \
        _Generic((b), \
        _ckd_type_cllong: _ckd_add_2_llong_llong_cllong, \
        default: _ckd_add_2_llong_llong_llong), \
    _ckd_type_cllong: \
        _Generic((b), \
        _ckd_type_cllong: _ckd_add_2_llong_cllong_cllong, \
        default:  _ckd_add_2_llong_cllong_llong), \
    _ckd_type_ullong: \
        _Generic((b), \
        _ckd_type_cullong: _ckd_add_2_ullong_ullong_cullong, \
        default: _ckd_add_2_ullong_ullong_ullong), \
    _ckd_type_cullong: \
        _Generic((b), \
        _ckd_type_cullong: _ckd_add_2_ullong_cullong_cullong, \
        default:  _ckd_add_2_ullong_cullong_ullong), \
    _ckd_type_int128: \
        _Generic((b), \
        _ckd_type_cint128: _ckd_add_2_int128_int128_cint128, \
        default: _ckd_add_2_int128_int128_int128), \
    _ckd_type_cint128: \
        _Generic((b), \
        _ckd_type_cint128: _ckd_add_2_int128_cint128_cint128, \
        default:  _ckd_add_2_int128_cint128_int128), \
    _ckd_type_uint128: \
        _Generic((b), \
        _ckd_type_cuint128: _ckd_add_2_uint128_uint128_cuint128, \
        default: _ckd_add_2_uint128_uint128_uint128), \
    _ckd_type_cuint128: \
        _Generic((b), \
        _ckd_type_cuint128: _ckd_add_2_uint128_cuint128_cuint128, \
        default:  _ckd_add_2_uint128_cuint128_uint128), \
    default: _ckd_invalid)(a, b)
#define _ckd_add_3(r, a, b)  _Generic((r), \
    signed char *: \
        _Generic((a), \
        _ckd_type_schar: \
            _Generic((b), \
            _ckd_type_cschar: _ckd_add_3_schar_schar_cschar, \
            default: _ckd_add_3_schar_schar_schar), \
        _ckd_type_cschar: \
            _Generic((b), \
            _ckd_type_cschar: _ckd_add_3_schar_cschar_cschar, \
            default:  _ckd_add_3_schar_cschar_schar), \
        default: _ckd_add_3_schar_schar_schar), \
    unsigned char *: \
        _Generic((a), \
        _ckd_type_uchar: \
            _Generic((b), \
            _ckd_type_cuchar: _ckd_add_3_uchar_uchar_cuchar, \
            default: _ckd_add_3_uchar_uchar_uchar), \
        _ckd_type_cuchar: \
            _Generic((b), \
            _ckd_type_cuchar: _ckd_add_3_uchar_cuchar_cuchar, \
            default:  _ckd_add_3_uchar_cuchar_uchar), \
        default: _ckd_add_3_uchar_uchar_uchar), \
    short *: \
        _Generic((a), \
        _ckd_type_shrt: \
            _Generic((b), \
            _ckd_type_cshrt: _ckd_add_3_shrt_shrt_cshrt, \
            default: _ckd_add_3_shrt_shrt_shrt), \
        _ckd_type_cshrt: \
            _Generic((b), \
            _ckd_type_cshrt: _ckd_add_3_shrt_cshrt_cshrt, \
            default:  _ckd_add_3_shrt_cshrt_shrt), \
        default: _ckd_add_3_shrt_shrt_shrt), \
    unsigned short *: \
        _Generic((a), \
        _ckd_type_ushrt: \
            _Generic((b), \
            _ckd_type_cushrt: _ckd_add_3_ushrt_ushrt_cushrt, \
            default: _ckd_add_3_ushrt_ushrt_ushrt), \
        _ckd_type_cushrt: \
            _Generic((b), \
            _ckd_type_cushrt: _ckd_add_3_ushrt_cushrt_cushrt, \
            default:  _ckd_add_3_ushrt_cushrt_ushrt), \
        default: _ckd_add_3_ushrt_ushrt_ushrt), \
    int *: \
        _Generic((a), \
        _ckd_type_int: \
            _Generic((b), \
            _ckd_type_cint: _ckd_add_3_int_int_cint, \
            default: _ckd_add_3_int_int_int), \
        _ckd_type_cint: \
            _Generic((b), \
            _ckd_type_cint: _ckd_add_3_int_cint_cint, \
            default:  _ckd_add_3_int_cint_int), \
        default: _ckd_add_3_int_int_int), \
    unsigned int *: \
        _Generic((a), \
        _ckd_type_uint: \
            _Generic((b), \
            _ckd_type_cuint: _ckd_add_3_uint_uint_cuint, \
            default: _ckd_add_3_uint_uint_uint), \
        _ckd_type_cuint: \
            _Generic((b), \
            _ckd_type_cuint: _ckd_add_3_uint_cuint_cuint, \
            default:  _ckd_add_3_uint_cuint_uint), \
        default: _ckd_add_3_uint_uint_uint), \
    long *: \
        _Generic((a), \
        _ckd_type_long: \
            _Generic((b), \
            _ckd_type_clong: _ckd_add_3_long_long_clong, \
            default: _ckd_add_3_long_long_long), \
        _ckd_type_clong: \
            _Generic((b), \
            _ckd_type_clong: _ckd_add_3_long_clong_clong, \
            default:  _ckd_add_3_long_clong_long), \
        default: _ckd_add_3_long_long_long), \
    unsigned long *: \
        _Generic((a), \
        _ckd_type_ulong: \
            _Generic((b), \
            _ckd_type_culong: _ckd_add_3_ulong_ulong_culong, \
            default: _ckd_add_3_ulong_ulong_ulong), \
        _ckd_type_culong: \
            _Generic((b), \
            _ckd_type_culong: _ckd_add_3_ulong_culong_culong, \
            default:  _ckd_add_3_ulong_culong_ulong), \
        default: _ckd_add_3_ulong_ulong_ulong), \
    long long *: \
        _Generic((a), \
        _ckd_type_llong: \
            _Generic((b), \
            _ckd_type_cllong: _ckd_add_3_llong_llong_cllong, \
            default: _ckd_add_3_llong_llong_llong), \
        _ckd_type_cllong: \
            _Generic((b), \
            _ckd_type_cllong: _ckd_add_3_llong_cllong_cllong, \
            default:  _ckd_add_3_llong_cllong_llong), \
        default: _ckd_add_3_llong_llong_llong), \
    unsigned long long *: \
        _Generic((a), \
        _ckd_type_ullong: \
            _Generic((b), \
            _ckd_type_cullong: _ckd_add_3_ullong_ullong_cullong, \
            default: _ckd_add_3_ullong_ullong_ullong), \
        _ckd_type_cullong: \
            _Generic((b), \
            _ckd_type_cullong: _ckd_add_3_ullong_cullong_cullong, \
            default:  _ckd_add_3_ullong_cullong_ullong), \
        default: _ckd_add_3_ullong_ullong_ullong), \
    __int128 *: \
        _Generic((a), \
        _ckd_type_int128: \
            _Generic((b), \
            _ckd_type_cint128: _ckd_add_3_int128_int128_cint128, \
            default: _ckd_add_3_int128_int128_int128), \
        _ckd_type_cint128: \
            _Generic((b), \
            _ckd_type_cint128: _ckd_add_3_int128_cint128_cint128, \
            default:  _ckd_add_3_int128_cint128_int128), \
        default: _ckd_add_3_int128_int128_int128), \
    unsigned __int128 *: \
        _Generic((a), \
        _ckd_type_uint128: \
            _Generic((b), \
            _ckd_type_cuint128: _ckd_add_3_uint128_uint128_cuint128, \
            default: _ckd_add_3_uint128_uint128_uint128), \
        _ckd_type_cuint128: \
            _Generic((b), \
            _ckd_type_cuint128: _ckd_add_3_uint128_cuint128_cuint128, \
            default:  _ckd_add_3_uint128_cuint128_uint128), \
        default: _ckd_add_3_uint128_uint128_uint128), \
    default: _ckd_invalid)(r, a, b)
#define _ckd_add_N(_2,_3,N,...) _ckd_add_##N
#define ckd_add(w, ...)  _ckd_add_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)

#define _ckd_sub_2(a, b)  _Generic((a), \
    _ckd_type_schar: \
        _Generic((b), \
        _ckd_type_cschar: _ckd_sub_2_schar_schar_cschar, \
        default: _ckd_sub_2_schar_schar_schar), \
    _ckd_type_cschar: \
        _Generic((b), \
        _ckd_type_cschar: _ckd_sub_2_schar_cschar_cschar, \
        default:  _ckd_sub_2_schar_cschar_schar), \
    _ckd_type_uchar: \
        _Generic((b), \
        _ckd_type_cuchar: _ckd_sub_2_uchar_uchar_cuchar, \
        default: _ckd_sub_2_uchar_uchar_uchar), \
    _ckd_type_cuchar: \
        _Generic((b), \
        _ckd_type_cuchar: _ckd_sub_2_uchar_cuchar_cuchar, \
        default:  _ckd_sub_2_uchar_cuchar_uchar), \
    _ckd_type_shrt: \
        _Generic((b), \
        _ckd_type_cshrt: _ckd_sub_2_shrt_shrt_cshrt, \
        default: _ckd_sub_2_shrt_shrt_shrt), \
    _ckd_type_cshrt: \
        _Generic((b), \
        _ckd_type_cshrt: _ckd_sub_2_shrt_cshrt_cshrt, \
        default:  _ckd_sub_2_shrt_cshrt_shrt), \
    _ckd_type_ushrt: \
        _Generic((b), \
        _ckd_type_cushrt: _ckd_sub_2_ushrt_ushrt_cushrt, \
        default: _ckd_sub_2_ushrt_ushrt_ushrt), \
    _ckd_type_cushrt: \
        _Generic((b), \
        _ckd_type_cushrt: _ckd_sub_2_ushrt_cushrt_cushrt, \
        default:  _ckd_sub_2_ushrt_cushrt_ushrt), \
    _ckd_type_int: \
        _Generic((b), \
        _ckd_type_cint: _ckd_sub_2_int_int_cint, \
        default: _ckd_sub_2_int_int_int), \
    _ckd_type_cint: \
        _Generic((b), \
        _ckd_type_cint: _ckd_sub_2_int_cint_cint, \
        default:  _ckd_sub_2_int_cint_int), \
    _ckd_type_uint: \
        _Generic((b), \
        _ckd_type_cuint: _ckd_sub_2_uint_uint_cuint, \
        default: _ckd_sub_2_uint_uint_uint), \
    _ckd_type_cuint: \
        _Generic((b), \
        _ckd_type_cuint: _ckd_sub_2_uint_cuint_cuint, \
        default:  _ckd_sub_2_uint_cuint_uint), \
    _ckd_type_long: \
        _Generic((b), \
        _ckd_type_clong: _ckd_sub_2_long_long_clong, \
        default: _ckd_sub_2_long_long_long), \
    _ckd_type_clong: \
        _Generic((b), \
        _ckd_type_clong: _ckd_sub_2_long_clong_clong, \
        default:  _ckd_sub_2_long_clong_long), \
    _ckd_type_ulong: \
        _Generic((b), \
        _ckd_type_culong: _ckd_sub_2_ulong_ulong_culong, \
        default: _ckd_sub_2_ulong_ulong_ulong), \
    _ckd_type_culong: \
        _Generic((b), \
        _ckd_type_culong: _ckd_sub_2_ulong_culong_culong, \
        default:  _ckd_sub_2_ulong_culong_ulong), \
    _ckd_type_llong: \
        _Generic((b), \
        _ckd_type_cllong: _ckd_sub_2_llong_llong_cllong, \
        default: _ckd_sub_2_llong_llong_llong), \
    _ckd_type_cllong: \
        _Generic((b), \
        _ckd_type_cllong: _ckd_sub_2_llong_cllong_cllong, \
        default:  _ckd_sub_2_llong_cllong_llong), \
    _ckd_type_ullong: \
        _Generic((b), \
        _ckd_type_cullong: _ckd_sub_2_ullong_ullong_cullong, \
        default: _ckd_sub_2_ullong_ullong_ullong), \
    _ckd_type_cullong: \
        _Generic((b), \
        _ckd_type_cullong: _ckd_sub_2_ullong_cullong_cullong, \
        default:  _ckd_sub_2_ullong_cullong_ullong), \
    _ckd_type_int128: \
        _Generic((b), \
        _ckd_type_cint128: _ckd_sub_2_int128_int128_cint128, \
        default: _ckd_sub_2_int128_int128_int128), \
    _ckd_type_cint128: \
        _Generic((b), \
        _ckd_type_cint128: _ckd_sub_2_int128_cint128_cint128, \
        default:  _ckd_sub_2_int128_cint128_int128), \
    _ckd_type_uint128: \
        _Generic((b), \
        _ckd_type_cuint128: _ckd_sub_2_uint128_uint128_cuint128, \
        default: _ckd_sub_2_uint128_uint128_uint128), \
    _ckd_type_cuint128: \
        _Generic((b), \
        _ckd_type_cuint128: _ckd_sub_2_uint128_cuint128_cuint128, \
        default:  _ckd_sub_2_uint128_cuint128_uint128), \
    default: _ckd_invalid)(a, b)
#define _ckd_sub_3(r, a, b)  _Generic((r), \
    signed char *: \
        _Generic((a), \
        _ckd_type_schar: \
            _Generic((b), \
            _ckd_type_cschar: _ckd_sub_3_schar_schar_cschar, \
            default: _ckd_sub_3_schar_schar_schar), \
        _ckd_type_cschar: \
            _Generic((b), \
            _ckd_type_cschar: _ckd_sub_3_schar_cschar_cschar, \
            default:  _ckd_sub_3_schar_cschar_schar), \
        default: _ckd_sub_3_schar_schar_schar), \
    unsigned char *: \
        _Generic((a), \
        _ckd_type_uchar: \
            _Generic((b), \
            _ckd_type_cuchar: _ckd_sub_3_uchar_uchar_cuchar, \
            default: _ckd_sub_3_uchar_uchar_uchar), \
        _ckd_type_cuchar: \
            _Generic((b), \
            _ckd_type_cuchar: _ckd_sub_3_uchar_cuchar_cuchar, \
            default:  _ckd_sub_3_uchar_cuchar_uchar), \
        default: _ckd_sub_3_uchar_uchar_uchar), \
    short *: \
        _Generic((a), \
        _ckd_type_shrt: \
            _Generic((b), \
            _ckd_type_cshrt: _ckd_sub_3_shrt_shrt_cshrt, \
            default: _ckd_sub_3_shrt_shrt_shrt), \
        _ckd_type_cshrt: \
            _Generic((b), \
            _ckd_type_cshrt: _ckd_sub_3_shrt_cshrt_cshrt, \
            default:  _ckd_sub_3_shrt_cshrt_shrt), \
        default: _ckd_sub_3_shrt_shrt_shrt), \
    unsigned short *: \
        _Generic((a), \
        _ckd_type_ushrt: \
            _Generic((b), \
            _ckd_type_cushrt: _ckd_sub_3_ushrt_ushrt_cushrt, \
            default: _ckd_sub_3_ushrt_ushrt_ushrt), \
        _ckd_type_cushrt: \
            _Generic((b), \
            _ckd_type_cushrt: _ckd_sub_3_ushrt_cushrt_cushrt, \
            default:  _ckd_sub_3_ushrt_cushrt_ushrt), \
        default: _ckd_sub_3_ushrt_ushrt_ushrt), \
    int *: \
        _Generic((a), \
        _ckd_type_int: \
            _Generic((b), \
            _ckd_type_cint: _ckd_sub_3_int_int_cint, \
            default: _ckd_sub_3_int_int_int), \
        _ckd_type_cint: \
            _Generic((b), \
            _ckd_type_cint: _ckd_sub_3_int_cint_cint, \
            default:  _ckd_sub_3_int_cint_int), \
        default: _ckd_sub_3_int_int_int), \
    unsigned int *: \
        _Generic((a), \
        _ckd_type_uint: \
            _Generic((b), \
            _ckd_type_cuint: _ckd_sub_3_uint_uint_cuint, \
            default: _ckd_sub_3_uint_uint_uint), \
        _ckd_type_cuint: \
            _Generic((b), \
            _ckd_type_cuint: _ckd_sub_3_uint_cuint_cuint, \
            default:  _ckd_sub_3_uint_cuint_uint), \
        default: _ckd_sub_3_uint_uint_uint), \
    long *: \
        _Generic((a), \
        _ckd_type_long: \
            _Generic((b), \
            _ckd_type_clong: _ckd_sub_3_long_long_clong, \
            default: _ckd_sub_3_long_long_long), \
        _ckd_type_clong: \
            _Generic((b), \
            _ckd_type_clong: _ckd_sub_3_long_clong_clong, \
            default:  _ckd_sub_3_long_clong_long), \
        default: _ckd_sub_3_long_long_long), \
    unsigned long *: \
        _Generic((a), \
        _ckd_type_ulong: \
            _Generic((b), \
            _ckd_type_culong: _ckd_sub_3_ulong_ulong_culong, \
            default: _ckd_sub_3_ulong_ulong_ulong), \
        _ckd_type_culong: \
            _Generic((b), \
            _ckd_type_culong: _ckd_sub_3_ulong_culong_culong, \
            default:  _ckd_sub_3_ulong_culong_ulong), \
        default: _ckd_sub_3_ulong_ulong_ulong), \
    long long *: \
        _Generic((a), \
        _ckd_type_llong: \
            _Generic((b), \
            _ckd_type_cllong: _ckd_sub_3_llong_llong_cllong, \
            default: _ckd_sub_3_llong_llong_llong), \
        _ckd_type_cllong: \
            _Generic((b), \
            _ckd_type_cllong: _ckd_sub_3_llong_cllong_cllong, \
            default:  _ckd_sub_3_llong_cllong_llong), \
        default: _ckd_sub_3_llong_llong_llong), \
    unsigned long long *: \
        _Generic((a), \
        _ckd_type_ullong: \
            _Generic((b), \
            _ckd_type_cullong: _ckd_sub_3_ullong_ullong_cullong, \
            default: _ckd_sub_3_ullong_ullong_ullong), \
        _ckd_type_cullong: \
            _Generic((b), \
            _ckd_type_cullong: _ckd_sub_3_ullong_cullong_cullong, \
            default:  _ckd_sub_3_ullong_cullong_ullong), \
        default: _ckd_sub_3_ullong_ullong_ullong), \
    __int128 *: \
        _Generic((a), \
        _ckd_type_int128: \
            _Generic((b), \
            _ckd_type_cint128: _ckd_sub_3_int128_int128_cint128, \
            default: _ckd_sub_3_int128_int128_int128), \
        _ckd_type_cint128: \
            _Generic((b), \
            _ckd_type_cint128: _ckd_sub_3_int128_cint128_cint128, \
            default:  _ckd_sub_3_int128_cint128_int128), \
        default: _ckd_sub_3_int128_int128_int128), \
    unsigned __int128 *: \
        _Generic((a), \
        _ckd_type_uint128: \
            _Generic((b), \
            _ckd_type_cuint128: _ckd_sub_3_uint128_uint128_cuint128, \
            default: _ckd_sub_3_uint128_uint128_uint128), \
        _ckd_type_cuint128: \
            _Generic((b), \
            _ckd_type_cuint128: _ckd_sub_3_uint128_cuint128_cuint128, \
            default:  _ckd_sub_3_uint128_cuint128_uint128), \
        default: _ckd_sub_3_uint128_uint128_uint128), \
    default: _ckd_invalid)(r, a, b)
#define _ckd_sub_N(_2,_3,N,...) _ckd_sub_##N
#define ckd_sub(w, ...)  _ckd_sub_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)

#define _ckd_mul_2(a, b)  _Generic((a), \
    _ckd_type_schar: \
        _Generic((b), \
        _ckd_type_cschar: _ckd_mul_2_schar_schar_cschar, \
        default: _ckd_mul_2_schar_schar_schar), \
    _ckd_type_cschar: \
        _Generic((b), \
        _ckd_type_cschar: _ckd_mul_2_schar_cschar_cschar, \
        default:  _ckd_mul_2_schar_cschar_schar), \
    _ckd_type_uchar: \
        _Generic((b), \
        _ckd_type_cuchar: _ckd_mul_2_uchar_uchar_cuchar, \
        default: _ckd_mul_2_uchar_uchar_uchar), \
    _ckd_type_cuchar: \
        _Generic((b), \
        _ckd_type_cuchar: _ckd_mul_2_uchar_cuchar_cuchar, \
        default:  _ckd_mul_2_uchar_cuchar_uchar), \
    _ckd_type_shrt: \
        _Generic((b), \
        _ckd_type_cshrt: _ckd_mul_2_shrt_shrt_cshrt, \
        default: _ckd_mul_2_shrt_shrt_shrt), \
    _ckd_type_cshrt: \
        _Generic((b), \
        _ckd_type_cshrt: _ckd_mul_2_shrt_cshrt_cshrt, \
        default:  _ckd_mul_2_shrt_cshrt_shrt), \
    _ckd_type_ushrt: \
        _Generic((b), \
        _ckd_type_cushrt: _ckd_mul_2_ushrt_ushrt_cushrt, \
        default: _ckd_mul_2_ushrt_ushrt_ushrt), \
    _ckd_type_cushrt: \
        _Generic((b), \
        _ckd_type_cushrt: _ckd_mul_2_ushrt_cushrt_cushrt, \
        default:  _ckd_mul_2_ushrt_cushrt_ushrt), \
    _ckd_type_int: \
        _Generic((b), \
        _ckd_type_cint: _ckd_mul_2_int_int_cint, \
        default: _ckd_mul_2_int_int_int), \
    _ckd_type_cint: \
        _Generic((b), \
        _ckd_type_cint: _ckd_mul_2_int_cint_cint, \
        default:  _ckd_mul_2_int_cint_int), \
    _ckd_type_uint: \
        _Generic((b), \
        _ckd_type_cuint: _ckd_mul_2_uint_uint_cuint, \
        default: _ckd_mul_2_uint_uint_uint), \
    _ckd_type_cuint: \
        _Generic((b), \
        _ckd_type_cuint: _ckd_mul_2_uint_cuint_cuint, \
        default:  _ckd_mul_2_uint_cuint_uint), \
    _ckd_type_long: \
        _Generic((b), \
        _ckd_type_clong: _ckd_mul_2_long_long_clong, \
        default: _ckd_mul_2_long_long_long), \
    _ckd_type_clong: \
        _Generic((b), \
        _ckd_type_clong: _ckd_mul_2_long_clong_clong, \
        default:  _ckd_mul_2_long_clong_long), \
    _ckd_type_ulong: \
        _Generic((b), \
        _ckd_type_culong: _ckd_mul_2_ulong_ulong_culong, \
        default: _ckd_mul_2_ulong_ulong_ulong), \
    _ckd_type_culong: \
        _Generic((b), \
        _ckd_type_culong: _ckd_mul_2_ulong_culong_culong, \
        default:  _ckd_mul_2_ulong_culong_ulong), \
    _ckd_type_llong: \
        _Generic((b), \
        _ckd_type_cllong: _ckd_mul_2_llong_llong_cllong, \
        default: _ckd_mul_2_llong_llong_llong), \
    _ckd_type_cllong: \
        _Generic((b), \
        _ckd_type_cllong: _ckd_mul_2_llong_cllong_cllong, \
        default:  _ckd_mul_2_llong_cllong_llong), \
    _ckd_type_ullong: \
        _Generic((b), \
        _ckd_type_cullong: _ckd_mul_2_ullong_ullong_cullong, \
        default: _ckd_mul_2_ullong_ullong_ullong), \
    _ckd_type_cullong: \
        _Generic((b), \
        _ckd_type_cullong: _ckd_mul_2_ullong_cullong_cullong, \
        default:  _ckd_mul_2_ullong_cullong_ullong), \
    _ckd_type_int128: \
        _Generic((b), \
        _ckd_type_cint128: _ckd_mul_2_int128_int128_cint128, \
        default: _ckd_mul_2_int128_int128_int128), \
    _ckd_type_cint128: \
        _Generic((b), \
        _ckd_type_cint128: _ckd_mul_2_int128_cint128_cint128, \
        default:  _ckd_mul_2_int128_cint128_int128), \
    _ckd_type_uint128: \
        _Generic((b), \
        _ckd_type_cuint128: _ckd_mul_2_uint128_uint128_cuint128, \
        default: _ckd_mul_2_uint128_uint128_uint128), \
    _ckd_type_cuint128: \
        _Generic((b), \
        _ckd_type_cuint128: _ckd_mul_2_uint128_cuint128_cuint128, \
        default:  _ckd_mul_2_uint128_cuint128_uint128), \
    default: _ckd_invalid)(a, b)
#define _ckd_mul_3(r, a, b)  _Generic((r), \
    signed char *: \
        _Generic((a), \
        _ckd_type_schar: \
            _Generic((b), \
            _ckd_type_cschar: _ckd_mul_3_schar_schar_cschar, \
            default: _ckd_mul_3_schar_schar_schar), \
        _ckd_type_cschar: \
            _Generic((b), \
            _ckd_type_cschar: _ckd_mul_3_schar_cschar_cschar, \
            default:  _ckd_mul_3_schar_cschar_schar), \
        default: _ckd_mul_3_schar_schar_schar), \
    unsigned char *: \
        _Generic((a), \
        _ckd_type_uchar: \
            _Generic((b), \
            _ckd_type_cuchar: _ckd_mul_3_uchar_uchar_cuchar, \
            default: _ckd_mul_3_uchar_uchar_uchar), \
        _ckd_type_cuchar: \
            _Generic((b), \
            _ckd_type_cuchar: _ckd_mul_3_uchar_cuchar_cuchar, \
            default:  _ckd_mul_3_uchar_cuchar_uchar), \
        default: _ckd_mul_3_uchar_uchar_uchar), \
    short *: \
        _Generic((a), \
        _ckd_type_shrt: \
            _Generic((b), \
            _ckd_type_cshrt: _ckd_mul_3_shrt_shrt_cshrt, \
            default: _ckd_mul_3_shrt_shrt_shrt), \
        _ckd_type_cshrt: \
            _Generic((b), \
            _ckd_type_cshrt: _ckd_mul_3_shrt_cshrt_cshrt, \
            default:  _ckd_mul_3_shrt_cshrt_shrt), \
        default: _ckd_mul_3_shrt_shrt_shrt), \
    unsigned short *: \
        _Generic((a), \
        _ckd_type_ushrt: \
            _Generic((b), \
            _ckd_type_cushrt: _ckd_mul_3_ushrt_ushrt_cushrt, \
            default: _ckd_mul_3_ushrt_ushrt_ushrt), \
        _ckd_type_cushrt: \
            _Generic((b), \
            _ckd_type_cushrt: _ckd_mul_3_ushrt_cushrt_cushrt, \
            default:  _ckd_mul_3_ushrt_cushrt_ushrt), \
        default: _ckd_mul_3_ushrt_ushrt_ushrt), \
    int *: \
        _Generic((a), \
        _ckd_type_int: \
            _Generic((b), \
            _ckd_type_cint: _ckd_mul_3_int_int_cint, \
            default: _ckd_mul_3_int_int_int), \
        _ckd_type_cint: \
            _Generic((b), \
            _ckd_type_cint: _ckd_mul_3_int_cint_cint, \
            default:  _ckd_mul_3_int_cint_int), \
        default: _ckd_mul_3_int_int_int), \
    unsigned int *: \
        _Generic((a), \
        _ckd_type_uint: \
            _Generic((b), \
            _ckd_type_cuint: _ckd_mul_3_uint_uint_cuint, \
            default: _ckd_mul_3_uint_uint_uint), \
        _ckd_type_cuint: \
            _Generic((b), \
            _ckd_type_cuint: _ckd_mul_3_uint_cuint_cuint, \
            default:  _ckd_mul_3_uint_cuint_uint), \
        default: _ckd_mul_3_uint_uint_uint), \
    long *: \
        _Generic((a), \
        _ckd_type_long: \
            _Generic((b), \
            _ckd_type_clong: _ckd_mul_3_long_long_clong, \
            default: _ckd_mul_3_long_long_long), \
        _ckd_type_clong: \
            _Generic((b), \
            _ckd_type_clong: _ckd_mul_3_long_clong_clong, \
            default:  _ckd_mul_3_long_clong_long), \
        default: _ckd_mul_3_long_long_long), \
    unsigned long *: \
        _Generic((a), \
        _ckd_type_ulong: \
            _Generic((b), \
            _ckd_type_culong: _ckd_mul_3_ulong_ulong_culong, \
            default: _ckd_mul_3_ulong_ulong_ulong), \
        _ckd_type_culong: \
            _Generic((b), \
            _ckd_type_culong: _ckd_mul_3_ulong_culong_culong, \
            default:  _ckd_mul_3_ulong_culong_ulong), \
        default: _ckd_mul_3_ulong_ulong_ulong), \
    long long *: \
        _Generic((a), \
        _ckd_type_llong: \
            _Generic((b), \
            _ckd_type_cllong: _ckd_mul_3_llong_llong_cllong, \
            default: _ckd_mul_3_llong_llong_llong), \
        _ckd_type_cllong: \
            _Generic((b), \
            _ckd_type_cllong: _ckd_mul_3_llong_cllong_cllong, \
            default:  _ckd_mul_3_llong_cllong_llong), \
        default: _ckd_mul_3_llong_llong_llong), \
    unsigned long long *: \
        _Generic((a), \
        _ckd_type_ullong: \
            _Generic((b), \
            _ckd_type_cullong: _ckd_mul_3_ullong_ullong_cullong, \
            default: _ckd_mul_3_ullong_ullong_ullong), \
        _ckd_type_cullong: \
            _Generic((b), \
            _ckd_type_cullong: _ckd_mul_3_ullong_cullong_cullong, \
            default:  _ckd_mul_3_ullong_cullong_ullong), \
        default: _ckd_mul_3_ullong_ullong_ullong), \
    __int128 *: \
        _Generic((a), \
        _ckd_type_int128: \
            _Generic((b), \
            _ckd_type_cint128: _ckd_mul_3_int128_int128_cint128, \
            default: _ckd_mul_3_int128_int128_int128), \
        _ckd_type_cint128: \
            _Generic((b), \
            _ckd_type_cint128: _ckd_mul_3_int128_cint128_cint128, \
            default:  _ckd_mul_3_int128_cint128_int128), \
        default: _ckd_mul_3_int128_int128_int128), \
    unsigned __int128 *: \
        _Generic((a), \
        _ckd_type_uint128: \
            _Generic((b), \
            _ckd_type_cuint128: _ckd_mul_3_uint128_uint128_cuint128, \
            default: _ckd_mul_3_uint128_uint128_uint128), \
        _ckd_type_cuint128: \
            _Generic((b), \
            _ckd_type_cuint128: _ckd_mul_3_uint128_cuint128_cuint128, \
            default:  _ckd_mul_3_uint128_cuint128_uint128), \
        default: _ckd_mul_3_uint128_uint128_uint128), \
    default: _ckd_invalid)(r, a, b)
#define _ckd_mul_N(_2,_3,N,...) _ckd_mul_##N
#define ckd_mul(w, ...)  _ckd_mul_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)

#define _ckd_div_2(a, b)  _Generic((a), \
    _ckd_type_schar: \
        _Generic((b), \
        _ckd_type_cschar: _ckd_div_2_schar_schar_cschar, \
        default: _ckd_div_2_schar_schar_schar), \
    _ckd_type_cschar: \
        _Generic((b), \
        _ckd_type_cschar: _ckd_div_2_schar_cschar_cschar, \
        default:  _ckd_div_2_schar_cschar_schar), \
    _ckd_type_uchar: \
        _Generic((b), \
        _ckd_type_cuchar: _ckd_div_2_uchar_uchar_cuchar, \
        default: _ckd_div_2_uchar_uchar_uchar), \
    _ckd_type_cuchar: \
        _Generic((b), \
        _ckd_type_cuchar: _ckd_div_2_uchar_cuchar_cuchar, \
        default:  _ckd_div_2_uchar_cuchar_uchar), \
    _ckd_type_shrt: \
        _Generic((b), \
        _ckd_type_cshrt: _ckd_div_2_shrt_shrt_cshrt, \
        default: _ckd_div_2_shrt_shrt_shrt), \
    _ckd_type_cshrt: \
        _Generic((b), \
        _ckd_type_cshrt: _ckd_div_2_shrt_cshrt_cshrt, \
        default:  _ckd_div_2_shrt_cshrt_shrt), \
    _ckd_type_ushrt: \
        _Generic((b), \
        _ckd_type_cushrt: _ckd_div_2_ushrt_ushrt_cushrt, \
        default: _ckd_div_2_ushrt_ushrt_ushrt), \
    _ckd_type_cushrt: \
        _Generic((b), \
        _ckd_type_cushrt: _ckd_div_2_ushrt_cushrt_cushrt, \
        default:  _ckd_div_2_ushrt_cushrt_ushrt), \
    _ckd_type_int: \
        _Generic((b), \
        _ckd_type_cint: _ckd_div_2_int_int_cint, \
        default: _ckd_div_2_int_int_int), \
    _ckd_type_cint: \
        _Generic((b), \
        _ckd_type_cint: _ckd_div_2_int_cint_cint, \
        default:  _ckd_div_2_int_cint_int), \
    _ckd_type_uint: \
        _Generic((b), \
        _ckd_type_cuint: _ckd_div_2_uint_uint_cuint, \
        default: _ckd_div_2_uint_uint_uint), \
    _ckd_type_cuint: \
        _Generic((b), \
        _ckd_type_cuint: _ckd_div_2_uint_cuint_cuint, \
        default:  _ckd_div_2_uint_cuint_uint), \
    _ckd_type_long: \
        _Generic((b), \
        _ckd_type_clong: _ckd_div_2_long_long_clong, \
        default: _ckd_div_2_long_long_long), \
    _ckd_type_clong: \
        _Generic((b), \
        _ckd_type_clong: _ckd_div_2_long_clong_clong, \
        default:  _ckd_div_2_long_clong_long), \
    _ckd_type_ulong: \
        _Generic((b), \
        _ckd_type_culong: _ckd_div_2_ulong_ulong_culong, \
        default: _ckd_div_2_ulong_ulong_ulong), \
    _ckd_type_culong: \
        _Generic((b), \
        _ckd_type_culong: _ckd_div_2_ulong_culong_culong, \
        default:  _ckd_div_2_ulong_culong_ulong), \
    _ckd_type_llong: \
        _Generic((b), \
        _ckd_type_cllong: _ckd_div_2_llong_llong_cllong, \
        default: _ckd_div_2_llong_llong_llong), \
    _ckd_type_cllong: \
        _Generic((b), \
        _ckd_type_cllong: _ckd_div_2_llong_cllong_cllong, \
        default:  _ckd_div_2_llong_cllong_llong), \
    _ckd_type_ullong: \
        _Generic((b), \
        _ckd_type_cullong: _ckd_div_2_ullong_ullong_cullong, \
        default: _ckd_div_2_ullong_ullong_ullong), \
    _ckd_type_cullong: \
        _Generic((b), \
        _ckd_type_cullong: _ckd_div_2_ullong_cullong_cullong, \
        default:  _ckd_div_2_ullong_cullong_ullong), \
    _ckd_type_int128: \
        _Generic((b), \
        _ckd_type_cint128: _ckd_div_2_int128_int128_cint128, \
        default: _ckd_div_2_int128_int128_int128), \
    _ckd_type_cint128: \
        _Generic((b), \
        _ckd_type_cint128: _ckd_div_2_int128_cint128_cint128, \
        default:  _ckd_div_2_int128_cint128_int128), \
    _ckd_type_uint128: \
        _Generic((b), \
        _ckd_type_cuint128: _ckd_div_2_uint128_uint128_cuint128, \
        default: _ckd_div_2_uint128_uint128_uint128), \
    _ckd_type_cuint128: \
        _Generic((b), \
        _ckd_type_cuint128: _ckd_div_2_uint128_cuint128_cuint128, \
        default:  _ckd_div_2_uint128_cuint128_uint128), \
    default: _ckd_invalid)(a, b)
#define _ckd_div_3(r, a, b)  _Generic((r), \
    signed char *: \
        _Generic((a), \
        _ckd_type_schar: \
            _Generic((b), \
            _ckd_type_cschar: _ckd_div_3_schar_schar_cschar, \
            default: _ckd_div_3_schar_schar_schar), \
        _ckd_type_cschar: \
            _Generic((b), \
            _ckd_type_cschar: _ckd_div_3_schar_cschar_cschar, \
            default:  _ckd_div_3_schar_cschar_schar), \
        default: _ckd_div_3_schar_schar_schar), \
    unsigned char *: \
        _Generic((a), \
        _ckd_type_uchar: \
            _Generic((b), \
            _ckd_type_cuchar: _ckd_div_3_uchar_uchar_cuchar, \
            default: _ckd_div_3_uchar_uchar_uchar), \
        _ckd_type_cuchar: \
            _Generic((b), \
            _ckd_type_cuchar: _ckd_div_3_uchar_cuchar_cuchar, \
            default:  _ckd_div_3_uchar_cuchar_uchar), \
        default: _ckd_div_3_uchar_uchar_uchar), \
    short *: \
        _Generic((a), \
        _ckd_type_shrt: \
            _Generic((b), \
            _ckd_type_cshrt: _ckd_div_3_shrt_shrt_cshrt, \
            default: _ckd_div_3_shrt_shrt_shrt), \
        _ckd_type_cshrt: \
            _Generic((b), \
            _ckd_type_cshrt: _ckd_div_3_shrt_cshrt_cshrt, \
            default:  _ckd_div_3_shrt_cshrt_shrt), \
        default: _ckd_div_3_shrt_shrt_shrt), \
    unsigned short *: \
        _Generic((a), \
        _ckd_type_ushrt: \
            _Generic((b), \
            _ckd_type_cushrt: _ckd_div_3_ushrt_ushrt_cushrt, \
            default: _ckd_div_3_ushrt_ushrt_ushrt), \
        _ckd_type_cushrt: \
            _Generic((b), \
            _ckd_type_cushrt: _ckd_div_3_ushrt_cushrt_cushrt, \
            default:  _ckd_div_3_ushrt_cushrt_ushrt), \
        default: _ckd_div_3_ushrt_ushrt_ushrt), \
    int *: \
        _Generic((a), \
        _ckd_type_int: \
            _Generic((b), \
            _ckd_type_cint: _ckd_div_3_int_int_cint, \
            default: _ckd_div_3_int_int_int), \
        _ckd_type_cint: \
            _Generic((b), \
            _ckd_type_cint: _ckd_div_3_int_cint_cint, \
            default:  _ckd_div_3_int_cint_int), \
        default: _ckd_div_3_int_int_int), \
    unsigned int *: \
        _Generic((a), \
        _ckd_type_uint: \
            _Generic((b), \
            _ckd_type_cuint: _ckd_div_3_uint_uint_cuint, \
            default: _ckd_div_3_uint_uint_uint), \
        _ckd_type_cuint: \
            _Generic((b), \
            _ckd_type_cuint: _ckd_div_3_uint_cuint_cuint, \
            default:  _ckd_div_3_uint_cuint_uint), \
        default: _ckd_div_3_uint_uint_uint), \
    long *: \
        _Generic((a), \
        _ckd_type_long: \
            _Generic((b), \
            _ckd_type_clong: _ckd_div_3_long_long_clong, \
            default: _ckd_div_3_long_long_long), \
        _ckd_type_clong: \
            _Generic((b), \
            _ckd_type_clong: _ckd_div_3_long_clong_clong, \
            default:  _ckd_div_3_long_clong_long), \
        default: _ckd_div_3_long_long_long), \
    unsigned long *: \
        _Generic((a), \
        _ckd_type_ulong: \
            _Generic((b), \
            _ckd_type_culong: _ckd_div_3_ulong_ulong_culong, \
            default: _ckd_div_3_ulong_ulong_ulong), \
        _ckd_type_culong: \
            _Generic((b), \
            _ckd_type_culong: _ckd_div_3_ulong_culong_culong, \
            default:  _ckd_div_3_ulong_culong_ulong), \
        default: _ckd_div_3_ulong_ulong_ulong), \
    long long *: \
        _Generic((a), \
        _ckd_type_llong: \
            _Generic((b), \
            _ckd_type_cllong: _ckd_div_3_llong_llong_cllong, \
            default: _ckd_div_3_llong_llong_llong), \
        _ckd_type_cllong: \
            _Generic((b), \
            _ckd_type_cllong: _ckd_div_3_llong_cllong_cllong, \
            default:  _ckd_div_3_llong_cllong_llong), \
        default: _ckd_div_3_llong_llong_llong), \
    unsigned long long *: \
        _Generic((a), \
        _ckd_type_ullong: \
            _Generic((b), \
            _ckd_type_cullong: _ckd_div_3_ullong_ullong_cullong, \
            default: _ckd_div_3_ullong_ullong_ullong), \
        _ckd_type_cullong: \
            _Generic((b), \
            _ckd_type_cullong: _ckd_div_3_ullong_cullong_cullong, \
            default:  _ckd_div_3_ullong_cullong_ullong), \
        default: _ckd_div_3_ullong_ullong_ullong), \
    __int128 *: \
        _Generic((a), \
        _ckd_type_int128: \
            _Generic((b), \
            _ckd_type_cint128: _ckd_div_3_int128_int128_cint128, \
            default: _ckd_div_3_int128_int128_int128), \
        _ckd_type_cint128: \
            _Generic((b), \
            _ckd_type_cint128: _ckd_div_3_int128_cint128_cint128, \
            default:  _ckd_div_3_int128_cint128_int128), \
        default: _ckd_div_3_int128_int128_int128), \
    unsigned __int128 *: \
        _Generic((a), \
        _ckd_type_uint128: \
            _Generic((b), \
            _ckd_type_cuint128: _ckd_div_3_uint128_uint128_cuint128, \
            default: _ckd_div_3_uint128_uint128_uint128), \
        _ckd_type_cuint128: \
            _Generic((b), \
            _ckd_type_cuint128: _ckd_div_3_uint128_cuint128_cuint128, \
            default:  _ckd_div_3_uint128_cuint128_uint128), \
        default: _ckd_div_3_uint128_uint128_uint128), \
    default: _ckd_invalid)(r, a, b)
#define _ckd_div_N(_2,_3,N,...) _ckd_div_##N
#define ckd_div(w, ...)  _ckd_div_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)


// ]]]
// EOF [[[

#endif /* CKDINT_H_ */

// ]]]
