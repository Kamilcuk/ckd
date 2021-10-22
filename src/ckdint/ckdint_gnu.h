{% import "library.jinja" as L %}
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
{% call() L.foreach_TYPE(inmacro=1) %}
    _ckd_$TYPE:  ckd_mk_$TYPE_t, \
    _ckd_c$TYPE: ckd_mk_$TYPE_t
{%- endcall %})

// Generic macros implementation for GNU compatible[[[
{% call() L.foreach_OP() %}

#define _ckd_$OP_2(a, b)  ({ \
        __auto_type _tMp = _ckd_getctype(_ckd_value(a) + _ckd_value(b))(0, 0); \
        ckd_overflow(_tMp) = __builtin_$OP_overflow(_ckd_value(a), _ckd_value(b), &ckd_value(_tMp)) || _ckd_overflow(a) || _ckd_overflow(b); \
        _tMp; \
        })

#define _ckd_$OP_3(r, a, b) \
        (__builtin_$OP_overflow(_ckd_value(a), _ckd_value(b), r) || _ckd_overflow(a) || _ckd_overflow(b))

{% endcall %}
// ]]]
// vim: ft=c

