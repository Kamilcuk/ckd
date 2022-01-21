// SPDX-FileCopyrightText: 2022 Kamil Cukrowski <kamilcukrowski@gmail.com>
// SPDX-License-Identifier: MIT
#include "test.h"

void test() {
#ifdef _CKDINT_GNU

#define TESTIN(K, T)  do { \
	ckd_##K##_t var; (void)var; \
	var = _ckd_ctypeof((T)0); \
	var = _ckd_ctypeof((ckd_##K##_t){0}); \
	var = _ckd_toct((T)0); \
	var = _ckd_toct((ckd_##K##_t){0}); \
} while(0)
	FOREACH_TYPE(TESTIN)

#else


#endif
}
