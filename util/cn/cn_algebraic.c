#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#include "cn.h"

/*
 * [Transformation]
 *
 * Phi_n(x^(p^e)) =
 *   n % p == 0 ? Phi_(n * p^e) (x)
 *              : Pi{i=0..e} Phi_(n * p^i) (x)
 *
 * to prevent the degree from growing larger,
 *
 * Phi_n(x^(p^e)) =
 *   n % p == 0 ? Phi_n (x^(p^e))  [no transformation]
 *              : Pi{i=0..e-1} Phi_(p*n) (x^(p^i)) * Phi_n(x)
 */

static int algebraic_factor(cn_t cn, int k, int p){
  int factor[4];
  int faccnt[4];
  int pfactors = 0;
  int n = cn->n;
  int i, j;

  {
    int pp = p;
    p = 1;
    pfactors = 0;
    if((pp & 0x1) == 0){
      if((n & 0x1) == 0){
        do{
          pp >>= 1;
          p <<= 1;
        }while((pp & 0x1) == 0);
      }else{
        int cnt = 0;
        do{
          pp >>= 1;
          cnt++;
        }while((pp & 0x1) == 0);
        factor[pfactors] = 2;
        faccnt[pfactors++] = cnt;
      }
    }
    for(i = 3; i <= pp / i; i += 2){
      if(pp % i != 0) continue;
      if(n % i == 0){
        do{
          pp /= i;
          p *= i;
        }while(pp % i == 0);
      }else{
        int cnt = 0;
        do{
          pp /= i;
          cnt++;
        }while(pp % i == 0);
        factor[pfactors] = i;
        faccnt[pfactors++] = cnt;
      }
    }
    if(pp > 1){
      if(n % pp == 0){
        p *= pp;
      }else{
        factor[pfactors] = pp;
        faccnt[pfactors++] = 1;
      }
    }
  }
  if(pfactors == 0){
    mpz_t *afs = aur_factor(cn->factor[cn->nfactors-1], p*n, k);
    if(afs == NULL) return 0;
    cn->newfactor = afs;
    return 2;
  }
  {
    int kp;
    int nnewfactors = 0;
    mpz_t comp;
    memcpy(comp, cn->factor[cn->nfactors-1], sizeof(mpz_t));

    cn->newfactor = NULL;
    kp = 1;
    for(i = 0; i < p; i++){
      kp *= k;
    }
    /*if(pfactors >= 1)*/{
      int f = factor[0];
      int cnt = faccnt[0];
      int kpq = kp;
      int pnq = p*n;
      mpz_t prev, cur, alf;
      mpz_init(prev);
      mpz_init(cur);
      mpz_init(alf);
      mpz_set_ui(prev, 1);
      for(i = 0; i <= cnt; i++){
        cn_eval(cur, n, kpq);
        mpz_divexact(alf, cur, prev);
        mpz_gcd(alf, alf, comp);
        if(mpz_cmp_ui(alf, 1) != 0){
          mpz_t *afs = aur_factor(alf, pnq, k);
          if(afs != NULL){
            nnewfactors += 2;
            cn->newfactor = realloc(cn->newfactor, nnewfactors * sizeof(mpz_t));
            memcpy(cn->newfactor[nnewfactors-2], afs[0], sizeof(mpz_t));
            memcpy(cn->newfactor[nnewfactors-1], afs[1], sizeof(mpz_t));
            free(afs);
          }else if(mpz_cmp(alf, comp) != 0){
            nnewfactors += 1;
            cn->newfactor = realloc(cn->newfactor, nnewfactors * sizeof(mpz_t));
            mpz_init(cn->newfactor[nnewfactors-1]);
            mpz_swap(cn->newfactor[nnewfactors-1], alf);
          }
        }
        mpz_swap(prev, cur);
        pnq *= f;
        {
          int tmp = kpq;
          int _;
          for(_ = 1; _ < f; _++){
            kpq *= tmp;
          }
        }
      }
      mpz_clear(prev);
      mpz_clear(cur);
      mpz_clear(alf);
    }
    if(pfactors >= 2){
      int f0 = factor[0];
      int f1 = factor[1];
      int cnt0 = faccnt[0];
      int cnt1 = faccnt[1];
      int kpr = kp;
      int pnr = p*n;
      mpz_t prev, cur, alf;
      mpz_init(prev);
      mpz_init(cur);
      mpz_init(alf);
      for(i = 1; i <= cnt1; i++){
        int kpqrprev = kpr;
        int kpqrcur;
        int pnqr;
        kpqrcur = kpr;
        for(j = 1; j < f1; j++){
          kpqrcur *= kpr;
        }
        kpr = kpqrcur;
        pnr *= f1;
        pnqr = pnr;
        mpz_set_ui(prev, 1);
        for(j = 0; j <= cnt0; j++){
          cn_eval(alf, n, kpqrprev);
          cn_eval(cur, n, kpqrcur);
          mpz_divexact(cur, cur, alf);
          mpz_divexact(alf, cur, prev);
          mpz_gcd(alf, alf, comp);
          if(mpz_cmp_ui(alf, 1) != 0){
            mpz_t *afs = aur_factor(alf, pnqr, k);
            if(afs != NULL){
              nnewfactors += 2;
              cn->newfactor = realloc(cn->newfactor, nnewfactors * sizeof(mpz_t));
              memcpy(cn->newfactor[nnewfactors-2], afs[0], sizeof(mpz_t));
              memcpy(cn->newfactor[nnewfactors-1], afs[1], sizeof(mpz_t));
              free(afs);
            }else if(mpz_cmp(alf, comp) != 0){
              nnewfactors += 1;
              cn->newfactor = realloc(cn->newfactor, nnewfactors * sizeof(mpz_t));
              mpz_init(cn->newfactor[nnewfactors-1]);
              mpz_swap(cn->newfactor[nnewfactors-1], alf);
            }
          }
          mpz_swap(prev, cur);
          pnqr *= f0;
          {
            int tmpprev = kpqrprev;
            int tmpcur = kpqrcur;
            int _;
            for(_ = 1; _ < f0; _++){
              kpqrprev *= tmpprev;
              kpqrcur *= tmpcur;
            }
          }
        }
      }
      mpz_clear(prev);
      mpz_clear(cur);
      mpz_clear(alf);
    }
    return nnewfactors;
  }
}

int cn_check_algebraic_factor(cn_t cn){
  int x = cn->x;
  int p;

  for(p = 2; (1 << p) <= x; p++);
  while(--p > 1){
    int k = 2;
    while(1){
      int m = 1;
      int i;
      for(i = 0; i < p; i++){
        m *= k;
      }
      if(m == x){
        return algebraic_factor(cn, k, p);
      }
      if(m > x) break;
      k++;
    }
  }
  /* not perfect power */
  {
    mpz_t *afs = aur_factor(cn->factor[cn->nfactors-1], cn->n, x);
    if(afs == NULL) return 0;
    cn->newfactor = afs;
    return 2;
  }
}

