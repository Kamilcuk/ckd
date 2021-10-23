{% import "library.jinja" as L %}
/**
 * @file
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * @copyright 2021 Kamil Cukrowski
 * SPDX-License-Identifier: MIT + Beerware
 */
// Header [[[
#ifndef CKDINT_H_
#define CKDINT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#ifndef _ckd_static
#define _ckd_static  static inline
#endif
// _ckd_fchpnt - function changes pointer
// _ckd_fconst - function only returns values
#if __GNUC__
#define _ckd_fchpnt  _ckd_static __attribute__((__warn_unused_result__))
#define _ckd_fconst  _ckd_fchpnt __attribute__((__const__))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ > 20230000L
#define _ckd_fconst  _ckd_static [[__nodiscard__]]
#define _ckd_fchpnt  _ckd_static [[__nodiscard__]]
#else
#define _ckd_fconst  _ckd_static
#define _ckd_fchpnt  _ckd_static
#endif

// ]]]
// Declare checked integer types [[[

{%- for N, T, DETECT, MAX, MIN in L.TYPES %}

/// @brief A checked integer type for storing value of type {{T}}.
typedef struct _ckd_{{N}}_t {
    /// @brief The stored value.
    {{T}} _vaLue;
    /// @brief The overflow flag.
    bool _oveRflow;
} ckd_{{N}}_t;

#define _ckd_{{N}}   {{T}}
#define _ckd_c{{N}}  ckd_{{N}}_t

{% endfor -%}

// ]]]
// Standard integer types aliases [[[

{% for N, _, _, MAX, MIN in L.ALIASEDTYPES %}
/**
 * @define ckd_{{N}}_t
 * @brief Check integer type ckd_{{N}}_t is an alias to one of ckd_*_t basic types.
 */
{% endfor %}

{% for N, _, _, MAX, MIN in L.ALIASEDTYPES %}
    {% for N2, _, _, MAX2, MIN2 in L.BASICTYPES %}
		{% if (MIN != "0" and MIN2 != "0") or (MIN == "0" and MIN2 == "0") %}
#if !defined(ckd_{{N}}_t) && defined({{MAX}}) && {{MAX}} == {{MAX2}} && {{MIN}} == {{MIN2}}
#define ckd_{{N}}_t  ckd_{{N2}}_t
#endif
		{% endif %}
    {% endfor %}
{% endfor %}

// ]]]
// Check integer accessors [[[

/**
 * @define bool ckd_overflow(ckd_type_t x);
 * @brief If ckd_type is a checked integer type, the ckd_overflow macro indicates if x was computed
using an operation that overflowed or suffered truncation or misinterpretation of sign.
 * @param x One of checked integer types.
 * @return The ckd_overflow macro returns true if overflow, truncation, or misinterpretation of sign
 * occurred when x was computed and false otherwise.
 */
#define ckd_overflow(x)  ((x)._oveRflow)

/**
 * @define type ckd_value(ckd_type x);
 * @brief If ckd_type is a checked integer type, the ckd_value macro indicates the value of x.
 * If the overflow flag is set to false, the value correctly represents the mathematical value of whatever
 * operation(s) produced x. Otherwise, the value of x is converted as if by assignment to the type of x.
 * @param x One of checked integer types.
 * @return The ckd_value macro returns the value of x.
 */
#define ckd_value(x)     ((x)._vaLue)

// ]]]
// ckd_mk_* functions [[[
{% for N, T, _, _, _ in L.ALLTYPES %}

/**
 * @brief This function constructs a checked integer type ckd_{{N}}_t
 * given an unchecked integer of type {{T}} and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact
 * state indicated by overflow.
 */
_ckd_fconst ckd_{{N}}_t ckd_mk_{{N}}_t({{T}} value, bool overflow) {
    const ckd_{{N}}_t tmp = {value, overflow}; return tmp;
}
{% endfor %}

// ]]]
// Macro helpers [[[

{% call() L.foreach_TYPE() %}
_ckd_fconst _ckd_c$TYPE _ckd_toct_$TYPE(_ckd_$TYPE v) { return ckd_mk_$TYPE_t(v, 0); }
_ckd_fconst _ckd_c$TYPE _ckd_toct_c$TYPE(_ckd_c$TYPE v) { return v; }
{% endcall %}

/**
 * @define ckd_toct(x)
 * @brief For any basic type and checked type convert it to checked type.
 * Integers have overflow equal to 0.
 * @param X Any integer type or checked integer type.
 * @return A checked integer type the same type of integer type
 * or the value of checked integer type.
 */
#define _ckd_toct(X) \
        _Generic((X), \
{% call() L.foreach_TYPE(inmacro=1) %}
        _ckd_c$TYPE: _ckd_toct_c$TYPE, \
        _ckd_$TYPE:  _ckd_toct_$TYPE
{%- endcall %})(X)


/**
 * @define _ckd_value(X)
 * @brief For any basic type returns it's value.
 * For any ckd_*_t type returns ckd_value(X).
 * @param X Any integer type or checked integer type.
 * @return Value of the integer or the value hold inside checked integer type.
 */
#define _ckd_value(X)  ckd_value(_ckd_toct(X))

/**
 * @define _ckd_overflow(X)
 * @param X Any integer type or checked integer type.
 * @return 0 for integer types, the overflow flat for checked integer types.
 */
#define _ckd_overflow(X)  ckd_overflow(_ckd_toct(X))

// ]]]
// Generic macros implementation [[[

// These two should provide _ckd_$OP_3 and _ckd_$OP_2
#if __GNUC__ > 5 && !CKD_USE_NOGNU
#include "ckdint/ckdint_gnu.h"
#else
#include "ckdint/ckdint_nognu.h"
#endif

{% call() L.foreach_OP() %}

/// @define _ckd_$OP_3
/// @brief ckd_$OP overflow for 3 arguments.
/// @see ckd_$OP

/// @define _ckd_$OP_2
/// @brief ckd_$OP overflow for 2 arguments.
/// @see ckd_$OP

/// @brief Macro overload on number of arguments for ckd_$OP
/// @see ckd_$OP
#define _ckd_$OP_N(_2, _3, N, ...)  _ckd_$OP_##N
/**
 * @define ckd_$OP(...)
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
#define ckd_$OP(w, ...)  _ckd_$OP_N(__VA_ARGS__, 3, 2)(w, __VA_ARGS__)

{% endcall %}
// ]]]
// EOF [[[

#endif  // CKDINT_H_

// ]]]
// vim: ft=c

