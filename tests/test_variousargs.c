// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"
void test() {
	{
		unsigned u;
		TEST_EQ(ckd_add(&u, (char)CHAR_MAX, ckd_mk_char_t(1, 1)), 1); TEST_EQ(u, CHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, (signed char)SCHAR_MAX, (unsigned char)1), 0); TEST_EQ(u, SCHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, ckd_mk_schar_t(SCHAR_MAX, 0), ckd_mk_uchar_t(1, 1)), 1); TEST_EQ(u, SCHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, (short)SHRT_MAX, (unsigned short)1), 0); TEST_EQ(u, SHRT_MAX + 1);
		TEST_EQ(ckd_add(&u, ckd_mk_shrt_t(SHRT_MAX, 0), ckd_mk_ushrt_t(1, 1)), 1); TEST_EQ(u, SHRT_MAX + 1);
		TEST_EQ(ckd_add(&u, ckd_mk_int_t(INT_MAX, 0), ckd_mk_uint_t(1, 1)), 1); TEST_EQ(u, (unsigned)INT_MAX + 1u);
	}
	{
		unsigned long u;
		TEST_EQ(ckd_add(&u, (char)CHAR_MAX, ckd_mk_char_t(1, 1)), 1); TEST_EQ(u, CHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, (signed char)SCHAR_MAX, (unsigned char)1), 0); TEST_EQ(u, SCHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, ckd_mk_schar_t(SCHAR_MAX, 0), ckd_mk_uchar_t(1, 1)), 1); TEST_EQ(u, SCHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, (short)SHRT_MAX, (unsigned short)1), 0); TEST_EQ(u, SHRT_MAX + 1);
		TEST_EQ(ckd_add(&u, ckd_mk_shrt_t(SHRT_MAX, 0), ckd_mk_ushrt_t(1, 1)), 1); TEST_EQ(u, SHRT_MAX + 1);
		TEST_EQ(ckd_add(&u, ckd_mk_int_t(INT_MAX, 0), ckd_mk_uint_t(1, 1)), 1); TEST_EQ(u, (unsigned)INT_MAX + 1ul);
		TEST_EQ(ckd_add(&u, ckd_mk_long_t(LONG_MAX, 0), ckd_mk_ulong_t(1, 1)), 1); TEST_EQ(u, (unsigned long)LONG_MAX + 1ul);
	}
	{
		unsigned long long u;
		TEST_EQ(ckd_add(&u, (char)CHAR_MAX, ckd_mk_char_t(1, 1)), 1); TEST_EQ(u, CHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, (signed char)SCHAR_MAX, (unsigned char)1), 0); TEST_EQ(u, SCHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, ckd_mk_schar_t(SCHAR_MAX, 0), ckd_mk_uchar_t(1, 1)), 1); TEST_EQ(u, SCHAR_MAX + 1);
		TEST_EQ(ckd_add(&u, (short)SHRT_MAX, (unsigned short)1), 0); TEST_EQ(u, SHRT_MAX + 1);
		TEST_EQ(ckd_add(&u, ckd_mk_shrt_t(SHRT_MAX, 0), ckd_mk_ushrt_t(1, 1)), 1); TEST_EQ(u, SHRT_MAX + 1);
		TEST_EQ(ckd_add(&u, ckd_mk_int_t(INT_MAX, 0), ckd_mk_uint_t(1, 1)), 1); TEST_EQ(u, (unsigned)INT_MAX + 1u);
		TEST_EQ(ckd_add(&u, ckd_mk_long_t(LONG_MAX, 0), ckd_mk_ulong_t(1, 1)), 1); TEST_EQ(u, (unsigned long)LONG_MAX + 1ull);
		TEST_EQ(ckd_add(&u, ckd_mk_llong_t(LLONG_MAX, 0), ckd_mk_ullong_t(1, 1)), 1); TEST_EQ(u, (unsigned long long)LLONG_MAX + 1ull);
	}
}
