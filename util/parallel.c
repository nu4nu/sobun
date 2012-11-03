#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

static char *readall(FILE *fp){
  char *buf;
  size_t sz = 65536;
  size_t len = 0;
  size_t ret;

  buf = malloc(sz);
  if(buf == NULL){
    return NULL;
  }

  do{
    ret = fread(buf + len, sizeof(char), sz - len, fp);
    len += ret;
    if(ret < sz){
      if(ferror(fp)){
        free(buf);
        return NULL;
      }else{
        buf[len] = '\0';
        return buf;
      }
    }
    sz += sz;
    buf = realloc(buf, sz);
    if(buf == NULL){
      return buf;
    }
  }while(1);
}

int main(int argc, char *argv[]){
  char *buf;
  char *cur;
  FILE *fp;
  int nprocs;
  int running;

  if(argc < 2){
    printf("Usage: %s <nprocs> [commandfile]\n", argv[0]);
    return 0;
  }
  nprocs = atoi(argv[1]);
  if(nprocs < 1){
    return 0;
  }
  if(argc > 2){
    fp = fopen(argv[2], "rb");
    if(fp == NULL){
      printf("%s doesn't exist!\n", argv[2]);
      return 0;
    }
  }else{
    fp = stdin;
  }

  buf = readall(fp);
  fclose(fp);

  cur = buf;

  running = 0;
  while(cur != NULL && *cur != '\0'){
    char *pos;
    pid_t pid;
    if(running == nprocs){
      int status;
      wait(&status);
      running--;
    }
    pos = strchr(cur, '\n');
    if(pos != NULL){
      *pos++ = '\0';
    }
    pid = fork();
    if(pid < 0){
      break;
    }else if(pid == 0){
      execlp("sh", "sh", "-c", cur, (char*)NULL);
      _exit(0);
    }else{
      running++;
    }
    cur = pos;
  }
  while(running > 0){
    int status;
    wait(&status);
    running--;
  }

  free(buf);

  return 0;
}

