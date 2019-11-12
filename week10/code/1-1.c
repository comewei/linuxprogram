#include"my.h"
static void callback1()
{
	printf("------callback1-------");
}
static void callback2()
{
	printf("------callback2-------");
}
static void callback3()
{
	printf("------callback3-------");
}

static void __attribute__((constructor)) before_main(void)
{
	printf("------before main------");
}
static void __attribute__((destructor)) after_main(void)
{
	printf("------after main------");
}


int main()
{
	atexit(callback1);
	atexit(callback2);
	atexit(callback3);
	
	FILE *fp;
	char buf[] = {"hello world\n"};
	if((fp = fopen("test.dat","w+")) == NULL)
	{
		perror("fail to create file!\n");
		return -1;
	}
	if(fputs(buf,fp) == EOF)                  //fputs使用全缓冲
	{
		perror("fail to fputs file!\n");
		return -1;
	}
	printf("test message!\n");
	//exit(0);
	//_exit(0);
	return 0;
}


