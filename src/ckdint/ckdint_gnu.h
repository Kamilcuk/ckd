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
#include "../ckdint.h"
#endif

#if __GNUC__ > 10
#define _ckd_wr(x) __attribute__((__access__(__write_only__, x)))
#else
#define _ckd_wr(x)
#endif

{% call() L.foreach_TYPE(char=1) %}
_ckd_wr(1) _ckd_fchpnt bool _ckd_assign_$TYPE(_ckd_$TYPE *v, _ckd_c$TYPE c) { *v = ckd_value(c); return ckd_overflow(c); }
_ckd_wr(1) _ckd_fchpnt bool _ckd_assign_c$TYPE(_ckd_c$TYPE *v, _ckd_c$TYPE c) { *v = c; return ckd_overflow(c); }
{% endcall %}

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
		__auto_type _ckd_r = (r); \
		__auto_type _ckd_ca = _ckd_toct(_ckd_a); \
		__auto_type _ckd_cb = _ckd_toct(_ckd_b); \
		__typeof__(_ckd_ctypeof(*_ckd_r)) _ckd_tmp; \
		ckd_overflow(_ckd_tmp) = __builtin_$OP_overflow(ckd_value(_ckd_ca), ckd_value(_ckd_cb), &ckd_value(_ckd_tmp)) \
			|| ckd_overflow(_ckd_ca) || ckd_overflow(_ckd_cb); \
		_Generic(*_ckd_r, \
	{% call() L.foreach_TYPE(char=1, inmacro=1) %}
		_ckd_$TYPE: _ckd_assign_$TYPE, \
		_ckd_c$TYPE: _ckd_assign_c$TYPE
	{%- endcall %})(_ckd_r, _ckd_tmp); \
		})

{% endcall %}
// ]]]
// vim: ft=c

