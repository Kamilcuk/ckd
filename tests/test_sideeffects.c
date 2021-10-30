#include "test.h"
static unsigned x;
static unsigned inc() {
	printf("incrementing %d\n", x);
	return x++;
}
static unsigned p;
static unsigned *pnt() {
	inc();
	return &p;
}
void test() {
	x = 0;
	TEST(ckd_value(ckd_add(inc(), 1u)) == 1);
	TEST(x == 1);
	TEST(ckd_value(ckd_add(1u, inc())) == 2);
	TEST(x == 2);
	TEST(ckd_add(pnt(), 1u, 1u) == 0);
	TEST(x == 3);
	TEST(ckd_add(&p, inc(), 1u) == 0);
	TEST(x == 4);
	TEST(ckd_add(&p, 1u, inc()) == 0);
	TEST(x == 5);
}
