#include "test.h"
int main() {
	int a; bool b;

	CKDTEST(ckd_add(2, 3), 5, 0);
	CKDTEST(ckd_sub(5, 3), 2, 0);
	CKDTEST(ckd_mul(2, 3), 6, 0);
	CKDTEST(ckd_mul(INT_MAX, 2), -2, 1);
	CKDTEST(ckd_div(4, 2), 2, 0);
	CKDTEST(ckd_div(INT_MIN, -1), 0, 1);

	CKDTEST(ckd_add(INT_MAX, 1), INT_MIN, 1);
	CKDTEST(ckd_mul(ckd_sub(ckd_add(INT_MAX, 1), INT_MIN + 2), 2), -4, 1);


    CKDTEST(ckd_mul(ckd_add(1, 1), 2), 4, 0);
	CKDTEST(ckd_div(ckd_mul(ckd_mul(1, 2), 4), 2), 2 * 4 / 2, 0);

	CKDTEST(ckd_add(INT_MAX, 1), INT_MIN, 1);
	CKDTEST(ckd_sub(INT_MIN, 1), INT_MAX, 1);
	CKDTEST(ckd_mul(INT_MAX / 2 + 1, 2), INT_MIN, 1);

	b = ckd_add(&a, 2, 2);
	TEST(a == 4);
	TEST(b == 0);

	b = ckd_mul(&a, ckd_add(2, 2), 2);
	TEST(a == 8);
	TEST(b == 0);

	b = ckd_add(&a, INT_MAX - 1, 1);
	TEST(a == INT_MAX);
	TEST(b == 0);

	b = ckd_add(&a, INT_MAX, 1);
	TEST(a == INT_MIN);
	TEST(b == 1);

	b = ckd_sub(&a, INT_MIN, 1);
	TEST(a == INT_MAX);
	TEST(b == 1);

	b = ckd_add(&a, INT_MIN, -1);
	TEST(a == INT_MAX);
	TEST(b == 1);

#ifndef _ckd_ONLYSAMETYPES
	CKDTEST(ckd_mul(1l, 2ll), 2, 0);

	uint64_t u64 = 2;
	CKDTEST(ckd_mul(u64, 2), 4, 0);

	b = ckd_add(&a, LONG_MAX, 0);
	TEST(a == (int)LONG_MAX);
	TEST(b == 1); // conversion overflowed
#endif

	CKDEND();
}
