#include "test.h"

int main() {
	CKDTEST(ckd_add(-2, 1u), (unsigned)-1, 1);
	CKDTEST(ckd_add(-2, 1ul), (unsigned long)-1, 1);
	CKDTEST(ckd_add(-2, 1ull), (unsigned long long)-1, 1);
	CKDTEST(ckd_sub(1ull, 2), (unsigned long long)-1, 1);
	CKDTEST(ckd_sub(1ull, 2ull), (unsigned long long)-1, 1);
	CKDTEST(ckd_sub(1, 2ull), (unsigned long long)-1, 1);
	CKDTEST(ckd_sub(1, 2), -1, 0);

	CKDEND();
}
