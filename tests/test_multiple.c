#include "test.h"
void test() {
    CKDTEST(ckd_mul(ckd_add(1, 1), 2), 4, 0);
	CKDTEST(ckd_add(ckd_add(INT_MAX, 1), 1), INT_MIN + 1, 1);
	// This will stall on no-gnu - too much nesting, takes too long to compile.
	CKDTEST(ckd_mul(ckd_sub(ckd_add(INT_MAX, 1), INT_MIN + 2), 2), -4, 1);

}

