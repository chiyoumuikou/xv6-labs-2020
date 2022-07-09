#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void process(int p[]){
  close(p[1]);
  int i;
  if(read(p[0],&i,sizeof(i))){
    printf("prime %d\n",i);
    int p1[2];
    pipe(p1);
    int j;
    if(fork()){
      close(p1[0]);
      while(read(p[0],&j,sizeof(j))){
        if(j%i){
          write(p1[1],&j,sizeof(j));
        }
      }
      close(p[0]);
      close(p1[1]);
      wait(0);
    }
    else{
      process(p1);
    }
  }
  exit(0);
}

int
main(){
  int p[2];
  pipe(p);
  if(fork()){
    close(p[0]);
    for(int i=2;i<36;i++)
    	write(p[1],&i,sizeof(i));
    close(p[1]);
    wait(0);
  }
  else{
    process(p);
  }
  exit(0);
}
