#ifndef _CN_H_
#define _CN_H_

#include <stdint.h>
#include <gmp.h>

typedef struct {
  int n;
  int x;
  int nfactors;
  mpz_t *factor;
  char flag;
  int lf_digit;
  mpz_t *newfactor;
} _cn_t;
typedef _cn_t *cn_t;

typedef struct {
  int *poly;
  int degree;
} cnpoly_t;

typedef struct {
  int64_t *poly;
  int degree;
} aurpoly_t;

#define CNFILE_TERMINATOR "(0 0 (0))"

#define CN_OK 0
#define CN_MEMORY_ERROR 1
#define CN_NOT_CN 2
#define CN_PARSE_ERROR(_x) (3 | ((_x) << 8))
#define CN_DIV_ERROR(_x) (4 | ((_x) << 8))
#define CN_PRIMARITY_ERROR(_x) (5 | ((_x) << 8))
#define CN_ORDER_ERROR(_x) (6 | ((_x) << 8))
#define CN_LF_PRIMARITY_ERROR (1 << 3)
#define CN_LF_ORDER_ERROR (1 << 4)
#define CN_LF_DIGIT_ERROR(_x) ((1 << 5) | ((_x) << 16))

#define CN_IS_PARSE_ERROR(_x) ((_x) != 0 && ((_x) & 0xff) <= 3)
#define CN_PARSE_ERROR_POS(_x) ((_x) >> 8)
#define CN_IS_FACTOR_ERROR(_x) (((_x) & 0xff) >= 4)

#define CN_BUF_SIZE 8192

#define CN_MAXN 1000
#define CN_MAXX 1000
#define CN_MAXPHI 400

#define ISPRIME(_x) mpz_probab_prime_p(_x, 30)

#define cn_init(_cn) do{ \
  (_cn) = malloc(sizeof(_cn_t)); \
}while(0)
#define cn_free(_cn) do{ \
  int _i; \
  for(_i = 0; _i < (_cn)->nfactors; _i++){ \
    mpz_clear((_cn)->factor[_i]); \
  } \
  free((_cn)->factor); \
}while(0)
#define cn_clear(_cn) free(_cn)

int cn_set_str(cn_t cn, const char *str);

void cn_eval(mpz_t cn, int n, int x);

cnpoly_t cn_poly(int n);
void cnpoly_init();
void cnpoly_free();

int cn_check_algebraic_factor(cn_t cn);

mpz_t *aur_factor(mpz_t comp, int n, int x);

aurpoly_t aur_Cpoly(int n);
aurpoly_t aur_Dpoly(int n);
void aurpoly_init();
void aurpoly_free();

mpz_t *pow_list(int x, int d);
void powlist_init();
void powlist_free();

#endif

