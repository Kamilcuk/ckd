{% import "library.jinja" as L %}
/**
 * @file ckdint_nognu.h
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * SPDX-License-Identifier: MIT + Beerware
 */
// Header [[[
#ifndef CKDINT_H_
#error  This is internal header
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

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

// ]]]
{% for N, T, DETECT, MAX, MIN in L.TYPES %}
	{% if MIN != "0" %}{# Only signed types #}
		{% set HALFIDX = loop.index / 2 | int * 2 %}
		{# Signed key #}
		{% set S = N %}
		{# Unsigned key #}
		{% set U = "uchar" if "schar" in N else "u"~N %}
		{# The normal key is set to signed #}
		{% set N = S %}
		{# MAX and MIN and signed maximum and minimum. UMAX is unsigned maximum #}
		{% set UMAX = "UCHAR_MAX" if "schar" in N else "U"~MAX %}
// Init macros [[[
// Signed minimum and maximum!
// TODO: Add _ckd_ prefix to S and U symbols.
#define S    {{T}}
#define U    unsigned {{ "char" if "schar" in N else T }}
#define _ckd_SGN  ((U)1 << (sizeof(U) * CHAR_BIT - 1))
{# // __CDT__PARSER__
#undef S
#define S  int
#undef U
#define U  unsigned
#}
// ]]]
// Addition and substraction operations [[[

// from https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L713
_ckd_fchpnt bool _ckd_add_sss_{{N}}(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? (S)*res > (S)s1 : (S)*res < (S)s1;
}

_ckd_fchpnt bool _ckd_sub_sss_{{N}}(U s1, U s2, U *res) {
	*res = s1 - s2;
	// taken from
	// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1058
	return (s1 ^ s2) & ~(*res ^ s2) & _ckd_SGN;
	// return s2 < 0 ? *res < s1 : *res > s2;
}

_ckd_fchpnt bool _ckd_add_uuu_{{N}}(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u1;
}

_ckd_fchpnt bool _ckd_sub_uuu_{{N}}(U u1, U u2, U *res) {
	*res = u1 - u2;
	return *res > u1;
}

_ckd_fchpnt bool _ckd_add_sus_{{N}}(U s1, U u2, U *res) {
	*res = s1 + u2;
	return (*res ^ _ckd_SGN) < u2;
}

_ckd_fchpnt bool _ckd_add_suu_{{N}}(U s1, U u2, U *res) {
	*res = s1 + u2;
	s1 += _ckd_SGN;
	return (*res ^ u2) & ~(s1 ^ u2) & _ckd_SGN;
}

_ckd_fchpnt bool _ckd_sub_sus_{{N}}(U s1, U u2, U *res) {
	*res = s1 - u2;
	return u2 > ((U)s1 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_suu_{{N}}(U s1, U u2, U *res) {
	*res = s1 - u2;
	return (S)s1 < 0 || u2 > s1;
}

_ckd_fchpnt bool _ckd_sub_uss_{{N}}(U u1, U s2, U *res) {
	*res = u1 - s2;
	return u1 >= (s2 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_usu_{{N}}(U u1, U s2, U *res) {
	U t1 = u1 ^ _ckd_SGN;
	U t2 = t1 - s2;
	*res = t2 ^ _ckd_SGN;
	return (S)s2 < 0 ? (S)t2 < (S)t1 : (S)t2 > (S)t1;
}

_ckd_fchpnt bool _ckd_add_ssu_{{N}}(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uus_{{N}}(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u2 || (S)*res < 0;
}

_ckd_fchpnt bool _ckd_sub_uus_{{N}}(U u1, U u2, U *res) {
	*res = u1 - u2;
	return u1 >= u2 ? (S)*res < 0 : (S)*res >= 0;
}

_ckd_fchpnt bool _ckd_sub_ssu_{{N}}(U s1, U s2, U *res) {
	*res = s1 - s2;
	return (S)s2 >= 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uss_{{N}}(U u1, U s1, U *res) {
	return _ckd_add_sus_{{N}}(s1, u1, res);
}

_ckd_fchpnt bool _ckd_add_usu_{{N}}(U u1, U s1, U *res) {
	return _ckd_add_suu_{{N}}(s1, u1, res);
}

// ]]]
// Multiplication [[[

// https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
_ckd_fconst bool _ckd_ovf_signed_{{N}}(S a, S b) {
	if (a > 0) {
		if (b > 0) {
			if (a > {{MAX}} / b) { // a positive, b positive
				return 1;
			}
		} else {
			if (b < {{MIN}} / a) { // a positive, b not positive
				return 1;
			}
		}
	} else {
		if (b > 0) {
			if (a < {{MIN}} / b) { // a not positive, b positive
				return 1;
			}
		} else {
			if (a != 0 && b < {{MAX}} / a) { // a not positive, b not positive
				return 1;
			}
		}
	}
	return 0;
}

// https://stackoverflow.com/a/1815391/9072753
_ckd_fconst bool _ckd_ovf_unsigned_{{N}}(U a, U b) {
	return a != 0 && b > {{UMAX}} / a;
}

// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1286

_ckd_fchpnt bool _ckd_mul_sss_{{N}}(U s1, U s2, U *res) {
	*res = s1 * s2;
	return _ckd_ovf_signed_{{N}}(s1, s2);
}

_ckd_fchpnt bool _ckd_mul_uuu_{{N}}(U u1, U u2, U *res) {
	*res = u1 * u2;
	return _ckd_ovf_unsigned_{{N}}(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_suu_{{N}}(U s1, U u2, U *res) {
	*res = s1 * u2;
	return ((S) s1 < 0 && u2) || _ckd_ovf_unsigned_{{N}}(s1, u2);
}

_ckd_fchpnt bool _ckd_mul_uus_{{N}}(U u1, U u2, U *res) {
	*res = u1 * u2;
	return (S)*res < 0 || _ckd_ovf_unsigned_{{N}}(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_sus_{{N}}(U s1, U u2, U *res) {
	*res = s1 * u2;
	return (S)u2 >= 0 ? _ckd_ovf_signed_{{N}}(s1, u2) : (s1 && ((S)s1 != -1 || u2 != *res));
}

_ckd_fchpnt bool _ckd_mul_ssu_{{N}}(U s1, U s2, U *res) {
	U t1 = (S)(s1 & s2) < 0 ? (-s1) : s1;
	U t2 = (S)(s1 & s2) < 0 ? (-s2) : s2;
	*res = t1 * t2;
	return (S)(s1 ^ s2) < 0 ? (s1 && s2) : _ckd_ovf_signed_{{N}}(t1, t2);
}

_ckd_fchpnt bool _ckd_mul_uss_{{N}}(U u1, U s2, U *res) {
	return _ckd_mul_sus_{{N}}(s2, u1, res);
}

_ckd_fchpnt bool _ckd_mul_usu_{{N}}(U u1, U s2, U *res) {
	return _ckd_mul_suu_{{N}}(s2, u1, res);
}

/* ------------------------------------------------------------------------- */

{% call() L.foreach_OP() %}
static bool (*const _ckd_$OP_{{N}}_choose_arr[])(U, U, U*) = {
	&_ckd_$OP_sss_{{N}},
	&_ckd_$OP_ssu_{{N}},
	&_ckd_$OP_sus_{{N}},
	&_ckd_$OP_suu_{{N}},
	&_ckd_$OP_uss_{{N}},
	&_ckd_$OP_usu_{{N}},
	&_ckd_$OP_uus_{{N}},
	&_ckd_$OP_uuu_{{N}},
};

_ckd_fchpnt bool _ckd_$OP_{{N}}_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_$OP_{{N}}_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_c{{S}} _ckd_$OP_2_{{S}}(unsigned idx, U a, U b, bool other) {
	_ckd_c{{S}} tmp;
	ckd_overflow(tmp) = _ckd_$OP_{{N}}_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_c{{U}} _ckd_$OP_2_{{U}}(unsigned idx, U a, U b, bool other) {
	_ckd_c{{U}} tmp;
	ckd_overflow(tmp) = _ckd_$OP_{{N}}_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

	{% call(A) L.foreach_TYPE(arg=1) %}
_ckd_fchpnt bool _ckd_$OP_3_{{S}}_to_$TYPE(_ckd_$TYPE *ret, unsigned idx, U a, U b, bool other) {
	_ckd_{{U}} tmp;
	const bool opovf = _ckd_$OP_{{N}}_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
		{% if HALFIDX > A.HALFIDX %}
			|| (S) {{A.MIN}} > (S) tmp
			|| (S) tmp > (S) {{A.MAX}}
		{% endif %}
			;
}
_ckd_fchpnt bool _ckd_$OP_3_{{U}}_to_$TYPE(_ckd_$TYPE *ret, unsigned idx, U a, U b, bool other) {
	_ckd_{{U}} tmp;
	const bool opovf = _ckd_$OP_{{N}}_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
		{% if HALFIDX > A.HALFIDX %}
		{% if A.MIN != "0" %}
			|| (U) {{A.MIN}} > tmp
		{% endif %}
			|| tmp > (U) {{A.MAX}}
		{% endif %}
			;
}
	{% endcall %}
{% endcall %}

// ]]]
// Undef macros [[[
#undef S
#undef U
#undef _ckd_SGN
// ]]]
	{% endif %}
{% endfor %}
// Helper macros [[[

#define _ckd_issigned(T) \
		_Generic(_ckd_value(T), \
{% call(d) L.foreach_TYPE(inmacro=1, arg=1) %}
		_ckd_$TYPE: {{ d.signed }}
{%- endcall %})

#define _ckd_idx(a, b)  ( \
		_ckd_issigned(a) << 2 | \
		_ckd_issigned(b) << 1 | \
		_ckd_issigned(_ckd_value(a) + _ckd_value(b)) \
		)
// ]]]
// Macros [[[
{% call() L.foreach_OP() %}

#define _ckd_$OP_3(r, a, b) \
			_Generic(_ckd_value(a) + _ckd_value(b) + *(r), \
	{% call() L.foreach_TYPE(inmacro=1) %}
			_ckd_$TYPE: _Generic(*(r), \
		{% call() L.foreach_TYPE(inmacro=1, repl="$TYPE2") %}
				_ckd_$TYPE2: _ckd_$OP_3_$TYPE_to_$TYPE2
		{%- endcall %})
	{%- endcall %})(r, _ckd_idx(a, b), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))

#define _ckd_$OP_2(a, b) \
			_Generic(_ckd_value(a) + _ckd_value(b), \
	{% call() L.foreach_TYPE(inmacro=1) %}
			_ckd_$TYPE: _ckd_$OP_2_$TYPE
	{%- endcall %})(_ckd_idx(a, b), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))
{% endcall %}

// ]]]
// vim: ft=c

