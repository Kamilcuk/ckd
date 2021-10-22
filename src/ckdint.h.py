#!/usr/bin/env python3
templatestr = r'''
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

{#- ------------------------------------------------------------------------- #}

{#- OPS - represent possible operations #}
{% set OPS = [ "add", "sub", "mul" ] %}

{#- TYPES format: name type detect max min #}
{# BASICTYPES - the main types #}
{% set BASICTYPES = [
        ("schar",  "signed char",        "1", "SCHAR_MAX",  "SCHAR_MIN"),
        ("uchar",  "unsigned char",      "1", "UCHAR_MAX",  "0"),
        ("shrt",   "short",              "1", "SHRT_MAX",   "SHRT_MIN"),
        ("ushrt",  "unsigned short",     "1", "USHRT_MAX",  "0"),
        ("int",    "int",                "1", "INT_MAX",    "INT_MIN"),
        ("uint",   "unsigned int",       "1", "UINT_MAX",   "0"),
        ("long",   "long",               "1", "LONG_MAX",   "LONG_MIN"),
        ("ulong",  "unsigned long",      "1", "ULONG_MAX",  "0"),
        ("llong",  "long long",          "1", "LLONG_MAX",  "LLONG_MIN"),
        ("ullong", "unsigned long long", "1", "ULLONG_MAX", "0"),
    ]
%}

{#- #}
{% set INT128TYPES = [
    ("int128",  "__int128",          "__SIZEOF_INT128__", "INT128_MAX",  "INT128_MIN"),
    ("uint128", "unsigned __int128", "__SIZEOF_INT128__", "UINT128_MAX", "0"),
    ]
%}

{#- TYPES - BASICTYPES + int128, so everything we can put into _Generic #}
{% set TYPES = BASICTYPES.copy() %}
{% if HAVE_UINT128 %}
    {% for d in INT128TYPES %}
        {% set _ = TYPES.append(d) %}
    {% endfor %}
{% endif %}

{#- ALIASEDTYPES represents all types that are aliased to basic types #}
{% set ALIASEDTYPES = [
        ("intmax",  "intmax_t",  "INTMAX_MAX",  "INTMAX_MAX",  "INTMAX_MIN"),
        ("uintmax", "uintmax_t", "UINTMAX_MAX", "UINTMAX_MAX", "0"),
        ("size",    "size_t",    "SIZE_MAX",    "SIZE_MAX",    "0"),
        ("intptr",  "intptr_t",  "INTPTR_MAX",  "INTPTR_MAX",  "INTPTR_MIN"),
        ("uintptr", "uintptr_t", "UINTPTR_MAX", "UINTPTR_MAX", "0"),
    ]
%}
{% for N in [ 8, 16, 32, 64 ] %}
    {% for p in [ "int", "int_least", "int_fast" ] %}
        {% set P = p | upper() %}
        {% set _ = ALIASEDTYPES.append( (p~N, p~N~"_t", P~N~"_MAX", P~N~"_MAX", P~N~"_MIN") ) %}
        {% set _ = ALIASEDTYPES.append( ("u"~p~N, "u"~p~N~"_t", "U"~P~N~"_MAX", "U"~P~N~"_MAX", "0") ) %}
    {% endfor %}
{% endfor %}

{#- ALLTYPES - actually all possible types #}
{% set ALLTYPES = TYPES.copy() %}
{% for d in ALIASEDTYPES %}
    {% set _ = ALLTYPES.append(d) %}
{% endfor %}

{%- set macrocontnl = ", \\
" %}

{#- Replace $OP for operation #}
{% macro foreach_OP() %}
    {% for OP in OPS %}
        {{- caller() | replace("$OP", OP) }}
    {%- endfor %}
{% endmacro %}

{#- Replace $TYPE for operation #}
{% macro foreach_TYPE(inmacro=0, end="") %}
    {% for N, _, _, _, _ in TYPES %}
        {% set NIDX = loop.index %}
        {{- caller() | replace("$TYPE", N) -}}
        {%- if inmacro -%}
            {{- macrocontnl if not loop.last else end -}}
        {%- endif -%}
    {%- endfor %}
{% endmacro %}

{#- ------------------------------------------------------------------------- #}

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

#ifndef _ckd_static
#define _ckd_static     static inline
#endif
#if __GNUC__
#define _ckd_funcconst  _ckd_static __attribute__((__warn_unused_result__)) __attribute__((__const__))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ > 20230000L
#define _ckd_funcconst  _ckd_static [[__nodiscard__]]
#else
#define _ckd_funcconst  _ckd_static
#endif

// ]]]
// Declare checked integer types [[[

{%- for N, T, DETECT, MAX, MIN in TYPES %}

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

{% for N, _, _, MAX, MIN in ALIASEDTYPES %}
    {% for N2, _, _, MAX2, MIN2 in BASICTYPES %}
#if !defined(ckd_{{N}}_t) && defined({{MAX}}) && {{MAX}} == {{MAX2}} && {{MIN}} == {{MIN2}}
/**
 * @define ckd_{{N}}_t
 * @brief Check integer type ckd_{{N}}_t is an alias to ckd_{{N2}}_t.
 */
#define ckd_{{N}}_t  ckd_{{N2}}_t
#endif
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
{% for N, T, _, _, _ in ALLTYPES %}

/**
 * @brief These functions construct a checked integer type ckd_{{N}}_t
 * given an unchecked integer of type {{T}} and an overflow flag.
 * If the overflow flag is true, the value is assumed to have involved overflow,
 * truncation, or  misinterpretation of sign.* Otherwise the value is assumed to
 * be mathematically correct.
 * @param value Unchecked integer.
 * @param oveflow Overflow flag.
 * @return Return a checked type that represents the value indicated by value and the exact 
 * state indicated by overflow.
 */
_ckd_funcconst ckd_{{N}}_t ckd_mk_{{N}}_t({{T}} value, bool overflow) {
    const ckd_{{N}}_t tmp = {value, overflow}; return tmp;
}

{% endfor %}
// ]]]
// Macro helpers [[[

struct _ckd_invalid_;
void _ckd_invalid(struct _ckd_invalid_);

{% call() foreach_TYPE() %}
_ckd_funcconst _ckd_$TYPE _ckd_value_c$TYPE(_ckd_c$TYPE v) { return ckd_value(v); }
_ckd_funcconst _ckd_$TYPE _ckd_value_$TYPE(_ckd_$TYPE v) { return v; }
_ckd_funcconst bool _ckd_overflow_c$TYPE(_ckd_c$TYPE v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_$TYPE(_ckd_$TYPE v) { (void)v; return 0; }
{% endcall %}

/**
 * @define _ckd_value(X)
 * @brief For any basic type returns it's value.
 * For any ckd_*_t type returns ckd_value(X).
 * @param X Any integer type or checked integer type.
 * @return Value of the integer or the value hold inside checked integer type.
 */
#define _ckd_value(X) \
        _Generic((X), \
{% call() foreach_TYPE(inmacro=1) %}
        _ckd_c$TYPE: _ckd_value_c$TYPE, \
        _ckd_$TYPE:  _ckd_value_$TYPE
{%- endcall %})(X)

/**
 * @define _ckd_overflow(X)
 * @param X Any integer type or checked integer type.
 * @return 0 for integer types, the overflow flat for checked integer types.
 */
#define _ckd_overflow(X) \
        _Generic((X), \
{% call() foreach_TYPE(inmacro=1) %}
        _ckd_c$TYPE: _ckd_overflow_c$TYPE, \
        _ckd_$TYPE:  _ckd_overflow_$TYPE
{%- endcall %})(X)

/**
 * @define _ckd_getctype(X)
 * @param X Any integer type or checked integer type.
 * @return ckd_mk_TYPE_t function pointer type associated with _ckd_value(X).
 * @see _ckd_value
 */
#define _ckd_getctype(X) \
    _Generic((X), \
{% call() foreach_TYPE(inmacro=1) %}
    _ckd_$TYPE:  ckd_mk_$TYPE_t, \
    _ckd_c$TYPE: ckd_mk_$TYPE_t
{%- endcall %})

// ]]]
// Generic macros implementation [[[
{% call() foreach_OP() %}

/// @brief ckd_$OP overflow for 2 arguments.
/// @see ckd_$OP
#define _ckd_$OP_2(a, b)  ({ \
        __auto_type _tMp = _ckd_getctype(_ckd_value(a) + _ckd_value(b))(0, 0); \
        ckd_overflow(_tMp) = __builtin_$OP_overflow(_ckd_value(a), _ckd_value(b), &ckd_value(_tMp)) || _ckd_overflow(a) || _ckd_overflow(b); \
        _tMp; \
        })
/// @brief ckd_$OP overflow for 3 arguments.
/// @see ckd_$OP
#define _ckd_$OP_3(r, a, b) \
        (__builtin_$OP_overflow(_ckd_value(a), _ckd_value(b), r) || _ckd_overflow(a) || _ckd_overflow(b))
/// @brief Macro overload on number of arguments for ckd_$OP
/// @see ckd_$OP
#define _ckd_$OP_N(_2,_3,N,...)  _ckd_$OP_##N
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
#define ckd_$OP(w, ...)  _ckd_$OP_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)

{% endcall %}
// ]]]
// EOF [[[

#endif /* CKDINT_H_ */

// ]]]
'''
# Python [[[
# The first line of this file is just one line, so that
# jinja2 reports errors like 2 lines below real error.
# It helps development.
# output_file - the output file to write the output to.
# If no arguments are given, it just writes to stdout.
import sys
import re
import os
from jinja2 import Template, Environment, BaseLoader

HAVE_UINT128 = int(sys.argv.pop(1)) if len(sys.argv) > 1 else 0
outf = open(sys.argv.pop(1), "w") if len(sys.argv) > 1 else sys.stdout

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

# https://groups.google.com/g/pocoo-libs/c/3yZl8vHJ9fI
# https://stackoverflow.com/questions/25449879/embed-custom-filter-definition-into-jinja2-template
def get_re_flags(flagstr):
    reflags = 0
    if flagstr:
        if flagstr.find("i") > -1: reflags |= re.IGNORECASE
        if flagstr.find("l") > -1: reflags |= re.LOCALE
        if flagstr.find("m") > -1: reflags |= re.MULTILINE
        if flagstr.find("s") > -1: reflags |= re.DOTALL
        if flagstr.find("u") > -1: reflags |= re.UNICODE
        if flagstr.find("x") > -1: reflags |= re.VERBOSE
    return reflags
def is_re_match(value, regex, flagstr=None):
    reflags = get_re_flags(flagstr)
    return not not re.search(regex, value, reflags)
def NISSIGNED(s):
    return isinstance(s, str) and len(s) > 0 and s[0] == "u"

env = Environment(
    loader=BaseLoader,
    autoescape=False,
    trim_blocks=True,
    lstrip_blocks=True
)
env.tests['is_re_match']=is_re_match
env.tests['NISSIGNED']=NISSIGNED

print(
    env.from_string(templatestr).render(
        HAVE_UINT128=HAVE_UINT128
    ),
    file=outf,
)

