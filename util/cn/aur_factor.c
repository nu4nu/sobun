#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <gmp.h>

#include "cn.h"

#if ULONG_MAX < INT64_MAX
#define NEED_IMPORT
#endif

static void aur_poly_eval(mpz_t res, aurpoly_t ap, mpz_t x){
  int i;

#ifdef NEED_IMPORT
  mpz_t tmp;
  mpz_init(tmp);
#endif

  mpz_set_ui(res, 0);
  for(i = ap.degree; i >= 0; i--){
    int64_t coeff = ap.poly[i];

    mpz_mul(res, res, x);

    if(coeff >= 0){
#ifndef NEED_IMPORT
      mpz_add_ui(res, res, coeff);
#else
      mpz_import(tmp, 1, -1, sizeof(int64_t), 0, 0, &coeff);
      mpz_add(res, res, tmp);
#endif
    }else{
      coeff = -coeff;
#ifndef NEED_IMPORT
      mpz_sub_ui(res, res, coeff);
#else
      mpz_import(tmp, 1, -1, sizeof(int64_t), 0, 0, &coeff);
      mpz_sub(res, res, tmp);
#endif
    }
  }
#ifdef NEED_IMPORT
  mpz_clear(tmp);
#endif
}

/* x = m * a * a */
/* n = mul * m * t */
static inline mpz_t *aur_get(mpz_t comp, int x, int m, int a, int mul){
  mpz_t aurc, aurd;
  mpz_t g0, g1;

  mpz_t *xmul = pow_list(x, mul);

  mpz_init(aurc);
  mpz_init(aurd);
  mpz_init(g0);
  mpz_init(g1);

  aur_poly_eval(aurc, aur_Cpoly(m), xmul[mul]);
  aur_poly_eval(aurd, aur_Dpoly(m), xmul[mul]);
  mpz_mul_ui(aurd, aurd, m * a);
  if(mul > 1){
    mpz_mul(aurd, aurd, xmul[mul >> 1]);
  }
  mpz_add(g0, aurc, aurd);
  mpz_sub(g1, aurc, aurd);

  mpz_clear(aurc);
  mpz_clear(aurd);

  mpz_gcd(g0, g0, comp);
  mpz_gcd(g1, g1, comp);

  if(mpz_cmp_ui(g0, 1) != 0 && mpz_cmp_ui(g1, 1) != 0){
    mpz_t *res = malloc(2 * sizeof(mpz_t));
    memcpy(res[0], g0, sizeof(mpz_t));
    memcpy(res[1], g1, sizeof(mpz_t));
    return res;
  }

  mpz_clear(g0);
  mpz_clear(g1);

  return NULL;
}

mpz_t *aur_factor(mpz_t comp, int n, int x){
  int m, a;

  if((n & 0x7) == 0){
    return NULL;
  }

  m = x;
  for(a = 31; a > 1; a--){
    if(m % (a * a) == 0){
      m /= a * a;
      break;
    }
  }

  /* assuming x is not perfect power */
  if(m == 1){
    return NULL;
  }

  if((m & 0x3) == 1){
    if((n & 0x1) == 0 || n % m != 0) return NULL;
    n /= m;
  }else{
    int m2 = m + m;
    if(((n ^ m2) & 0x3) != 0 || n % m2 != 0) return NULL;
    n /= m2;
  }

  return aur_get(comp, x, m, a, n);
}

