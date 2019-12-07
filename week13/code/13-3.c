//sigaction函数
#include"my.h"

#define PROMPT "Do you want terminate program ?"
char *prompt = PROMPT;
void ctrl_c(int signo)    //用户定义的信号处理函数
{
	fprintf(stderr,prompt);
	//fprintf(stderr,"Do you want terminate program ?\n");
}

int main()
{
	struct sigaction act;
	act.sa_handler = ctrl_c;        //将sigaction结构体中的信号处理函数与用户定义的绑定
	sigemptyset(&act.sa_mask);		
	act.sa_flags=0;
	if(sigaction(SIGINT,&act,NULL) < 0)
	{
		fprintf(stderr,"Install signal Action Error:%s\n",strerror(errno));
		exit(1);
	}
	printf("Process id is %d\n",getpid());
	while(1);
}
/*
sigaction(int signum,const struct sigaction *act,struct sigaction *oldact)
第一个参数为信号值
第二个参数为sigaction结构指针，内含对特定信号的处理
第三个参数用来保存原来对相应信号处理
*/

/*
struct sigaction {
         union{
         	__sighandler_t _sa_handler;      //指向用户指定信号处理函数，只有一个参数，不能传递信号值以外信息
            void (*_sa_sigaction)(int,struct siginfo *, void *)；    
            //第一个参数信号值，第二个指向结构体中包含信号携带数据值，posix中没有规范第三个参数标准，可为NULL
            }
            _usigset_t sa_mask；     //指定在信号处理函数中那些信号被阻塞，缺省情况下当前信号本身被阻塞
            unsigned long sa_flags；   //可以把标志位看成信号是否是否传递参数的开关，设置该位，则传递参数
            void (*sa_restorer)(void)；      //已过时
}
*/

