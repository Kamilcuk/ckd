{% import "library.jinja" as L %}
/**
 * @file ckdint_nognu.h
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * @copyright 2021 Kamil Cukrowski
 * SPDX-License-Identifier: MIT + Beerware
 *
 * While this file tries not to use any GNU extensions, it
 * strongly assumes that all types are twos-complement.
 */
// Header [[[
#ifndef CKDINT_H_
#error  This is internal header
#include "../ckdint.h"
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
#endif  // __SIZEOF_INT128__

{% call() L.foreach_TYPE(promotedonly=1) %}
typedef struct {
	/// Represents the stored value.
	_ckd_$TYPE v;
	/// Overflow?
	bool o;
	/// Was the original type signed?
	bool s;
} _ckd_arg_$TYPE;
{% endcall %}

// ]]]
{% call(V) L.foreach_TYPE(repl="", arg=1, promotedonly=1) %}
	{# Exclude char and short, they are promoted to int #}
	{# Only signed types, one go for unsigned&signed types. #}
	{% if V.SIGNED %}
		{# Signed key #}
		{% set S = V.N %}
		{# Unsigned key #}
		{% set U = "uchar" if "schar" in S else "u"~S %}
		{# The normal key is set to signed #}
		{% set N = S %}
		{# MAX and MIN and signed maximum and minimum. UMAX is unsigned maximum #}
		{% set UMAX = "UCHAR_MAX" if "schar" in N else "U"~V.MAX %}
		{% set MAX = V.MAX %}
		{% set MIN = V.MIN %}
		{% set HALFIDX = V.HALFIDX %}
// Init macros [[[
// Signed minimum and maximum!
// TODO: Add _ckd_ prefix to S and U symbols.
#define S    {{V.T}}
#define U    unsigned {{ "char" if "schar" in S else V.T }}
#define _ckd_SGN  ((U)1 << (sizeof(U) * CHAR_BIT - 1))
{# // __CDT__PARSER__
#undef S
#define S  int
#undef U
#define U  unsigned
#}
// ]]]
// Addition and substraction operations [[[

{# from https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L713 #}
_ckd_fchpnt bool _ckd_add_sss_{{N}}(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? (S)*res > (S)s1 : (S)*res < (S)s1;
}

_ckd_fchpnt bool _ckd_sub_sss_{{N}}(U s1, U s2, U *res) {
	*res = s1 - s2;
	{# https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1058 #}
	return (s1 ^ s2) & ~(*res ^ s2) & _ckd_SGN;
	{# return s2 < 0 ? *res < s1 : *res > s2; #}
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

{# https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow #}
_ckd_fconst bool _ckd_ovf_signed_{{N}}(S a, S b) {
	return a > 0 ? b > 0 ? (a > {{MAX}} / b) : (b < {{MIN}} / a) : b > 0 ? (a < {{MIN}} / b) : (a != 0 && b < {{MAX}} / a);
}

{# https://stackoverflow.com/a/1815391/9072753 #}
_ckd_fconst bool _ckd_ovf_unsigned_{{N}}(U a, U b) {
	return a != 0 && b > {{UMAX}} / a;
}

{# https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1286 #}

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
_ckd_fchpnt bool _ckd_$OP_{{N}}_choose(bool asigned, bool bsigned, bool ressigned, U a, U b, U *res) {
	if (asigned) {
		if (bsigned) {
			if (ressigned) {
				return _ckd_$OP_sss_{{N}}(a, b, res);
			}
			return _ckd_$OP_ssu_{{N}}(a, b, res);
		} else {
			if (ressigned) {
				return _ckd_$OP_sus_{{N}}(a, b, res);
			}
		}
		return _ckd_$OP_suu_{{N}}(a, b, res);
	} else {
		if (bsigned) {
			if (ressigned) {
				return _ckd_$OP_uss_{{N}}(a, b, res);
			}
			return _ckd_$OP_usu_{{N}}(a, b, res);
		} else {
			if (ressigned) {
				return _ckd_$OP_uus_{{N}}(a, b, res);
			}
		}
	}
	return _ckd_$OP_uuu_{{N}}(a, b, res);
}

_ckd_fconst _ckd_c{{S}} _ckd_$OP_2_{{S}}(_ckd_arg_{{S}} a, _ckd_arg_{{S}} b) {
	_ckd_c{{S}} tmp;
	ckd_overflow(tmp) = _ckd_$OP_{{N}}_choose(a.s, b.s, 1, a.v, b.v, (U*)&ckd_value(tmp)) || a.o || b.o;
	return tmp;
}

_ckd_fconst _ckd_c{{U}} _ckd_$OP_2_{{U}}(_ckd_arg_{{U}} a, _ckd_arg_{{U}} b) {
	_ckd_c{{U}} tmp;
	ckd_overflow(tmp) = _ckd_$OP_{{N}}_choose(a.s, b.s, 0, a.v, b.v, &ckd_value(tmp)) || a.o || b.o;
	return tmp;
}

	{% call(T) L.foreach_TYPE(char=1, arg=1) %}
{#
/*
	Do calculations on two promoted signed types and represent the result in any $TYPE.
	These functions have a little bit of logic around `#if` macros to remove them.
	First, we need to remove the `#if` and `#endif` if one of types is int128, cause preprocessor can't handle int128.
	Then, we can remove the check when resulting type is greater, like `int * int -> long`.
	We can also remove the check when we know it's true, like `int * int -> int`.
*/
#}
		{% set noint128 = "int128" not in S and "int128" not in T.T %}
_ckd_fchpnt bool _ckd_$OP_3_{{S}}_to_$TYPE(_ckd_$TYPE *ret, _ckd_arg_{{S}} a, _ckd_arg_{{S}} b) {
	_ckd_{{U}} tmp;
	const bool opovf = _ckd_$OP_{{N}}_choose(a.s, b.s, {{T.SIGNED}}, a.v, b.v, &tmp)
	{% if not T.SIGNED or (T.SIGNED and T.HALFIDX <= HALFIDX) %}
		{% if MIN != T.MIN %}
			{% set protect = not ( (T.MIN != "0" and MIN == "0") or (T.MIN == "0" and MIN != "0") ) and noint128 %}
			{% if protect %}
#if {{MIN}} < {{T.MIN}}
			{% endif %}
			|| (S) {{T.MIN}} > (S) tmp
			{% if protect %}
#endif
			{% endif %}
		{% endif %}
		{% if MAX != T.MAX %}
			{% if noint128 %}
#if {{MAX}} > {{T.MAX}}
			{% endif %}
			|| (S) tmp > (S) {{T.MAX}}
			{% if noint128 %}
#endif
			{% endif %}
		{% endif %}
	{% endif %}
			|| a.o || b.o;
	*ret = (_ckd_$TYPE) tmp;
	return opovf;
}
_ckd_fchpnt bool _ckd_$OP_3_{{U}}_to_$TYPE(_ckd_$TYPE *ret, _ckd_arg_{{U}} a, _ckd_arg_{{U}} b) {
	_ckd_{{U}} tmp;
	const bool opovf = _ckd_$OP_{{N}}_choose(a.s, b.s, {{T.SIGNED}}, a.v, b.v, &tmp)
	{% if T.SIGNED or (not T.SIGNED and T.HALFIDX <= HALFIDX) %}
			{% set protect = not T.SIGNED and noint128 %}
			{% if protect %}
#if {{UMAX}} > {{T.MAX}}
			{% endif %}
			|| (U) tmp > (U) {{T.MAX}}
			{% if protect %}
#endif
			{% endif %}
	{% endif %}
			|| a.o || b.o; // {{T.SIGNED}} {{T.HALFIDX}} {{HALFIDX}}
	*ret = (_ckd_$TYPE) tmp;
	return opovf;
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
{% endcall %}
// Additional 3 argument conversions [[[
{% call() L.foreach_OP() %}
	{% call(A) L.foreach_TYPE(promotedonly=1, arg=1) %}
		{% call(B) L.foreach_TYPE(char=1, repl="$TYPE2", arg=1) %}
			{% if B.CHAR or not ((A.HALFIDX <= B.HALFIDX and (A.SIGNED and not B.SIGNED)) or (A.HALFIDX < B.HALFIDX)) %}
_ckd_fchpnt bool _ckd_$OP_3_$TYPE_to_c$TYPE2(_ckd_c$TYPE2 *ret, _ckd_arg_$TYPE a, _ckd_arg_$TYPE b) {
	ckd_overflow(*ret) = _ckd_$OP_3_$TYPE_to_$TYPE2(&ckd_value(*ret), a, b); // {{A.HALFIDX}} {{B.HALFIDX}} {{A.SIGNED}} {{B.SIGNED}}
	return ckd_overflow(*ret);
}
			{% endif %}
		{% endcall%}
	{% endcall %}
{% endcall %}
// ]]]]
// Helper macros [[[

struct _ckd_invalid_;
void _ckd_invalid(struct _ckd_invalid_);

{% call() L.foreach_TYPE(promotedonly=1) %}
	{% call(T2) L.foreach_TYPE(repl="$TYPE2", char=1, arg=1) %}
_ckd_fconst _ckd_arg_$TYPE _ckd_c$TYPE2_to_arg_$TYPE(_ckd_c$TYPE2 _ckd_v) {
	const _ckd_arg_$TYPE _ckd_ret = { ckd_value(_ckd_v), ckd_overflow(_ckd_v), {{T2.SIGNED}} }; return _ckd_ret;
}
	{% endcall %}
{% endcall %}

/**
 * @define _ckd_arg(TO, FROM)
 * @brief Converts any integer or checked integer type into an _ckd_arg of integer type TO.
 * @param TO Any integer type or checked integer type.
 * @param FROM Any integer type or checked integer type.
 * @return _ckd_arg structure that will be passed to other functions.
 *
 * As of now, this is the part that makes nested invokations not possible to compile.
 * This is the slowest part because of the double _Generic(...: _Generic(....) );
 * I have no really good idea how to remove it. The problem is that `FROM` is macro expanded
 * by preprocessor for each type, which makes the preprocessor output unbearable big if `FROM`
 * is also a call to ckd_* function.
 * The arguments to the functions could be changed to `(_ckd_gvalue(FROM), _ckd_overflow(FROM))`
 * and then `_ckd_gvalue(FROM)` can be implicitly-promoted to `_ckd_gvalue(TO)` type.
 * But the problem is that then `FROM` is evaulated two times, and we do not want that.
 */
#define _ckd_arg(TO, FROM) \
			_Generic(_ckd_ctypeof(TO), \
	{% call() L.foreach_TYPE(promotedonly=1, inmacro=1) %}
			_ckd_c$TYPE: \
				_Generic(_ckd_ctypeof(FROM), \
		{% call() L.foreach_TYPE(char=1, inmacro=1, repl="$TYPE2") %}
				_ckd_c$TYPE2: _ckd_c$TYPE2_to_arg_$TYPE
		{%- endcall %})
	{%- endcall %})(_ckd_toct(FROM))

// ]]]
// Macros [[[
{% call() L.foreach_OP() %}

#define _ckd_$OP_3_in(T, r, a, b) \
			_Generic(T \
	{% call(A) L.foreach_TYPE(promotedonly=1, arg=1) %}
			,_ckd_$TYPE: _Generic(*(r) \
		{% call(B) L.foreach_TYPE(char=1, repl="$TYPE2", arg=1) %}
			{% if (A.HALFIDX <= B.HALFIDX and (A.SIGNED and not B.SIGNED)) or (A.HALFIDX < B.HALFIDX) %}
				,_ckd_$TYPE2:  _ckd_invalid \
				,_ckd_c$TYPE2: _ckd_invalid \
			{% else %}
				,_ckd_$TYPE2:  _ckd_$OP_3_$TYPE_to_$TYPE2 \
				,_ckd_c$TYPE2: _ckd_$OP_3_$TYPE_to_c$TYPE2 \
			{% endif %}
		{% endcall %}
				) \
	{% endcall %}
			)(r, _ckd_arg(T, a), _ckd_arg(T, b))

#define _ckd_$OP_3(r, a, b) \
		_ckd_$OP_3_in(ckd_value(_ckd_ctypeof(a)) + ckd_value(_ckd_ctypeof(b)) + ckd_value(_ckd_ctypeof(*(r))), r, a, b)

#define _ckd_$OP_2_in(T, a, b) \
			_Generic(T, \
	{% call() L.foreach_TYPE(promotedonly=1, inmacro=1) %}
		_ckd_$TYPE: _ckd_$OP_2_$TYPE
	{%- endcall %})(_ckd_arg(T, a), _ckd_arg(T, b))

#define _ckd_$OP_2(a, b) \
		_ckd_$OP_2_in(ckd_value(_ckd_ctypeof(a)) + ckd_value(_ckd_ctypeof(b)), a, b)

{% endcall %}

// ]]]
// vim: ft=c

