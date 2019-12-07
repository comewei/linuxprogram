//signal函数的使用
#include"my.h"

void sigfun(int signo)              //信号处理函数及实现
{
	switch(signo)
	{
		case 1:
			printf("Catch SIGHUB\n");
			signal(1,SIG_DFL);
			break;
		case 2:
			printf("Catch SIGINT\n");
			break;
		case 3:
			printf("Catch QUIT\n");
			break;
	}
}
int main()
{
	signal(1,sigfun);          //signal第一个参数指定信号的值，
	signal(2,sigfun);  		   //第二个参数传入函数地址，指定对前面信号的处理
	signal(3,sigfun);
	printf("test pid [%d]\n",getpid());
	while(1);
	return 0;
}


