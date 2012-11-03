#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#include "cn.h"

int cn_add_factor(cn_t cn, const char *str){
  mpz_t comp, factor;
  mpz_t tmpq, tmpr;
  int i;

  mpz_init(factor);
  mpz_init(tmpq);
  mpz_init(tmpr);

  if(cn->flag != 'C') goto err;
  memcpy(comp, cn->factor[cn->nfactors-1], sizeof(mpz_t));

  mpz_set_str(factor, str, 10);
  if(!ISPRIME(factor)) goto err;

  mpz_tdiv_qr(tmpq, tmpr, comp, factor);
  if(mpz_sgn(tmpr)) goto err;
  if(mpz_cmp_ui(tmpq, 1) <= 0) goto err;

  cn->flag = ISPRIME(tmpq) ? 'P' : 'C';
  cn->factor = realloc(cn->factor, (cn->nfactors+1) * sizeof(mpz_t));

  for(i = 0; i < cn->nfactors; i++){
    if(mpz_cmp(cn->factor[i], factor) > 0){
      memmove(cn->factor[i+1], cn->factor[i], (cn->nfactors-i) * sizeof(mpz_t));
      memcpy(cn->factor[i], factor, sizeof(mpz_t));
      cn->nfactors++;
      break;
    }
  }
  if(cn->flag == 'P'){
    for(i = 0; i < cn->nfactors; i++){
      if(mpz_cmp(cn->factor[i], tmpq) > 0){
        memmove(cn->factor[i+1], cn->factor[i], (cn->nfactors-i-1) * sizeof(mpz_t));
        mpz_set(comp, tmpq);
        memcpy(cn->factor[i], comp, sizeof(mpz_t));
        break;
      }
    }
  }else{
    mpz_set(cn->factor[cn->nfactors-1], tmpq);
  }

  {
    static char buf[1024];
    cn->lf_digit = strlen(mpz_get_str(buf, 10, cn->factor[cn->nfactors-1]));
  }

  mpz_clear(tmpq);
  mpz_clear(tmpr);

  return CN_OK;
  
err:
  mpz_clear(factor);
  mpz_clear(tmpq);
  mpz_clear(tmpr);
  return CN_DIV_ERROR(0);
}

