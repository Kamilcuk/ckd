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

// Generic macros implementation for GNU compatible[[[
{% call() L.foreach_OP() %}

#define _ckd_$OP_2(a, b)  __extension__({ \
		__auto_type _ckd_a = (a); \
		__auto_type _ckd_b = (b); \
		__auto_type _ckd_ca = _ckd_toct(_ckd_a); \
		__auto_type _ckd_cb = _ckd_toct(_ckd_b); \
		__typeof__(_ckd_ctypeof(ckd_value(_ckd_ca) + ckd_value(_ckd_cb))) _ckd_tmp; \
		ckd_overflow(_ckd_tmp) = __builtin_$OP_overflow(ckd_value(_ckd_ca), ckd_value(_ckd_cb), &ckd_value(_ckd_tmp)) \
			|| ckd_overflow(_ckd_ca) || ckd_overflow(_ckd_cb); \
		_ckd_tmp; \
		})

#define _ckd_$OP_3(r, a, b)  __extension__({ \
		__auto_type _ckd_a = (a); \
		__auto_type _ckd_b = (b); \
		__auto_type _ckd_ca = _ckd_toct(_ckd_a); \
		__auto_type _ckd_cb = _ckd_toct(_ckd_b); \
		__builtin_$OP_overflow(ckd_value(_ckd_ca), ckd_value(_ckd_cb), r) \
			|| ckd_overflow(_ckd_ca) || ckd_overflow(_ckd_cb); \
		})

{% endcall %}
// ]]]
// vim: ft=c

