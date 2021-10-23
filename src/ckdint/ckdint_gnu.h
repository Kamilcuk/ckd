{% import "library.jinja" as L %}
/**
 * @file ckdint_gnu.h
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * @copyright 2021 Kamil Cukrowski
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
		__auto_type _ckd_a = (a); \
		__auto_type _ckd_b = (b); \
		__auto_type _ckd_ca = _ckd_toct(_ckd_a); \
		__auto_type _ckd_cb = _ckd_toct(_ckd_b); \
		__auto_type _ckd_tmp = _ckd_getctype(ckd_value(_ckd_ca) + ckd_value(_ckd_cb))(0, 0); \
		ckd_overflow(_ckd_tmp) = __builtin_$OP_overflow(_ckd_value(_ckd_ca), ckd_value(_ckd_cb), &ckd_value(_ckd_tmp)) \
			|| ckd_overflow(_ckd_ca) || ckd_overflow(_ckd_cb); \
		_ckd_tmp; \
		})

#define _ckd_$OP_3(r, a, b)  ({ \
		__auto_type _ckd_a = (a); \
		__auto_type _ckd_b = (b); \
		__auto_type _ckd_ca = _ckd_toct(_ckd_a); \
		__auto_type _ckd_cb = _ckd_toct(_ckd_b); \
		__builtin_$OP_overflow(_ckd_value(_ckd_ca), ckd_value(_ckd_cb), r) \
			|| ckd_overflow(_ckd_ca) || ckd_overflow(_ckd_cb); \
		})

{% endcall %}
// ]]]
// vim: ft=c

