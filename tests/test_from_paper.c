#include "test.h"
#include <limits.h>
int main() {
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

	ckd_int_t a7 = ckd_add(INT_MAX, 1); // from this proposal
	// Wraps around: ckd_value(a7) = -2^31, ckd_overflow(a7) = true
	TEST(ckd_value(a7) == -2147483648);
	TEST(ckd_overflow(a7) == true);
}
