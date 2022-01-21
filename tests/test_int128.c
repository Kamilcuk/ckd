// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"
void test() {
#if defined(__SIZEOF_INT128__) && !defined(__INTEL_COMPILER) && !defined(__clang__)
	typedef __uint128_t U;
	typedef __int128_t S;
#define UMAX  UINT128_MAX
#define MAX    INT128_MAX
#define MIN    INT128_MIN
#define TEST_128OP3(type, op, a, b, v, o)  do { \
	type _r; \
	TEST(ckd_##op(&_r, a, b) == o); \
	TEST(_r == v); \
} while (0)
#define TEST_128COP3(type, op, a, b, v, o)  do { \
	type _r; \
	TEST(ckd_##op(&_r, a, b) == o); \
	TEST(ckd_value(_r) == v); \
	TEST(ckd_overflow(_r) == o); \
} while (0)

	{
		__uint128_t a = 1, b = 2, c = 3;
		__uint128_t r = ckd_value(ckd_add(a, ckd_mul(b, c)));
		TEST(r == b * c + a);
	}
	{
		__int128_t a = 1, b = 2, c = 3;
		__int128_t r = ckd_value(ckd_add(a, ckd_mul(b, c)));
		TEST(r == b * c + a);
	}
	{
		ckd_uint128_t r = ckd_add(UINT128_MAX, 1);
		TEST(ckd_value(r) == 0);
		TEST(ckd_overflow(r) == 1);
		r = ckd_sub(INT128_MIN, (__uint128_t)1);
		TEST(ckd_value(r) == INT128_MAX);
		TEST(ckd_overflow(r) == 1);
	}
	{
		ckd_uint128_t uc = ckd_mk_uint128_t(UINT128_MAX, 0);
		ckd_int128_t sc = ckd_mk_int128_t(INT128_MAX, 0);
		__int128_t sv = UINT128_MAX;
		__uint128_t uv = INT128_MAX;
		TEST(ckd_sub(&uv, uc, uc) == 0);
		TEST(uv == 0);
		TEST(ckd_sub(&uc, uc, uc) == 0);
		TEST(ckd_value(uc) == 0);
		TEST(ckd_overflow(uc) == 0);
		TEST(ckd_add(&uc, uv, uv) == 0);
		TEST(ckd_value(uc) == 0);
		TEST(ckd_overflow(uc) == 0);

		TEST(ckd_sub(&sv, sc, sc) == 0);
		TEST(sv == 0);
		TEST(ckd_sub(&sc, sc, sc) == 0);
		TEST(ckd_value(sc) == 0);
		TEST(ckd_overflow(sc) == 0);
		TEST(ckd_add(&sc, sv, sv) == 0);
		TEST(ckd_value(sc) == 0);
		TEST(ckd_overflow(sc) == 0);
	}
	{
		ckd_int128_t a = ckd_add(MAX, MAX);
		CKDTEST(a, (U)-2, 1);
		a = ckd_sub(MAX, 0);
		CKDTEST(a, MAX, 0);
	}
	{
		TEST_128OP3(S, add, (S)2, (U)3, 5, 0);
		TEST_128OP3(S, add, (S)2, (S)3, 5, 0);
		TEST_128OP3(S, add, (S)MAX, (U)1, MIN, 1);
		TEST_128OP3(S, add, (U)2, (U)3, 5, 0);
		TEST_128OP3(S, add, (U)MAX, (U)1, MIN, 1);
		TEST_128OP3(S, add, (U)2, (S)3, 5, 0);
		TEST_128OP3(S, add, (U)MAX, (S)1, MIN, 1);

		TEST_128OP3(S, sub, (S)MAX, (S)MIN, -1, 1);
		TEST_128OP3(S, sub, (U)MIN, (S)1, MAX, 0);
		TEST_128OP3(S, sub, (S)MIN, (U)1, MAX, 1);
		TEST_128OP3(S, sub, (U)MIN, (U)1, MAX, 0);

		TEST_128OP3(S, mul, (U)2, (U)3, 6, 0);
		TEST_128OP3(S, mul, (U)2, (S)3, 6, 0);
		TEST_128OP3(S, mul, (S)2, (U)3, 6, 0);
		TEST_128OP3(S, mul, (U)MAX, (U)2, (S)((U)MAX * (U)2), 1);
		TEST_128OP3(S, mul, (S)MAX, (U)2, (S)((U)MAX * (U)2), 1);
		TEST_128OP3(S, mul, (U)MAX, (S)2, (S)((U)MAX * (U)2), 1);

		TEST_128OP3(U, add, (S)2, (U)3, 5, 0);
		TEST_128OP3(U, add, (U)UMAX, (S)1, 0, 1);
		TEST_128OP3(U, add, (U)UMAX, (U)1, 0, 1);
		TEST_128OP3(U, add, UMAX, 1, 0, 1);

		TEST_128OP3(U, sub, (U)UMAX, (U)1, (U)UMAX - 1, 0);
		TEST_128OP3(U, sub, (S)-1, (U)1, (U)-2, 1);
		TEST_128OP3(U, sub, (U)1, (S)2, (U)-1, 1);
		TEST_128OP3(U, sub, (S)2, (S)1, (U)1, 0);
		TEST_128OP3(U, sub, (S)2, (S)3, (U)-1, 1);
		TEST_128OP3(U, sub, (S)MAX, (S)-1, (U)MAX + 1, 0);

		TEST_128OP3(U, mul, (S)-1, 1, UMAX, 1);
		TEST_128OP3(U, mul, (U)2, (U)3, 6, 0);
		TEST_128OP3(U, mul, (U)2, (S)3, 6, 0);
		TEST_128OP3(U, mul, (S)2, (U)3, 6, 0);
		TEST_128OP3(U, mul, (U)MAX, (U)3, (U)((U)MAX * (U)3), 1);
		TEST_128OP3(U, mul, (U)2, (S)-3, (U)-6, 1);
		TEST_128OP3(U, mul, (S)-2, (U)3, (U)-6, 1);
	}
	{
		TEST_128COP3(ckd_int128_t, mul, UMAX, 1, (S)UMAX, 1);
		TEST_128COP3(ckd_uint128_t, mul, UMAX, 1, UMAX, 0);
	}
	{
		#define TEST_TOSMALLER(K, T) do { \
			TEST_COP3(K, add, (S)2, (S)3, 5, 0); \
			TEST_COP3(K, sub, (S)3, (S)2, 1, 0); \
			TEST_COP3(K, mul, (S)2, (S)3, 6, 0); \
		} while (0)
		TEST_TOSMALLER(char, _);
		FOREACH_TYPE(TEST_TOSMALLER);
	}
	{
		__uint128_t u;
		TEST_EQ(ckd_add(&u, (char)CHAR_MAX, ckd_mk_char_t(1, 1)), 1); TEST(u == (U)CHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, (signed char)SCHAR_MAX, (unsigned char)UCHAR_MAX), 0); TEST(u == (U)SCHAR_MAX + UCHAR_MAX);
		TEST_EQ(ckd_add(&u, ckd_mk_schar_t(SCHAR_MAX, 0), ckd_mk_uchar_t(1, 1)), 1); TEST(u == (U)SCHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, (short)SHRT_MAX, (unsigned short)USHRT_MAX), 0); TEST(u == (U)SHRT_MAX + USHRT_MAX);
		TEST_EQ(ckd_add(&u, ckd_mk_shrt_t(SHRT_MAX, 0), ckd_mk_ushrt_t(1, 1)), 1); TEST(u == (U)SHRT_MAX + 1);
		TEST_EQ(ckd_add(&u, INT_MAX, UINT_MAX), 0); TEST(u == (U)INT_MAX + (U)UINT_MAX);
		TEST_EQ(ckd_add(&u, ckd_mk_int_t(INT_MAX, 0), ckd_mk_uint_t(1, 1)), 1); TEST_EQ(u, INT_MAX + 1u);
		TEST_EQ(ckd_add(&u, LONG_MAX, ULONG_MAX), 0); TEST(u == (U)LONG_MAX + ULONG_MAX);
		TEST_EQ(ckd_add(&u, ckd_mk_long_t(LONG_MAX, 0), ckd_mk_ulong_t(1, 1)), 1); TEST_EQ(u, LONG_MAX + 1ul);
		TEST_EQ(ckd_add(&u, LLONG_MAX, ULLONG_MAX), 0); TEST(u == (U)LLONG_MAX + (U)ULLONG_MAX);
		TEST_EQ(ckd_add(&u, ckd_mk_llong_t(LLONG_MAX, 0), ckd_mk_ullong_t(1, 1)), 1); TEST_EQ(u, LLONG_MAX + 1ull);
		TEST_EQ(ckd_add(&u, ckd_mk_uint128_t(INT128_MAX, 0), ckd_mk_int128_t(1, 1)), 1); TEST(u == INT128_MAX + (U)1);
	}
#endif
}
