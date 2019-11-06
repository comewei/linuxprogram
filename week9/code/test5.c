#include"my.h"
int main(int argc ,char *argv[])
{
	printf("test5:pid=%d,ppid=%d\n",getpid(),getppid());
	for(int i=0;i<argc;i++)
	{
		printf("test5:%d  :  %s\n",i,argv[i]);
	}
	printf("---------test5 end----------\n");
	
	return 0;
}
