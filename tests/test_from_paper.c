#include "test.h"
#include <limits.h>
void test() {
	ckd_int_t array[2] = {ckd_mk_int_t(1, false), ckd_mk_int_t(2, false)};
	CKDTEST(array[0], 1, false);
	CKDTEST(array[1], 2, false);

	// assumes 32-bit int, so MAX_INT = 2^31 - 1
#if INT_MAX == INT32_MAX
	int64_t a5;
	bool flag2 = ckd_add(&a5, INT_MAX, 1);  // from n2683
	// No wraparound: a5 = + 2^31, flag = false
	TEST(a5 == 2147483648);
	TEST(flag2 == false);
#endif

	//ckd_int64_t a6 = ckd_add(MAX_INT, 1); // from this proposal
	// Error: ckd_add returns a ckd_int32_t,
	// which does not implicitly convert to ckd_int64_t
	ckd_int_t a6 = ckd_add(INT_MAX, 1); // from this proposal
	TEST(ckd_value(a6) == INT_MIN);
	TEST(ckd_overflow(a6) == 1);

	ckd_int_t a7 = ckd_add(INT_MAX, 1); // from this proposal
	// Wraps around: ckd_value(a7) = -2^31, ckd_overflow(a7) = true
	TEST(ckd_value(a7) == -2147483648);
	TEST(ckd_overflow(a7) == true);

	CKDTEST(ckd_add(40, 2), 42, 0);
	int temp;
  	TEST(ckd_add(&temp, 2000, 20) == 0);
	TEST(temp == 2020);
}
