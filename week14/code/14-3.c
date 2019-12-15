//参数传递问题
//线程在进程内部运行，线程与进程的进程号相同
#include"my.h"

void fun(void *arg)
{
	printf("Worker : thread is running . pid=%d\n",getpid());
}

int main()
{
	pthread_t tid;
	int ret;
	ret = pthread_create(&tid,NULL,(void *(*)())fun,NULL);
	if(ret != 0)
	{
		perror("create failed!\n");
		return -1;
	}
	//pthread_join(tid,NULL);
	printf("Master %d  :  Alll done!\n",getpid());
	return 0;
}

/*
int pthread_create(pthread_t *restrict tidp,const pthread_attr_t *restrict_attr,
					void* (*start_rtn)(void*),void *restrict arg)

返回值：成功返回0，出错返回出错编号
参数：
	第一个参数为指向进程标识符的指针
	第二个参数用来设置线程属性
	第三个参数是线程运行函数的地址
	第四个参数是运行函数的参数
注意：在编译时记得加上 -lpthread 参数调用静态链接库，因为pthread不是Linux的默认库
*/

/*
int pthread_join(pthread_t thread,void **value_ptr)
参数：
	第一个参数为等待退出线程的线程号
	第二个参数为退出线程的返回值
*/
