{% import "library.jinja" as L %}
/**
 * @file ckdint_gnu.h
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * @copyright 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
 * SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
 * SPDX-License-Identifier: MIT
 */
#ifndef CKDINT_GNU
#define CKDINT_GNU
#ifndef CKDINT_H_
#error  This is internal header
#include "../ckdint.h"
#endif
// Helper macros [[[

/**
 * @def _ckd_ctypeof(x)
 * @brief For any basic type and checked type return a zero intialized
 * associated checked integer type. This is to be used in _Generic expressions.
 * @param X Any integer type or checked integer type.
 * @return A checked integer type the same type of integer type
 * or the type of the value of checked integer type.
 */
#define _ckd_ctypeof(X) \
		_Generic((X) \
	{% call(A) L.foreach_TYPE(char=1) %}
		,{{A.T}}: ({{A.C}}){0} \
		,{{A.C}}: ({{A.C}}){0} \
	{% endcall %}
		)

{% call(A) L.foreach_TYPE(char=1) %}
_ckd_fconst {{A.C}} _ckd_toct_c$TYPE({{A.C}} _ckd_v, bool _ckd_ignore) { (void)_ckd_ignore; return _ckd_v; }
{% endcall %}

/**
 * @def _ckd_toct(x)
 * @brief For any basic type and checked type convert it to associated
 * checked integer type. Integers have overflow equal to 0.
 * @param X Any integer type or checked integer type.
 * @return A checked integer type the same type of integer type
 * or the value of checked integer type.
 */
#define _ckd_toct(X) \
		_Generic((X) \
	{% call(A) L.foreach_TYPE(char=1) %}
		,{{A.T}}: ckd_mk_$TYPE_t \
		,{{A.C}}: _ckd_toct_c$TYPE \
	{% endcall %}
		)(X, 0)


// Checked Type TO some other type.
{% call(A) L.foreach_TYPE(char=1) %}
_ckd_fconst {{A.T}} _ckd_ctto$TYPE({{A.C}} _ckd_v) { return ckd_value(_ckd_v); }
_ckd_fconst {{A.C}} _ckd_cttoc$TYPE({{A.C}} _ckd_v) { return _ckd_v; }
{% endcall %}

// ]]]
// Generic macros implementation for GNU compatible [[[
{% call() L.foreach_OP() %}

#define _ckd_gnu_$OP_2(a, b, _)  __extension__({ \
		__auto_type _ckd_a = (a); \
		__auto_type _ckd_b = (b); \
		__auto_type _ckd_ca = _ckd_toct(_ckd_a); \
		__auto_type _ckd_cb = _ckd_toct(_ckd_b); \
		__typeof__(_ckd_ctypeof(ckd_value(_ckd_ca) + ckd_value(_ckd_cb))) _ckd_tmp; \
		ckd_overflow(_ckd_tmp) = __builtin_$OP_overflow(ckd_value(_ckd_ca), ckd_value(_ckd_cb), &ckd_value(_ckd_tmp)) \
			|| ckd_overflow(_ckd_ca) || ckd_overflow(_ckd_cb); \
		_ckd_tmp; \
		})

#define _ckd_gnu_$OP_3(r, a, b)  __extension__({ \
		__auto_type _ckd_a = (a); \
		__auto_type _ckd_b = (b); \
		__auto_type _ckd_r = (r); \
		__auto_type _ckd_ca = _ckd_toct(_ckd_a); \
		__auto_type _ckd_cb = _ckd_toct(_ckd_b); \
		__typeof__(_ckd_ctypeof(*_ckd_r)) _ckd_tmp; \
		ckd_overflow(_ckd_tmp) = __builtin_$OP_overflow(ckd_value(_ckd_ca), ckd_value(_ckd_cb), &ckd_value(_ckd_tmp)) \
			|| ckd_overflow(_ckd_ca) || ckd_overflow(_ckd_cb); \
		*_ckd_r = _Generic(*_ckd_r \
	{% call(A) L.foreach_TYPE(char=1) %}
			,{{A.T}}: _ckd_ctto$TYPE \
			,{{A.C}}: _ckd_cttoc$TYPE \
	{% endcall %}
			)(_ckd_tmp); \
		ckd_overflow(_ckd_tmp); \
		})

{% endcall %}

#define _ckd_gnu_mk(value, overflow)  __extension__({ \
		__auto_type _ckd_v = (value); \
		_Generic((_ckd_v) \
	{% call(A) L.foreach_TYPE() %}
		,{{A.T}}: ckd_mk_$TYPE_t \
	{% endcall %}
		)(_ckd_v, overflow); \
		})

// ]]]
#endif
// vim: ft=c

