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
{% set DATA = [
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
{% if HAVE_UINT128 %}
    {% for d in DATA128 %}
        {% set _ = DATA.append(d) %}
    {% endfor %}
{% endif %}
{% set NAMES = [] %}{% for d in DATA %}{% set _ = NAMES.append(d[0]) %}{% endfor %}
{% set NAMESTYPES = [] %}{% for d in DATA %}{% set _ = NAMESTYPES.append((d[0], d[1])) %}{% endfor %}
{% set PREFIXES = [("", ""), ("c", ""), ("", "c"), ("c", "c")] %}
{% macro PVALUE(var, prefix) %}
    {% if prefix == "" -%}
        {{var}}
    {%- else -%}
        ckd_value({{var}})
    {%- endif %}
{%- endmacro %}
{% macro PORINEXACT(var, prefix) %}
    {% if prefix == "c" -%}
        |ckd_inexact({{var}})
    {%- endif %}
{%- endmacro %}

{% if ONLYSAMETYPES %}
#define _ckd_ONLYSAMETYPES  1
{% endif %}

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
#elif __STDC_VERSION__ >  20230000L
#define _ckd_funcconst  _ckd_static [[__nodiscard__]]
#else
#define _ckd_funcconst _ckd_static
#endif

#define ckd_inexact(x)  ((x)._ineXact)
#define ckd_value(x)    ((x)._vaLue)

// ]]]
// Type specific [[[

{% for N, T, DETECT, MAX, MIN in DATA %}

/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    {{T}} _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_{{N}}_t;

{# Generic types with N suffix used for templating #}
#define _ckd_type_{{N}}  {{T}}
#define _ckd_type_c{{N}} ckd_{{N}}_t

/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_{{N}}_t type that holds {{T}} variable type.
_ckd_funcconst ckd_{{N}}_t ckd_mk_{{N}}_t({{T}} value, bool inexact) {
    return (ckd_{{N}}_t){value, inexact};
}

#define _ckd_max_{{N}}  ({{MAX}})
#define _ckd_min_{{N}}  ({{MIN}})

{% endfor %}

// ]]]
// Type specific operation [[[

{% for N, T in NAMESTYPES %}
{% set ISSIGNED = MIN != "0" %}
{% for OP in OPS %}

_ckd_static bool _ckd_{{OP}}_3_{{N}}_{{N}}_{{N}}_in({{T}} *r, {{T}} a, {{T}} b) {
    const {{T}} max = _ckd_max_{{N}}; (void)max;
    const {{T}} min = _ckd_min_{{N}}; (void)min;
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
{% macro op_add_signed() %}
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
{% endmacro %}
{% macro op_add_unsigned() %}
    return *r = a + b, *r < (a | b);
{% endmacro %}
{% macro op_sub_signed() %}
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
{% endmacro %}
{% macro op_sub_unsigned() %}
{# This is I think plainly wrong. #}
    *r = a - b;
    return a < min + b;
{% endmacro %}
{% macro op_mul() %}
    {# both signed and unsigned #}
    *r = a * b;
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return 1;
            }
        } else {
            if (b < min / a) { // a positive, b not positive
                return 1;
            }
        }
    } else {
        if (b > 0) {
            if (a < min / b) { // a not positive, b positive
                return 1;
            }
        } else {
            if (a != 0 && b < max / a) { // a not positive, b not positive
                return 1;
            }
        }
    }
    return 0;
{% endmacro %}
{% macro op_div() %}
    {# both signed and unsigned #}
    {% if "int128" not in N %}
    #if _ckd_min_{{N}} != 0 && _ckd_min_{{N}} < -_ckd_max_{{N}}
    {% else %}
    #if {{ N == "int128" }}
    {% endif %}
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = 0, 1;
    return *r = a / b, 0;
{% endmacro %}
{# #}
{# Choose the proper operation #}
{% if OP != "div" %}{# There is no __buildin_div_* #}
#if __GNUC__ > 5 && !defined(CKD_DO_NOT_USE_BUILTINS)
    return __builtin_{{OP}}_overflow(a, b, r);
#else // __GNUC__
{% if OP == "add" and ISSIGNED %}
    {{- op_add_signed() -}} 
{% elif OP == "add" and not ISSIGNED %}
    {{- op_add_unsigned() -}} 
{% elif OP == "sub" and ISSIGNED %}
    {{- op_sub_signed() -}} 
{% elif OP == "sub" and not ISSIGNED %}
    {{- op_sub_unsigned() -}} 
{% elif OP == "mul" %}
    {{- op_mul() -}} 
{% endif %}
#endif // __GNUC__
{% else %}{# OP != "div" #}
    {{- op_div() -}} 
{% endif %}{# OP == "div" -#}
}

{% endfor %}{# foreach OPS #}
{% endfor %}{# foreach DATA #}

// ]]]
// Each type with every type operations [[[

{% macro check_range_in(var, NR) -%}
    | ( {{var}} < _ckd_min_{{NR}} ) | ( {{var}} > _ckd_max_{{NR}} )
{%- endmacro %}
{% macro check_range(P1, P2, N1, N2, NR) %}
    {% if NR != N1 %}
        {% set var = PVALUE("a", P1) %}
        {{- check_range_in(var, NR) -}}
    {% endif %}
    {% if NR != N2 %}
        {% set var = PVALUE("b", P2) %}
        {{- check_range_in(var, NR) -}}
    {% endif %}
{%- endmacro %}
{% macro name_to_name(OP, N1, N2, NR) %}
// Operation {{OP}} on {{N1}} and {{N2}} -> {{NR}}
    {% for P1, P2 in PREFIXES %}
_ckd_static bool _ckd_{{OP}}_3_{{NR}}_{{P1}}{{N1}}_{{P2}}{{N2}}(_ckd_type_{{NR}} *r, _ckd_type_{{P1}}{{N1}} a, _ckd_type_{{P2}}{{N2}} b) {
    {% if N1 == N2 and N2 == NR and P1 == "" and P2 == "" %}
    {# This is the basic, basic case #}
    return _ckd_{{OP}}_3_{{NR}}_{{NR}}_{{NR}}_in(r, a, b);
    {% else %}
    return _ckd_{{OP}}_3_{{NR}}_{{NR}}_{{NR}}(r, {{PVALUE("a", P1)}}, {{PVALUE("b", P2)}})
        {{- PORINEXACT("a",P1) -}}{{- PORINEXACT("b",P2) -}}{{- check_range(P1, P2, N1, N2, NR) -}} ;
    {% endif %}
}
_ckd_funcconst ckd_{{NR}}_t _ckd_{{OP}}_2_{{NR}}_{{P1}}{{N1}}_{{P2}}{{N2}}(_ckd_type_{{P1}}{{N1}} a, _ckd_type_{{P2}}{{N2}} b) {
    ckd_{{NR}}_t r; r._ineXact = _ckd_{{OP}}_3_{{NR}}_{{P1}}{{N1}}_{{P2}}{{N2}}(&r._vaLue, a, b); return r;
}
    {% endfor %}
{% endmacro %}

{% set RET = namespace() %}
{% macro only_smaller(N1, N1IDX, N2, N2IDX, NR, NRIDX) %}
    {% if (N1 is NISSIGNED) == (NR is NISSIGNED) and N1IDX < NRIDX %}
        {% set N1 = NR %}
    {% endif %}
    {% if (N2 is NISSIGNED) == (NR is NISSIGNED) and N2IDX < NRIDX %}
        {% set N2 = NR %}
    {% endif %}
    {% set RET.N1 = N1 %}
    {% set RET.N2 = N2 %}
{% endmacro %}

{% for OP in OPS %}
    {% for N1 in NAMES %}
        {{- name_to_name(OP, N1, N1, N1) -}}
    {% endfor %}
{% endfor %}
{% if not ONLYSAMETYPES %}
{% for OP in OPS %}
    {% for N1 in NAMES %}
        {% set N1IDX = loop.index %}
        {% for N2 in NAMES %}
            {% set N2IDX = loop.index %}
            {% for NR in NAMES %}
                {% set NRIDX = loop.index %}
                {{- only_smaller(N1, N1IDX, N2, N2IDX, NR, NRIDX) -}}
                {% if RET.N1 == N1 and RET.N2 == N2 and (N1 != N2 or N1 != NR) %}
                    {{- name_to_name(OP, N1, N2, NR) -}}
                {% endif %}
            {% endfor %}
        {% endfor %}
    {% endfor %}
{% endfor %}
{% endif %}

// ]]]
// Generic macros implementation [[[

struct _ckd_invalid_;
void _ckd_invalid(struct _ckd_invalid_);

{% set macrocontnl = ", \\
" %}
{# #}
{% macro generics(end="") %}
    {% for N, T in NAMESTYPES %}
        {% set NIDX = loop.index %}
{{ caller(N, T, NIDX) }}{{ macrocontnl if not loop.last else end }}
    {%- endfor %}
{% endmacro %}

#define ckd_mk(value, inexact)  _Generic((value), \
{% call(N, T, NIDX) generics() %}
    {{T}}: ckd_mk_{{N}}_t
{%- endcall %} \
    )(value, inexact)

{% macro ingen_in(OP, CNT, P1, N1, N1IDX, NR, NRIDX) %}
    {% for N2 in NAMES %}
        {% set N2IDX = loop.index %}
        {# #}
        {# handle gen2 - determine NR type to be the bigger type #}
        {% if CNT == 2 %}
            {% set NR = N1 %}
            {% set NRIDX = N1IDX %}
            {% if N1IDX < N2IDX %}
                {% set NR = N2 %}
                {% set NRIDX = N2IDX %}
            {% endif %}
        {% endif %}
        {# #}
        {# handle OP_3 smaller types exclusion #}
        {{- only_smaller(N1, N1IDX, N2, N2IDX, NR, NRIDX) -}}
        {# #}
_ckd_type_{{N2}}:  _ckd_{{OP}}_{{CNT}}_{{NR}}_{{P1}}{{RET.N1}}_{{RET.N2}}, \
_ckd_type_c{{N2}}: _ckd_{{OP}}_{{CNT}}_{{NR}}_{{P1}}{{RET.N1}}_c{{RET.N2}}{{ macrocontnl if not loop.last else end }}
    {%- endfor %}
{% endmacro %}

{% macro ingen(OP, CNT, NR="", NRIDX=-1) %}
    {% for N1, T1 in NAMESTYPES %}
        {% set N1IDX = loop.index %}
        {% if not ONLYSAMETYPES %}
_ckd_type_{{N1}}: \
    _Generic((b), \
    {{ ingen_in(OP, CNT, "", N1, N1IDX, NR, NRIDX) | indent(4) }}, \
    default: _ckd_invalid), \
_ckd_type_c{{N1}}: \
    _Generic((b), \
    {{ ingen_in(OP, CNT, "c", N1, N1IDX, NR, NRIDX) | indent(4) }}, \
    default: _ckd_invalid){{ macrocontnl }}
        {%- else %}
            {# If we got called from OP_2 or the types are the same #}
            {% if NRIDX == -1 or NR == N1 %}
                {% set NR = N1 %}
                {% set N2 = N1 %}
_ckd_type_{{N1}}: \
    _Generic((b), \
    _ckd_type_c{{N2}}: _ckd_{{OP}}_{{CNT}}_{{NR}}_{{N1}}_c{{N2}}, \
    default: _ckd_{{OP}}_{{CNT}}_{{NR}}_{{N1}}_{{N2}}), \
_ckd_type_c{{N1}}: \
    _Generic((b), \
    _ckd_type_c{{N2}}: _ckd_{{OP}}_{{CNT}}_{{NR}}_c{{N1}}_c{{N2}}, \
    default:  _ckd_{{OP}}_{{CNT}}_{{NR}}_c{{N1}}_{{N2}}){{ macrocontnl }}
            {%- endif %}
        {% endif %}
    {%- endfor %}
{%- endmacro %}
    
{% for OP in OPS %}
#define _ckd_{{OP}}_2(a, b)  _Generic((a), \
    {{ ingen(OP, 2) | indent(4)
}}    default: _ckd_invalid)(a, b)
#define _ckd_{{OP}}_3(r, a, b)  _Generic((r), \
{% call(NR, TR, NRIDX) generics() %}
    {{TR}} *: \
        _Generic((a), \
        {{ ingen(OP, 3, NR, NRIDX) | indent(8)
}}        default: _ckd_{{OP}}_3_{{NR}}_{{NR}}_{{NR}})
{%- endcall %}, \
    default: _ckd_invalid)(r, a, b)
#define _ckd_{{OP}}_N(_2,_3,N,...) _ckd_{{OP}}_##N
#define ckd_{{OP}}(w, ...)  _ckd_{{OP}}_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)

{% endfor %}

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
#   ONLYSAMETYPES - Generate shorter version and handle only same types in macros.
#   output_file - the output file to write the output to.
# If no arguments are given, it just writes to stdout.
import sys
import re
from jinja2 import Template, Environment, BaseLoader

HAVE_UINT128 = int(sys.argv.pop(1)) if len(sys.argv) > 1 else 0
# Set this to 0 to compile only same types operations, like ckd_add(int*, int, int)
ONLYSAMETYPES = int(sys.argv.pop(1)) if len(sys.argv) > 1 else 0
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
        ONLYSAMETYPES=ONLYSAMETYPES,
        HAVE_UINT128=HAVE_UINT128
    ),
    file=outf,
)

