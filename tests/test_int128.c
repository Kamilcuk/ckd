#include "test.h"
int main() {
#if defined(__SIZEOF_INT128__) && !defined(__INTEL_COMPILER)
	{
		__uint128_t a = 1, b = 2, c = 3;
		__uint128_t r = ckd_value(ckd_add(a, ckd_mul(b, c)));
		TEST(r == b * c + a);
	}
	{
		__int128_t a = 1, b = 2, c = 3;
		__int128_t r = ckd_value(ckd_add(a, ckd_mul(b, c)));
		TEST(r == b * c + a);
	}
	{
		ckd_uint128_t r = ckd_add(UINT128_MAX, 1);
		TEST(ckd_value(r) == 0);
		TEST(ckd_overflow(r) == 1);
		r = ckd_sub(INT128_MIN, (__uint128_t)1);
		TEST(ckd_value(r) == INT128_MAX);
		TEST(ckd_overflow(r) == 1);
	}
#endif
	CKDEND();
}
