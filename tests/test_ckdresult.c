// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"

void test() {
	TEST_COP3(llong, mul, LLONG_MAX, (long long)2, (long long)((unsigned long long)LLONG_MAX * 2), 1);
	TEST_COP3(llong, mul, LLONG_MAX, (long long)1, LLONG_MAX, 0);
	TEST_COP3(llong, mul, ULLONG_MAX, 1, ULLONG_MAX, 1);
	TEST_COP3(ullong, mul, ULLONG_MAX, 1, ULLONG_MAX, 0);
	TEST_COP3(ullong, mul, ULLONG_MAX, 2, ULLONG_MAX * 2, 1);

#define TESTIN(K, T)  do{ \
	TEST_COP3(K, add, 2, 3, 5, 0); \
} while(0)
	FOREACH_TYPE(TESTIN);

}
