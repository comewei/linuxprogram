#include"my.h"
int main()
{
	printf("caller2 pid = %d,ppid = %d\n",getpid(),getppid());
	execlp("test1","./test1","123","hello","world",NULL);
	printf("execlp after calling\n");
	
	return 0;
}
