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
 * First everything is converted to unsigned types.
 */
// Header [[[
#define _CKDINT_NOGNU
#ifndef _CKDINT_H_
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
typedef struct {
	/// Represents the stored value.
	{{A.T}} _Value;
	/// Overflow?
	bool _Overflow;
	/// Was the original type signed?
	bool _Signed;
} _CKD_arg_$TYPE;
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
#define _S    {{V.ST}}
#define _U    {{V.UT}}
#define _SGN  ((_U)1 << (sizeof(_U) * CHAR_BIT - 1))
{# // __CDT__PARSER__
#undef _S
#define _S  int
#undef _U
#define _U  unsigned
#}
// ]]]
// Addition and substraction operations [[[

{# from https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L713 #}
_CKD_fchpnt(3) bool _CKD_add_sss_{{N}}(_U _S1, _U _S2, _U *_Res) {
	*_Res = _S1 + _S2;
	return (_S)_S2 < 0 ? (_S)*_Res > (_S)_S1 : (_S)*_Res < (_S)_S1;
}

_CKD_fchpnt(3) bool _CKD_sub_sss_{{N}}(_U _S1, _U _S2, _U *_Res) {
	*_Res = _S1 - _S2;
	{# https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1058 #}
	return (_S1 ^ _S2) & ~(*_Res ^ _S2) & _SGN;
	{# return _S2 < 0 ? *_Res < _S1 : *_Res > _S2; #}
}

_CKD_fchpnt(3) bool _CKD_add_uuu_{{N}}(_U _U1, _U _U2, _U *_Res) {
	*_Res = _U1 + _U2;
	return *_Res < _U1;
}

_CKD_fchpnt(3) bool _CKD_sub_uuu_{{N}}(_U _U1, _U _U2, _U *_Res) {
	*_Res = _U1 - _U2;
	return *_Res > _U1;
}

_CKD_fchpnt(3) bool _CKD_add_sus_{{N}}(_U _S1, _U _U2, _U *_Res) {
	*_Res = _S1 + _U2;
	return (*_Res ^ _SGN) < _U2;
}

_CKD_fchpnt(3) bool _CKD_add_suu_{{N}}(_U _S1, _U _U2, _U *_Res) {
	*_Res = _S1 + _U2;
	_S1 += _SGN;
	return (*_Res ^ _U2) & ~(_S1 ^ _U2) & _SGN;
}

_CKD_fchpnt(3) bool _CKD_sub_sus_{{N}}(_U _S1, _U _U2, _U *_Res) {
	*_Res = _S1 - _U2;
	return _U2 > ((_U)_S1 ^ _SGN);
}

_CKD_fchpnt(3) bool _CKD_sub_suu_{{N}}(_U _S1, _U _U2, _U *_Res) {
	*_Res = _S1 - _U2;
	return (_S)_S1 < 0 || _U2 > _S1;
}

_CKD_fchpnt(3) bool _CKD_sub_uss_{{N}}(_U _U1, _U _S2, _U *_Res) {
	*_Res = _U1 - _S2;
	return _U1 >= (_S2 ^ _SGN);
}

_CKD_fchpnt(3) bool _CKD_sub_usu_{{N}}(_U _U1, _U _S2, _U *_Res) {
	const _U _T1 = _U1 ^ _SGN;
	const _U _T2 = _T1 - _S2;
	*_Res = _T2 ^ _SGN;
	return (_S)_S2 < 0 ? (_S)_T2 < (_S)_T1 : (_S)_T2 > (_S)_T1;
}

_CKD_fchpnt(3) bool _CKD_add_ssu_{{N}}(_U _S1, _U _S2, _U *_Res) {
	*_Res = _S1 + _S2;
	return (_S)_S2 < 0 ? ((_S)(_S1 | *_Res) < 0) : ((_S)(_S1 & *_Res) < 0);
}

_CKD_fchpnt(3) bool _CKD_add_uus_{{N}}(_U _U1, _U _U2, _U *_Res) {
	*_Res = _U1 + _U2;
	return *_Res < _U2 || (_S)*_Res < 0;
}

_CKD_fchpnt(3) bool _CKD_sub_uus_{{N}}(_U _U1, _U _U2, _U *_Res) {
	*_Res = _U1 - _U2;
	return _U1 >= _U2 ? (_S)*_Res < 0 : (_S)*_Res >= 0;
}

_CKD_fchpnt(3) bool _CKD_sub_ssu_{{N}}(_U _S1, _U _S2, _U *_Res) {
	*_Res = _S1 - _S2;
	return (_S)_S2 >= 0 ? ((_S)(_S1 | *_Res) < 0) : ((_S)(_S1 & *_Res) < 0);
}

_CKD_fchpnt(3) bool _CKD_add_uss_{{N}}(_U _U1, _U _S1, _U *_Res) {
	return _CKD_add_sus_{{N}}(_S1, _U1, _Res);
}

_CKD_fchpnt(3) bool _CKD_add_usu_{{N}}(_U _U1, _U _S1, _U *_Res) {
	return _CKD_add_suu_{{N}}(_S1, _U1, _Res);
}

// ]]]
// Multiplication [[[

{# https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow #}
_CKD_fconst bool _CKD_ovf_signed_{{N}}(_S _A, _S _B) {
	return _A > 0 ? _B > 0 ? (_A > {{MAX}} / _B) : (_B < {{MIN}} / _A) : _B > 0 ? (_A < {{MIN}} / _B) : (_A != 0 && _B < {{MAX}} / _A);
}

{# https://stackoverflow.com/a/1815391/9072753 #}
_CKD_fconst bool _CKD_ovf_unsigned_{{N}}(_U _A, _U _B) {
	return _A != 0 && _B > {{UMAX}} / _A;
}

{# https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1286 #}

_CKD_fchpnt(3) bool _CKD_mul_sss_{{N}}(_U _S1, _U _S2, _U *_Res) {
	*_Res = _S1 * _S2;
	return _CKD_ovf_signed_{{N}}(_S1, _S2);
}

_CKD_fchpnt(3) bool _CKD_mul_uuu_{{N}}(_U _U1, _U _U2, _U *_Res) {
	*_Res = _U1 * _U2;
	return _CKD_ovf_unsigned_{{N}}(_U1, _U2);
}

_CKD_fchpnt(3) bool _CKD_mul_suu_{{N}}(_U _S1, _U _U2, _U *_Res) {
	*_Res = _S1 * _U2;
	return ((_S) _S1 < 0 && _U2) || _CKD_ovf_unsigned_{{N}}(_S1, _U2);
}

_CKD_fchpnt(3) bool _CKD_mul_uus_{{N}}(_U _U1, _U _U2, _U *_Res) {
	*_Res = _U1 * _U2;
	return (_S)*_Res < 0 || _CKD_ovf_unsigned_{{N}}(_U1, _U2);
}

_CKD_fchpnt(3) bool _CKD_mul_sus_{{N}}(_U _S1, _U _U2, _U *_Res) {
	*_Res = _S1 * _U2;
	return (_S)_U2 >= 0 ? _CKD_ovf_signed_{{N}}(_S1, _U2) : (_S1 && ((_S)_S1 != -1 || _U2 != *_Res));
}

_CKD_fchpnt(3) bool _CKD_mul_ssu_{{N}}(_U _S1, _U _S2, _U *_Res) {
	const _U _T1 = (_S)(_S1 & _S2) < 0 ? (-_S1) : _S1;
	const _U _T2 = (_S)(_S1 & _S2) < 0 ? (-_S2) : _S2;
	*_Res = _T1 * _T2;
	return (_S)(_S1 ^ _S2) < 0 ? (_S1 && _S2) : _CKD_ovf_signed_{{N}}(_T1, _T2);
}

_CKD_fchpnt(3) bool _CKD_mul_uss_{{N}}(_U _U1, _U _S2, _U *_Res) {
	return _CKD_mul_sus_{{N}}(_S2, _U1, _Res);
}

_CKD_fchpnt(3) bool _CKD_mul_usu_{{N}}(_U _U1, _U _S2, _U *_Res) {
	return _CKD_mul_suu_{{N}}(_S2, _U1, _Res);
}

/* ------------------------------------------------------------------------- */

{% call() L.foreach_OP() %}
_CKD_fchpnt(6) bool _CKD_$OP_{{N}}_choose(bool asigned, bool bsigned, bool ressigned, _U _A, _U _B, _U *_Res) {
	if (asigned) {
		if (bsigned) {
			if (ressigned) {
				return _CKD_$OP_sss_{{N}}(_A, _B, _Res);
			}
			return _CKD_$OP_ssu_{{N}}(_A, _B, _Res);
		} else {
			if (ressigned) {
				return _CKD_$OP_sus_{{N}}(_A, _B, _Res);
			}
		}
		return _CKD_$OP_suu_{{N}}(_A, _B, _Res);
	} else {
		if (bsigned) {
			if (ressigned) {
				return _CKD_$OP_uss_{{N}}(_A, _B, _Res);
			}
			return _CKD_$OP_usu_{{N}}(_A, _B, _Res);
		} else {
			if (ressigned) {
				return _CKD_$OP_uus_{{N}}(_A, _B, _Res);
			}
		}
	}
	return _CKD_$OP_uuu_{{N}}(_A, _B, _Res);
}

_CKD_fconst {{V.SC}} _CKD_$OP_2_{{S}}(_CKD_arg_{{U}} _A, _CKD_arg_{{U}} _B) {
	{{V.SC}} _Tmp;
	ckd_overflow(_Tmp) = _CKD_$OP_{{N}}_choose(_A._Signed, _B._Signed, 1, _A._Value, _B._Value, (_U*)&ckd_value(_Tmp)) || _A._Overflow || _B._Overflow;
	return _Tmp;
}

_CKD_fconst {{V.UC}} _CKD_$OP_2_{{U}}(_CKD_arg_{{U}} _A, _CKD_arg_{{U}} _B) {
	{{V.UC}} _Tmp;
	ckd_overflow(_Tmp) = _CKD_$OP_{{N}}_choose(_A._Signed, _B._Signed, 0, _A._Value, _B._Value, &ckd_value(_Tmp)) || _A._Overflow || _B._Overflow;
	return _Tmp;
}

	{% call(B) L.foreach_TYPE(char=1) %}
		{# if OPERATIONEXISTS(V, B) #}
		{% if V.HALFIDX >= B.HALFIDX %}
{#
/*
	Do calculations on two promoted signed types and represent the result in any $TYPE.
	These functions have a little bit of logic around `#if` macros to remove them.
	First, we need to remove the `#if` and `#endif` if one of types is int128, cause preprocessor can't handle int128.
	Then, we can remove the check when resulting type is greater, like `int * int -> long`.
	We can also remove the check when we know it's true, like `int * int -> int`.
*/
#}
		{% set noint128 = "int128" not in S and "int128" not in B.T %}
_CKD_fchpnt(1) bool _CKD_$OP_3_{{U}}_to_$TYPE({{B.T}} *_Ret, _CKD_arg_{{U}} _A, _CKD_arg_{{U}} _B) {
	{{V.UT}} _Tmp;
	const bool _Opovf = _CKD_$OP_{{N}}_choose(_A._Signed, _B._Signed, {{B.SIGNED}}, _A._Value, _B._Value, &_Tmp)
	{% if B.SIGNED or (not B.SIGNED and B.HALFIDX <= HALFIDX) %}
			{% set protect = not B.SIGNED and noint128 %}
			{% if protect %}
#if {{UMAX}} > {{B.MAX}}
			{% endif %}
			|| (_U) _Tmp > (_U) {{B.MAX}}
			{% if protect %}
#endif
			{% endif %}
	{% endif %}
			|| _A._Overflow || _B._Overflow;
	*_Ret = ({{B.T}}) _Tmp;
	return _Opovf;
}
		{% endif %}
	{% endcall %}

{% endcall %}

// ]]]
// Undef macros [[[
#undef _S
#undef _U
#undef _SGN
// ]]]
	{% endif %}
{% endcall %}
// Additional 3 argument conversions [[[
{% call() L.foreach_OP() %}
	{% call(A) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
		{% call(B) L.foreach_TYPE(char=1, repl="$TYPE2") %}
			{% if B.CHAR or OPERATIONEXISTS(A, B) | int %}
_CKD_fchpnt(1) bool _CKD_$OP_3_$TYPE_to_c$TYPE2({{B.C}} *_Ret, _CKD_arg_$TYPE a, _CKD_arg_$TYPE b) {
	return (ckd_overflow(*_Ret) = _CKD_$OP_3_$TYPE_to_$TYPE2(&ckd_value(*_Ret), a, b));
}
			{% endif %}
		{% endcall%}
	{% endcall %}
{% endcall %}
// ]]]]
// Helper macros [[[

{% call(A) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
	{% call(B) L.foreach_TYPE(char=1, repl="$TYPE2") %}
		{% if OPERATIONEXISTS(A, B) | int %}
_CKD_fconst _CKD_arg_$TYPE _CKD_$TYPE2_to_arg_$TYPE({{B.T}} _CKD_v) {
	const _CKD_arg_$TYPE _CKD_ret = { _CKD_v, 0, {{B.SIGNED}} }; return _CKD_ret;
}
_CKD_fconst _CKD_arg_$TYPE _CKD_c$TYPE2_to_arg_$TYPE({{B.C}} _CKD_v) {
	const _CKD_arg_$TYPE _CKD_ret = { ckd_value(_CKD_v), ckd_overflow(_CKD_v), {{B.SIGNED}} }; return _CKD_ret;
}
		{% endif %}
	{% endcall %}
{% endcall %}

/**
 * @define _CKD_topuntype(X)
 * @brief TO Promoted UNsigned TYPE
 * @param X Checked integer type or normal integer type.
 * @return Associated unsigned promoted integer type of the associated normal integer with value 0.
 */
#define _CKD_topuntype(X) \
        _Generic((X) \
{% call(V) L.foreach_TYPE(char=1) %}
	{% if not V.PROMOTED %}
        ,{{V.C}}: (unsigned)0 \
        ,{{V.T}}: (unsigned)0 \
	{% else %}
        ,{{V.C}}: ({{V.UT}})0 \
        ,{{V.T}}: ({{V.UT}})0 \
	{% endif %}
{% endcall %}
		)

/**
 * @define _CKD_totype(X)
 * @param X Checked integer type or normal integer type.
 * @return Associated normal integer type with value 0.
 */
#define _CKD_totype(X) \
        _Generic((X) \
{% call(V) L.foreach_TYPE(char=1) %}
        ,{{V.C}}: ({{V.T}})0 \
        ,{{V.T}}: ({{V.T}})0 \
{% endcall %}
		)

/**
 * @define _CKD_arg(TO, FROM)
 * @brief Converts any integer or checked integer type into an _CKD_arg of integer type TO.
 * @param TO Any integer type or checked integer type.
 * @param FROM Any integer type or checked integer type.
 * @return _CKD_arg structure that will be passed to other functions.
 *
 * This is what makes nested invokations like `ckd_add(ckd_add(....), ..)` the slowest.
 * It's because FROM is expanded 4 times here.
 */
#define _CKD_arg(TO, FROM) \
			_Generic((TO) \
	{% call(A) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
			,{{A.T}}: \
				_Generic((FROM) \
		{% call(B) L.foreach_TYPE(char=1, repl="$TYPE2") %}
			{% if OPERATIONEXISTS(A, B) | int %}
				,{{B.T}}: _CKD_$TYPE2_to_arg_$TYPE \
				,{{B.C}}: _CKD_c$TYPE2_to_arg_$TYPE \
			{% else %}
				,{{B.T}}: /*unreachable*/-1 \
				,{{B.C}}: /*unreachable*/-1 \
			{% endif %}
		{% endcall %}
				) \
	{% endcall %}
			)(FROM)

// ]]]
// Macros [[[
{% call() L.foreach_OP() %}

#define _CKD_$OP_3(r, a, b) \
			_Generic( \
				_CKD_topuntype(a) + _CKD_topuntype(b) + _CKD_topuntype(*(r)) \
	{% call(A) L.foreach_TYPE(promotedonly=1, unsignedonly=1) %}
			,{{A.T}}: _Generic(*(r) \
		{% call(B) L.foreach_TYPE(char=1, repl="$TYPE2") %}
			{% if OPERATIONEXISTS(A, B) | int %}
				,{{B.T}}:  _CKD_$OP_3_$TYPE_to_$TYPE2 \
				,{{B.C}}: _CKD_$OP_3_$TYPE_to_c$TYPE2 \
			{% else %}
				,{{B.T}}: /*unreachable*/-1 \
				,{{B.C}}: /*unreachable*/-1 \
			{% endif %}
		{% endcall %}
				) \
	{% endcall %}
			)(r, _CKD_arg( \
					_CKD_topuntype(a) + _CKD_topuntype(b) + _CKD_topuntype(*(r)) \
				, a), _CKD_arg( \
					_CKD_topuntype(a) + _CKD_topuntype(b) + _CKD_topuntype(*(r)) \
				, b))

#define _CKD_$OP_2(a, b) \
			_Generic(_CKD_totype(a) + _CKD_totype(b) \
	{% call(A) L.foreach_TYPE(promotedonly=1) %}
			,{{A.T}}: _CKD_$OP_2_$TYPE \
	{% endcall %}
			)( \
			_CKD_arg(_CKD_topuntype(a) + _CKD_topuntype(b), a), \
			_CKD_arg(_CKD_topuntype(a) + _CKD_topuntype(b), b))

{% endcall %}

// ]]]
// vim: ft=c

