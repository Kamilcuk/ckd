// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"

void test() {
#if __GNUC__ && !__INTEL_COMPILER
	CKDTEST(ckd_mul((__int128)-1, (__int128)1), -1, 0);
	CKDTEST(ckd_mul((__int128)1, (__int128)-1), -1, 0);
	CKDTEST(ckd_mul((__int128)0, (__int128)-1), 0, 0);
#endif
	CKDTEST(ckd_mul((long)-1, (long)1), -1, 0);
}
