#include "test.h"
int main() {
	int a; bool b;

	CKDTEST(ckd_add(2, 3), 5, 0);
	CKDTEST(ckd_sub(5, 3), 2, 0);
	CKDTEST(ckd_mul(2, 3), 6, 0);
	CKDTEST(ckd_mul(INT_MAX, 2), -2, 1);

	CKDTEST(ckd_add(INT_MAX, 1), INT_MIN, 1);
	CKDTEST(ckd_mul(ckd_sub(ckd_add(INT_MAX, 1), INT_MIN + 2), 2), -4, 1);

    CKDTEST(ckd_mul(ckd_add(1, 1), 2), 4, 0);

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

	uint64_t u64 = 2;
	// !ONLYSAMETYPES calls _ckd_mul_2_uint64_uin64_int
	//  ONLYSAMETYPES calls _ckd_mul_2_uint64_uint64_uint64
	CKDTEST(ckd_mul(u64, 2), 4, 0);

	// !ONLYSAMETYPES calls _ckd_mul_2_llong_long_llong
	//  ONLYSAMETYPES calls _ckd_mul_2_long_long_long
	CKDTEST(ckd_mul(1l, 2ll), 2, 0);

	CKDEND();
}
