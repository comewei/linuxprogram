#include"my.h"  //作业 三个子进程之间的通信
#define MAXSIZE 65535

int main()
{
	int i=0;
	long sum=0;
	pid_t pid1,pid2,pid3;
	int fd1[2];
	int fd2[2];
	char rbuf[1],wbuf[1],wn,rn;
	memset(rbuf,0,sizeof(rbuf));
	memset(wbuf,0,sizeof(wbuf));
	pipe(fd1);
	pid1 = fork();
	if(pid1<0)
	{
		perror("fork child1 failed.\n");
		return -1;
	}else if(pid1 == 0)
	{
		close(fd1[0]);
		sprintf(wbuf,"%d",1);
		while(i <= MAXSIZE)
		{
			wn = write(fd1[1],wbuf,sizeof(wbuf));
			i++;
			if(wn == -1)
			{
				printf("[child1] write error.\n");
				break;
			}
		}
		printf("chlid1 have write done.\n");
		close(fd1[1]);
		exit(0);
		//child1内容
		//向pipe1中写65536个数字
	}else
	{
		sleep(1);
		pipe(fd2);             //第二个管道
		pid2 = fork();
		if(pid2<0)
		{
			perror("fork child2 failed.\n");
			return -1;
		}else if(pid2 == 0)
		{
			close(fd1[1]);      //关闭pipe1写管道
			close(fd2[0]);      //关闭pipe2读管道
			i=0;
			while(i <= MAXSIZE)
			{
				//child2从pipe2读
				rn = read(fd1[0],rbuf,sizeof(rbuf));
				i++;
				printf("%s,",rbuf);
				if(rn == 0)
				{
					printf("[child2] read error.\n");
					break;
				}
				//child2向pipe2写
				wn = write(fd2[1],rbuf,sizeof(rbuf));
				if(rn == 0)
				{
					printf("[child2] write error.\n");
					break;
				}
			}
			close(fd1[0]);
			close(fd2[1]);
			return 0;
			//child2内容
			//读取pipe1中65536个数字并显示
			//将65536个数字写入pipe2
		}else
		{
			sleep(1);
			pid3 = fork();
			if(pid3<0)
			{
				perror("fork child3 failed.\n");
				return -1;
			}else if(pid3 == 0)
			{
				close(fd2[1]);
				i=0;
				while(i <= MAXSIZE)
				{
					//child3从pipe2读
					rn = read(fd2[0],rbuf,sizeof(rbuf));
					i++;
					sum += rbuf[0] - '0';
					if(rn == 0)
					{
						printf("[child3] read error.\n");
						break;
					}
				}
				printf("\nsum = %ld\n",sum);
				close(fd2[0]);
				//child3内容
				//从pipe2中读出数字并求和
			}else
			{
				sleep(1);
				printf("I'm parent progress.\n");
			}
		}
	}
}
