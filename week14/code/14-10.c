#include"my.h"

pthread_rwlock_t rwlock;
int gn=0;

void *work(void *par)
{
	int i;
	//pthread_rwlock_wrlock(&rwlock);           //获取一个写入锁
	for(i=0;i<LOOP;i++)
	{
		gn++;
	}
	//pthread_rwlock_unlock(&rwlock);           //释放写入锁
	return NULL;
}

int main()
{	
	pthread_t tid[NUM];
	char err[1024];
	int i,ret;
	
	ret = pthread_rwlock_init(&rwlock,NULL);     //初始化读写锁
	
	if(ret != 0)
	{
		fprintf(stderr,"init rw lock failed  (%s) !\n",strerror_r(ret,err,sizeof(err)));
		exit(1);
	}
	
	//pthread_rwlock_wrlock(&rwlock);                 //初始化写锁
	for(i=0;i<NUM;i++)
	{
		ret = pthread_create(&tid[i],NULL,work,NULL);
		if(ret != 0)
		{
			perror("create failed!\n");
			exit(2);
		}
	}
	
	//pthread_rwlock_unlock(&rwlock);
	for(i=0;i<NUM;i++)
	{
		pthread_join(tid[i],NULL);
	}
	
	pthread_rwlock_destroy(&rwlock);               //销毁读写锁
	
	printf("thread number       :%d\n",NUM);
	printf("loop per thread     :%d\n",LOOP);
	printf("expect result       :%d\n",LOOP*NUM);
	printf("actul result        :%d\n",gn);
	
	return 0;
		
}



/*
读写锁与互斥量类似，不过读写锁允许更高的并行性。
读写锁有三种状态：读模式下加锁装态、写模式下加锁状态、不加锁状态
当读写锁以读模式锁住时，它是一共享模式锁住的
当读写锁以写模式锁住时，它是以独占模式锁住的
*/

