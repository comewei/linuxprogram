#include"my.h"
int main()
{
	int pid1,pid2,pid3,status,rv;
	
	printf("parent fork child1\n");
	pid1 = fork();
	
	if(pid1 < 0)
	{
		perror("fork error!\n");
		return -1;
	}else if(pid1 == 0)
	{
		printf("child1 pid=%d\n",getpid());
		exit(10);
	}else
	{
		sleep(1);
		printf("parent fork child2\n");
		pid2 = fork();
		if(pid2 < 0)
		{
			perror("fork error!\n");
			return -1;
		}else if(pid2 == 0)
		{
			printf("child2 pid=%d\n",getpid());
			exit(20);
		}else
		{
			sleep(1);
			printf("parent fork child3\n");
			pid3 = fork();
			if(pid3 < 0)
			{
				perror("fork error!\n");
				return -1;
			}else if(pid3 == 0)
			{
				printf("child3 pid=%d\n",getpid());
				exit(30);
			}else
			{
				sleep(1);
				printf("parent wait child end!\n");
				rv = wait(&status);
				printf("1: child %d end,exit code is %d\n",rv,WEXITSTATUS(status));
				rv = waitpid(pid2,&status,0);
				printf("2: child %d end,exit code is %d\n",rv,WEXITSTATUS(status));
				rv = waitpid(pid3,&status,WNOHANG);
				printf("3: child %d end,exit code is %d\n",rv,WEXITSTATUS(status));
				
				return 0;
			}
		}
	}	
}



/*
int main()
{
	int pid1,pid2,pid3,status,rv;
	pid1 = fork();
	pid2 = fork();
	pid3 = fork();
	if(pid1 < 0 || pid2 < 0 || pid3 < 0)
	{
		perror("fork error!\n");
		return -1;
	}else if(pid1 == 0)
	{
		printf("child1 pid=%d\n",getpid());
		sleep(10);
		exit(18);
	}else if(pid2 == 0)
	{
		printf("child2 pid=%d\n",getpid());
		sleep(5);
		exit(99);
	}else if(pid3 == 0)
	{
		printf("child3 pid=%d\n",getpid());
		sleep(2);
		exit(100);
	}else
	{
		printf("parent wait child end!\n");
		rv = wait(&status);
		printf("1: child %d end,exit code is %d\n",rv,WEXITSTATUS(status));
		rv = waitpid(pid1,&status,0);
		printf("2: child %d end,exit code is %d\n",rv,WEXITSTATUS(status));
		rv = waitpid(pid2,&status,WNOHANG);
		printf("3: child %d end,exit code is %d\n",rv,WEXITSTATUS(status));
		
		return 0;
		
	}
}*/
