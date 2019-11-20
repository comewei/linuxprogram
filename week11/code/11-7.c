#include"my.h"                 //验证亲缘进程可以通过文件通信
int main()
{
	int pid1,pid2,pid3,status,rv,i,size;
	char buf[512] = "";
	FILE *fp;
	fp = fopen("out.dat","w+");
	
	pid1 = fork();
	
	if(pid1 < 0)
	{
		perror("fork error!\n");
		return -1;
	}else if(pid1 == 0)
	{
		for(i=0;i<10;i++)
		{
			fprintf(fp,"child1 pid=%d : %d\n",getpid(),i);
		}
		exit(10);
	}else
	{
		sleep(1);
		pid2 = fork();
		if(pid2 < 0)
		{
			perror("fork error!\n");
			return -1;
		}else if(pid2 == 0)
		{
			for(i=0;i<10;i++)
			{
				fprintf(fp,"child2 pid=%d : %d\n",getpid(),i);
			}
			exit(20);
		}else
		{
			sleep(1);
			pid3 = fork();
			if(pid3 < 0)
			{
				perror("fork error!\n");
				return -1;
			}else if(pid3 == 0)
			{
				for(i=0;i<10;i++)
				{
					fprintf(fp,"child3 pid=%d : %d\n",getpid(),i);
				}
				exit(30);
			}else
			{
				//读取文件out.dat内容
				//sleep(1);
				//fgets(buf,1024,fp);
				//printf("%s\n",buf);			
				return 0;
			}
		}
	}	
}


