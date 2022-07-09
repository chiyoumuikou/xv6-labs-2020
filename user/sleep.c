#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	if(argc<=1) fprintf(2,"You should give a sleep number.\n");
	int sleepnum=atoi(argv[1]);
	sleep(sleepnum);
	exit(0);
}

