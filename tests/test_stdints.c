#include "test.h"
int main() {
	ckd_int32_t a = ckd_add((int32_t)1, (int32_t)2);
	TEST(ckd_value(a) == 3);
	TEST(ckd_overflow(a) == false);
}
