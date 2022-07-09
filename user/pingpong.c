#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[1024];

int
main()
{
  int p1[2],p2[2];
  pipe(p1);
  pipe(p2);
  int pid = fork();
  if(pid > 0){
    close(p1[0]);
    write(p1[1],"a",1);
    close(p1[1]);
    close(p2[1]);
    int res=read(p2[0],buf,1);
    close(p2[0]);
    if(res==1) printf("%d: received pong\n",getpid());
  }
  else if(pid == 0){
    close(p1[1]);
    int res=read(p1[0],buf,1);
    if(res==1) printf("%d: received ping\n",getpid());
    close(p2[0]);
    write(p2[1],"a",1);
    close(p2[1]);
  }
  else{
    printf("fork error\n");
  }
  exit(0);
}
