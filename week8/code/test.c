#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	printf("ppid = %d,pid = %d",getppid(),getpid());
	while(1);
	return 0;
}
