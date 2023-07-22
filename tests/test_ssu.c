// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"
void test() {
	unsigned u = 0;
	TEST_EQ(ckd_add(&u, INT_MAX, INT_MAX), 0);
	TEST_EQ(u, (unsigned)((long)INT_MAX + INT_MAX));

	TEST_EQ(ckd_add(&u, INT_MIN, INT_MIN), 1);
	TEST_EQ(u, (unsigned)((long)INT_MIN + INT_MIN));

	{
		unsigned char uc;
		TEST_EQ(ckd_add(&uc, INT_MAX, INT_MAX), 1);
		TEST_EQ(uc, (unsigned char)((long)INT_MAX + INT_MAX));
	}

	TEST_EQ(ckd_sub(&u, INT_MAX, INT_MIN), 0);
	TEST_EQ(u, (unsigned)((long)INT_MAX - (long)INT_MIN));

	TEST_EQ(ckd_mul(&u, INT_MAX, 3), 1);
	TEST_EQ(u, (unsigned)((long)INT_MAX * 3));

	TEST_EQ(ckd_mul(&u, INT_MAX, -3), 1);
	TEST_EQ(u, (unsigned)((long)INT_MAX * -3));
}
