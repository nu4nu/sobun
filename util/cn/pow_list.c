#include <stdlib.h>
#include <gmp.h>

#include "cn.h"

static struct {
  mpz_t *list;
  int degree;
} powlist[CN_MAXX+1];

static inline void pow_list_append(int x, int d){
  mpz_t *list = powlist[x].list;
  int i;

  for(i = powlist[x].degree+1; i <= d; i++){
    mpz_init(list[i]);
    mpz_mul_ui(list[i], list[i-1], x);
  }

  powlist[x].degree = d;
}

static inline void pow_list_init(int x, int d){
  powlist[x].list = malloc((CN_MAXPHI+1) * sizeof(mpz_t));
  mpz_init_set_ui(powlist[x].list[0], 1);
  mpz_init_set_ui(powlist[x].list[1], x);
  powlist[x].degree = 1;
  pow_list_append(x, d);
}

mpz_t *pow_list(int x, int d){
  if(powlist[x].list == NULL){
    pow_list_init(x, d);
  }else if(powlist[x].degree < d){
    pow_list_append(x, d);
  }
  return powlist[x].list;
}

void powlist_init(){
  int i;
  for(i = 0; i <= CN_MAXX; i++){
    powlist[i].list = NULL;
  }
}

void powlist_free(){
  int i;
  for(i = 0; i <= CN_MAXX; i++){
    if(powlist[i].list != NULL){
      int j;
      for(j = 0; j <= powlist[i].degree; j++){
        mpz_clear(powlist[i].list[j]);
      }
      free(powlist[i].list);
    }
  }
}

