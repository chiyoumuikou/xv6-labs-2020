#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
  if(argc < 2){
    printf("xargs: You should give some arguments.");
    exit(0);
  }
  int i;
  char *xargv[1024];
  for(i=0;i<argc-1;i++){
    xargv[i]=argv[i+1];
  }
  char buf[512];
  int res=1;
  char* p=buf;
  while(res){
    int word_st=0,word_ed=0;
    while(1){
      res=read(0,p,1);
      word_ed++;
      if(*p==' '||*p=='\n'||!res){
        *p=0;
        xargv[i]=&buf[word_st];        
        //printf("%d %d %s\n",word_st,word_ed,xargv[i]);
        i++;
        word_st=word_ed;
      }
      if(*p=='\n'||!res) break;
      //word_ed++;
      p++;
    }
    if(fork()==0){
      exec(xargv[0],xargv);
      printf("xargs: exec error.");
    }
    wait(0);
  }
  exit(0);
}
