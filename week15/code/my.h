#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<string.h>
#include<sys/time.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>

#define LOOP 1000000
#define NUM 4


//homework  begin
#define ARRAY_NUM 2
#define ARRAR_SIZE 1000
void initarray(int *a,int n) 
{
	srand((int)time(0));
	for(int i=0;i<n;i++)
	{
		a[i] = 1 + (int)(1000.0 * rand()/(RAND_MAX + 1.0));
	}

};
//homework end

#define TN 100
#define WRITER_FIRST  
