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
// Init macros [[[
// Signed minimum and maximum!
// TODO: Add _ckd_ prefix to S and U symbols.
#define S    signed char
#define U    unsigned char
#define _ckd_SGN  ((U)1 << (sizeof(U) * CHAR_BIT - 1))
// ]]]
// Addition and substraction operations [[[

// from https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L713
_ckd_fchpnt bool _ckd_add_sss_schar(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? (S)*res > (S)s1 : (S)*res < (S)s1;
}

_ckd_fchpnt bool _ckd_sub_sss_schar(U s1, U s2, U *res) {
	*res = s1 - s2;
	// taken from
	// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1058
	return (s1 ^ s2) & ~(*res ^ s2) & _ckd_SGN;
	// return s2 < 0 ? *res < s1 : *res > s2;
}

_ckd_fchpnt bool _ckd_add_uuu_schar(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u1;
}

_ckd_fchpnt bool _ckd_sub_uuu_schar(U u1, U u2, U *res) {
	*res = u1 - u2;
	return *res > u1;
}

_ckd_fchpnt bool _ckd_add_sus_schar(U s1, U u2, U *res) {
	*res = s1 + u2;
	return (*res ^ _ckd_SGN) < u2;
}

_ckd_fchpnt bool _ckd_add_suu_schar(U s1, U u2, U *res) {
	*res = s1 + u2;
	s1 += _ckd_SGN;
	return (*res ^ u2) & ~(s1 ^ u2) & _ckd_SGN;
}

_ckd_fchpnt bool _ckd_sub_sus_schar(U s1, U u2, U *res) {
	*res = s1 - u2;
	return u2 > ((U)s1 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_suu_schar(U s1, U u2, U *res) {
	*res = s1 - u2;
	return (S)s1 < 0 || u2 > s1;
}

_ckd_fchpnt bool _ckd_sub_uss_schar(U u1, U s2, U *res) {
	*res = u1 - s2;
	return u1 >= (s2 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_usu_schar(U u1, U s2, U *res) {
	U t1 = u1 ^ _ckd_SGN;
	U t2 = t1 - s2;
	*res = t2 ^ _ckd_SGN;
	return (S)s2 < 0 ? (S)t2 < (S)t1 : (S)t2 > (S)t1;
}

_ckd_fchpnt bool _ckd_add_ssu_schar(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uus_schar(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u2 || (S)*res < 0;
}

_ckd_fchpnt bool _ckd_sub_uus_schar(U u1, U u2, U *res) {
	*res = u1 - u2;
	return u1 >= u2 ? (S)*res < 0 : (S)*res >= 0;
}

_ckd_fchpnt bool _ckd_sub_ssu_schar(U s1, U s2, U *res) {
	*res = s1 - s2;
	return (S)s2 >= 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uss_schar(U u1, U s1, U *res) {
	return _ckd_add_sus_schar(s1, u1, res);
}

_ckd_fchpnt bool _ckd_add_usu_schar(U u1, U s1, U *res) {
	return _ckd_add_suu_schar(s1, u1, res);
}

// ]]]
// Multiplication [[[

// https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
_ckd_fconst bool _ckd_ovf_signed_schar(S a, S b) {
	if (a > 0) {
		if (b > 0) {
			if (a > SCHAR_MAX / b) { // a positive, b positive
				return 1;
			}
		} else {
			if (b < SCHAR_MIN / a) { // a positive, b not positive
				return 1;
			}
		}
	} else {
		if (b > 0) {
			if (a < SCHAR_MIN / b) { // a not positive, b positive
				return 1;
			}
		} else {
			if (a != 0 && b < SCHAR_MAX / a) { // a not positive, b not positive
				return 1;
			}
		}
	}
	return 0;
}

// https://stackoverflow.com/a/1815391/9072753
_ckd_fconst bool _ckd_ovf_unsigned_schar(U a, U b) {
	return a != 0 && b > UCHAR_MAX / a;
}

// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1286

_ckd_fchpnt bool _ckd_mul_sss_schar(U s1, U s2, U *res) {
	*res = s1 * s2;
	return _ckd_ovf_signed_schar(s1, s2);
}

_ckd_fchpnt bool _ckd_mul_uuu_schar(U u1, U u2, U *res) {
	*res = u1 * u2;
	return _ckd_ovf_unsigned_schar(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_suu_schar(U s1, U u2, U *res) {
	*res = s1 * u2;
	return ((S) s1 < 0 && u2) || _ckd_ovf_unsigned_schar(s1, u2);
}

_ckd_fchpnt bool _ckd_mul_uus_schar(U u1, U u2, U *res) {
	*res = u1 * u2;
	return (S)*res < 0 || _ckd_ovf_unsigned_schar(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_sus_schar(U s1, U u2, U *res) {
	*res = s1 * u2;
	return (S)u2 >= 0 ? _ckd_ovf_signed_schar(s1, u2) : (s1 && ((S)s1 != -1 || u2 != *res));
}

_ckd_fchpnt bool _ckd_mul_ssu_schar(U s1, U s2, U *res) {
	U t1 = (S)(s1 & s2) < 0 ? (-s1) : s1;
	U t2 = (S)(s1 & s2) < 0 ? (-s2) : s2;
	*res = t1 * t2;
	return (S)(s1 ^ s2) < 0 ? (s1 && s2) : _ckd_ovf_signed_schar(t1, t2);
}

_ckd_fchpnt bool _ckd_mul_uss_schar(U u1, U s2, U *res) {
	return _ckd_mul_sus_schar(s2, u1, res);
}

_ckd_fchpnt bool _ckd_mul_usu_schar(U u1, U s2, U *res) {
	return _ckd_mul_suu_schar(s2, u1, res);
}

/* ------------------------------------------------------------------------- */

static bool (*const _ckd_add_schar_choose_arr[])(U, U, U*) = {
	&_ckd_add_sss_schar,
	&_ckd_add_ssu_schar,
	&_ckd_add_sus_schar,
	&_ckd_add_suu_schar,
	&_ckd_add_uss_schar,
	&_ckd_add_usu_schar,
	&_ckd_add_uus_schar,
	&_ckd_add_uuu_schar,
};

_ckd_fchpnt bool _ckd_add_schar_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_add_schar_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cschar _ckd_add_2_schar(unsigned idx, U a, U b, bool other) {
	_ckd_cschar tmp;
	ckd_overflow(tmp) = _ckd_add_schar_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cuchar _ckd_add_2_uchar(unsigned idx, U a, U b, bool other) {
	_ckd_cuchar tmp;
	ckd_overflow(tmp) = _ckd_add_schar_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_add_3_schar_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_schar_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_schar_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_schar_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_schar_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_schar_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_schar_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_schar_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_schar_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_schar_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uchar_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_add_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_sub_schar_choose_arr[])(U, U, U*) = {
	&_ckd_sub_sss_schar,
	&_ckd_sub_ssu_schar,
	&_ckd_sub_sus_schar,
	&_ckd_sub_suu_schar,
	&_ckd_sub_uss_schar,
	&_ckd_sub_usu_schar,
	&_ckd_sub_uus_schar,
	&_ckd_sub_uuu_schar,
};

_ckd_fchpnt bool _ckd_sub_schar_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_sub_schar_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cschar _ckd_sub_2_schar(unsigned idx, U a, U b, bool other) {
	_ckd_cschar tmp;
	ckd_overflow(tmp) = _ckd_sub_schar_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cuchar _ckd_sub_2_uchar(unsigned idx, U a, U b, bool other) {
	_ckd_cuchar tmp;
	ckd_overflow(tmp) = _ckd_sub_schar_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_sub_3_schar_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_schar_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_schar_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_schar_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_schar_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_schar_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_schar_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_schar_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_schar_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_schar_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uchar_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_sub_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_mul_schar_choose_arr[])(U, U, U*) = {
	&_ckd_mul_sss_schar,
	&_ckd_mul_ssu_schar,
	&_ckd_mul_sus_schar,
	&_ckd_mul_suu_schar,
	&_ckd_mul_uss_schar,
	&_ckd_mul_usu_schar,
	&_ckd_mul_uus_schar,
	&_ckd_mul_uuu_schar,
};

_ckd_fchpnt bool _ckd_mul_schar_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_mul_schar_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cschar _ckd_mul_2_schar(unsigned idx, U a, U b, bool other) {
	_ckd_cschar tmp;
	ckd_overflow(tmp) = _ckd_mul_schar_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cuchar _ckd_mul_2_uchar(unsigned idx, U a, U b, bool other) {
	_ckd_cuchar tmp;
	ckd_overflow(tmp) = _ckd_mul_schar_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_mul_3_schar_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_schar_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_schar_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_schar_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_schar_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_schar_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_schar_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_schar_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_schar_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_schar_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uchar_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uchar tmp;
	const bool opovf = _ckd_mul_schar_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}

// ]]]
// Undef macros [[[
#undef S
#undef U
#undef _ckd_SGN
// ]]]
// Init macros [[[
// Signed minimum and maximum!
// TODO: Add _ckd_ prefix to S and U symbols.
#define S    short
#define U    unsigned short
#define _ckd_SGN  ((U)1 << (sizeof(U) * CHAR_BIT - 1))
// ]]]
// Addition and substraction operations [[[

// from https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L713
_ckd_fchpnt bool _ckd_add_sss_shrt(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? (S)*res > (S)s1 : (S)*res < (S)s1;
}

_ckd_fchpnt bool _ckd_sub_sss_shrt(U s1, U s2, U *res) {
	*res = s1 - s2;
	// taken from
	// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1058
	return (s1 ^ s2) & ~(*res ^ s2) & _ckd_SGN;
	// return s2 < 0 ? *res < s1 : *res > s2;
}

_ckd_fchpnt bool _ckd_add_uuu_shrt(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u1;
}

_ckd_fchpnt bool _ckd_sub_uuu_shrt(U u1, U u2, U *res) {
	*res = u1 - u2;
	return *res > u1;
}

_ckd_fchpnt bool _ckd_add_sus_shrt(U s1, U u2, U *res) {
	*res = s1 + u2;
	return (*res ^ _ckd_SGN) < u2;
}

_ckd_fchpnt bool _ckd_add_suu_shrt(U s1, U u2, U *res) {
	*res = s1 + u2;
	s1 += _ckd_SGN;
	return (*res ^ u2) & ~(s1 ^ u2) & _ckd_SGN;
}

_ckd_fchpnt bool _ckd_sub_sus_shrt(U s1, U u2, U *res) {
	*res = s1 - u2;
	return u2 > ((U)s1 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_suu_shrt(U s1, U u2, U *res) {
	*res = s1 - u2;
	return (S)s1 < 0 || u2 > s1;
}

_ckd_fchpnt bool _ckd_sub_uss_shrt(U u1, U s2, U *res) {
	*res = u1 - s2;
	return u1 >= (s2 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_usu_shrt(U u1, U s2, U *res) {
	U t1 = u1 ^ _ckd_SGN;
	U t2 = t1 - s2;
	*res = t2 ^ _ckd_SGN;
	return (S)s2 < 0 ? (S)t2 < (S)t1 : (S)t2 > (S)t1;
}

_ckd_fchpnt bool _ckd_add_ssu_shrt(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uus_shrt(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u2 || (S)*res < 0;
}

_ckd_fchpnt bool _ckd_sub_uus_shrt(U u1, U u2, U *res) {
	*res = u1 - u2;
	return u1 >= u2 ? (S)*res < 0 : (S)*res >= 0;
}

_ckd_fchpnt bool _ckd_sub_ssu_shrt(U s1, U s2, U *res) {
	*res = s1 - s2;
	return (S)s2 >= 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uss_shrt(U u1, U s1, U *res) {
	return _ckd_add_sus_shrt(s1, u1, res);
}

_ckd_fchpnt bool _ckd_add_usu_shrt(U u1, U s1, U *res) {
	return _ckd_add_suu_shrt(s1, u1, res);
}

// ]]]
// Multiplication [[[

// https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
_ckd_fconst bool _ckd_ovf_signed_shrt(S a, S b) {
	if (a > 0) {
		if (b > 0) {
			if (a > SHRT_MAX / b) { // a positive, b positive
				return 1;
			}
		} else {
			if (b < SHRT_MIN / a) { // a positive, b not positive
				return 1;
			}
		}
	} else {
		if (b > 0) {
			if (a < SHRT_MIN / b) { // a not positive, b positive
				return 1;
			}
		} else {
			if (a != 0 && b < SHRT_MAX / a) { // a not positive, b not positive
				return 1;
			}
		}
	}
	return 0;
}

// https://stackoverflow.com/a/1815391/9072753
_ckd_fconst bool _ckd_ovf_unsigned_shrt(U a, U b) {
	return a != 0 && b > USHRT_MAX / a;
}

// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1286

_ckd_fchpnt bool _ckd_mul_sss_shrt(U s1, U s2, U *res) {
	*res = s1 * s2;
	return _ckd_ovf_signed_shrt(s1, s2);
}

_ckd_fchpnt bool _ckd_mul_uuu_shrt(U u1, U u2, U *res) {
	*res = u1 * u2;
	return _ckd_ovf_unsigned_shrt(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_suu_shrt(U s1, U u2, U *res) {
	*res = s1 * u2;
	return ((S) s1 < 0 && u2) || _ckd_ovf_unsigned_shrt(s1, u2);
}

_ckd_fchpnt bool _ckd_mul_uus_shrt(U u1, U u2, U *res) {
	*res = u1 * u2;
	return (S)*res < 0 || _ckd_ovf_unsigned_shrt(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_sus_shrt(U s1, U u2, U *res) {
	*res = s1 * u2;
	return (S)u2 >= 0 ? _ckd_ovf_signed_shrt(s1, u2) : (s1 && ((S)s1 != -1 || u2 != *res));
}

_ckd_fchpnt bool _ckd_mul_ssu_shrt(U s1, U s2, U *res) {
	U t1 = (S)(s1 & s2) < 0 ? (-s1) : s1;
	U t2 = (S)(s1 & s2) < 0 ? (-s2) : s2;
	*res = t1 * t2;
	return (S)(s1 ^ s2) < 0 ? (s1 && s2) : _ckd_ovf_signed_shrt(t1, t2);
}

_ckd_fchpnt bool _ckd_mul_uss_shrt(U u1, U s2, U *res) {
	return _ckd_mul_sus_shrt(s2, u1, res);
}

_ckd_fchpnt bool _ckd_mul_usu_shrt(U u1, U s2, U *res) {
	return _ckd_mul_suu_shrt(s2, u1, res);
}

/* ------------------------------------------------------------------------- */

static bool (*const _ckd_add_shrt_choose_arr[])(U, U, U*) = {
	&_ckd_add_sss_shrt,
	&_ckd_add_ssu_shrt,
	&_ckd_add_sus_shrt,
	&_ckd_add_suu_shrt,
	&_ckd_add_uss_shrt,
	&_ckd_add_usu_shrt,
	&_ckd_add_uus_shrt,
	&_ckd_add_uuu_shrt,
};

_ckd_fchpnt bool _ckd_add_shrt_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_add_shrt_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cshrt _ckd_add_2_shrt(unsigned idx, U a, U b, bool other) {
	_ckd_cshrt tmp;
	ckd_overflow(tmp) = _ckd_add_shrt_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cushrt _ckd_add_2_ushrt(unsigned idx, U a, U b, bool other) {
	_ckd_cushrt tmp;
	ckd_overflow(tmp) = _ckd_add_shrt_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_add_3_shrt_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_shrt_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_shrt_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_shrt_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_shrt_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_shrt_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_shrt_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_shrt_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_shrt_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_shrt_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ushrt_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_add_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_sub_shrt_choose_arr[])(U, U, U*) = {
	&_ckd_sub_sss_shrt,
	&_ckd_sub_ssu_shrt,
	&_ckd_sub_sus_shrt,
	&_ckd_sub_suu_shrt,
	&_ckd_sub_uss_shrt,
	&_ckd_sub_usu_shrt,
	&_ckd_sub_uus_shrt,
	&_ckd_sub_uuu_shrt,
};

_ckd_fchpnt bool _ckd_sub_shrt_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_sub_shrt_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cshrt _ckd_sub_2_shrt(unsigned idx, U a, U b, bool other) {
	_ckd_cshrt tmp;
	ckd_overflow(tmp) = _ckd_sub_shrt_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cushrt _ckd_sub_2_ushrt(unsigned idx, U a, U b, bool other) {
	_ckd_cushrt tmp;
	ckd_overflow(tmp) = _ckd_sub_shrt_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_sub_3_shrt_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_shrt_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_shrt_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_shrt_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_shrt_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_shrt_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_shrt_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_shrt_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_shrt_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_shrt_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ushrt_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_sub_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_mul_shrt_choose_arr[])(U, U, U*) = {
	&_ckd_mul_sss_shrt,
	&_ckd_mul_ssu_shrt,
	&_ckd_mul_sus_shrt,
	&_ckd_mul_suu_shrt,
	&_ckd_mul_uss_shrt,
	&_ckd_mul_usu_shrt,
	&_ckd_mul_uus_shrt,
	&_ckd_mul_uuu_shrt,
};

_ckd_fchpnt bool _ckd_mul_shrt_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_mul_shrt_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cshrt _ckd_mul_2_shrt(unsigned idx, U a, U b, bool other) {
	_ckd_cshrt tmp;
	ckd_overflow(tmp) = _ckd_mul_shrt_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cushrt _ckd_mul_2_ushrt(unsigned idx, U a, U b, bool other) {
	_ckd_cushrt tmp;
	ckd_overflow(tmp) = _ckd_mul_shrt_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_mul_3_shrt_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_shrt_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_shrt_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_shrt_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_shrt_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_shrt_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_shrt_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_shrt_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_shrt_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_shrt_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ushrt_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ushrt tmp;
	const bool opovf = _ckd_mul_shrt_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}

// ]]]
// Undef macros [[[
#undef S
#undef U
#undef _ckd_SGN
// ]]]
// Init macros [[[
// Signed minimum and maximum!
// TODO: Add _ckd_ prefix to S and U symbols.
#define S    int
#define U    unsigned int
#define _ckd_SGN  ((U)1 << (sizeof(U) * CHAR_BIT - 1))
// ]]]
// Addition and substraction operations [[[

// from https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L713
_ckd_fchpnt bool _ckd_add_sss_int(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? (S)*res > (S)s1 : (S)*res < (S)s1;
}

_ckd_fchpnt bool _ckd_sub_sss_int(U s1, U s2, U *res) {
	*res = s1 - s2;
	// taken from
	// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1058
	return (s1 ^ s2) & ~(*res ^ s2) & _ckd_SGN;
	// return s2 < 0 ? *res < s1 : *res > s2;
}

_ckd_fchpnt bool _ckd_add_uuu_int(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u1;
}

_ckd_fchpnt bool _ckd_sub_uuu_int(U u1, U u2, U *res) {
	*res = u1 - u2;
	return *res > u1;
}

_ckd_fchpnt bool _ckd_add_sus_int(U s1, U u2, U *res) {
	*res = s1 + u2;
	return (*res ^ _ckd_SGN) < u2;
}

_ckd_fchpnt bool _ckd_add_suu_int(U s1, U u2, U *res) {
	*res = s1 + u2;
	s1 += _ckd_SGN;
	return (*res ^ u2) & ~(s1 ^ u2) & _ckd_SGN;
}

_ckd_fchpnt bool _ckd_sub_sus_int(U s1, U u2, U *res) {
	*res = s1 - u2;
	return u2 > ((U)s1 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_suu_int(U s1, U u2, U *res) {
	*res = s1 - u2;
	return (S)s1 < 0 || u2 > s1;
}

_ckd_fchpnt bool _ckd_sub_uss_int(U u1, U s2, U *res) {
	*res = u1 - s2;
	return u1 >= (s2 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_usu_int(U u1, U s2, U *res) {
	U t1 = u1 ^ _ckd_SGN;
	U t2 = t1 - s2;
	*res = t2 ^ _ckd_SGN;
	return (S)s2 < 0 ? (S)t2 < (S)t1 : (S)t2 > (S)t1;
}

_ckd_fchpnt bool _ckd_add_ssu_int(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uus_int(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u2 || (S)*res < 0;
}

_ckd_fchpnt bool _ckd_sub_uus_int(U u1, U u2, U *res) {
	*res = u1 - u2;
	return u1 >= u2 ? (S)*res < 0 : (S)*res >= 0;
}

_ckd_fchpnt bool _ckd_sub_ssu_int(U s1, U s2, U *res) {
	*res = s1 - s2;
	return (S)s2 >= 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uss_int(U u1, U s1, U *res) {
	return _ckd_add_sus_int(s1, u1, res);
}

_ckd_fchpnt bool _ckd_add_usu_int(U u1, U s1, U *res) {
	return _ckd_add_suu_int(s1, u1, res);
}

// ]]]
// Multiplication [[[

// https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
_ckd_fconst bool _ckd_ovf_signed_int(S a, S b) {
	if (a > 0) {
		if (b > 0) {
			if (a > INT_MAX / b) { // a positive, b positive
				return 1;
			}
		} else {
			if (b < INT_MIN / a) { // a positive, b not positive
				return 1;
			}
		}
	} else {
		if (b > 0) {
			if (a < INT_MIN / b) { // a not positive, b positive
				return 1;
			}
		} else {
			if (a != 0 && b < INT_MAX / a) { // a not positive, b not positive
				return 1;
			}
		}
	}
	return 0;
}

// https://stackoverflow.com/a/1815391/9072753
_ckd_fconst bool _ckd_ovf_unsigned_int(U a, U b) {
	return a != 0 && b > UINT_MAX / a;
}

// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1286

_ckd_fchpnt bool _ckd_mul_sss_int(U s1, U s2, U *res) {
	*res = s1 * s2;
	return _ckd_ovf_signed_int(s1, s2);
}

_ckd_fchpnt bool _ckd_mul_uuu_int(U u1, U u2, U *res) {
	*res = u1 * u2;
	return _ckd_ovf_unsigned_int(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_suu_int(U s1, U u2, U *res) {
	*res = s1 * u2;
	return ((S) s1 < 0 && u2) || _ckd_ovf_unsigned_int(s1, u2);
}

_ckd_fchpnt bool _ckd_mul_uus_int(U u1, U u2, U *res) {
	*res = u1 * u2;
	return (S)*res < 0 || _ckd_ovf_unsigned_int(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_sus_int(U s1, U u2, U *res) {
	*res = s1 * u2;
	return (S)u2 >= 0 ? _ckd_ovf_signed_int(s1, u2) : (s1 && ((S)s1 != -1 || u2 != *res));
}

_ckd_fchpnt bool _ckd_mul_ssu_int(U s1, U s2, U *res) {
	U t1 = (S)(s1 & s2) < 0 ? (-s1) : s1;
	U t2 = (S)(s1 & s2) < 0 ? (-s2) : s2;
	*res = t1 * t2;
	return (S)(s1 ^ s2) < 0 ? (s1 && s2) : _ckd_ovf_signed_int(t1, t2);
}

_ckd_fchpnt bool _ckd_mul_uss_int(U u1, U s2, U *res) {
	return _ckd_mul_sus_int(s2, u1, res);
}

_ckd_fchpnt bool _ckd_mul_usu_int(U u1, U s2, U *res) {
	return _ckd_mul_suu_int(s2, u1, res);
}

/* ------------------------------------------------------------------------- */

static bool (*const _ckd_add_int_choose_arr[])(U, U, U*) = {
	&_ckd_add_sss_int,
	&_ckd_add_ssu_int,
	&_ckd_add_sus_int,
	&_ckd_add_suu_int,
	&_ckd_add_uss_int,
	&_ckd_add_usu_int,
	&_ckd_add_uus_int,
	&_ckd_add_uuu_int,
};

_ckd_fchpnt bool _ckd_add_int_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_add_int_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cint _ckd_add_2_int(unsigned idx, U a, U b, bool other) {
	_ckd_cint tmp;
	ckd_overflow(tmp) = _ckd_add_int_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cuint _ckd_add_2_uint(unsigned idx, U a, U b, bool other) {
	_ckd_cuint tmp;
	ckd_overflow(tmp) = _ckd_add_int_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_add_3_int_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_int_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_int_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SHRT_MIN > (S) tmp
			|| (S) tmp > (S) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SHRT_MIN > tmp
			|| tmp > (U) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_int_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_int_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_int_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_int_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_int_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_int_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_int_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_uint_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_add_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_sub_int_choose_arr[])(U, U, U*) = {
	&_ckd_sub_sss_int,
	&_ckd_sub_ssu_int,
	&_ckd_sub_sus_int,
	&_ckd_sub_suu_int,
	&_ckd_sub_uss_int,
	&_ckd_sub_usu_int,
	&_ckd_sub_uus_int,
	&_ckd_sub_uuu_int,
};

_ckd_fchpnt bool _ckd_sub_int_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_sub_int_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cint _ckd_sub_2_int(unsigned idx, U a, U b, bool other) {
	_ckd_cint tmp;
	ckd_overflow(tmp) = _ckd_sub_int_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cuint _ckd_sub_2_uint(unsigned idx, U a, U b, bool other) {
	_ckd_cuint tmp;
	ckd_overflow(tmp) = _ckd_sub_int_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_sub_3_int_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_int_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_int_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SHRT_MIN > (S) tmp
			|| (S) tmp > (S) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SHRT_MIN > tmp
			|| tmp > (U) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_int_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_int_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_int_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_int_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_int_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_int_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_int_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_uint_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_sub_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_mul_int_choose_arr[])(U, U, U*) = {
	&_ckd_mul_sss_int,
	&_ckd_mul_ssu_int,
	&_ckd_mul_sus_int,
	&_ckd_mul_suu_int,
	&_ckd_mul_uss_int,
	&_ckd_mul_usu_int,
	&_ckd_mul_uus_int,
	&_ckd_mul_uuu_int,
};

_ckd_fchpnt bool _ckd_mul_int_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_mul_int_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cint _ckd_mul_2_int(unsigned idx, U a, U b, bool other) {
	_ckd_cint tmp;
	ckd_overflow(tmp) = _ckd_mul_int_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cuint _ckd_mul_2_uint(unsigned idx, U a, U b, bool other) {
	_ckd_cuint tmp;
	ckd_overflow(tmp) = _ckd_mul_int_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_mul_3_int_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_int_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_int_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SHRT_MIN > (S) tmp
			|| (S) tmp > (S) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SHRT_MIN > tmp
			|| tmp > (U) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_int_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_int_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_int_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_int_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_int_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_int_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_int_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_uint_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_uint tmp;
	const bool opovf = _ckd_mul_int_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}

// ]]]
// Undef macros [[[
#undef S
#undef U
#undef _ckd_SGN
// ]]]
// Init macros [[[
// Signed minimum and maximum!
// TODO: Add _ckd_ prefix to S and U symbols.
#define S    long
#define U    unsigned long
#define _ckd_SGN  ((U)1 << (sizeof(U) * CHAR_BIT - 1))
// ]]]
// Addition and substraction operations [[[

// from https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L713
_ckd_fchpnt bool _ckd_add_sss_long(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? (S)*res > (S)s1 : (S)*res < (S)s1;
}

_ckd_fchpnt bool _ckd_sub_sss_long(U s1, U s2, U *res) {
	*res = s1 - s2;
	// taken from
	// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1058
	return (s1 ^ s2) & ~(*res ^ s2) & _ckd_SGN;
	// return s2 < 0 ? *res < s1 : *res > s2;
}

_ckd_fchpnt bool _ckd_add_uuu_long(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u1;
}

_ckd_fchpnt bool _ckd_sub_uuu_long(U u1, U u2, U *res) {
	*res = u1 - u2;
	return *res > u1;
}

_ckd_fchpnt bool _ckd_add_sus_long(U s1, U u2, U *res) {
	*res = s1 + u2;
	return (*res ^ _ckd_SGN) < u2;
}

_ckd_fchpnt bool _ckd_add_suu_long(U s1, U u2, U *res) {
	*res = s1 + u2;
	s1 += _ckd_SGN;
	return (*res ^ u2) & ~(s1 ^ u2) & _ckd_SGN;
}

_ckd_fchpnt bool _ckd_sub_sus_long(U s1, U u2, U *res) {
	*res = s1 - u2;
	return u2 > ((U)s1 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_suu_long(U s1, U u2, U *res) {
	*res = s1 - u2;
	return (S)s1 < 0 || u2 > s1;
}

_ckd_fchpnt bool _ckd_sub_uss_long(U u1, U s2, U *res) {
	*res = u1 - s2;
	return u1 >= (s2 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_usu_long(U u1, U s2, U *res) {
	U t1 = u1 ^ _ckd_SGN;
	U t2 = t1 - s2;
	*res = t2 ^ _ckd_SGN;
	return (S)s2 < 0 ? (S)t2 < (S)t1 : (S)t2 > (S)t1;
}

_ckd_fchpnt bool _ckd_add_ssu_long(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uus_long(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u2 || (S)*res < 0;
}

_ckd_fchpnt bool _ckd_sub_uus_long(U u1, U u2, U *res) {
	*res = u1 - u2;
	return u1 >= u2 ? (S)*res < 0 : (S)*res >= 0;
}

_ckd_fchpnt bool _ckd_sub_ssu_long(U s1, U s2, U *res) {
	*res = s1 - s2;
	return (S)s2 >= 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uss_long(U u1, U s1, U *res) {
	return _ckd_add_sus_long(s1, u1, res);
}

_ckd_fchpnt bool _ckd_add_usu_long(U u1, U s1, U *res) {
	return _ckd_add_suu_long(s1, u1, res);
}

// ]]]
// Multiplication [[[

// https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
_ckd_fconst bool _ckd_ovf_signed_long(S a, S b) {
	if (a > 0) {
		if (b > 0) {
			if (a > LONG_MAX / b) { // a positive, b positive
				return 1;
			}
		} else {
			if (b < LONG_MIN / a) { // a positive, b not positive
				return 1;
			}
		}
	} else {
		if (b > 0) {
			if (a < LONG_MIN / b) { // a not positive, b positive
				return 1;
			}
		} else {
			if (a != 0 && b < LONG_MAX / a) { // a not positive, b not positive
				return 1;
			}
		}
	}
	return 0;
}

// https://stackoverflow.com/a/1815391/9072753
_ckd_fconst bool _ckd_ovf_unsigned_long(U a, U b) {
	return a != 0 && b > ULONG_MAX / a;
}

// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1286

_ckd_fchpnt bool _ckd_mul_sss_long(U s1, U s2, U *res) {
	*res = s1 * s2;
	return _ckd_ovf_signed_long(s1, s2);
}

_ckd_fchpnt bool _ckd_mul_uuu_long(U u1, U u2, U *res) {
	*res = u1 * u2;
	return _ckd_ovf_unsigned_long(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_suu_long(U s1, U u2, U *res) {
	*res = s1 * u2;
	return ((S) s1 < 0 && u2) || _ckd_ovf_unsigned_long(s1, u2);
}

_ckd_fchpnt bool _ckd_mul_uus_long(U u1, U u2, U *res) {
	*res = u1 * u2;
	return (S)*res < 0 || _ckd_ovf_unsigned_long(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_sus_long(U s1, U u2, U *res) {
	*res = s1 * u2;
	return (S)u2 >= 0 ? _ckd_ovf_signed_long(s1, u2) : (s1 && ((S)s1 != -1 || u2 != *res));
}

_ckd_fchpnt bool _ckd_mul_ssu_long(U s1, U s2, U *res) {
	U t1 = (S)(s1 & s2) < 0 ? (-s1) : s1;
	U t2 = (S)(s1 & s2) < 0 ? (-s2) : s2;
	*res = t1 * t2;
	return (S)(s1 ^ s2) < 0 ? (s1 && s2) : _ckd_ovf_signed_long(t1, t2);
}

_ckd_fchpnt bool _ckd_mul_uss_long(U u1, U s2, U *res) {
	return _ckd_mul_sus_long(s2, u1, res);
}

_ckd_fchpnt bool _ckd_mul_usu_long(U u1, U s2, U *res) {
	return _ckd_mul_suu_long(s2, u1, res);
}

/* ------------------------------------------------------------------------- */

static bool (*const _ckd_add_long_choose_arr[])(U, U, U*) = {
	&_ckd_add_sss_long,
	&_ckd_add_ssu_long,
	&_ckd_add_sus_long,
	&_ckd_add_suu_long,
	&_ckd_add_uss_long,
	&_ckd_add_usu_long,
	&_ckd_add_uus_long,
	&_ckd_add_uuu_long,
};

_ckd_fchpnt bool _ckd_add_long_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_add_long_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_clong _ckd_add_2_long(unsigned idx, U a, U b, bool other) {
	_ckd_clong tmp;
	ckd_overflow(tmp) = _ckd_add_long_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_culong _ckd_add_2_ulong(unsigned idx, U a, U b, bool other) {
	_ckd_culong tmp;
	ckd_overflow(tmp) = _ckd_add_long_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_add_3_long_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_long_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_long_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SHRT_MIN > (S) tmp
			|| (S) tmp > (S) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SHRT_MIN > tmp
			|| tmp > (U) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_long_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_long_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) INT_MIN > (S) tmp
			|| (S) tmp > (S) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) INT_MIN > tmp
			|| tmp > (U) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_long_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_long_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_long_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_long_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_long_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ulong_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_add_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_sub_long_choose_arr[])(U, U, U*) = {
	&_ckd_sub_sss_long,
	&_ckd_sub_ssu_long,
	&_ckd_sub_sus_long,
	&_ckd_sub_suu_long,
	&_ckd_sub_uss_long,
	&_ckd_sub_usu_long,
	&_ckd_sub_uus_long,
	&_ckd_sub_uuu_long,
};

_ckd_fchpnt bool _ckd_sub_long_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_sub_long_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_clong _ckd_sub_2_long(unsigned idx, U a, U b, bool other) {
	_ckd_clong tmp;
	ckd_overflow(tmp) = _ckd_sub_long_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_culong _ckd_sub_2_ulong(unsigned idx, U a, U b, bool other) {
	_ckd_culong tmp;
	ckd_overflow(tmp) = _ckd_sub_long_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_sub_3_long_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_long_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_long_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SHRT_MIN > (S) tmp
			|| (S) tmp > (S) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SHRT_MIN > tmp
			|| tmp > (U) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_long_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_long_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) INT_MIN > (S) tmp
			|| (S) tmp > (S) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) INT_MIN > tmp
			|| tmp > (U) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_long_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_long_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_long_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_long_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_long_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ulong_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_sub_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_mul_long_choose_arr[])(U, U, U*) = {
	&_ckd_mul_sss_long,
	&_ckd_mul_ssu_long,
	&_ckd_mul_sus_long,
	&_ckd_mul_suu_long,
	&_ckd_mul_uss_long,
	&_ckd_mul_usu_long,
	&_ckd_mul_uus_long,
	&_ckd_mul_uuu_long,
};

_ckd_fchpnt bool _ckd_mul_long_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_mul_long_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_clong _ckd_mul_2_long(unsigned idx, U a, U b, bool other) {
	_ckd_clong tmp;
	ckd_overflow(tmp) = _ckd_mul_long_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_culong _ckd_mul_2_ulong(unsigned idx, U a, U b, bool other) {
	_ckd_culong tmp;
	ckd_overflow(tmp) = _ckd_mul_long_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_mul_3_long_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_long_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_long_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SHRT_MIN > (S) tmp
			|| (S) tmp > (S) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SHRT_MIN > tmp
			|| tmp > (U) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_long_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_long_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) INT_MIN > (S) tmp
			|| (S) tmp > (S) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) INT_MIN > tmp
			|| tmp > (U) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_long_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_long_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_long_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_long_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_long_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ulong_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ulong tmp;
	const bool opovf = _ckd_mul_long_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}

// ]]]
// Undef macros [[[
#undef S
#undef U
#undef _ckd_SGN
// ]]]
// Init macros [[[
// Signed minimum and maximum!
// TODO: Add _ckd_ prefix to S and U symbols.
#define S    long long
#define U    unsigned long long
#define _ckd_SGN  ((U)1 << (sizeof(U) * CHAR_BIT - 1))
// ]]]
// Addition and substraction operations [[[

// from https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L713
_ckd_fchpnt bool _ckd_add_sss_llong(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? (S)*res > (S)s1 : (S)*res < (S)s1;
}

_ckd_fchpnt bool _ckd_sub_sss_llong(U s1, U s2, U *res) {
	*res = s1 - s2;
	// taken from
	// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1058
	return (s1 ^ s2) & ~(*res ^ s2) & _ckd_SGN;
	// return s2 < 0 ? *res < s1 : *res > s2;
}

_ckd_fchpnt bool _ckd_add_uuu_llong(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u1;
}

_ckd_fchpnt bool _ckd_sub_uuu_llong(U u1, U u2, U *res) {
	*res = u1 - u2;
	return *res > u1;
}

_ckd_fchpnt bool _ckd_add_sus_llong(U s1, U u2, U *res) {
	*res = s1 + u2;
	return (*res ^ _ckd_SGN) < u2;
}

_ckd_fchpnt bool _ckd_add_suu_llong(U s1, U u2, U *res) {
	*res = s1 + u2;
	s1 += _ckd_SGN;
	return (*res ^ u2) & ~(s1 ^ u2) & _ckd_SGN;
}

_ckd_fchpnt bool _ckd_sub_sus_llong(U s1, U u2, U *res) {
	*res = s1 - u2;
	return u2 > ((U)s1 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_suu_llong(U s1, U u2, U *res) {
	*res = s1 - u2;
	return (S)s1 < 0 || u2 > s1;
}

_ckd_fchpnt bool _ckd_sub_uss_llong(U u1, U s2, U *res) {
	*res = u1 - s2;
	return u1 >= (s2 ^ _ckd_SGN);
}

_ckd_fchpnt bool _ckd_sub_usu_llong(U u1, U s2, U *res) {
	U t1 = u1 ^ _ckd_SGN;
	U t2 = t1 - s2;
	*res = t2 ^ _ckd_SGN;
	return (S)s2 < 0 ? (S)t2 < (S)t1 : (S)t2 > (S)t1;
}

_ckd_fchpnt bool _ckd_add_ssu_llong(U s1, U s2, U *res) {
	*res = s1 + s2;
	return (S)s2 < 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uus_llong(U u1, U u2, U *res) {
	*res = u1 + u2;
	return *res < u2 || (S)*res < 0;
}

_ckd_fchpnt bool _ckd_sub_uus_llong(U u1, U u2, U *res) {
	*res = u1 - u2;
	return u1 >= u2 ? (S)*res < 0 : (S)*res >= 0;
}

_ckd_fchpnt bool _ckd_sub_ssu_llong(U s1, U s2, U *res) {
	*res = s1 - s2;
	return (S)s2 >= 0 ? ((S)(s1 | *res) < 0) : ((S)(s1 & *res) < 0);
}

_ckd_fchpnt bool _ckd_add_uss_llong(U u1, U s1, U *res) {
	return _ckd_add_sus_llong(s1, u1, res);
}

_ckd_fchpnt bool _ckd_add_usu_llong(U u1, U s1, U *res) {
	return _ckd_add_suu_llong(s1, u1, res);
}

// ]]]
// Multiplication [[[

// https://wiki.sei.cmu.edu/confluence/display/c/INT32-C.+Ensure+that+operations+on+signed+integers+do+not+result+in+overflow
_ckd_fconst bool _ckd_ovf_signed_llong(S a, S b) {
	if (a > 0) {
		if (b > 0) {
			if (a > LLONG_MAX / b) { // a positive, b positive
				return 1;
			}
		} else {
			if (b < LLONG_MIN / a) { // a positive, b not positive
				return 1;
			}
		}
	} else {
		if (b > 0) {
			if (a < LLONG_MIN / b) { // a not positive, b positive
				return 1;
			}
		} else {
			if (a != 0 && b < LLONG_MAX / a) { // a not positive, b not positive
				return 1;
			}
		}
	}
	return 0;
}

// https://stackoverflow.com/a/1815391/9072753
_ckd_fconst bool _ckd_ovf_unsigned_llong(U a, U b) {
	return a != 0 && b > ULLONG_MAX / a;
}

// https://github.com/gcc-mirror/gcc/blob/16e2427f50c208dfe07d07f18009969502c25dc8/gcc/internal-fn.c#L1286

_ckd_fchpnt bool _ckd_mul_sss_llong(U s1, U s2, U *res) {
	*res = s1 * s2;
	return _ckd_ovf_signed_llong(s1, s2);
}

_ckd_fchpnt bool _ckd_mul_uuu_llong(U u1, U u2, U *res) {
	*res = u1 * u2;
	return _ckd_ovf_unsigned_llong(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_suu_llong(U s1, U u2, U *res) {
	*res = s1 * u2;
	return ((S) s1 < 0 && u2) || _ckd_ovf_unsigned_llong(s1, u2);
}

_ckd_fchpnt bool _ckd_mul_uus_llong(U u1, U u2, U *res) {
	*res = u1 * u2;
	return (S)*res < 0 || _ckd_ovf_unsigned_llong(u1, u2);
}

_ckd_fchpnt bool _ckd_mul_sus_llong(U s1, U u2, U *res) {
	*res = s1 * u2;
	return (S)u2 >= 0 ? _ckd_ovf_signed_llong(s1, u2) : (s1 && ((S)s1 != -1 || u2 != *res));
}

_ckd_fchpnt bool _ckd_mul_ssu_llong(U s1, U s2, U *res) {
	U t1 = (S)(s1 & s2) < 0 ? (-s1) : s1;
	U t2 = (S)(s1 & s2) < 0 ? (-s2) : s2;
	*res = t1 * t2;
	return (S)(s1 ^ s2) < 0 ? (s1 && s2) : _ckd_ovf_signed_llong(t1, t2);
}

_ckd_fchpnt bool _ckd_mul_uss_llong(U u1, U s2, U *res) {
	return _ckd_mul_sus_llong(s2, u1, res);
}

_ckd_fchpnt bool _ckd_mul_usu_llong(U u1, U s2, U *res) {
	return _ckd_mul_suu_llong(s2, u1, res);
}

/* ------------------------------------------------------------------------- */

static bool (*const _ckd_add_llong_choose_arr[])(U, U, U*) = {
	&_ckd_add_sss_llong,
	&_ckd_add_ssu_llong,
	&_ckd_add_sus_llong,
	&_ckd_add_suu_llong,
	&_ckd_add_uss_llong,
	&_ckd_add_usu_llong,
	&_ckd_add_uus_llong,
	&_ckd_add_uuu_llong,
};

_ckd_fchpnt bool _ckd_add_llong_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_add_llong_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cllong _ckd_add_2_llong(unsigned idx, U a, U b, bool other) {
	_ckd_cllong tmp;
	ckd_overflow(tmp) = _ckd_add_llong_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cullong _ckd_add_2_ullong(unsigned idx, U a, U b, bool other) {
	_ckd_cullong tmp;
	ckd_overflow(tmp) = _ckd_add_llong_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_add_3_llong_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_llong_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_llong_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SHRT_MIN > (S) tmp
			|| (S) tmp > (S) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SHRT_MIN > tmp
			|| tmp > (U) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_llong_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_llong_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) INT_MIN > (S) tmp
			|| (S) tmp > (S) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) INT_MIN > tmp
			|| tmp > (U) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_llong_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_llong_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) LONG_MIN > (S) tmp
			|| (S) tmp > (S) LONG_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) LONG_MIN > tmp
			|| tmp > (U) LONG_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_llong_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) ULONG_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) ULONG_MAX
			;
}
_ckd_fchpnt bool _ckd_add_3_llong_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_llong_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_add_3_ullong_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_add_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_sub_llong_choose_arr[])(U, U, U*) = {
	&_ckd_sub_sss_llong,
	&_ckd_sub_ssu_llong,
	&_ckd_sub_sus_llong,
	&_ckd_sub_suu_llong,
	&_ckd_sub_uss_llong,
	&_ckd_sub_usu_llong,
	&_ckd_sub_uus_llong,
	&_ckd_sub_uuu_llong,
};

_ckd_fchpnt bool _ckd_sub_llong_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_sub_llong_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cllong _ckd_sub_2_llong(unsigned idx, U a, U b, bool other) {
	_ckd_cllong tmp;
	ckd_overflow(tmp) = _ckd_sub_llong_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cullong _ckd_sub_2_ullong(unsigned idx, U a, U b, bool other) {
	_ckd_cullong tmp;
	ckd_overflow(tmp) = _ckd_sub_llong_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_sub_3_llong_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_llong_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_llong_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SHRT_MIN > (S) tmp
			|| (S) tmp > (S) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SHRT_MIN > tmp
			|| tmp > (U) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_llong_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_llong_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) INT_MIN > (S) tmp
			|| (S) tmp > (S) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) INT_MIN > tmp
			|| tmp > (U) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_llong_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_llong_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) LONG_MIN > (S) tmp
			|| (S) tmp > (S) LONG_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) LONG_MIN > tmp
			|| tmp > (U) LONG_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_llong_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) ULONG_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) ULONG_MAX
			;
}
_ckd_fchpnt bool _ckd_sub_3_llong_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_llong_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_sub_3_ullong_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_sub_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
static bool (*const _ckd_mul_llong_choose_arr[])(U, U, U*) = {
	&_ckd_mul_sss_llong,
	&_ckd_mul_ssu_llong,
	&_ckd_mul_sus_llong,
	&_ckd_mul_suu_llong,
	&_ckd_mul_uss_llong,
	&_ckd_mul_usu_llong,
	&_ckd_mul_uus_llong,
	&_ckd_mul_uuu_llong,
};

_ckd_fchpnt bool _ckd_mul_llong_choose(unsigned idx, U a, U b, U *res) {
	return _ckd_mul_llong_choose_arr[idx](a, b, res);
}

_ckd_fconst _ckd_cllong _ckd_mul_2_llong(unsigned idx, U a, U b, bool other) {
	_ckd_cllong tmp;
	ckd_overflow(tmp) = _ckd_mul_llong_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fconst _ckd_cullong _ckd_mul_2_ullong(unsigned idx, U a, U b, bool other) {
	_ckd_cullong tmp;
	ckd_overflow(tmp) = _ckd_mul_llong_choose(idx, a, b, (void*)&ckd_value(tmp)) || other;
	return tmp;
}

_ckd_fchpnt bool _ckd_mul_3_llong_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SCHAR_MIN > (S) tmp
			|| (S) tmp > (S) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_schar(_ckd_schar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SCHAR_MIN > tmp
			|| tmp > (U) SCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_llong_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_uchar(_ckd_uchar *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UCHAR_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_llong_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) SHRT_MIN > (S) tmp
			|| (S) tmp > (S) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_shrt(_ckd_shrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) SHRT_MIN > tmp
			|| tmp > (U) SHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_llong_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_ushrt(_ckd_ushrt *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) USHRT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_llong_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) INT_MIN > (S) tmp
			|| (S) tmp > (S) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_int(_ckd_int *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) INT_MIN > tmp
			|| tmp > (U) INT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_llong_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_uint(_ckd_uint *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) UINT_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_llong_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) LONG_MIN > (S) tmp
			|| (S) tmp > (S) LONG_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_long(_ckd_long *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (U) LONG_MIN > tmp
			|| tmp > (U) LONG_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_llong_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| (S) 0 > (S) tmp
			|| (S) tmp > (S) ULONG_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_ulong(_ckd_ulong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			|| tmp > (U) ULONG_MAX
			;
}
_ckd_fchpnt bool _ckd_mul_3_llong_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_llong(_ckd_llong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_llong_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}
_ckd_fchpnt bool _ckd_mul_3_ullong_to_ullong(_ckd_ullong *ret, unsigned idx, U a, U b, bool other) {
	_ckd_ullong tmp;
	const bool opovf = _ckd_mul_llong_choose(idx, a, b, &tmp);
	*ret = tmp;
	return opovf || other
			;
}

// ]]]
// Undef macros [[[
#undef S
#undef U
#undef _ckd_SGN
// ]]]
// Helper macros [[[

#define _ckd_issigned(T) \
		_Generic(_ckd_value(T), \
		_ckd_schar: 0, \
		_ckd_uchar: 1, \
		_ckd_shrt: 0, \
		_ckd_ushrt: 1, \
		_ckd_int: 0, \
		_ckd_uint: 1, \
		_ckd_long: 0, \
		_ckd_ulong: 1, \
		_ckd_llong: 0, \
		_ckd_ullong: 1)

#define _ckd_idx(a, b)  ( \
		_ckd_issigned(a) << 2 | \
		_ckd_issigned(b) << 1 | \
		_ckd_issigned(_ckd_value(a) + _ckd_value(b)) \
		)
// ]]]
// Macros [[[

#define _ckd_add_3(r, a, b) \
			_Generic(_ckd_value(a) + _ckd_value(b) + *(r), \
			_ckd_schar: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_schar_to_schar, \
				_ckd_uchar: _ckd_add_3_schar_to_uchar, \
				_ckd_shrt: _ckd_add_3_schar_to_shrt, \
				_ckd_ushrt: _ckd_add_3_schar_to_ushrt, \
				_ckd_int: _ckd_add_3_schar_to_int, \
				_ckd_uint: _ckd_add_3_schar_to_uint, \
				_ckd_long: _ckd_add_3_schar_to_long, \
				_ckd_ulong: _ckd_add_3_schar_to_ulong, \
				_ckd_llong: _ckd_add_3_schar_to_llong, \
				_ckd_ullong: _ckd_add_3_schar_to_ullong), \
			_ckd_uchar: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_uchar_to_schar, \
				_ckd_uchar: _ckd_add_3_uchar_to_uchar, \
				_ckd_shrt: _ckd_add_3_uchar_to_shrt, \
				_ckd_ushrt: _ckd_add_3_uchar_to_ushrt, \
				_ckd_int: _ckd_add_3_uchar_to_int, \
				_ckd_uint: _ckd_add_3_uchar_to_uint, \
				_ckd_long: _ckd_add_3_uchar_to_long, \
				_ckd_ulong: _ckd_add_3_uchar_to_ulong, \
				_ckd_llong: _ckd_add_3_uchar_to_llong, \
				_ckd_ullong: _ckd_add_3_uchar_to_ullong), \
			_ckd_shrt: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_shrt_to_schar, \
				_ckd_uchar: _ckd_add_3_shrt_to_uchar, \
				_ckd_shrt: _ckd_add_3_shrt_to_shrt, \
				_ckd_ushrt: _ckd_add_3_shrt_to_ushrt, \
				_ckd_int: _ckd_add_3_shrt_to_int, \
				_ckd_uint: _ckd_add_3_shrt_to_uint, \
				_ckd_long: _ckd_add_3_shrt_to_long, \
				_ckd_ulong: _ckd_add_3_shrt_to_ulong, \
				_ckd_llong: _ckd_add_3_shrt_to_llong, \
				_ckd_ullong: _ckd_add_3_shrt_to_ullong), \
			_ckd_ushrt: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_ushrt_to_schar, \
				_ckd_uchar: _ckd_add_3_ushrt_to_uchar, \
				_ckd_shrt: _ckd_add_3_ushrt_to_shrt, \
				_ckd_ushrt: _ckd_add_3_ushrt_to_ushrt, \
				_ckd_int: _ckd_add_3_ushrt_to_int, \
				_ckd_uint: _ckd_add_3_ushrt_to_uint, \
				_ckd_long: _ckd_add_3_ushrt_to_long, \
				_ckd_ulong: _ckd_add_3_ushrt_to_ulong, \
				_ckd_llong: _ckd_add_3_ushrt_to_llong, \
				_ckd_ullong: _ckd_add_3_ushrt_to_ullong), \
			_ckd_int: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_int_to_schar, \
				_ckd_uchar: _ckd_add_3_int_to_uchar, \
				_ckd_shrt: _ckd_add_3_int_to_shrt, \
				_ckd_ushrt: _ckd_add_3_int_to_ushrt, \
				_ckd_int: _ckd_add_3_int_to_int, \
				_ckd_uint: _ckd_add_3_int_to_uint, \
				_ckd_long: _ckd_add_3_int_to_long, \
				_ckd_ulong: _ckd_add_3_int_to_ulong, \
				_ckd_llong: _ckd_add_3_int_to_llong, \
				_ckd_ullong: _ckd_add_3_int_to_ullong), \
			_ckd_uint: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_uint_to_schar, \
				_ckd_uchar: _ckd_add_3_uint_to_uchar, \
				_ckd_shrt: _ckd_add_3_uint_to_shrt, \
				_ckd_ushrt: _ckd_add_3_uint_to_ushrt, \
				_ckd_int: _ckd_add_3_uint_to_int, \
				_ckd_uint: _ckd_add_3_uint_to_uint, \
				_ckd_long: _ckd_add_3_uint_to_long, \
				_ckd_ulong: _ckd_add_3_uint_to_ulong, \
				_ckd_llong: _ckd_add_3_uint_to_llong, \
				_ckd_ullong: _ckd_add_3_uint_to_ullong), \
			_ckd_long: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_long_to_schar, \
				_ckd_uchar: _ckd_add_3_long_to_uchar, \
				_ckd_shrt: _ckd_add_3_long_to_shrt, \
				_ckd_ushrt: _ckd_add_3_long_to_ushrt, \
				_ckd_int: _ckd_add_3_long_to_int, \
				_ckd_uint: _ckd_add_3_long_to_uint, \
				_ckd_long: _ckd_add_3_long_to_long, \
				_ckd_ulong: _ckd_add_3_long_to_ulong, \
				_ckd_llong: _ckd_add_3_long_to_llong, \
				_ckd_ullong: _ckd_add_3_long_to_ullong), \
			_ckd_ulong: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_ulong_to_schar, \
				_ckd_uchar: _ckd_add_3_ulong_to_uchar, \
				_ckd_shrt: _ckd_add_3_ulong_to_shrt, \
				_ckd_ushrt: _ckd_add_3_ulong_to_ushrt, \
				_ckd_int: _ckd_add_3_ulong_to_int, \
				_ckd_uint: _ckd_add_3_ulong_to_uint, \
				_ckd_long: _ckd_add_3_ulong_to_long, \
				_ckd_ulong: _ckd_add_3_ulong_to_ulong, \
				_ckd_llong: _ckd_add_3_ulong_to_llong, \
				_ckd_ullong: _ckd_add_3_ulong_to_ullong), \
			_ckd_llong: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_llong_to_schar, \
				_ckd_uchar: _ckd_add_3_llong_to_uchar, \
				_ckd_shrt: _ckd_add_3_llong_to_shrt, \
				_ckd_ushrt: _ckd_add_3_llong_to_ushrt, \
				_ckd_int: _ckd_add_3_llong_to_int, \
				_ckd_uint: _ckd_add_3_llong_to_uint, \
				_ckd_long: _ckd_add_3_llong_to_long, \
				_ckd_ulong: _ckd_add_3_llong_to_ulong, \
				_ckd_llong: _ckd_add_3_llong_to_llong, \
				_ckd_ullong: _ckd_add_3_llong_to_ullong), \
			_ckd_ullong: _Generic(*(r), \
				_ckd_schar: _ckd_add_3_ullong_to_schar, \
				_ckd_uchar: _ckd_add_3_ullong_to_uchar, \
				_ckd_shrt: _ckd_add_3_ullong_to_shrt, \
				_ckd_ushrt: _ckd_add_3_ullong_to_ushrt, \
				_ckd_int: _ckd_add_3_ullong_to_int, \
				_ckd_uint: _ckd_add_3_ullong_to_uint, \
				_ckd_long: _ckd_add_3_ullong_to_long, \
				_ckd_ulong: _ckd_add_3_ullong_to_ulong, \
				_ckd_llong: _ckd_add_3_ullong_to_llong, \
				_ckd_ullong: _ckd_add_3_ullong_to_ullong))(r, _ckd_idx(a, b), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))

#define _ckd_add_2(a, b) \
			_Generic(_ckd_value(a) + _ckd_value(b), \
			_ckd_schar: _ckd_add_2_schar, \
			_ckd_uchar: _ckd_add_2_uchar, \
			_ckd_shrt: _ckd_add_2_shrt, \
			_ckd_ushrt: _ckd_add_2_ushrt, \
			_ckd_int: _ckd_add_2_int, \
			_ckd_uint: _ckd_add_2_uint, \
			_ckd_long: _ckd_add_2_long, \
			_ckd_ulong: _ckd_add_2_ulong, \
			_ckd_llong: _ckd_add_2_llong, \
			_ckd_ullong: _ckd_add_2_ullong)(_ckd_idx(a, b), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))

#define _ckd_sub_3(r, a, b) \
			_Generic(_ckd_value(a) + _ckd_value(b) + *(r), \
			_ckd_schar: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_schar_to_schar, \
				_ckd_uchar: _ckd_sub_3_schar_to_uchar, \
				_ckd_shrt: _ckd_sub_3_schar_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_schar_to_ushrt, \
				_ckd_int: _ckd_sub_3_schar_to_int, \
				_ckd_uint: _ckd_sub_3_schar_to_uint, \
				_ckd_long: _ckd_sub_3_schar_to_long, \
				_ckd_ulong: _ckd_sub_3_schar_to_ulong, \
				_ckd_llong: _ckd_sub_3_schar_to_llong, \
				_ckd_ullong: _ckd_sub_3_schar_to_ullong), \
			_ckd_uchar: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_uchar_to_schar, \
				_ckd_uchar: _ckd_sub_3_uchar_to_uchar, \
				_ckd_shrt: _ckd_sub_3_uchar_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_uchar_to_ushrt, \
				_ckd_int: _ckd_sub_3_uchar_to_int, \
				_ckd_uint: _ckd_sub_3_uchar_to_uint, \
				_ckd_long: _ckd_sub_3_uchar_to_long, \
				_ckd_ulong: _ckd_sub_3_uchar_to_ulong, \
				_ckd_llong: _ckd_sub_3_uchar_to_llong, \
				_ckd_ullong: _ckd_sub_3_uchar_to_ullong), \
			_ckd_shrt: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_shrt_to_schar, \
				_ckd_uchar: _ckd_sub_3_shrt_to_uchar, \
				_ckd_shrt: _ckd_sub_3_shrt_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_shrt_to_ushrt, \
				_ckd_int: _ckd_sub_3_shrt_to_int, \
				_ckd_uint: _ckd_sub_3_shrt_to_uint, \
				_ckd_long: _ckd_sub_3_shrt_to_long, \
				_ckd_ulong: _ckd_sub_3_shrt_to_ulong, \
				_ckd_llong: _ckd_sub_3_shrt_to_llong, \
				_ckd_ullong: _ckd_sub_3_shrt_to_ullong), \
			_ckd_ushrt: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_ushrt_to_schar, \
				_ckd_uchar: _ckd_sub_3_ushrt_to_uchar, \
				_ckd_shrt: _ckd_sub_3_ushrt_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_ushrt_to_ushrt, \
				_ckd_int: _ckd_sub_3_ushrt_to_int, \
				_ckd_uint: _ckd_sub_3_ushrt_to_uint, \
				_ckd_long: _ckd_sub_3_ushrt_to_long, \
				_ckd_ulong: _ckd_sub_3_ushrt_to_ulong, \
				_ckd_llong: _ckd_sub_3_ushrt_to_llong, \
				_ckd_ullong: _ckd_sub_3_ushrt_to_ullong), \
			_ckd_int: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_int_to_schar, \
				_ckd_uchar: _ckd_sub_3_int_to_uchar, \
				_ckd_shrt: _ckd_sub_3_int_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_int_to_ushrt, \
				_ckd_int: _ckd_sub_3_int_to_int, \
				_ckd_uint: _ckd_sub_3_int_to_uint, \
				_ckd_long: _ckd_sub_3_int_to_long, \
				_ckd_ulong: _ckd_sub_3_int_to_ulong, \
				_ckd_llong: _ckd_sub_3_int_to_llong, \
				_ckd_ullong: _ckd_sub_3_int_to_ullong), \
			_ckd_uint: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_uint_to_schar, \
				_ckd_uchar: _ckd_sub_3_uint_to_uchar, \
				_ckd_shrt: _ckd_sub_3_uint_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_uint_to_ushrt, \
				_ckd_int: _ckd_sub_3_uint_to_int, \
				_ckd_uint: _ckd_sub_3_uint_to_uint, \
				_ckd_long: _ckd_sub_3_uint_to_long, \
				_ckd_ulong: _ckd_sub_3_uint_to_ulong, \
				_ckd_llong: _ckd_sub_3_uint_to_llong, \
				_ckd_ullong: _ckd_sub_3_uint_to_ullong), \
			_ckd_long: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_long_to_schar, \
				_ckd_uchar: _ckd_sub_3_long_to_uchar, \
				_ckd_shrt: _ckd_sub_3_long_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_long_to_ushrt, \
				_ckd_int: _ckd_sub_3_long_to_int, \
				_ckd_uint: _ckd_sub_3_long_to_uint, \
				_ckd_long: _ckd_sub_3_long_to_long, \
				_ckd_ulong: _ckd_sub_3_long_to_ulong, \
				_ckd_llong: _ckd_sub_3_long_to_llong, \
				_ckd_ullong: _ckd_sub_3_long_to_ullong), \
			_ckd_ulong: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_ulong_to_schar, \
				_ckd_uchar: _ckd_sub_3_ulong_to_uchar, \
				_ckd_shrt: _ckd_sub_3_ulong_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_ulong_to_ushrt, \
				_ckd_int: _ckd_sub_3_ulong_to_int, \
				_ckd_uint: _ckd_sub_3_ulong_to_uint, \
				_ckd_long: _ckd_sub_3_ulong_to_long, \
				_ckd_ulong: _ckd_sub_3_ulong_to_ulong, \
				_ckd_llong: _ckd_sub_3_ulong_to_llong, \
				_ckd_ullong: _ckd_sub_3_ulong_to_ullong), \
			_ckd_llong: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_llong_to_schar, \
				_ckd_uchar: _ckd_sub_3_llong_to_uchar, \
				_ckd_shrt: _ckd_sub_3_llong_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_llong_to_ushrt, \
				_ckd_int: _ckd_sub_3_llong_to_int, \
				_ckd_uint: _ckd_sub_3_llong_to_uint, \
				_ckd_long: _ckd_sub_3_llong_to_long, \
				_ckd_ulong: _ckd_sub_3_llong_to_ulong, \
				_ckd_llong: _ckd_sub_3_llong_to_llong, \
				_ckd_ullong: _ckd_sub_3_llong_to_ullong), \
			_ckd_ullong: _Generic(*(r), \
				_ckd_schar: _ckd_sub_3_ullong_to_schar, \
				_ckd_uchar: _ckd_sub_3_ullong_to_uchar, \
				_ckd_shrt: _ckd_sub_3_ullong_to_shrt, \
				_ckd_ushrt: _ckd_sub_3_ullong_to_ushrt, \
				_ckd_int: _ckd_sub_3_ullong_to_int, \
				_ckd_uint: _ckd_sub_3_ullong_to_uint, \
				_ckd_long: _ckd_sub_3_ullong_to_long, \
				_ckd_ulong: _ckd_sub_3_ullong_to_ulong, \
				_ckd_llong: _ckd_sub_3_ullong_to_llong, \
				_ckd_ullong: _ckd_sub_3_ullong_to_ullong))(r, _ckd_idx(a, b), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))

#define _ckd_sub_2(a, b) \
			_Generic(_ckd_value(a) + _ckd_value(b), \
			_ckd_schar: _ckd_sub_2_schar, \
			_ckd_uchar: _ckd_sub_2_uchar, \
			_ckd_shrt: _ckd_sub_2_shrt, \
			_ckd_ushrt: _ckd_sub_2_ushrt, \
			_ckd_int: _ckd_sub_2_int, \
			_ckd_uint: _ckd_sub_2_uint, \
			_ckd_long: _ckd_sub_2_long, \
			_ckd_ulong: _ckd_sub_2_ulong, \
			_ckd_llong: _ckd_sub_2_llong, \
			_ckd_ullong: _ckd_sub_2_ullong)(_ckd_idx(a, b), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))

#define _ckd_mul_3(r, a, b) \
			_Generic(_ckd_value(a) + _ckd_value(b) + *(r), \
			_ckd_schar: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_schar_to_schar, \
				_ckd_uchar: _ckd_mul_3_schar_to_uchar, \
				_ckd_shrt: _ckd_mul_3_schar_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_schar_to_ushrt, \
				_ckd_int: _ckd_mul_3_schar_to_int, \
				_ckd_uint: _ckd_mul_3_schar_to_uint, \
				_ckd_long: _ckd_mul_3_schar_to_long, \
				_ckd_ulong: _ckd_mul_3_schar_to_ulong, \
				_ckd_llong: _ckd_mul_3_schar_to_llong, \
				_ckd_ullong: _ckd_mul_3_schar_to_ullong), \
			_ckd_uchar: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_uchar_to_schar, \
				_ckd_uchar: _ckd_mul_3_uchar_to_uchar, \
				_ckd_shrt: _ckd_mul_3_uchar_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_uchar_to_ushrt, \
				_ckd_int: _ckd_mul_3_uchar_to_int, \
				_ckd_uint: _ckd_mul_3_uchar_to_uint, \
				_ckd_long: _ckd_mul_3_uchar_to_long, \
				_ckd_ulong: _ckd_mul_3_uchar_to_ulong, \
				_ckd_llong: _ckd_mul_3_uchar_to_llong, \
				_ckd_ullong: _ckd_mul_3_uchar_to_ullong), \
			_ckd_shrt: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_shrt_to_schar, \
				_ckd_uchar: _ckd_mul_3_shrt_to_uchar, \
				_ckd_shrt: _ckd_mul_3_shrt_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_shrt_to_ushrt, \
				_ckd_int: _ckd_mul_3_shrt_to_int, \
				_ckd_uint: _ckd_mul_3_shrt_to_uint, \
				_ckd_long: _ckd_mul_3_shrt_to_long, \
				_ckd_ulong: _ckd_mul_3_shrt_to_ulong, \
				_ckd_llong: _ckd_mul_3_shrt_to_llong, \
				_ckd_ullong: _ckd_mul_3_shrt_to_ullong), \
			_ckd_ushrt: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_ushrt_to_schar, \
				_ckd_uchar: _ckd_mul_3_ushrt_to_uchar, \
				_ckd_shrt: _ckd_mul_3_ushrt_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_ushrt_to_ushrt, \
				_ckd_int: _ckd_mul_3_ushrt_to_int, \
				_ckd_uint: _ckd_mul_3_ushrt_to_uint, \
				_ckd_long: _ckd_mul_3_ushrt_to_long, \
				_ckd_ulong: _ckd_mul_3_ushrt_to_ulong, \
				_ckd_llong: _ckd_mul_3_ushrt_to_llong, \
				_ckd_ullong: _ckd_mul_3_ushrt_to_ullong), \
			_ckd_int: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_int_to_schar, \
				_ckd_uchar: _ckd_mul_3_int_to_uchar, \
				_ckd_shrt: _ckd_mul_3_int_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_int_to_ushrt, \
				_ckd_int: _ckd_mul_3_int_to_int, \
				_ckd_uint: _ckd_mul_3_int_to_uint, \
				_ckd_long: _ckd_mul_3_int_to_long, \
				_ckd_ulong: _ckd_mul_3_int_to_ulong, \
				_ckd_llong: _ckd_mul_3_int_to_llong, \
				_ckd_ullong: _ckd_mul_3_int_to_ullong), \
			_ckd_uint: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_uint_to_schar, \
				_ckd_uchar: _ckd_mul_3_uint_to_uchar, \
				_ckd_shrt: _ckd_mul_3_uint_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_uint_to_ushrt, \
				_ckd_int: _ckd_mul_3_uint_to_int, \
				_ckd_uint: _ckd_mul_3_uint_to_uint, \
				_ckd_long: _ckd_mul_3_uint_to_long, \
				_ckd_ulong: _ckd_mul_3_uint_to_ulong, \
				_ckd_llong: _ckd_mul_3_uint_to_llong, \
				_ckd_ullong: _ckd_mul_3_uint_to_ullong), \
			_ckd_long: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_long_to_schar, \
				_ckd_uchar: _ckd_mul_3_long_to_uchar, \
				_ckd_shrt: _ckd_mul_3_long_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_long_to_ushrt, \
				_ckd_int: _ckd_mul_3_long_to_int, \
				_ckd_uint: _ckd_mul_3_long_to_uint, \
				_ckd_long: _ckd_mul_3_long_to_long, \
				_ckd_ulong: _ckd_mul_3_long_to_ulong, \
				_ckd_llong: _ckd_mul_3_long_to_llong, \
				_ckd_ullong: _ckd_mul_3_long_to_ullong), \
			_ckd_ulong: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_ulong_to_schar, \
				_ckd_uchar: _ckd_mul_3_ulong_to_uchar, \
				_ckd_shrt: _ckd_mul_3_ulong_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_ulong_to_ushrt, \
				_ckd_int: _ckd_mul_3_ulong_to_int, \
				_ckd_uint: _ckd_mul_3_ulong_to_uint, \
				_ckd_long: _ckd_mul_3_ulong_to_long, \
				_ckd_ulong: _ckd_mul_3_ulong_to_ulong, \
				_ckd_llong: _ckd_mul_3_ulong_to_llong, \
				_ckd_ullong: _ckd_mul_3_ulong_to_ullong), \
			_ckd_llong: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_llong_to_schar, \
				_ckd_uchar: _ckd_mul_3_llong_to_uchar, \
				_ckd_shrt: _ckd_mul_3_llong_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_llong_to_ushrt, \
				_ckd_int: _ckd_mul_3_llong_to_int, \
				_ckd_uint: _ckd_mul_3_llong_to_uint, \
				_ckd_long: _ckd_mul_3_llong_to_long, \
				_ckd_ulong: _ckd_mul_3_llong_to_ulong, \
				_ckd_llong: _ckd_mul_3_llong_to_llong, \
				_ckd_ullong: _ckd_mul_3_llong_to_ullong), \
			_ckd_ullong: _Generic(*(r), \
				_ckd_schar: _ckd_mul_3_ullong_to_schar, \
				_ckd_uchar: _ckd_mul_3_ullong_to_uchar, \
				_ckd_shrt: _ckd_mul_3_ullong_to_shrt, \
				_ckd_ushrt: _ckd_mul_3_ullong_to_ushrt, \
				_ckd_int: _ckd_mul_3_ullong_to_int, \
				_ckd_uint: _ckd_mul_3_ullong_to_uint, \
				_ckd_long: _ckd_mul_3_ullong_to_long, \
				_ckd_ulong: _ckd_mul_3_ullong_to_ulong, \
				_ckd_llong: _ckd_mul_3_ullong_to_llong, \
				_ckd_ullong: _ckd_mul_3_ullong_to_ullong))(r, _ckd_idx(a, b), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))

#define _ckd_mul_2(a, b) \
			_Generic(_ckd_value(a) + _ckd_value(b), \
			_ckd_schar: _ckd_mul_2_schar, \
			_ckd_uchar: _ckd_mul_2_uchar, \
			_ckd_shrt: _ckd_mul_2_shrt, \
			_ckd_ushrt: _ckd_mul_2_ushrt, \
			_ckd_int: _ckd_mul_2_int, \
			_ckd_uint: _ckd_mul_2_uint, \
			_ckd_long: _ckd_mul_2_long, \
			_ckd_ulong: _ckd_mul_2_ulong, \
			_ckd_llong: _ckd_mul_2_llong, \
			_ckd_ullong: _ckd_mul_2_ullong)(_ckd_idx(a, b), _ckd_value(a), _ckd_value(b), _ckd_overflow(a) || _ckd_overflow(b))

// ]]]
// vim: ft=c

