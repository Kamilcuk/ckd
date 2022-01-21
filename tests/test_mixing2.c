// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "mixing.h"

void test() {
	T(unsigned long long, long long);
	T(unsigned long long, unsigned long);
	T(unsigned long long, long);
	T(long long, char);
	T(long long, long long);
}
