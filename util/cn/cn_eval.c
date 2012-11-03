#include <gmp.h>

#include "cn.h"

void cn_eval(mpz_t cn, int n, int x){
  cnpoly_t cp;
  int *poly, degree;
  mpz_t *pw;
  int i;

  cp = cn_poly(n);
  poly = cp.poly;
  degree = cp.degree;
  pw = pow_list(x, degree);

  mpz_set_ui(cn, 0);

  for(i = 0; i <= degree; i++){
    int j = poly[i];
    while(j > 0){
      mpz_add(cn, cn, pw[i]);
      j--;
    }
    while(j < 0){
      mpz_sub(cn, cn, pw[i]);
      j++;
    }
  }
}

