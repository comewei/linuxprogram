#include "/home/rlk/linuxprogram/week6/code/staticlib/staticlib.h"
#include<stdio.h>
#define ARRAY_SIZE 100
int main()
{
	int a[ARRAY_SIZE];
	initarray(a,ARRAY_SIZE);
	showarray(a,ARRAY_SIZE);
	
	printf("max = %4d\n",max(a,ARRAY_SIZE));
	printf("sum = %4d\n",sum(a,ARRAY_SIZE));
	
	return 0;
}
