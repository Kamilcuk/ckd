// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"
void test() {
	TEST_OP3(long long, mul, LLONG_MAX, (long long)2, (long long)((unsigned long long)LLONG_MAX * 2), 1);
	TEST_OP3(long long, mul, LLONG_MAX, (long long)1, LLONG_MAX, 0);
	TEST_OP3(long long, mul, ULLONG_MAX, 1, ULLONG_MAX, 1);
	TEST_OP3(unsigned long long, mul, ULLONG_MAX, 1, ULLONG_MAX, 0);
	TEST_OP3(unsigned long long, mul, ULLONG_MAX, 2, ULLONG_MAX * 2, 1);
}
