#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "cn.h"

static aurpoly_t aurCpoly[CN_MAXN+1];
static aurpoly_t aurDpoly[CN_MAXN+1];

static int q[CN_MAXPHI+1];

/* a: positive integer, b: odd positive */
static int jacobi(int a, int b){
  int r = 1;
  while(b != 1){
    a %= b;
    while((a & 0x3) == 0){
      a >>= 2;
    }
    if((a & 0x1) == 0){
      a >>= 1;
      if((b & 0x7) == 3 || (b & 0x7) == 5) r = -r;
    }
    if((a & b & 0x3) == 3) r = -r;
    a ^= b;
    b ^= a;
    a ^= b;
  }
  return r;
}

static int q_update(int N){
  static int aurtable[4][4] = {
    {  0,  0,  0,  0},  /* dummy */
    {  1,  1,  1,  1},
    {  2,  0, -2,  0},
    {  1, -1,  1, -1}
  };
  int factor[4];
  int nfactors = 0;
  int n = N;
  int phi;
  int k, i;

  if((n & 0x1) == 0){
    n >>= 1;
    factor[nfactors++] = 2;
    phi = 2;
  }else{
    phi = 1;
  }
  for(i = 3; i <= n / i; i += 2){
    if(n % i != 0) continue;
    n /= i;
    factor[nfactors++] = i;
    phi *= i-1;
  }
  if(n > 1){
    factor[nfactors++] = n;
    phi *= n-1;
  }
  phi = (phi+1) >> 1;

  q[0] = 0;
  k = 1;
  do{
    {
      int kk;
      kk = k + k - 1;
      for(i = 0; i < nfactors; i++){
        if(kk % factor[i] == 0){
          q[kk] = 0;
          goto nojacobi;
        }
      }
      q[kk] = jacobi(N, kk);
nojacobi:;
    }
    {
      int r = aurtable[N & 0x3][k & 0x3];
      for(i = 0; i < nfactors; i++){
        if(k % factor[i] == 0){
          r *= factor[i]-1;
        }else{
          r = -r;
        }
      }
      q[k+k] = r;
    }
    k++;
  }while(k <= phi);

  return phi;
}

/* assume n is square-free */
static void aur_poly_init(int n){
  int64_t *c, *d;
  int phi;
  int k, kk;

  phi = q_update(n);

  c = malloc((phi+1) * sizeof(int64_t));
  d = malloc(phi * sizeof(int64_t));
  c[0] = 1;
  d[0] = 1;

  k = 1;
  kk = 2;
  while(1){
    int64_t r;
    int i;

    if(kk > phi) break;
    r = 0;
    for(i = 0; kk - 2*i > 0; i++){
      r += n * q[kk - 2*i - 1] * d[i] - q[kk - 2*i] * c[i];
    }
    assert(r % kk == 0);
    c[k] = r / kk;
    kk++;

    if(kk > phi) break;
    r = 0;
    for(i = 0; kk - 2*i > 0; i++){
      r -=     q[kk - 2*i - 1] * d[i] - q[kk - 2*i] * c[i];
    }
    assert(r % kk == 0);
    d[k] = r / kk;
    kk++;
    k++;
  }
  for(k = phi; k > phi - k; k--){
    c[k] = c[phi - k];
    d[k-1] = d[phi - k];
  }
  aurCpoly[n].poly = c;
  aurCpoly[n].degree = phi;
  aurDpoly[n].poly = d;
  aurDpoly[n].degree = phi-1;
}

aurpoly_t aur_Cpoly(int n){
  if(aurCpoly[n].poly == NULL){
    aur_poly_init(n);
  }
  return aurCpoly[n];
}

aurpoly_t aur_Dpoly(int n){
  if(aurDpoly[n].poly == NULL){
    aur_poly_init(n);
  }
  return aurDpoly[n];
}

void aurpoly_init(){
  int i;
  for(i = 0; i <= CN_MAXN; i++){
    aurCpoly[i].poly = NULL;
    aurDpoly[i].poly = NULL;
  }
}

void aurpoly_free(){
  int i;
  for(i = 0; i <= CN_MAXN; i++){
    free(aurCpoly[i].poly);
    free(aurDpoly[i].poly);
  }
}

