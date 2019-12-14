#include "my.h"               //与14-2.c一起说明线程派生和进程派生的时间开销

void * threadfun(void *arg)
{
	pthread_exit(NULL);
}

int main()
{
	pid_t pid;
	int i,ret;
	struct timeval tv1,tv2;
	struct timezone tz;
	gettimeofday(&tv1,&tz);
	
	for(i=0;i<1000;i++)
	{
		pid=fork();
	}
	
	gettimeofday(&tv2,&tz);
	printf("running time is %ld\n",tv2.tv_usec-tv1.tv_usec);
	return 0;
}
