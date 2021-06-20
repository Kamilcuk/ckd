#!/usr/bin/env python3
import sys; from jinja2 import Template; outf = open(sys.argv[1], 'w') if len(sys.argv) > 1 else sys.stdout; print(Template(r'''
{# The above is only one line, so that jinja2 reports just 2 lines below the error location. #}
// Header [[[
/*
 * @file
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * SPDX-License-Identifier: MIT + Beerware
 */
#ifndef CKDINT_H_
#define CKDINT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

{% set ops = [ "add", "sub", "mul", "div" ] %}
{% set data = [
        ("int","int","INT_MAX","INT_MIN"),
        ("uint","unsigned int","UINT_MAX","0"),
        ("long","long","LONG_MAX","LONG_MIN"),
        ("ulong","unsigned long","ULONG_MAX","0"),
        ("llong","long long","LLONG_MAX","LLONG_MIN"),
        ("ullong","unsigned long long","ULLONG_MAX","0"),
    ]
%}
{% set PREFIXES = [("", ""), ("c", ""), ("", "c"), ("c", "c")] %}

#define _ckd_static  static inline

#define ckd_inexact(x)  ((x)._ineXact)
#define ckd_value(x)    ((x)._vaLue)

// ]]]
// Type specific [[[

{% for N, T, MAX, MIN in data %}

/// @brief The type to store value with inexact information.
typedef struct {
    /// The stored value.
    {{T}} _vaLue;
    /// Did overflow occured or not.
    bool _ineXact;
} ckd_{{N}}_t;

typedef {{T}} _ckd_type_{{N}};
typedef ckd_{{N}}_t _ckd_type_c{{N}};

/// @define ckd_mk_{{N}}_t
/// @param value to hold
/// @param inexact be inexact or not
/// @brief Constructs a ckd_{{N}}_t type that holds {{T}} variable type.
#define ckd_mk_{{N}}_t(value, inexact)  (ckd_{{N}}_t){value, inexact}

#define _ckd_max_{{N}}  ({{MAX}})
#define _ckd_min_{{N}}  ({{MIN}})
#define _ckd_issigned_{{N}}  (_ckd_min_{{N}} == 0)

_ckd_static {{T}} _ckd_value_{{N}}({{T}} a) { return a; }
_ckd_static {{T}} _ckd_value_c{{N}}(ckd_{{N}}_t a) { return ckd_value(a); }
_ckd_static {{T}} _ckd_inexact_{{N}}({{T}} a) { return 0; }
_ckd_static {{T}} _ckd_inexact_c{{N}}(ckd_{{N}}_t a) { return ckd_inexact(a); }
#define _ckd_v_{{N}}(a)  _Generic((a), \
        {{T}}: _ckd_value_{{N}}, \
        ckd_{{N}}_t: _ckd_value_c{{N}})(a)
#define _ckd_ine_{{N}}(a)  _Generic((a), \
        {{T}}: _ckd_inexact_{{N}}, \
        ckd_{{N}}_t: _ckd_inexact_c{{N}})(a)

{% endfor %}

// ]]]
// Type specific operation [[[

{% for N, T, _, _ in data %}
{% set ISSIGNED = MIN != "0" %}
{% for OP in ops %}

_ckd_static bool _ckd_{{OP}}_3_{{N}}_{{N}}_in({{T}} *r, {{T}} a, {{T}} b) {
    const {{T}} max = _ckd_max_{{N}}; (void)max;
    const {{T}} min = _ckd_min_{{N}}; (void)min;
{#
    Operations on integers + checking for overflow.
    I have __not__ implemented overflow semantics, in the below code
    I only _check_ if overflow _has happened_. So compiler can still optimize
    the calculation itself as overflowing signed operations result in undefined behavior.
#}
{% macro op_add_signed() %}
    // https://stackoverflow.com/q/3944505/9072753
    *r = a + b;
    return (a < 0) ? (b < min - a) : (b > max - a);
{% endmacro %}
{% macro op_add_unsigned() %}
    // https://stackoverflow.com/a/6472982/9072753
    return *r = a + b, *r < (a | b);
{% endmacro %}
{% macro op_sub_signed() %}
    // https://codereview.stackexchange.com/questions/93687/test-if-arithmetic-OPeration-will-cause-undefined-behavior/93699#93699
    *r = a - b;
    return (b < 0) ? (a > max + b) : (a < min + b);
{% endmacro %}
{% macro op_sub_unsigned() %}
    // This is I think plainly wrong.
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
    #if _ckd_min_{{N}} != 0 && _ckd_min_{{N}} < -_ckd_max_{{N}}
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
    {{ op_add_signed() }} 
{% elif OP == "add" and not ISSIGNED %}
    {{ op_add_unsigned() }} 
{% elif OP == "sub" and ISSIGNED %}
    {{ op_sub_signed() }} 
{% elif OP == "sub" and not ISSIGNED %}
    {{ op_sub_unsigned() }} 
{% elif OP == "mul" %}
    {{ op_mul() }} 
{% endif %}
#endif // __GNUC__
{% else %}{# OP != "div" #}
    {{ op_div() }} 
{% endif %}{# OP == "div" -#}
}

_ckd_static bool _ckd_{{OP}}_3_{{N}}_{{N}}({{T}} *r, {{T}} a, {{T}} b) {
    return _ckd_{{OP}}_3_{{N}}_{{N}}_in(r, a, b);
}
_ckd_static bool _ckd_{{OP}}_3_{{N}}_c{{N}}({{T}} *r, {{T}} a, ckd_{{N}}_t b) {
    return _ckd_{{OP}}_3_{{N}}_{{N}}(r, a, ckd_value(b)) | ckd_inexact(b);
}
_ckd_static bool _ckd_{{OP}}_3_c{{N}}_{{N}}({{T}} *r, ckd_{{N}}_t a, {{T}} b) {
    return _ckd_{{OP}}_3_{{N}}_{{N}}(r, ckd_value(a), b) | ckd_inexact(a);
}
_ckd_static bool _ckd_{{OP}}_3_c{{N}}_c{{N}}({{T}} *r, ckd_{{N}}_t a, ckd_{{N}}_t b) {
    return _ckd_{{OP}}_3_{{N}}_{{N}}(r, ckd_value(a), ckd_value(b)) | ckd_inexact(a) | ckd_inexact(b);
}

{% for P1, P2 in PREFIXES %}
    {% set M1 = P1 ~ N %}
    {% set M2 = P2 ~ N %}
_ckd_static ckd_{{N}}_t _ckd_{{OP}}_2_{{M1}}_{{M2}}(_ckd_type_{{M1}} a, _ckd_type_{{M2}} b) {
    ckd_{{N}}_t r; r._ineXact = _ckd_{{OP}}_3_{{M1}}_{{M2}}(&r._vaLue, a, b); return r;
}
{% endfor %}{# foreach prefixes #}
{% endfor %}{# foreach ops #}
{% endfor %}{# foreach data #}

// ]]]
// Each type with every type operations [[[

{% macro name_to_name(OP, N1, N2, NR) %}
// Operation {{OP}} on {{N1}} and {{N2}} -> {{NR}}
    {% for P1, P2 in PREFIXES %}
        {% set M1 = P1 ~ N1 %}
        {% set M2 = P2 ~ N2 %}
_ckd_static bool _ckd_{{OP}}_3_{{M1}}_{{M2}}(_ckd_type_{{NR}} *r, _ckd_type_{{M1}} a, _ckd_type_{{M2}} b) {
    return _ckd_{{OP}}_3_{{NR}}_{{NR}}(r, _ckd_v_{{N1}}(a), _ckd_v_{{N2}}(b)) | _ckd_ine_{{N1}}(a) | _ckd_ine_{{N2}}(b);
}
_ckd_static _ckd_type_c{{NR}} _ckd_{{OP}}_2_{{M1}}_{{M2}}(_ckd_type_{{M1}} a, _ckd_type_{{M2}} b) {
    return _ckd_{{OP}}_2_c{{NR}}_c{{NR}}(
        ckd_mk_{{NR}}_t(_ckd_v_{{N1}}(a), _ckd_ine_{{N1}}(a)),
        ckd_mk_{{NR}}_t(_ckd_v_{{N2}}(b), _ckd_ine_{{N2}}(b)));
}
    {% endfor %}
{% endmacro %}

{% for OP in ops %}
    {% for N1, _, _, _ in data %}
        {% set N1IDX = loop.index %}
        {% for N2, _, _, _ in data %}
            {% if N1 != N2 %}
                {% set N2IDX = loop.index %}
                {% set NR = N1 %}
                {% if N1IDX < N2IDX %}
                    {% set NR = N2 %}
                {% endif %}
                {{- name_to_name(OP, N1, N2, NR) -}}
            {% endif %}
        {% endfor %}
    {% endfor %}
{% endfor %}

// ]]]
// Generic macros implementation [[[

struct _ckd_invalid_;
void _ckd_invalid(struct _ckd_invalid_);

{% set macrocontnl = ", \\
" %}
{# #}
{% macro generics(end="") %}
{% for N, T, MAX, MIN in data %}
{{ caller(T, N) }}{{ macrocontnl if not loop.last else end }}
{%- endfor %}
{% endmacro %}

#define ckd_mk(value, inexact)  _Generic((value), \
{% call(T, N) generics() %}
    {{T}}: ckd_mk_{{N}}_t
{%- endcall %} \
    )(value, inexact)

{% macro ingen(OP, CNT) %}
    {% call(T, N) generics() -%}
_ckd_type_{{N}}: \
    _Generic((b), \
    {% for N2, _, _, _ in data %}
    _ckd_type_{{N2}}:  _ckd_{{OP}}_{{CNT}}_{{N}}_{{N2}}, \
    _ckd_type_c{{N2}}: _ckd_{{OP}}_{{CNT}}_{{N}}_c{{N2}}, \
    {% endfor %}
    default: _ckd_invalid), \
_ckd_type_c{{N}}: \
    _Generic((b), \
    {% for N2, _, _, _ in data %}
    _ckd_type_{{N2}}:  _ckd_{{OP}}_{{CNT}}_c{{N}}_{{N2}}, \
    _ckd_type_c{{N2}}: _ckd_{{OP}}_{{CNT}}_c{{N}}_c{{N2}}, \
    {% endfor %}
    default: _ckd_invalid)            
    {%- endcall %}
{% endmacro %}
    
{% for OP in ops %}
#define _ckd_{{OP}}_2(a, b)  _Generic((a), \
    {{ ingen(OP, 2) | indent(4) }}, \
    default: _ckd_invalid)(a, b)
#define _ckd_{{OP}}_3(r, a, b)  _Generic((r), \
{% call(T, N) generics() %}
    {{T}} *: \
        _Generic((a), \
        {{ ingen(OP, 3) | indent(8) }}, \
        default: _ckd_invalid)
{%- endcall %}, \
    default: _ckd_invalid)(r, a, b)
#define _ckd_{{OP}}_N(_2,_3,N,...) _ckd_{{OP}}_##N
#define ckd_{{OP}}(w, ...)  _ckd_{{OP}}_N(__VA_ARGS__,3,2)(w,__VA_ARGS__)

{% endfor %}

// ]]]
// EOF [[[

#endif /* CKDINT_H_ */

// ]]]
// vim: ft=c tabstop=4 expandtab shiftwidth=4 softtabstop=4 autoindent foldmethod=marker foldmarker=[[[,]]]
''', autoescape=False, trim_blocks=True, lstrip_blocks=True).render(), file=outf)


