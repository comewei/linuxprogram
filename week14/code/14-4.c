#include"my.h"

void *fun(void *arg)
{
	int TID = pthread_self();    //pthread_self()返回线程的线程号
	//int TID = syscall(SYS-gettid);
	printf("worker---%d : getttid return %d\n",TID,TID);
	printf("worker---%d : pthread_self return %p\n",TID,(void*)pthread_self());
	printf("worker---%d : will exit!\n",TID);
	pthread_exit(NULL);
	return NULL;
}

int main()
{
	pthread_t tid;
	int ret;
	ret = pthread_create(&tid,NULL,fun,NULL);
	if(ret != 0)
	{
		perror("create failed!\n");
		return -1;
	}
	pthread_join(tid,NULL);
	ret = pthread_create(&tid,NULL,fun,NULL);
	if(ret != 0)
	{
		perror("create failed!\n");
		return -1;
	}
	pthread_join(tid,NULL);
	printf("Master %d  :  Alll done!\n",getpid());
	return 0;
}

/*
void pthread_exit(void *retval)
参数为函数的返回值，返回值会传给pthread_join()的第二个参数
*/
