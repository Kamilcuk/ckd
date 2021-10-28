#include "test.h"

int main() {
#ifdef __GNUC__

#define TESTIN(K, T)  do { \
	ckd_##K##_t var; (void)var; \
	var = _ckd_ctypeof((T)0); \
	var = _ckd_ctypeof((ckd_##K##_t){0}); \
	var = _ckd_toct((T)0); \
	var = _ckd_toct((ckd_##K##_t){0}); \
} while(0)
	FOREACH_TYPE(TESTIN)

#endif
#if CKD_USE_NOGNU
#define TESTINARG2(K, T, K2, T2)  do { \
	_ckd_arg_##K to; (void)to; \
	to = _ckd_arg((ckd_##K##_t){0}, (ckd_##K2##_t){0}); \
} while (0)
#define TESTINARG(K, T)  FOREACH_PROMOTEDTYPE(TESTINARG2, K, T)
	FOREACH_TYPE(TESTINARG);
#endif
	CKDEND();
}
