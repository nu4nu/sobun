#include <stdio.h>
#include <gmp.h>

#include "cn.h"

void cn_out_str(FILE *fp, cn_t cn){
  int i;

  fprintf(fp, "(%d %d (", cn->n, cn->x);
  if(cn->nfactors == 1){
    fputc('1', fp);
  }else{
    for(i = 0; i < cn->nfactors-1; i++){
      if(i != 0){
        fputc(' ', fp);
      }
      mpz_out_str(fp, 10, cn->factor[i]);
    }
  }
  fprintf(fp, ") (%c %d))\n", cn->flag, cn->lf_digit);
}

