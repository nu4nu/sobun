#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#include "cn.h"

#define EXPECT(_cond) do{ \
  if(!(_cond)) return CN_PARSE_ERROR(ix); \
}while(0)

static inline int read_int(const char *str, int *n){
  int x = 0;
  int i = 0;
  do{
    x = x * 10 + str[i++] - '0';
  }while(str[i] >= '0' && str[i] <= '9');
  *n = x;
  return i;
}

static int pass1(cn_t cn, const char *str){
  int ix;
  int cnt;

  if(str[0] != '('){
    return CN_NOT_CN;
  }
  if(strcmp(str, CNFILE_TERMINATOR) == 0){
    return CN_NOT_CN;
  }
  ix = 1;

  EXPECT(str[ix] >= '0' && str[ix] <= '9');
  ix += read_int(str+ix, &cn->n);

  EXPECT(str[ix] == ' ');
  ix++;

  EXPECT(str[ix] >= '0' && str[ix] <= '9');
  ix += read_int(str+ix, &cn->x);

  EXPECT(str[ix] == ' ');
  ix++;

  EXPECT(str[ix] == '(');
  ix++;

  cnt = 2;
  while(1){
    EXPECT(str[ix] >= '0' && str[ix] <= '9');
    while(str[ix] >= '0' && str[ix] <= '9') ix++;
    EXPECT(str[ix] == ' ' || str[ix] == ')');
    if(str[ix] == ')') break;
    ix++;
    cnt++;
  }
  ix++;

  EXPECT(str[ix] == ' ');
  ix++;

  EXPECT(str[ix] == '(');
  ix++;

  EXPECT(str[ix] == 'C' || str[ix] == 'P');
  cn->flag = str[ix];
  ix++;

  EXPECT(str[ix] == ' ');
  ix++;

  EXPECT(str[ix] >= '0' && str[ix] <= '9');
  ix += read_int(str+ix, &cn->lf_digit);

  EXPECT(str[ix] == ')');
  ix++;

  EXPECT(str[ix] == ')');
  ix++;

  EXPECT(str[ix] == '\0');

  cn->factor = malloc(cnt * sizeof(mpz_t));
  if(cn->factor == NULL){
    return CN_MEMORY_ERROR;
  }
  return CN_OK;
}

static char buf[CN_BUF_SIZE];

static int pass2(cn_t cn, const char *str){
  mpz_t comp;
  int ret = CN_OK;

  str = strchr(str+5, '(');
  str++;

  mpz_init(comp);
  cn_eval(comp, cn->n, cn->x);

  if(str[0] == '1' && str[1] == ')'){
    memcpy(cn->factor[0], comp, sizeof(mpz_t));
    cn->nfactors = 1;
  }else{
    int fix = 0;
    mpz_t tmpq, tmpr;
    mpz_init(tmpq);
    mpz_init(tmpr);
    do{
      mpz_t factor;
      int i = 0;
      while(*str >= '0' && *str <= '9'){
        buf[i++] = *str++;
      }
      buf[i] = '\0';
      mpz_init_set_str(factor, buf, 10);
      mpz_tdiv_qr(tmpq, tmpr, comp, factor);
      if(mpz_sgn(tmpr)){
        if(ret == CN_OK){
          ret = CN_DIV_ERROR(fix);
        }
      }else{
        mpz_set(comp, tmpq);
        if(!ISPRIME(factor)){
          if(ret == CN_OK){
            ret = CN_PRIMARITY_ERROR(fix);
          }
        }
        if(fix > 0 && mpz_cmp(cn->factor[fix-1], factor) > 0){
          if(ret == CN_OK){
            ret = CN_ORDER_ERROR(fix);
          }
        }
        memcpy(cn->factor[fix++], factor, sizeof(mpz_t));
      }
    }while(*str++ == ' ');
    mpz_clear(tmpq);
    mpz_clear(tmpr);
    memcpy(cn->factor[fix++], comp, sizeof(mpz_t));
    cn->nfactors = fix;
  }
  {
    char realflag;
    int realdigit;
    realflag = ISPRIME(comp) ? 'P' : 'C';
    if(cn->flag != realflag){
      ret |= CN_LF_PRIMARITY_ERROR;
    }
    if(cn->nfactors > 1 && realflag == 'P'
    && mpz_cmp(cn->factor[cn->nfactors-2], comp) > 0){
      ret |= CN_LF_ORDER_ERROR;
    }
    realdigit = strlen(mpz_get_str(buf, 10, comp));
    if(cn->lf_digit != realdigit){
      ret |= CN_LF_DIGIT_ERROR(realdigit);
    }
  }
  return ret;
}

int cn_set_str(cn_t cn, const char *str){
  int ret;

  ret = pass1(cn, str);
  if(ret != CN_OK){
    return ret;
  }
  return pass2(cn, str);
}

