#!/usr/bin/env python3
import sys; from jinja2 import Template; outf = open(sys.argv[1], 'w') if len(sys.argv) > 1 else sys.stdout; print(Template(r'''
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

/* ------------------------------------------------------------------------- */

{# operations #}
{% set ops = [ "add", "sub", "mul", "div" ] %}
{# type, suffix, gcc__builtin_op_prefix, #}
{% set data = [
        ("int","int","INT_MAX","INT_MIN"),
        ("unsigned int","uint","UINT_MAX","0"),
    ]
%}
{% if 0 %}
        ("long","long","LONG_MAX","LONG_MIN"),
        ("unsigned long","ulong","ULONG_MAX","0"),
        ("long long","llong","LLONG_MAX","LLONG_MIN"),
        ("unsigned long long","ullong","ULLONG_MAX","0"),
{% endif %}

/* ------------------------------------------------------------------------- */

#define _ckd_staticinline  static inline

#define ckd_inexact(x)  ((x)._inexact)
#define ckd_value(x)    ((x)._value)

{% for T, N, MAX, MIN in data %}
{% set ISSIGNED = MIN == "0" %}

#define _ckd_max_{{N}}  ({{MAX}})
#define _ckd_min_{{N}}  ({{MIN}})
#define _ckd_issigned_{{N}}  (_ckd_min_{{N}} == 0)

typedef struct {
    {{T}} _value;
    bool _inexact;
} ckd_{{N}}_t;

typedef {{T}} _ckd_type_{{N}};
typedef ckd_{{N}}_t _ckd_type_c{{N}};

#define ckd_mk_{{N}}_t(value, inexact)  (ckd_{{N}}_t){value, inexact)

{% for OP in ops %}

_ckd_staticinline
bool _ckd_{{OP}}_3_{{N}}_{{N}}({{T}} *r, {{T}} a, {{T}} b) {
    const {{T}} max = _ckd_max_{{N}};
    const {{T}} min = _ckd_min_{{N}};
    (void)max;
    (void)min;
{% if OP != "div" %}
#ifdef __GNUC__
    return __builtin_{{OP}}_overflow(a, b, r);
#else // __GNUC__
{% if OP == "add" and ISSIGNED %}
    // https://stackoverflow.com/q/3944505/9072753
    if (a >= 0 && b >= 0) {
        if (_ckd_max_{{N}} - a <= b) {
            return *r = b - (max - a), 1;
        }
    } else if (a < 0 && b < 0) {
        if (a <= max - b) {
            return *r = (max - b) - a, 1;
        }
    }
    return *r = a + b, 0;
{% elif OP == "add" and not ISSIGNED %}
    // https://stackoverflow.com/a/6472982/9072753
    return *r = a + b, *r < (a | b);
{% elif OP == "sub" and ISSIGNED %}
    // https://codereview.stackexchange.com/questions/93687/test-if-arithmetic-OPeration-will-cause-undefined-behavior/93699#93699
    if (b < 0) {
        if (a > max + b) {
            return *r = a - (max + b), 1;
           }
        }
    } else {
        if (a < min + b) {
            return *r = (min + b) - a, 1;
        }
    }
    return *r = a - b, 0
{% elif OP == "sub" and not ISSIGNED %}
    *r = a - b;
    return *r > (a | b);
{% elif OP == "mul" %}
    // both signed and unsigned
    if (a > 0) {
        if (b > 0) {
            if (a > max / b) { // a positive, b positive
                return *r = max / b * a, 1;
            }
        }
        if (b < min / a) { // a positive, b not positive
            return *r = min / a * b, 1;
        }
    }
    if (b > 0) {
        if (a < min / b) { // a not positive, b positive
            return *r = min / b * a, 1;
        }
    }
    if (a != 0 && b < max / a) { // a not positive, b not positive
        return *r = max / a * b, 1;
    }
    return *r = a * b, 0;
{% endif %}{# OP != "div" #}
#endif // __GNUC__
{% else %}{# OP == "div" #}
    #if _ckd_min_{{N}} != 0 && _ckd_min_{{N}} < -_ckd_max_{{N}}
        if (a == min && b == -1) {
            return *r = 0, 1;
        }
    #endif
    if (b == 0) return *r = min, 1;
    return *r = a / b, 0;    
{% endif %}{# OP == "div" #}
}

_ckd_staticinline
bool _ckd_{{OP}}_3_{{N}}_c{{N}}({{T}} *r, {{T}} a, ckd_{{N}}_t b) {
    return _ckd_{{OP}}_3_{{N}}_{{N}}(r, a, ckd_value(b)) | ckd_inexact(b);
}

_ckd_staticinline
bool _ckd_{{OP}}_3_c{{N}}_{{N}}({{T}} *r, ckd_{{N}}_t a, {{T}} b) {
    return _ckd_{{OP}}_3_{{N}}_{{N}}(r, ckd_value(a), b) | ckd_inexact(a);
}

_ckd_staticinline
bool _ckd_{{OP}}_3_c{{N}}_c{{N}}({{T}} *r, ckd_{{N}}_t a, ckd_{{N}}_t b) {
    return _ckd_{{OP}}_3_{{N}}_{{N}}(r, ckd_value(a), ckd_value(b)) | ckd_inexact(a) | ckd_inexact(b);
}

_ckd_staticinline
ckd_{{N}}_t _ckd_{{OP}}_2_{{N}}_{{N}}({{T}} a, {{T}} b) {
    ckd_{{N}}_t r; r._inexact = _ckd_{{OP}}_3_{{N}}_{{N}}(&r._value, a, b); return r;
}

_ckd_staticinline
ckd_{{N}}_t _ckd_{{OP}}_2_c{{N}}_{{N}}(ckd_{{N}}_t a, {{T}} b) {
    ckd_{{N}}_t r; r._inexact = _ckd_{{OP}}_3_c{{N}}_{{N}}(&r._value, a, b); return r;
}

_ckd_staticinline
ckd_{{N}}_t _ckd_{{OP}}_2_{{N}}_c{{N}}({{T}} a, ckd_{{N}}_t b) {
    ckd_{{N}}_t r; r._inexact = _ckd_{{OP}}_3_{{N}}_c{{N}}(&r._value, a, b); return r;
}

_ckd_staticinline
ckd_{{N}}_t _ckd_{{OP}}_2_c{{N}}_c{{N}}(ckd_{{N}}_t a, ckd_{{N}}_t b) {
    ckd_{{N}}_t r; r._inexact = _ckd_{{OP}}_3_c{{N}}_c{{N}}(&r._value, a, b); return r;
}

{# foreach ops #}
{% endfor %}
{# foreach data #}
{% endfor %}

struct _ckd_invalid_;
void _ckd_invalid(struct _ckd_invalid_);

{% macro generics(end="") %}
{% for T, N, MAX, MIN in data %}
{{ caller(T, N) }}{{ ", \\
" if not loop.last else end }}
{%- endfor %}
{% endmacro %}

#define ckd_mk(value, inexact)  _Generic((value), \
{% call(T, N) generics() %}
    {{T}}: ckd_mk_{{N}}_t
{%- endcall %} \
    )(value, inexact)

{% macro ingen(OP, CNT) %}
{% call(T, N) generics() -%}
{{T}}: \
    _Generic((b), \
    {{T}}: _ckd_{{OP}}_{{CNT}}_{{N}}_{{N}}, \
    ckd_{{N}}_t: _ckd_{{OP}}_{{CNT}}_{{N}}_c{{N}}, \
    default: _ckd_invalid), \
ckd_{{N}}_t: \
    _Generic((b), \
    {{T}}: _ckd_{{OP}}_{{CNT}}_c{{N}}_{{N}}, \
    ckd_{{N}}_t: _ckd_{{OP}}_{{CNT}}_c{{N}}_c{{N}}, \
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

#endif /* CKDINT_H_ */

''', autoescape=False, trim_blocks=True).render(), file=outf)
# vim: ft=c tabstop=4 expandtab shiftwidth=4 softtabstop=4 autoindent

