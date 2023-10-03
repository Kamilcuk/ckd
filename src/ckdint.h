{% import "library.jinja" as L %}
/**
 * @file
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * @copyright 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
 * SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
 * SPDX-License-Identifier: MIT
 */
// Header [[[
#ifndef CKDINT_H_
#define CKDINT_H_

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef _ckd_static
/// @def _ckd_static
#ifdef CKD_COVERAGE
#define _ckd_static  static __attribute__((__noinline__)) __attribute__((__used__))
#else
#define _ckd_static  static inline
#endif
#endif
/// @def _ckd_fchpnt(x)
/// @brief Function attribute for functions that return value and change pointer.
/// @def _ckd_fconst
/// @brief Function attribute for functions that only return value.
#if __GNUC__
#define _ckd_fconst     _ckd_static __attribute__((__warn_unused_result__)) __attribute__((__const__))
#if __GNUC__ >= 10 && !__INTEL_COMPILER
#define _ckd_fchpnt(x)  _ckd_static __attribute__((__warn_unused_result__)) __attribute__((__access__(__write_only__, x)))
#else
#define _ckd_fchpnt(x)  _ckd_static __attribute__((__warn_unused_result__))
#endif
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ > 20230000L
#define _ckd_fconst     _ckd_static [[__nodiscard__]]
#define _ckd_fchpnt(x)  _ckd_static [[__nodiscard__]]
#else
#define _ckd_fconst     _ckd_static
#define _ckd_fchpnt(x)  _ckd_static
#endif

#define CKD_VERSION_DESCRIBE  {{ CKD_VERSION_DESCRIBE }}
#define CKD_VERSION           {{ CKD_VERSION }}

// ]]]
// Declare checked integer types [[[
{% call(V) L.foreach_TYPE(char=1) %}
/// @brief A checked integer type for storing value of type {{V.T}}.
typedef struct {
	/// @brief The stored value.
	{{V.T}} _ckd_Value;
	/// @brief The overflow flag.
	bool _ckd_Overflow;
} {{V.C}};
{% endcall %}
// ]]]
// Standard integer types aliases [[[

{% call(A) L.foreach_TYPE(array=L.ALIASEDTYPES) %}
/// @def ckd_$TYPE_t
/// @brief Checked integer type ckd_$TYPE_t is an alias to one of ckd_*_t basic types.
#ifdef CKD_DOXYGEN
#define ckd_$TYPE_t  /* implementation defined type */
#else
	{# Optionall "el"if from the second case #}
	{% set ns = namespace(EL="") %}
#ifdef {{A.MAX}}
	{% call(B) L.foreach_TYPE(array=L.BASICTYPES) %}
		{% if ((A.SIGNED and B.SIGNED) or (not A.SIGNED and not B.SIGNED)) %}
#{{ns.EL}}if {{A.MAX}} == {{B.MAX}}
typedef {{B.C}} {{A.C}};
			{% set ns.EL = "el" %}
		{% endif %}
	{% endcall %}
#endif
#endif
#endif
{% endcall %}

// ]]]
// Check integer accessors [[[

/**
 * @def ckd_overflow(ckd_type_t x)
 * @brief If ckd_type is a checked integer type, the ckd_overflow macro indicates if x was computed
using an operation that overflowed or suffered truncation or misinterpretation of sign.
 * @param x One of checked integer types.
 * @return The ckd_overflow macro returns true if overflow, truncation, or misinterpretation of sign
 * occurred when x was computed and false otherwise.
 */
#define ckd_overflow(x)  ((x)._ckd_Overflow)

/**
 * @def ckd_value(ckd_type x)
 * @brief If ckd_type is a checked integer type, the ckd_value macro indicates the value of x.
 * If the overflow flag is set to false, the value correctly represents the mathematical value of whatever
 * operation(s) produced x. Otherwise, the value of x is converted as if by assignment to the type of x.
 * @param x One of checked integer types.
 * @return The ckd_value macro returns the value of x.
 */
#define ckd_value(x)     ((x)._ckd_Value)

// ]]]
// ckd_mk_* functions [[[
{% call(V) L.foreach_TYPE(array=L.ALLTYPES, char=1) %}
/**
 * @brief This function constructs a checked integer type ckd_{{V.N}}_t
 * given an unchecked integer of type {{V.T}} and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param _ckd_value Unchecked integer.
 * @param _ckd_overflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact
 * state indicated by overflow.
 */
_ckd_fconst {{V.C}} ckd_mk_{{V.N}}_t({{V.T}} _ckd_value, bool _ckd_overflow) {
	const {{V.C}} _ckd_tmp = {_ckd_value, _ckd_overflow};
	return _ckd_tmp;
}
{% endcall %}

// ]]]
// Macro helpers [[[
// ]]]
// Generic macros implementation [[[

// These two should provide _ckd_$OP_3 and _ckd_$OP_2
#if __GNUC__ >= 5 && !CKD_NOGNU_SOURCE
#include "ckdint/ckdint_gnu.h"
#else
#include "ckdint/ckdint_nognu.h"
#endif

/// @def ckd_mk(value, overflow)
/// @param value unchecked integer
/// @param overflow inexact flag
/// @brief This macro constructs a checked integer type given an unchecked integer and an inexact flag.
/// If the inexact flag is true, the value is assumed to have involved overflow, truncation, or
/// misinterpretation of sign.* Otherwise the value is assumed to be mathematically correct.
/// Constructing a checked integer with an inexact flag set to true can be useful when
/// explicitly indicating an error inside an expression.
/// @return This macro returns a checked type that represents the value indicated by value and the exact state
/// indicated by inexact.
#ifdef CKDINT_GNU
#define ckd_mk(value, overflow)  _ckd_gnu_mk(value, overflow)
#elif defined(CKDINT_NOGNU)
#define ckd_mk(value, overflow)  _ckd_nognu_mk(value, overflow)
#else
#error "ckdint internal error - neight gnu or nognu version was included"
#endif

{% call() L.foreach_OP() %}

/// @def _ckd_$OP_N
/// @brief Macro overload on number of arguments for ckd_$OP
/// @see ckd_$OP
#ifdef CKDINT_GNU
#define _ckd_$OP_N(_1, _2, _3, N, ...)  _ckd_gnu_$OP_##N(_1, _2, _3)
#elif defined(CKDINT_NOGNU)
#define _ckd_$OP_N(_1, _2, _3, N, ...)  _ckd_nognu_$OP_##N(_1, _2, _3)
#else
#error "ckdint internal error - neight gnu or nognu version was included"
#endif

/**
 * @def ckd_$OP(result, a, b)
 * @brief `bool ckd_$OP(type1 *result, type2 a, type3 b);` or `ckd_type_t ckd_$OP(type1 a, type2 b);`
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
 * These macros perform operation $OP of the mathematical values of a and b.
 * In the first form, they store the result of the operation in *result, and in the second form, they return
 * the result as a checked integer.  Each operation is performed as if both operands were represented in a
 * signed integer type with infinite range, and the result was then converted from this integer type to a
 * particular type.  For the first form, this particular type is type1. For the second form, this type is the
 * type that would have been used had the operands undergone usual arithmetic conversion. (Section 6.3.1.8)
 */
#ifdef CKD_DOXYGEN
#define ckd_$OP(result, a, b)
#else
#define ckd_$OP(...)  _ckd_$OP_N(__VA_ARGS__, 3, 2)
#endif

{% endcall %}
// ]]]
// Extensions [[[

/// @def _ckd_inc_in
/// @brief internal callback from ckd_inc
#ifdef CKDINT_GNU
#define _ckd_inc_in(pnt, inc, ...)  __extension__({ \
		__auto_type _ckd_pnt = (pnt); \
		ckd_add(_ckd_pnt, *_ckd_pnt, (inc)); \
		})
#else
#define _ckd_inc_in(pnt, inc, ...)  ckd_add((pnt), *(pnt), (inc))
#endif

/**
 * @def ckd_inc(...)
 * @brief ckd_inc(pnt) or ckd_inc(pnt, inc).
 * Increments value pointed to by pnt by 1 or by inc.
 * @param pnt Pointer to checked integer type or normal integer type.
 * Warning: it is evaulated twice in nognu mode!
 * @param inc The value to increment with. 1 by default.
 * @return overflow
 */
#ifdef CKD_DOXYGEN
#define ckd_inc(pnt, inc)
#else
#define ckd_inc(...)  _ckd_inc_in(__VA_ARGS__, 1)
#endif

/// @def _ckd_dec_in
/// @brief internal callback from ckd_dec
#ifdef CKDINT_GNU
#define _ckd_dec_in(pnt, inc, ...)  __extension__({ \
		__auto_type _ckd_pnt = (pnt); \
		ckd_sub(_ckd_pnt, *_ckd_pnt, (inc)); \
		})
#else
#define _ckd_dec_in(pnt, inc, ...)  ckd_sub((pnt), *(pnt), (inc))
#endif

/**
 * @def ckd_dec(...)
 * @brief ckd_dec(pnt) or ckd_dec(pnt, inc).
 * Decrements value pointed to by pnt by 1 or by inc.
 * @param pnt Pointer to checked integer type or normal integer type.
 * Warning: it is evaulated twice in nognu mode!
 * @param inc The value to increment with. 1 by default.
 * @return overflow
 */
#ifdef CKD_DOXYGEN
#define ckd_dec(pnt, inc)
#else
#define ckd_dec(...)  _ckd_dec_in(__VA_ARGS__, 1)
#endif

// ]]]
// EOF [[[
#endif  // CKDINT_H_
// ]]]
// vim: ft=c

