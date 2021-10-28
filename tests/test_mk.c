#include "test.h"

#define T(KEY, TYPE)  do{ \
		ckd_##KEY##_t tmp = ckd_mk((TYPE)__LINE__, __LINE__%2); \
		CKDTEST(tmp, __LINE__, __LINE__%2); \
		ckd_##KEY##_t tmp2 = ckd_mk_##KEY##_t((TYPE)__LINE__, __LINE__%2); \
		CKDTEST(tmp2, __LINE__, __LINE__%2); \
	}while(0)

#define TT(KEY) T(KEY, KEY##_t)

int main() {
	T(schar, signed char);
	T(uchar, unsigned char);
	T(shrt, short);
	T(ushrt, unsigned short);
	T(int, signed);
	T(uint, unsigned);
	T(long, signed long);
	T(ulong, unsigned long);
	T(llong, signed long long);
	T(ullong, unsigned long long);
	T(intmax, intmax_t);
	T(uintmax, uintmax_t);
	T(size, size_t);
	T(ptrdiff, ptrdiff_t);
	T(intptr, intptr_t);
	T(uintptr, uintptr_t);
	T(int8, int8_t);
	T(uint8, uint8_t);
	T(int_least8, int_least8_t);
	T(uint_least8, uint_least8_t);
	T(int_fast8, int_fast8_t);
	T(uint_fast8, uint_fast8_t);
	T(int16, int16_t);
	T(uint16, uint16_t);
	T(int_least16, int_least16_t);
	T(uint_least16, uint_least16_t);
	T(int_fast16, int_fast16_t);
	T(uint_fast16, uint_fast16_t);
	T(int32, int32_t);
	T(uint32, uint32_t);
	T(int_least32, int_least32_t);
	T(uint_least32, uint_least32_t);
	T(int_fast32, int_fast32_t);
	T(uint_fast32, uint_fast32_t);
	T(int64, int64_t);
	T(uint64, uint64_t);
	T(int_least64, int_least64_t);
	T(uint_least64, uint_least64_t);
	T(int_fast64, int_fast64_t);
	T(uint_fast64, uint_fast64_t);
	T(size, size_t);
	CKDEND();
}
