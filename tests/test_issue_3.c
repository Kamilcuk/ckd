// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"
#include <inttypes.h>
void test() {
	int8_t x = 2;
	int32_t y = 0x7fffffff;
	uint32_t z;
	TEST_EQ(ckd_add(&z, x, y), 0);
	TEST_EQ(z, 0x80000001u);
}