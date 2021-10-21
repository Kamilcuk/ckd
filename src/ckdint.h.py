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

{# -#}
{% set OPS = [ "add", "sub", "mul", "div" ] %}
{# DATA format: name type detect max min #}
{% set DATA_STANDARD = [
        ("schar"  ,"signed char"       ,"1"                ,"SCHAR_MAX"  ,"SCHAR_MIN") ,
        ("uchar"  ,"unsigned char"     ,"1"                ,"UCHAR_MAX"  ,"0")         ,
        ("shrt"   ,"short"             ,"1"                ,"SHRT_MAX"   ,"SHRT_MIN")  ,
        ("ushrt"  ,"unsigned short"    ,"1"                ,"USHRT_MAX"  ,"0")         ,
        ("int"    ,"int"               ,"1"                ,"INT_MAX"    ,"INT_MIN")   ,
        ("uint"   ,"unsigned int"      ,"1"                ,"UINT_MAX"   ,"0")         ,
        ("long"   ,"long"              ,"1"                ,"LONG_MAX"   ,"LONG_MIN")  ,
        ("ulong"  ,"unsigned long"     ,"1"                ,"ULONG_MAX"  ,"0")         ,
        ("llong"  ,"long long"         ,"1"                ,"LLONG_MAX"  ,"LLONG_MIN") ,
        ("ullong" ,"unsigned long long","1"                ,"ULLONG_MAX" ,"0")         ,
    ]
%}
{% set DATA128 = [
        ("int128" ,"__int128"          ,"__SIZEOF_INT128__","INT128_MAX" ,"INT128_MIN"),
        ("uint128","unsigned __int128" ,"__SIZEOF_INT128__","UINT128_MAX","0")         ,
    ]
%}
{% set DATA = [] %}
{% if HAVE_UINT128 %}
    {% for d in DATA_STANDARD %}
        {% set _ = DATA.append(d) %}
    {% endfor %}
    {% for d in DATA128 %}
        {% set _ = DATA.append(d) %}
    {% endfor %}
{% endif %}
{% set NAMES = [] %}{% for d in DATA %}{% set _ = NAMES.append(d[0]) %}{% endfor %}
{% set NAMESTYPES = [] %}{% for d in DATA %}{% set _ = NAMESTYPES.append((d[0], d[1])) %}{% endfor %}
{% set PREFIXES = [("", ""), ("c", ""), ("", "c"), ("c", "c")] %}

{% set macrocontnl = ", \\
" %}
{% macro foreach_OP() %}
    {% for OP in OPS %}
{{ caller() | replace("$OP", OP) }}
    {%- endfor %}
{% endmacro %}
{% macro foreach_TYPE(inmacro=0, end="") %}
    {% for N, T in NAMESTYPES %}
        {% set NIDX = loop.index %}
{{ caller() | replace("$TYPE", N) }}{% if inmacro %}{{ macrocontnl if not loop.last else end }}{% endif %}
    {%- endfor %}
{% endmacro %}

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

#define _ckd_static     static inline
#if __GNUC__
#define _ckd_funcconst  _ckd_static __attribute__((__warn_unused_result__)) __attribute__((__const__))
#if __GNUC__ >= 10
#define _ckd_access_w(...)  __attribute__((__access__(__write_only__, __VA_ARGS__)))
#endif
#elif __STDC_VERSION__ >  20230000L
#define _ckd_funcconst  _ckd_static [[__nodiscard__]]
#else
#define _ckd_funcconst _ckd_static
#endif

#ifndef _ckd_access_w
#define _ckd_access_w(...)  /**/
#endif

#define ckd_overflow(x)  ((x)._oveRflow)
#define ckd_value(x)     ((x)._vaLue)

// ]]]
// Type specific [[[

{% for N, T, DETECT, MAX, MIN in DATA %}

/// @brief The type to store value with overflow information.
typedef struct {
    /// The stored value.
    {{T}} _vaLue;
    /// Did overflow occured or not?
    bool _oveRflow;
} ckd_{{N}}_t;

{# Generic types with N suffix used for templating #}
#define _ckd_{{N}}  {{T}}
#define _ckd_c{{N}} ckd_{{N}}_t

/// @param value to hold
/// @param oveflow Overflowed or not
/// @brief Constructs a ckd_{{N}}_t type that holds {{T}} variable type.
_ckd_funcconst ckd_{{N}}_t ckd_mk_{{N}}_t({{T}} value, bool overflow) {
    return (ckd_{{N}}_t){value, overflow};
}

#define _ckd_max_{{N}}  ({{MAX}})
#define _ckd_min_{{N}}  ({{MIN}})

{% endfor %}

// ]]]
// Type specific operation [[[

{% for N, T, DETECT, MAX, MIN in DATA %}
{% set ISSIGNED = MIN != "0" %}
{% for OP in OPS %}

{#
    Operations on integers + checking for overflow.
    I have __not__ implemented overflow semantics, in the below code
    I only _check_ if overflow _has happened_. So compiler can still optimize
    the calculation itself as overflowing signed operations result in undefined behavior.

    Based on:
        https://stackoverflow.com/q/3944505/9072753
        https://codereview.stackexchange.com/questions/93687/test-if-arithmetic-OPeration-will-cause-undefined-behavior/93699#93699
        https://stackoverflow.com/a/6472982/9072753
#}
/**
 * Calculates a {{OP}} b with infinite type width and stores the result in res.
 * @param res Place to store the result to.
 * @param a
 * @param b
 * @param others Should be locagically OR-ed to the result.
 * @return If the result is not within range of type {{T}} or others.
 */
_ckd_static _ckd_access_w(1)
bool _ckd_{{OP}}_3_{{N}}({{T}} *res, {{T}} a, {{T}} b, bool others) {
    const {{T}} max = _ckd_max_{{N}}; (void)max;
    const {{T}} min = _ckd_min_{{N}}; (void)min;
    // Stores the result of calculation.
    {{T}} r;
    // Stores if the calculation overflowed.
    bool o = 0;
    {# Choose the proper operation -#}
{% if OP != "div" %}{# There is no __buildin_div_* #}
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    o = __builtin_{{OP}}_overflow(a, b, &r);
#else // __GNUC__
{% if OP == "add" and ISSIGNED %}
    r = a + b;
    o = (a < 0) ? (b < min - a) : (b > max - a);
{% elif OP == "add" and not ISSIGNED %}
    r = a + b;
    o = r < (a | b);
{% elif OP == "sub" and ISSIGNED %}
    r = a - b;
    o = (b < 0) ? (a > max + b) : (a < min + b);
{% elif OP == "sub" and not ISSIGNED %}
    {#- This is I think plainly wrong. #}
    r = a - b;
    o = a < min + b;
{% elif OP == "mul" %}
    {#- both signed and unsigned #}
    r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                o = 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                o = 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                o = 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                o = 1;
            }
        }
    }
{% endif %}
#endif // __GNUC__
{% else %}{# OP != "div" #}
    {# both signed and unsigned #}
    {% if "int128" not in N %}
    #if _ckd_min_{{N}} != 0 && _ckd_min_{{N}} < -_ckd_max_{{N}}
    {% else %}
    #if {{ N == "int128" }}
    {% endif %}
        if (a == min && b == -1) {
            r = 0;
            o = 1;
        } else
    #endif
    if (b == 0) {
        r = 0;
        o = 1;
    } else {
        r = a / b;
        o = 0;
    }
{% endif %}{# OP == "div" -#}
    *res = r;
    return others || o;
}

/// Wrapper around _ckd_{{OP}}_3_{{N}}.
_ckd_funcconst _ckd_c{{N}} _ckd_{{OP}}_2_{{N}}({{T}} a, {{T}} b, bool others) {
    _ckd_c{{N}} tmp;
    ckd_overflow(tmp) = _ckd_{{OP}}_3_{{N}}(&ckd_value(tmp), a, b, others);
    return tmp;
}

{% endfor %}{# foreach OPS #}
{% endfor %}{# foreach DATA #}

// ]]]
// Standard integer types aliases [[[

{% for V in [8, 16, 32, 64] %}
    {% for N, T, DETECT, MAX, MIN in (DATA_STANDARD | reverse()) %}
        {% if MIN == "0" %}
            {% set P = "U" %}
        {% else %}
            {% set P = "" %}
        {% endif %}
#if !defined(ckd_int{{V}}_t) && {{P}}INT{{V}}_MAX == {{MAX}} && {{P}}INT{{V}}_MIN == {{MIN}}
#define ckd_{{P|lower()}}int{{V}}_t ckd_{{N}}_t
#endif
    {% endfor %}
{% endfor %}

// ]]]
// Generic _ckd_overflow and _ckd_value with normal types [[[

{% call() foreach_TYPE() %}
_ckd_funcconst _ckd_$TYPE _ckd_value_c$TYPE(_ckd_c$TYPE v) { return ckd_value(v); }
_ckd_funcconst _ckd_$TYPE _ckd_value_$TYPE(_ckd_$TYPE v) { return v; }
_ckd_funcconst bool _ckd_overflow_c$TYPE(_ckd_c$TYPE v) { return ckd_overflow(v); }
_ckd_funcconst bool _ckd_overflow_$TYPE(_ckd_$TYPE v) { return 0; }
{% endcall %}

/// @define _ckd_value(X)
// For any basic type returns it's value.
// For any ckd_*_t type returns ckd_value(X).
#define _ckd_value(X) \
        _Generic((X), \
{% call() foreach_TYPE(inmacro=1) %}
        _ckd_c$TYPE: _ckd_value_c$TYPE, \
        _ckd_$TYPE:  _ckd_value_$TYPE
{%- endcall %} \
        )(X)

/// @define _ckd_overflow(X)
/// Same as _ckd_value, but returns ckd_overflow(0) or 0.
#define _ckd_overflow(X) \
        _Generic((X), \
{% call() foreach_TYPE(inmacro=1) %}
        _ckd_c$TYPE: _ckd_overflow_c$TYPE, \
        _ckd_$TYPE:  _ckd_overflow_$TYPE
{%- endcall %} \
        )(X)

// ]]]
// Generic macros implementation [[[

struct _ckd_invalid_;
void _ckd_invalid(struct _ckd_invalid_);

#define ckd_mk(value, overflow)  _Generic((value), \
{% call() foreach_TYPE(inmacro=1) %}
    _ckd_$TYPE: ckd_mk_$TYPE_t
{%- endcall %} \
    )(value, overflow)

/* ------------------------------------------------------------------------- */

{% call() foreach_OP() %}

#define _ckd_$OP_2(a, b)  \
    _Generic(_ckd_value(a) + _ckd_value(b), \
{% call() foreach_TYPE(inmacro=1) %}
    _ckd_$TYPE: _ckd_$OP_2_$TYPE
{%- endcall %}, \
    default: _ckd_invalid)(_ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_$OP_3(r, a, b) \
    _Generic(_ckd_value(a) + _ckd_value(b) + *(r), \
{% call() foreach_TYPE(inmacro=1) %}
    _ckd_$TYPE: _ckd_$OP_3_$TYPE
{%- endcall %}, \
    default: _ckd_invalid)((r), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
#define _ckd_$OP_N(_2,_3,N,...) _ckd_$OP_##N
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
# This script takes 3 arguments:
#   HAVE_UINT128 - do we have uint128 or not
#   output_file - the output file to write the output to.
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

