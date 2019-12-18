//两个线程共享一个环形缓冲
//缓冲区大小为5
//一个线程写
//一个线程读
#include"my.h"     
pthread_mutex_t mutex;  
sem_t space,product;                
void *customer(void *arg)
{
	while(1)
	{
		sem_wait(&space);             
		pthread_mutex_lock(&mutex);  
		//
		//生产者生产
		//
		pthread_mutex_unlock(&mutex); 
		sem_post(&product);         
	}
	return NULL;
}

void *producer(void *arg)
{
	while(1)
	{
		sem_wait(&product);             
		pthread_mutex_lock(&mutex);  
		//
		//消费者消费
		//
		pthread_mutex_unlock(&mutex); 		
		
		sem_post(&space);         
	}
	return NULL;
}

int main()
{
	pthread_t tid[2];
	int i,ret;
	void *(*pt[2])();
	
	pt[0]=customer;
	pt[1]=producer;
	ret = pthread_mutex_init(&mutex,NULL);
	ret = sem_init(&space,0,5);        //space初值5
	ret = sem_init(&product,0,0);      //product初值0
	for(i=0;i<2;i++)
	{
		ret = pthread_create(&tid[i],NULL,pt[i],NULL);
		if(ret!=0)
		{
			perror("create thread!\n");
			exit(1);
		} 
	}
	for(i=0;i<2;i++)
	{
		pthread_join(tid[i],NULL);
	}
	return 0;
}

/*
pthread_yield()
*/











