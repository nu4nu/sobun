#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cn.h"

static cnpoly_t cnpoly[CN_MAXN+1];

static inline void get_inversed_poly(int N, int n){
  int degree;
  int i;

  degree = cnpoly[n].degree;

  cnpoly[N].poly = malloc((degree+1) * sizeof(int));

  cnpoly[N].poly[0] = 1;
  for(i = 1; i <= degree; i++){
    cnpoly[N].poly[i] = -cnpoly[n].poly[i];
    i++;
    cnpoly[N].poly[i] = cnpoly[n].poly[i];
  }
  cnpoly[N].degree = degree;
}

static inline void get_multipled_poly(int N, int n){
  int degree;
  int p = N / n;
  int i, j;

  degree = p * cnpoly[n].degree;

  cnpoly[N].poly = malloc((degree+1) * sizeof(int));

  cnpoly[N].poly[0] = 1;
  for(i = j = 1; i <= degree; ){
    int k = p - 1;
    do{
      cnpoly[N].poly[i++] = 0;
      k--;
    }while(k > 0);
    cnpoly[N].poly[i++] = cnpoly[n].poly[j++];
  }
  cnpoly[N].degree = degree;
}

static void cn_poly_init_with_factors(int N, int *factor, int nfactors){
  if(nfactors == 0){  /* N == 1 */
    cnpoly[1].poly = malloc(2 * sizeof(int));
    cnpoly[1].poly[0] = -1;
    cnpoly[1].poly[1] = 1;
    cnpoly[1].degree = 1;
  }else if(nfactors == 1){
    int i;
    cnpoly[N].poly = malloc(N * sizeof(int));
    for(i = 0; i < N; i++){
      cnpoly[N].poly[i] = 1;
    }
    cnpoly[N].degree = N - 1;
  }else if(factor[0] == 2){
    int n = N >> 1;
    cn_poly_init_with_factors(n, factor+1, nfactors-1);
    get_inversed_poly(N, n);
  }else if(nfactors == 2){
    int *poly;
    int degree;
    int i, j;

    degree = N - factor[0] - factor[1] + 1;
    poly = malloc((degree+1) * sizeof(int));
    memset(poly, 0, degree * sizeof(int));
    for(i = 0; i < degree; i += factor[0]){
      for(j = i; j < degree; j += factor[1]){
        poly[j]++;
        poly[j+1]--;
      }
    }
    poly[degree] = 1;

    cnpoly[N].poly = poly;
    cnpoly[N].degree = degree;
  }else{
    int *poly;
    int degree;
    int f01, f12, f20;
    int i, j, k, l, p, _;
    assert(nfactors == 3);

    f01 = factor[0] * factor[1];
    f12 = factor[1] * factor[2];
    f20 = factor[2] * factor[0];
    degree = (factor[0]-1) * (factor[1]-1) * (factor[2]-1);
    poly = malloc((degree+1) * sizeof(int));
    memset(poly, 0, (degree+1) * sizeof(int));

    i = 0;
    p = 1;
    _ = 0xd28508;
    do{
      for(j = i; j < degree; j += f01){
        for(k = j; k < degree; k += f20){
          for(l = k; l < degree; l += f12){
            poly[l] += p;
          }
        }
      }
      {
        int code = _ & 0x7;
        _ >>= 3;
        i += code > 3 ? -factor[code - 4] : factor[code];
        p = -p;
      }
    }while(_ != 0);

    for(i = 0; i < degree; i++){
      poly[i+1] += poly[i];
    }
    
    cnpoly[N].poly = poly;
    cnpoly[N].degree = degree;
  }
}

static void cn_poly_init(int N){
  int factor[4];
  int nfactors = 0;
  int n = N;
  int p;
  int i;
  if((n & 0x1) == 0){
    do{
      n >>= 1;
    }while((n & 0x1) == 0);
    factor[nfactors++] = 2;
    p = 2;
  }else{
    p = 1;
  }
  for(i = 3; i <= n / i; i += 2){
    if(n % i != 0) continue;
    do{
      n /= i;
    }while(n % i == 0);
    factor[nfactors++] = i;
    p *= i;
  }
  if(n > 1){
    factor[nfactors++] = n;
    p *= n;
  }
  cn_poly_init_with_factors(p, factor, nfactors);
  if(N != p){
    get_multipled_poly(N, p);
  }
}

cnpoly_t cn_poly(int N){
  if(cnpoly[N].poly == NULL){
    cn_poly_init(N);
  }
  return cnpoly[N];
}

void cnpoly_init(){
  int i;
  for(i = 0; i <= CN_MAXN; i++){
    cnpoly[i].poly = NULL;
  }
}

void cnpoly_free(){
  int i;
  for(i = 0; i <= CN_MAXN; i++){
    free(cnpoly[i].poly);
  }
}

