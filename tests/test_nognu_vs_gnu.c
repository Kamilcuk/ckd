#include "test.h"
#if !defined(__GNUC__) || defined(CKD_NOGNU_SOURCE)
void test() {}
#else
#include <ckdint/ckdint_gnu.h>
#include <ckdint/ckdint_nognu.h>
#include <assert.h>
void test() {
	long step = UINT_MAX >> 8;
	for (long a = INT_MIN; a < INT_MAX; a += step) {
		for (long b = INT_MIN; b < INT_MAX; b += step) {
			printf("%ld %ld\n", a, b);
			{
				unsigned nognur, gnur;
				bool nognuo, gnuo;
				nognuo = _ckd_nognu_add_3(&nognur, (int)a, (int)b);
				gnuo = _ckd_gnu_add_3(&gnur, (int)a, (int)b);
				TEST_EQ(nognur, gnur);
				TEST_EQ(nognuo, gnuo);
				nognuo = _ckd_nognu_sub_3(&nognur, (int)a, (int)b);
				gnuo = _ckd_gnu_sub_3(&gnur, (int)a, (int)b);
				TEST_EQ(nognur, gnur);
				TEST_EQ(nognuo, gnuo);
				nognuo = _ckd_nognu_mul_3(&nognur, (int)a, (int)b);
				gnuo = _ckd_gnu_mul_3(&gnur, (int)a, (int)b);
				TEST_EQ(nognur, gnur);
				TEST_EQ(nognuo, gnuo);
			}
		}
	}
}
#endif
