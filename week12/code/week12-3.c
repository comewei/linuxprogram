#include"my.h"  //作业 三个子进程之间的通信
#define MAXSIZE 65535

int main()
{
	int i=0;
	long sum=0;      //存储管道内数字和
	pid_t pid1,pid2,pid3;
	int fd1[2];
	int fd2[2];
	char rbuf[1],wbuf[1],wn,rn;
	memset(rbuf,0,sizeof(rbuf));
	memset(wbuf,0,sizeof(wbuf));
	pipe(fd1);       //创建pipe1
	pid1 = fork();
	if(pid1<0)
	{
		perror("fork child1 failed.\n");
		return -1;
	}else if(pid1 == 0)
	{
		close(fd1[0]);         //关闭pipe1读管道
		sprintf(wbuf,"%d",1);
		printf("[child1] writing to pipe1.\n");
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
		printf("[chlid1] have write done.\n");
		close(fd1[1]);
		exit(0);
		//child1内容
		//向pipe1中写65536个数字
	}else
	{
		sleep(1);
		pipe(fd2);             //创建pipe2
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
			printf("[child2] reading from pipe1.\n");
			printf("[child2] writing to pipe2.\n");
			while(i <= MAXSIZE)
			{
				//child2内容
				//读取pipe1中65536个数字并显示
				//将65536个数字写入pipe2
				
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
			printf("\n[child2] done.\n");
			close(fd1[0]);           //读完后关闭pipe1读管道
			close(fd2[1]);		     //写完后关闭pipe2写管道
			return 0;
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
				//child3内容
				//从pipe2中读出数字并求和
				close(fd2[1]);           //关闭pipe2读管道
				i=0;
				printf("[child3] reading and calculating sum form pipe2.\n");
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
				printf("[child3] the sum of the number in pipe2 is %ld\n",sum);
				printf("[child3] done.\n");
				close(fd2[0]);           //读完后关闭pipe2读管道
			}else
			{
				sleep(1);
				printf("[parent] waiting children end.\n");
				printf("[parent] end.\n");
			}
		}
	}
}
