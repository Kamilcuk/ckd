/**
 * @file ckdint_gnu.h
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * SPDX-License-Identifier: MIT + Beerware
 */
#ifndef CKDINT_H_
#error  This is internal header
#endif

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
    _ckd_cullong: ckd_mk_ullong_t)

// Generic macros implementation for GNU compatible[[[

#define _ckd_add_2(a, b)  ({ \
        __auto_type _tMp = _ckd_getctype(_ckd_value(a) + _ckd_value(b))(0, 0); \
        ckd_overflow(_tMp) = __builtin_add_overflow(_ckd_value(a), _ckd_value(b), &ckd_value(_tMp)) || _ckd_overflow(a) || _ckd_overflow(b); \
        _tMp; \
        })

#define _ckd_add_3(r, a, b) \
        (__builtin_add_overflow(_ckd_value(a), _ckd_value(b), r) || _ckd_overflow(a) || _ckd_overflow(b))


#define _ckd_sub_2(a, b)  ({ \
        __auto_type _tMp = _ckd_getctype(_ckd_value(a) + _ckd_value(b))(0, 0); \
        ckd_overflow(_tMp) = __builtin_sub_overflow(_ckd_value(a), _ckd_value(b), &ckd_value(_tMp)) || _ckd_overflow(a) || _ckd_overflow(b); \
        _tMp; \
        })

#define _ckd_sub_3(r, a, b) \
        (__builtin_sub_overflow(_ckd_value(a), _ckd_value(b), r) || _ckd_overflow(a) || _ckd_overflow(b))


#define _ckd_mul_2(a, b)  ({ \
        __auto_type _tMp = _ckd_getctype(_ckd_value(a) + _ckd_value(b))(0, 0); \
        ckd_overflow(_tMp) = __builtin_mul_overflow(_ckd_value(a), _ckd_value(b), &ckd_value(_tMp)) || _ckd_overflow(a) || _ckd_overflow(b); \
        _tMp; \
        })

#define _ckd_mul_3(r, a, b) \
        (__builtin_mul_overflow(_ckd_value(a), _ckd_value(b), r) || _ckd_overflow(a) || _ckd_overflow(b))

// ]]]
// vim: ft=c

