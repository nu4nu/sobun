#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#include "cn.h"

static char buf[CN_BUF_SIZE+16];
static cn_t cn;

static int flag_pretty;
static int flag_aur;
static int flag_echo;
static int flag_composite;
static int flag_prime;

int parse_opts(int argc, char *argv[]){
  flag_pretty = 0;
  flag_aur = 0;
  flag_echo = 0;
  flag_composite = 1;
  flag_prime = 1;
  return 0;
}

void handle_each_line(){
  int ret;
  ret = cn_set_str(cn, buf);
  if(ret != CN_OK){
    if(ret == CN_MEMORY_ERROR || ret == CN_NOT_CN) return;
    if(CN_IS_PARSE_ERROR(ret)){
      int cnt = CN_PARSE_ERROR_POS(ret);
      fprintf(stderr, "parse error:\n%s\n", buf);
      while(cnt--){
        fputc(' ', stderr);
      }
      fputs("^\n\n", stderr);
    }else{
      fprintf(stderr, "%s\n", buf);
      fprintf(stderr, "calc error retval = %d, reg1 = %d, reg2 = %d\n", ret&0xff, (ret>>8)&0xff, ret>>16);
      cn_free(cn);
    }
    return;
  }

  ret = cn_check_algebraic_factor(cn);
  if(ret > 0){
    int i;
    char tmpbuf[CN_BUF_SIZE+10];
//    if(flag_echo){
      puts(buf);
//    }
    for(i = 0; i < ret; i++){
      char flag = ISPRIME(cn->newfactor[i]) ? 'P' : 'C';
      int digit = strlen(mpz_get_str(tmpbuf, 10, cn->newfactor[i]));
      printf("%c%d = ", flag, digit);
      mpz_out_str(stdout, 10, cn->newfactor[i]);
      puts("");
      mpz_clear(cn->newfactor[i]);
    }
    puts("");
    free(cn->newfactor);
  }else{
    if(flag_pretty){
      printf("%c%d = ", cn->flag, cn->lf_digit);
    }
    mpz_out_str(stdout, 10, cn->factor[cn->nfactors-1]);
    puts("");
  }
  cn_free(cn);
}

int main(int argc, char *argv[]){
  if(parse_opts(argc, argv) < 0){
    printf("komata\n");
    return 0;
  }

  cn_init(cn);
  cnpoly_init();
  aurpoly_init();
  powlist_init();
  while(fgets(buf, CN_BUF_SIZE, stdin) != NULL){
    char *pos = strpbrk(buf, "\r\n");
    if(pos == NULL){
      fputs("Input too long\n", stderr);
      exit(EXIT_FAILURE);
    }
    *pos = '\0';
    handle_each_line();
  }
  cn_clear(cn);
  cnpoly_free();
  aurpoly_free();
  powlist_free();

  return 0;
}

