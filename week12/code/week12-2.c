#include"my.h"                //验证缓冲区的最大容量

int main()
{
	pid_t p;
	long i=0;
	int fd[2],rn,wn,psize;
	char rbuf[30],wbuf[1];
	memset(rbuf,0,sizeof(rbuf));
	memset(wbuf,0,sizeof(wbuf));
	pipe(fd);     //建立管道
	//psize = fcntl(fd[0],?F_GETPIPE_SZ);
	//printf("pipe size is %d.\n",psize);
	p = vfork();
	if(p<0)
	{
		perror("fork failed.\n");
		return -1;
	}else if(p==0)
	{
		close(fd[0]);          //子进程写 关闭读功能
		sprintf(wbuf,"%d",1);
		while(i<70000)
		{
			wn = write(fd[1],wbuf,sizeof(wbuf));
			printf("[child] write to pipe %ld bytes.\n",i++);
			if(wn == -1)
			{
				printf("[child] write error.\n");
				break;
			}
		}
		close(fd[1]);
		exit(0);
	}else
	{
		close(fd[1]);      //父进程读，关闭写管道
		
		while(1)
		{
			rn = read(fd[0],rbuf,sizeof(rbuf));
			printf("[parent] read from pipe %d bytes.Content of pipe is %s\n",wn,rbuf);
			if(rn == 0)
			{
				printf("[parent] read error.\n");
				break;
			}
		}
		close(fd[0]);
		return 0;
		
	}
}
