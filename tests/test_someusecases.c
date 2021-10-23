#include "test.h"

size_t my_calloc(size_t a, size_t b) {
	size_t r;
	if (ckd_mul(&r, a, b)) {
		return -1;
	}
	return r;
}

size_t my_calloc2(size_t a, size_t b) {
	ckd_size_t r = ckd_mul(a, b);
	if (ckd_overflow(r)) {
		return -1;
	}
	return ckd_value(r);
}

int append3(size_t bufsize) {
	ckd_size_t cbufsize = ckd_mk_size_t(bufsize, 0);
	cbufsize = ckd_add(cbufsize, 1);
	if (ckd_overflow(cbufsize)) {
		return -1;
	}
	cbufsize = ckd_add(cbufsize, 1);
	if (ckd_overflow(cbufsize)) {
		return -2;
	}
	cbufsize = ckd_add(cbufsize, 1);
	if (ckd_overflow(cbufsize)) {
		return -3;
	}
	return ckd_value(cbufsize);
}

#define _ckd_inc_1(x)     ckd_add(x, *(x), 1)
#define _ckd_inc_2(x, y)  ckd_add(x, *(x), y)
#define _ckd_inc_(_1,_2,N,...) _ckd_inc##N
#define ckd_inc(...)  _ckd_inc_(__VA_ARGS__,_2,_1)(__VA_ARGS__)

int append3_2(size_t bufsize) {
	// Incrementing variable never simpler!
	if (ckd_inc(&bufsize)) {
		return -1;
	}
	if (ckd_inc(&bufsize, 1)) {
		return -2;
	}
	if (ckd_inc(&bufsize)) {
		return -3;
	}
	return bufsize;
}


int main() {
	TEST_EQ(my_calloc(1, 2), 2);
	TEST_EQ(my_calloc(SIZE_MAX, 1), (size_t)-1);
	TEST_EQ(my_calloc2(1, 2), 2);
	TEST_EQ(my_calloc2(SIZE_MAX, 1), (size_t)-1);

	TEST_EQ(append3(1), 4);
	TEST_EQ(append3(SIZE_MAX), -1);
	TEST_EQ(append3(SIZE_MAX - 1), -2);
	TEST_EQ(append3(SIZE_MAX - 2), -3);

	TEST_EQ(append3_2(1), 4);
	TEST_EQ(append3_2(SIZE_MAX), -1);
	TEST_EQ(append3_2(SIZE_MAX - 1), -2);
	TEST_EQ(append3_2(SIZE_MAX - 2), -3);


	CKDEND();
}
