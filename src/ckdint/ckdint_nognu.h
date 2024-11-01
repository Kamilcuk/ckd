{% import "library.jinja" as L %}
/**
 * @file ckdint_nognu.h
 * @author Kamil Cukrowski <kamilcukrowski@gmail.com>
 * @date 2021-06-19
 * @copyright 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
 * SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
 * SPDX-License-Identifier: MIT
 *
 * While this file tries not to use any GNU extensions, it
 * strongly assumes that all types are twos-complement.
 * First everything is converted to unsigned types.
 */
// Header [[[
#ifndef CKDINT_NOGNU
#define CKDINT_NOGNU
#ifndef CKDINT_H_
#error  This is internal header
#include "../ckdint.h"
#endif

{% if HAVE_UINT128 %}
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
{% endif %}

{% macro OPERATIONEXISTS(A, B) %}
	{{- 0 if ((A.HALFIDX <= B.HALFIDX and (A.SIGNED and not B.SIGNED)) or (A.HALFIDX < B.HALFIDX)) else 1 -}}
{% endmacro %}

{% call(A) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
/// Argument type structure passed around as arguments converted to unsigned type.
typedef struct {
	/// Represents the stored value.
	{{A.T}} _ckd_Value;
	/// Overflow?
	bool _ckd_Overflow;
	/// Was the original type signed?
	bool _ckd_Signed;
} _ckd_arg_$TYPE;
{% endcall %}

// ]]]
{% call(V) L.foreach_TYPE(repl="", promotedonly=1) %}
	{# Exclude char and short, they are promoted to int #}
	{# Only signed types, one go for unsigned&signed types. #}
	{% if V.SIGNED %}
		{% set S = V.SN %}
		{% set U = V.UN %}
		{% set N = S %}
		{# MAX and MIN and signed maximum and minimum. UMAX is unsigned maximum #}
		{% set UMAX = V.UMAX %}
		{% set MAX = V.MAX %}
		{% set MIN = V.MIN %}
		{% set HALFIDX = V.HALFIDX %}
// Init macros [[[
// Signed minimum and maximum!
#define _ckd_S    {{V.ST}}
#define _ckd_U    {{V.UT}}
#define _ckd_sign  ((_ckd_U)1 << (sizeof(_ckd_U) * CHAR_BIT - 1))
{# // __CDT__PARSER__
#undef _ckd_S
#define _ckd_S  int
#undef _ckd_U
#define _ckd_U  unsigned
#}
// ]]]
// Addition and substraction operations [[[

{# from https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L713 #}
_ckd_fchpnt(3) bool _ckd_add_sss_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 + _ckd_S2;
	return (_ckd_S)_ckd_S2 < 0 ? (_ckd_S)*_ckd_res > (_ckd_S)_ckd_S1 : (_ckd_S)*_ckd_res < (_ckd_S)_ckd_S1;
}

_ckd_fchpnt(3) bool _ckd_sub_sss_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 - _ckd_S2;
	{# https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1058 #}
	return (_ckd_S1 ^ _ckd_S2) & ~(*_ckd_res ^ _ckd_S2) & _ckd_sign;
	{# return _ckd_S2 < 0 ? *_ckd_res < _ckd_S1 : *_ckd_res > _ckd_S2; #}
}

_ckd_fchpnt(3) bool _ckd_add_uuu_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_U1 + _ckd_U2;
	return *_ckd_res < _ckd_U1;
}

_ckd_fchpnt(3) bool _ckd_sub_uuu_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_U1 - _ckd_U2;
	return *_ckd_res > _ckd_U1;
}

_ckd_fchpnt(3) bool _ckd_add_sus_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 + _ckd_U2;
	return (*_ckd_res ^ _ckd_sign) < _ckd_U2;
}

_ckd_fchpnt(3) bool _ckd_add_suu_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 + _ckd_U2;
	_ckd_S1 += _ckd_sign;
	return (*_ckd_res ^ _ckd_U2) & ~(_ckd_S1 ^ _ckd_U2) & _ckd_sign;
}

_ckd_fchpnt(3) bool _ckd_sub_sus_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 - _ckd_U2;
	return _ckd_U2 > ((_ckd_U)_ckd_S1 ^ _ckd_sign);
}

_ckd_fchpnt(3) bool _ckd_sub_suu_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 - _ckd_U2;
	return (_ckd_S)_ckd_S1 < 0 || _ckd_U2 > _ckd_S1;
}

_ckd_fchpnt(3) bool _ckd_sub_uss_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_U1 - _ckd_S2;
	return _ckd_U1 >= (_ckd_S2 ^ _ckd_sign);
}

_ckd_fchpnt(3) bool _ckd_sub_usu_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	const _ckd_U _t1 = _ckd_U1 ^ _ckd_sign;
	const _ckd_U _t2 = _t1 - _ckd_S2;
	*_ckd_res = _t2 ^ _ckd_sign;
	return (_ckd_S)_ckd_S2 < 0 ? (_ckd_S)_t2 < (_ckd_S)_t1 : (_ckd_S)_t2 > (_ckd_S)_t1;
}

_ckd_fchpnt(3) bool _ckd_add_ssu_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 + _ckd_S2;
	return (_ckd_S)_ckd_S2 < 0 ? ((_ckd_S)(_ckd_S1 | *_ckd_res) < 0) : ((_ckd_S)(_ckd_S1 & *_ckd_res) < 0);
}

_ckd_fchpnt(3) bool _ckd_add_uus_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_U1 + _ckd_U2;
	return *_ckd_res < _ckd_U2 || (_ckd_S)*_ckd_res < 0;
}

_ckd_fchpnt(3) bool _ckd_sub_uus_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_U1 - _ckd_U2;
	return _ckd_U1 >= _ckd_U2 ? ((_ckd_S)*_ckd_res < 0) : ((_ckd_S)*_ckd_res >= 0);
}

_ckd_fchpnt(3) bool _ckd_sub_ssu_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 - _ckd_S2;
	return (_ckd_S)_ckd_S2 >= 0 ? ((_ckd_S)(_ckd_S1 | *_ckd_res) < 0) : ((_ckd_S)(_ckd_S1 & *_ckd_res) < 0);
}

_ckd_fchpnt(3) bool _ckd_add_uss_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_S1, _ckd_U *_ckd_res) {
	return _ckd_add_sus_{{N}}(_ckd_S1, _ckd_U1, _ckd_res);
}

_ckd_fchpnt(3) bool _ckd_add_usu_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_S1, _ckd_U *_ckd_res) {
	return _ckd_add_suu_{{N}}(_ckd_S1, _ckd_U1, _ckd_res);
}

// ]]]
// Multiplication [[[

{# https://www.informit.com/articles/article.aspx?p=1959565&seqNum=13 #}
_ckd_fconst bool _ckd_ovf_signed_{{N}}(_ckd_S s1, _ckd_S s2, _ckd_S r) {
	return (s2 < 0 && s1 == {{MIN}}) || (s2 && r / s2 != s1);
}

{# https://stackoverflow.com/a/1815391/9072753 #}
_ckd_fconst bool _ckd_ovf_unsigned_{{N}}(_ckd_U _ckd_a, _ckd_U _ckd_b) {
	return _ckd_a != 0 && _ckd_b > {{UMAX}} / _ckd_a;
}

{# https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1286 #}

_ckd_fchpnt(3) bool _ckd_mul_sss_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 * _ckd_S2;
	return _ckd_ovf_signed_{{N}}(_ckd_S1, _ckd_S2, *_ckd_res);
}

_ckd_fchpnt(3) bool _ckd_mul_uuu_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_U1 * _ckd_U2;
	return _ckd_ovf_unsigned_{{N}}(_ckd_U1, _ckd_U2);
}

_ckd_fchpnt(3) bool _ckd_mul_suu_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 * _ckd_U2;
	return ((_ckd_S) _ckd_S1 < 0 && _ckd_U2) || _ckd_ovf_unsigned_{{N}}(_ckd_S1, _ckd_U2);
}

_ckd_fchpnt(3) bool _ckd_mul_uus_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_U1 * _ckd_U2;
	return (_ckd_S)*_ckd_res < 0 || _ckd_ovf_unsigned_{{N}}(_ckd_U1, _ckd_U2);
}

_ckd_fchpnt(3) bool _ckd_mul_sus_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_U2, _ckd_U *_ckd_res) {
	*_ckd_res = _ckd_S1 * _ckd_U2;
	return (_ckd_S)_ckd_U2 >= 0 ? _ckd_ovf_signed_{{N}}(_ckd_S1, _ckd_U2, *_ckd_res)
		: (_ckd_S1 && ((_ckd_S)_ckd_S1 != -1 || _ckd_U2 != *_ckd_res));
}

_ckd_fchpnt(3) bool _ckd_mul_ssu_{{N}}(_ckd_U _ckd_S1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	const _ckd_U _t1 = (_ckd_S)(_ckd_S1 & _ckd_S2) < 0 ? (-_ckd_S1) : _ckd_S1;
	const _ckd_U _t2 = (_ckd_S)(_ckd_S1 & _ckd_S2) < 0 ? (-_ckd_S2) : _ckd_S2;
	*_ckd_res = _t1 * _t2;
	return (_ckd_S)(_ckd_S1 ^ _ckd_S2) < 0 ? (_ckd_S1 && _ckd_S2) : _ckd_ovf_unsigned_{{N}}(_t1, _t2);
}

_ckd_fchpnt(3) bool _ckd_mul_uss_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	return _ckd_mul_sus_{{N}}(_ckd_S2, _ckd_U1, _ckd_res);
}

_ckd_fchpnt(3) bool _ckd_mul_usu_{{N}}(_ckd_U _ckd_U1, _ckd_U _ckd_S2, _ckd_U *_ckd_res) {
	return _ckd_mul_suu_{{N}}(_ckd_S2, _ckd_U1, _ckd_res);
}

/* ------------------------------------------------------------------------- */

{% call() L.foreach_OP() %}

_ckd_fchpnt(5) bool _ckd_$OP_{{N}}_choose_s(bool _ckd_asigned, bool _ckd_bsigned,
		_ckd_U _ckd_a, _ckd_U _ckd_b, _ckd_U *_ckd_res) {
	if (_ckd_asigned) {
		if (_ckd_bsigned) {
			return _ckd_$OP_sss_{{N}}(_ckd_a, _ckd_b, _ckd_res);
		}
		return _ckd_$OP_sus_{{N}}(_ckd_a, _ckd_b, _ckd_res);
	} else if (_ckd_bsigned) {
		return _ckd_$OP_uss_{{N}}(_ckd_a, _ckd_b, _ckd_res);
	}
	return _ckd_$OP_uus_{{N}}(_ckd_a, _ckd_b, _ckd_res);
}

_ckd_fchpnt(5) bool _ckd_$OP_{{N}}_choose_u(bool _ckd_asigned, bool _ckd_bsigned,
		_ckd_U _ckd_a, _ckd_U _ckd_b, _ckd_U *_ckd_res) {
	if (_ckd_asigned) {
		if (_ckd_bsigned) {
			return _ckd_$OP_ssu_{{N}}(_ckd_a, _ckd_b, _ckd_res);
		}
		return _ckd_$OP_suu_{{N}}(_ckd_a, _ckd_b, _ckd_res);
	} else if (_ckd_bsigned) {
		return _ckd_$OP_usu_{{N}}(_ckd_a, _ckd_b, _ckd_res);
	}
	return _ckd_$OP_uuu_{{N}}(_ckd_a, _ckd_b, _ckd_res);
}

_ckd_fconst {{V.SC}} _ckd_$OP_2_{{S}}(_ckd_arg_{{U}} _ckd_a, _ckd_arg_{{U}} _ckd_b) {
	{{V.SC}} _ckd_tmp;
	{{V.UT}} _ckd_utmp;
	ckd_overflow(_ckd_tmp) = _ckd_$OP_{{N}}_choose_s(
			_ckd_a._ckd_Signed, _ckd_b._ckd_Signed, _ckd_a._ckd_Value, _ckd_b._ckd_Value, &_ckd_utmp)
			|| _ckd_a._ckd_Overflow || _ckd_b._ckd_Overflow;
	ckd_value(_ckd_tmp) = _ckd_utmp;
	return _ckd_tmp;
}

_ckd_fconst {{V.UC}} _ckd_$OP_2_{{U}}(_ckd_arg_{{U}} _ckd_a, _ckd_arg_{{U}} _ckd_b) {
	{{V.UC}} _ckd_tmp;
	ckd_overflow(_ckd_tmp) = _ckd_$OP_{{N}}_choose_u(
			_ckd_a._ckd_Signed, _ckd_b._ckd_Signed, _ckd_a._ckd_Value, _ckd_b._ckd_Value, &ckd_value(_ckd_tmp))
			|| _ckd_a._ckd_Overflow || _ckd_b._ckd_Overflow;
	return _ckd_tmp;
}

	{% call(B) L.foreach_TYPE(char=1) %}
		{# ###if OPERATIONEXISTS(V, B)### #}
		{% if V.HALFIDX >= B.HALFIDX %}
{#
/*
	Do calculations on two promoted signed types and represent the result in any $TYPE.
	These functions have a little bit of logic around `#if` macros to remove them.
	First, we need to remove the `#if` and `#endif` if one of types is int128, cause preprocessor can't handle int128.
	Then, we can remove the check when resulting type is greater, like `int * int -> long`.
	We can also remove the check when we know it's true, like `int * int -> int`.

	V - promoted type from both operands and the result
	B - any type that is the actual result type
*/
#}
		{% set noint128 = "int128" not in S and "int128" not in B.T %}
_ckd_fchpnt(1) bool _ckd_$OP_3_{{U}}_to_$TYPE({{B.T}} *_ckd_ret, _ckd_arg_{{U}} _ckd_a, _ckd_arg_{{U}} _ckd_b) {
	{{V.UT}} _ckd_tmp;
	const bool _ckd_of =
	{% if B.SIGNED == 1 %}
		_ckd_$OP_{{N}}_choose_s(
	{% elif B.SIGNED == 0 %}
		_ckd_$OP_{{N}}_choose_u(
	{% else %}
	{# In case of CHAR - we do not know if it is SIGNED or not beforehand, has to be checked in preprocessor #}
#if {{B.SIGNED}}
		_ckd_$OP_{{N}}_choose_s(
#else
		_ckd_$OP_{{N}}_choose_u(
#endif
	{% endif %}
			_ckd_a._ckd_Signed, _ckd_b._ckd_Signed, _ckd_a._ckd_Value, _ckd_b._ckd_Value, &_ckd_tmp)
			|| _ckd_a._ckd_Overflow || _ckd_b._ckd_Overflow
	{# /*
		In case the operation is done on promoted types, the _choose_s has no way of getting the maximum of promoted type
		Because of that, we check if the result type is within the ranges of the actual type.
		Signed has to be within signed, and unsigned has to be smaller than max.
	*/ #}
	{% if B.SIGNED or (not B.SIGNED and B.HALFIDX <= HALFIDX) %}
			{% set protect = not B.SIGNED and noint128 %}
			{% if protect %}
#if {{UMAX}} > {{B.MAX}}
			{% endif %}
#if {{B.SIGNED}}
			|| (_ckd_S)_ckd_tmp > {{B.MAX}} || (_ckd_S)_ckd_tmp < {{B.MIN}}
#else
			|| _ckd_tmp > {{B.MAX}}
#endif
			{% if protect %}
#endif
			{% endif %}
			;
	{% endif %}
	*_ckd_ret = ({{B.T}})_ckd_tmp;
	return _ckd_of;
}
		{% endif %}
	{% endcall %}

{% endcall %}

// ]]]
// Undef macros [[[
#undef _ckd_S
#undef _ckd_U
#undef _ckd_sign
// ]]]
	{% endif %}
{% endcall %}
// Additional 3 argument conversions [[[
{% call() L.foreach_OP() %}
	{% call(A) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
		{% call(B) L.foreach_TYPE(char=1, repl="$TYPE2") %}
			{% if B.CHAR or OPERATIONEXISTS(A, B) | int %}
_ckd_fchpnt(1) bool _ckd_$OP_3_$TYPE_to_c$TYPE2({{B.C}} *_ckd_ret, _ckd_arg_$TYPE _ckd_a, _ckd_arg_$TYPE _ckd_b) {
	return (ckd_overflow(*_ckd_ret) = _ckd_$OP_3_$TYPE_to_$TYPE2(&ckd_value(*_ckd_ret), _ckd_a, _ckd_b));
}
			{% endif %}
		{% endcall%}
	{% endcall %}
{% endcall %}
// ]]]]
// Helper macros [[[

{# There are 11 basic types. 22 types with checked integer types. 26 with int128. So type indexes range from 0 to 25. #}
{% set MUL = 100 %}
/**
 * @def _ckd_toidx(X)
 * @param X Any checked integer type or normal integer type.
 * @return Unique number of that type.
 * @brief Imagine all checked integer types and normal integer types are numbered.
 * This returns the number. char has 0.
 */
#define _ckd_toidx(X) \
			_Generic((X) \
	{% call(V) L.foreach_TYPE(char=1) %}
			,{{V.T}}: {{ V.T_IDX }} \
			,{{V.C}}: {{ V.C_IDX }} \
	{% endcall %}
			)

/**
 * @def _ckd_topidx(X)
 * @brief TO Promoted IDX.
 * @param X Any checked and unchecked integer type.
 * @return Number of type after integer promotions.
 * @see _ckd_toidx
 */
#define _ckd_topidx(X) \
			_Generic((X) \
	{% call(V) L.foreach_TYPE(char=1) %}
			,{{V.T}}: {# #}
				{%- if V.IDX == -1 -%}
					{#- char -#}
					12-2*({{ V.SIGNED }})
				{%- elif V.IDX < 6 and V.SIGNED -%}
					{#- int -#}
					10
				{%- elif V.IDX < 6 and not V.SIGNED -%}
					{#- unsigned int -#}
					12
				{%- else -%}
					{{ V.T_IDX }}
				{%- endif %} \
			,{{V.C}}: {{ V.C_IDX }} \
	{% endcall %}
			)

/**
 * @def _ckd_putoidx(X)
 * @brief Promoted Unsigned TO IDX. Same as _ckd_toidx, but only promoted unsigned types.
 * @param X Any promoted unsigned integer type.
 * @return Index of that type.
 * @see _ckd_toidx
 */
#define _ckd_putoidx(X) \
			_Generic((X) \
	{% call(V) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
			,{{V.T}}: {{ V.T_IDX }} \
	{% endcall %}
			)

/**
 * @def _ckd_topuntype(X)
 * @brief TO Promoted UNsigned TYPE
 * @param X Checked integer type or normal integer type.
 * @return Associated unsigned promoted integer type of the associated normal integer with value 0.
 */
#define _ckd_topuntype(X) \
			_Generic((X) \
	{% call(V) L.foreach_TYPE(promotedonly=1) %}
			,{{V.C}}: ({{V.UT}})0 \
			,{{V.T}}: ({{V.UT}})0 \
	{% endcall %}
			,default: 0u \
			)

/**
 * @def _ckd_totype(X)
 * @param X Checked integer type or normal integer type.
 * @return Associated normal integer type with value 0.
 */
#define _ckd_totype(X) \
			_Generic((X) \
	{% call(V) L.foreach_TYPE(char=1) %}
			,{{V.C}}: ({{V.T}})0 \
			,{{V.T}}: ({{V.T}})0 \
	{% endcall %}
			)

// ]]]]
// _ckd_arg creation [[[

{% call(A) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
	{% call(B) L.foreach_TYPE(char=1, repl="$TYPE2") %}
		{% if OPERATIONEXISTS(A, B) | int %}
			{# Automatically integer promote lower types #}
			{% if A.HALFIDX == B.HALFIDX %}
_ckd_fconst _ckd_arg_$TYPE _ckd_$TYPE2_to_arg_$TYPE({{B.T}} _ckd_v) {
	const _ckd_arg_$TYPE _ckd_ret = { _ckd_v, 0, {{B.SIGNED}} }; return _ckd_ret;
}
			{% endif %}
_ckd_fconst _ckd_arg_$TYPE _ckd_c$TYPE2_to_arg_$TYPE({{B.C}} _ckd_v) {
	const _ckd_arg_$TYPE _ckd_ret = { ckd_value(_ckd_v), ckd_overflow(_ckd_v), {{B.SIGNED}} }; return _ckd_ret;
}
		{% endif %}
	{% endcall %}
{% endcall %}

/**
 * @def _ckd_arg(TO, FROM)
 * @brief Converts any integer or checked integer type into an _ckd_arg of integer type TO.
 * @param TO Any integer type or checked integer type.
 * @param FROM Any integer type or checked integer type.
 * @return _ckd_arg structure that will be passed to other functions.
 */
#define _ckd_arg(TO, FROM) \
			_Generic((int(*)[{{MUL}} * _ckd_putoidx(TO) + _ckd_topidx(FROM)])0 \
	{% call(T) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
		{% call(F) L.foreach_TYPE(char=1, repl="$TYPE2") %}
			{% if OPERATIONEXISTS(T, F) | int %}
				{% if T.HALFIDX == F.HALFIDX %}
			,int(*)[{{MUL * T.T_IDX + F.T_IDX}}]: _ckd_$TYPE2_to_arg_$TYPE \
				{% elif F.T_IDX >= 10 %}
					{# Lower types still need to be handled, cause I can not filter them above #}
					{% if F.SIGNED %}
			,int(*)[{{MUL * T.T_IDX + F.T_IDX}}]: _ckd_{{T.SN}}_to_arg_$TYPE \
					{% else %}
			,int(*)[{{MUL * T.T_IDX + F.T_IDX}}]: _ckd_$TYPE_to_arg_$TYPE \
					{% endif %}
				{% endif %}
				{##}
			,int(*)[{{MUL * T.T_IDX + F.C_IDX}}]: _ckd_c$TYPE2_to_arg_$TYPE \
			{% endif %}
		{% endcall %}
	{% endcall %}
			)(FROM)

// ]]]
// Macros [[[
{% call() L.foreach_OP() %}

#define _ckd_$OP_3_IN(TOTYPE, r, a, b) \
			_Generic((int(*)[{{MUL}} * _ckd_putoidx(TOTYPE) + _ckd_toidx(*(r))])0 \
	{% call(A) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
		{% call(B) L.foreach_TYPE(char=1, repl="$TYPE2") %}
			{% if OPERATIONEXISTS(A, B) | int %}
			,int(*)[{{MUL * A.T_IDX + B.T_IDX}}]: _ckd_$OP_3_$TYPE_to_$TYPE2 \
			,int(*)[{{MUL * A.T_IDX + B.C_IDX}}]: _ckd_$OP_3_$TYPE_to_c$TYPE2 \
			{% endif %}
		{% endcall %}
	{% endcall %}
			)(r, \
			_ckd_arg(TOTYPE, a), \
			_ckd_arg(TOTYPE, b))

#define _ckd_nognu_$OP_3(r, a, b) \
		_ckd_$OP_3_IN(_ckd_topuntype(a) + _ckd_topuntype(b) + _ckd_topuntype(*(r)), r, a, b)

#define _ckd_nognu_$OP_2(a, b, _) \
			_Generic(_ckd_totype(a) + _ckd_totype(b) \
	{% call(A) L.foreach_TYPE(promotedonly=1) %}
			,{{A.T}}: _ckd_$OP_2_$TYPE \
	{% endcall %}
			)( \
			_ckd_arg(_ckd_topuntype(a) + _ckd_topuntype(b), a), \
			_ckd_arg(_ckd_topuntype(a) + _ckd_topuntype(b), b))

{% endcall %}

#define _ckd_nognu_mk(value, overflow) \
		_Generic((value) \
	{% call(A) L.foreach_TYPE() %}
		,{{A.T}}: ckd_mk_$TYPE_t \
	{% endcall %}
		)(value, overflow)

// ]]]
#endif
// vim: ft=c

