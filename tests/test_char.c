// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"
void test() {
	TEST_OP3(char, add, 1, 2, 3, 0);
	TEST_COP3(char, add, 1, 2, 3, 0);
	ckd_char_t a = ckd_mk_char_t(2, 0);
	TEST_COP3(char, add, a, 3, 5, 0);
	TEST_COP3(char, add, 4, a, 6, 0);
	TEST_COP3(char, add, a, a, 4, 0);
}
