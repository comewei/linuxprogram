#include"my.h"
static int sig_cnt[NSIG];          //NSIG宏定义表示该系统支持的最多信号数
static volatile sig_atomic_t get_SIGINT=0;

void handler(int signo)          //用户定义的信号处理函数
{
	if(signo == SIGINT)			//发送信号1时结束进程
	{
		get_SIGINT=1;
	}else
	{
		sig_cnt[signo]++;
	}
}

int main(int argc,char *argv[])
{
	int i=0;
	sigset_t blockall_mask;
	sigset_t empty_mask;
	printf("%s:PID is %d\n",argv[0],getpid());
	printf("NSIG=%d\n",NSIG);
	
	for(i=1;i<NSIG;i++)
	{
		if(i==SIGKILL || i==SIGSTOP || i==32 || i==33)      //不接受32，33信号
		{
			continue;
		}
		if(signal(i,&handler)==SIG_ERR)         //将除以上四个以外的信号都和用户定义的信号处理函数绑定
		{
			fprintf(stderr,"signal for signo(%d) failed (%s)\n",i,strerror(errno));
		}
	}
	
	if(argc>1)
	{
		int sleep_time = atoi(argv[1]);
		sigfillset(&blockall_mask);
		if(sigprocmask(SIG_SETMASK,&blockall_mask,NULL) == -1)     
		{
			fprintf(stderr,"setprocmasks to release all signal failed (%s)\n",strerror(errno));
			return -3;
		}
	}
	
	while(!get_SIGINT)
	{
		continue;
	}
	
	printf("%-10s%-10s\n","signo","times");
	printf("-----------------------------\n");
	
	for(i=1;i<NSIG;i++)
	{
		if(sig_cnt[i] != 0)
		{
			printf("%-10d %-10d\n",i,sig_cnt[i]);
		}
	}
	
	return 0;
}


/*
typedef struct{
	unsigned long sig[_NSIG_WORDS]；
}sigset_t
信号集用来描述信号的集合，linux所支持的所有信号可以全部或部分的出现在信号集中
主要与信号阻塞相关函数配合使用

int sigemptyset(sigset_t *set)//初始化由set指定的信号集，信号集里面的所有信号都被清空
int sigfillset(sigset_t *set)//set指向的信号集中将包含linux支持的64种信号
*/

/*
有时不希望在接到信号就立即停止当前执行去处理信号，也不希望忽略该信号，而是延后一段时间去调用信号处理函数，通过阻塞实现
操作系统在信号被接触阻塞前不会将信号传递出去，被阻塞的信号也不会影响进程的行为，信号只是暂时被阻止传递

int sigprocmask(ubt how,const sigset_t *set,sigset_t *oldset)
how:
	SIG_SETMASK 将set的值设定为新的进程信号掩码
*/
