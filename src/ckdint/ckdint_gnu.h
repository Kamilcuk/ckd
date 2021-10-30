{% import "library.jinja" as L %}
/**
 * @file ckdint_gnu.h
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * @copyright 2021 Kamil Cukrowski
 * SPDX-License-Identifier: MIT + Beerware
 */
#define _CKDINT_GNU
#ifndef _CKDINT_H_
#error  This is internal header
#include "../ckdint.h"
#endif
// Helper macros [[[

/**
 * @define ckd_ctypeof(x)
 * @brief For any basic type and checked type return a zero intialized
 * associated checked integer type. This is to be used in _Generic expressions.
 * @param X Any integer type or checked integer type.
 * @return A checked integer type the same type of integer type
 * or the type of the value of checked integer type.
 */
#define _CKD_ctypeof(X) \
        _Generic((X) \
	{% call(A) L.foreach_TYPE(char=1) %}
        ,{{A.T}}: ({{A.C}}){0} \
		,{{A.C}}: ({{A.C}}){0} \
	{% endcall %}
		)

{% call(A) L.foreach_TYPE(char=1) %}
_CKD_fconst {{A.C}} _CKD_toct_c$TYPE({{A.C}} _Value, bool _Ignored) { (void)_Ignored; return _Value; }
{% endcall %}

/**
 * @define ckd_toct(x)
 * @brief For any basic type and checked type convert it to associated
 * checked integer type. Integers have overflow equal to 0.
 * @param X Any integer type or checked integer type.
 * @return A checked integer type the same type of integer type
 * or the value of checked integer type.
 */
#define _CKD_toct(X) \
        _Generic((X) \
	{% call(A) L.foreach_TYPE(char=1) %}
		,{{A.T}}: ckd_mk_$TYPE_t \
		,{{A.C}}: _CKD_toct_c$TYPE \
	{% endcall %}
		)(X, 0)


// Checked Type TO some other type.
{% call(A) L.foreach_TYPE(char=1) %}
_CKD_fconst {{A.T}} _CKD_ctto$TYPE({{A.C}} _Val) { return ckd_value(_Val); }
_CKD_fconst {{A.C}} _CKD_cttoc$TYPE({{A.C}} _Val) { return _Val; }
{% endcall %}

// ]]]
// Generic macros implementation for GNU compatible [[[
{% call() L.foreach_OP() %}

#define _CKD_$OP_2(a, b)  __extension__({ \
		__auto_type _CKD_a = (a); \
		__auto_type _CKD_b = (b); \
		__auto_type _CKD_ca = _CKD_toct(_CKD_a); \
		__auto_type _CKD_cb = _CKD_toct(_CKD_b); \
		__typeof__(_CKD_ctypeof(ckd_value(_CKD_ca) + ckd_value(_CKD_cb))) _CKD_tmp; \
		ckd_overflow(_CKD_tmp) = __builtin_$OP_overflow(ckd_value(_CKD_ca), ckd_value(_CKD_cb), &ckd_value(_CKD_tmp)) \
			|| ckd_overflow(_CKD_ca) || ckd_overflow(_CKD_cb); \
		_CKD_tmp; \
		})

#define _CKD_$OP_3(r, a, b)  __extension__({ \
		__auto_type _CKD_a = (a); \
		__auto_type _CKD_b = (b); \
		__auto_type _CKD_r = (r); \
		__auto_type _CKD_ca = _CKD_toct(_CKD_a); \
		__auto_type _CKD_cb = _CKD_toct(_CKD_b); \
		__typeof__(_CKD_ctypeof(*_CKD_r)) _CKD_tmp; \
		ckd_overflow(_CKD_tmp) = __builtin_$OP_overflow(ckd_value(_CKD_ca), ckd_value(_CKD_cb), &ckd_value(_CKD_tmp)) \
			|| ckd_overflow(_CKD_ca) || ckd_overflow(_CKD_cb); \
		*_CKD_r = _Generic(*_CKD_r \
	{% call(A) L.foreach_TYPE(char=1) %}
			,{{A.T}}: _CKD_ctto$TYPE \
			,{{A.C}}: _CKD_cttoc$TYPE \
	{% endcall %}
			)(_CKD_tmp); \
		ckd_overflow(_CKD_tmp); \
		})

{% endcall %}
// ]]]
// vim: ft=c

