#include "test.h"
void test() {
	ckd_int32_t a = ckd_add((int32_t)1, (int32_t)2);
	TEST(ckd_value(a) == 3);
	TEST(ckd_overflow(a) == false);


	ckd_size_t b = ckd_add((size_t)1, (size_t)2);
	TEST(ckd_value(b) == 3);
	TEST(ckd_overflow(b) == false);
}
