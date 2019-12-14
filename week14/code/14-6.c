#include"my.h"
int arg=0;
void foo(void *v)
{
	int n=(int)v,*sum,i;
	arg++;
	sum=(int *)malloc(sizeof(int));
	//*sum=0;
	printf("%d : global arg=%d\n",n,arg);
	for(i=0;i<=(n+1)*100;i++)
	{
		*sum+=i;
	}
	int arg;
	arg=n*100;
	printf("%d : local arg=%d,sum=%d\n",n,arg,*sum);
	//int *pt = (int *)malloc(sizeof(int));
	//*pt=0;
	//for(int i=0;i<arg;i++)
	//{
	//	*pt += i;
	//}
	pthread_exit((void *)sum);
}

int main()
{
	pthread_t tid[NUM];
	int rev[NUM],**pt;
	//void* rst;
	for(int i=0;i<NUM;i++)
	{
		rev[i] = pthread_create(&tid[i],NULL,(void *(*)())foo,(void*)i);
		if(rev[i] != 0)
		{
			perror("thread failed!\n");
			exit(-1);
		}
		
		pthread_join(tid[i],(void **)&pt);
		printf("master %d : arg=%d,sum=%d\n",i,arg,*pt);
	}
	
}

/*
pthread_join(pthread_t thread,void **value_ptr)
参数：
	thread:等待退出线程的线程号
	value_ptr:退出线程的返回值

*/
