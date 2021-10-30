#include "test.h"

void test() {
#ifdef _CKDINT_GNU

#define TESTIN(K, T)  do { \
	ckd_##K##_t var; (void)var; \
	var = _CKD_ctypeof((T)0); \
	var = _CKD_ctypeof((ckd_##K##_t){0}); \
	var = _CKD_toct((T)0); \
	var = _CKD_toct((ckd_##K##_t){0}); \
} while(0)
	FOREACH_TYPE(TESTIN)

#else


#endif
}
