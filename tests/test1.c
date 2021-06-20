#include "test.h"
int main() {
	int a; bool b;
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

	CKDTEST(ckd_mul(2, 2), 4, 0);
	CKDTEST(ckd_mul(INT_MAX, 2), -2, 1);
	CKDTEST(ckd_div(4, 2), 2, 0);
	CKDTEST(ckd_div(INT_MIN, -1), 0, 1);

	CKDTEST(ckd_add(INT_MAX, 1), INT_MIN, 1);
	CKDTEST(ckd_mul(ckd_sub(ckd_add(INT_MAX, 1), INT_MIN + 2), 2), -4, 1);


    CKDTEST(ckd_mul(ckd_add(1, 1), 2), 4, 0);
	CKDTEST(ckd_div(ckd_mul(ckd_mul(1, 2), 4), 2), 2 * 4 / 2, 0);

}
