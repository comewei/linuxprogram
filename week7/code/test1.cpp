#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
using namespace std;

int main()
{
	int fd;
	FILE *file;
	char *s = "hello,world\n";
	
	if((fd = open("test1.txt",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))==-1)
	{
		cout << "Error open file" << endl;
		return -1;
	}
	if((file=fopen("test2.txt","w+"))==NULL)
	{
		cout << "Error open file" << endl;
		return -1;
	}
	cout << "File has been opened" << endl;
	sleep(30);
	
	if(write(fd,s,strlen(s))<strlen(s))
	{
		cout << "Write error" << endl;
		return -1;
	}
	if(fwrite(s,sizeof(char),strlen(s),file)<strlen(s))
	{
		cout << "Write error in 2" <<  endl;
		return -1;
	}
	cout << "After write" << endl;
	sleep(30);
	cout << "After sleep" << endl;
	close(fd);
	return 0;
}

