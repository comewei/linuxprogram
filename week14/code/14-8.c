#include"my.h"

void *thread_function(void *arg);
int row_now=1;
void *thread_function(void *arg)
{
	int print_count2=0;
	while(print_count2++<5)
	{
		if(run_now == 2)
		{
			printf("function thread is running\n");
			run_now=1;
		}else
		{
			printf("function thread is sleep\n");
			sleep(1);
		}
	}
	pthread_exit(NULL);
}
