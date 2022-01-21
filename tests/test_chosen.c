// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"
void test() {
	TEST_OP3(char, add, (unsigned)INT_MAX, 0u, (char)INT_MAX, 1);
	TEST_OP3(char, add, UINT_MAX, 1u, 0, 1);
	TEST_COP3(char, add, (unsigned)INT_MAX, 0u, (char)INT_MAX, 1);
	TEST_COP3(uint, add, (int)INT_MAX, (int)0, INT_MAX, 0);
	TEST_COP3(ullong, add, (unsigned long long)INT_MAX, (char)0, INT_MAX, 0);
	TEST_COP3(llong, add, (long long)INT_MAX, (char)0, INT_MAX, 0);
	TEST_COP3(long, add, (long)INT_MAX, (char)0, INT_MAX, 0);
	TEST_COP3(ulong, add, (unsigned long)INT_MAX, (char)0, INT_MAX, 0);
	TEST_COP3(int, add, (int)INT_MAX, (char)0, INT_MAX, 0);
	TEST_COP3(uint, add, (unsigned int)INT_MAX, (char)0, INT_MAX, 0);
	TEST_COP3(ulong, mul, (long long)INT_MAX, (long long)0, 0, 0);
	TEST_OP3(long, mul, (unsigned int)INT_MAX, (unsigned int)0, 0, 0);
}
