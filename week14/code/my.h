#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<sys/time.h>
#include<sys/types.h>
#define NUM 4
struct sendval{
	int n;
	int s;
	long time;
};



void *thread_function(void *arg);
int run_now=1;
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
