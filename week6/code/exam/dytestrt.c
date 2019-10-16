#include "dylib.h"
#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
#define ARRAY_SIZE 100
int main()
{
	void *hd;
	void (*f1)();
	int (*f2)(),(*f3)();
	char *error;
	int a[ARRAY_SIZE];
	initarray(a,ARRAY_SIZE);
	hd = dlopen("../dynamiclib/libdylib.so",RTLD_LAZY);
	if(!hd)
	{
		fprintf(stderr,"%s\n",dlerror());
	}
	f1 = dlsym(hd,"showarray");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}
	f2 = dlsym(hd,"max");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}
	f3 = dlsym(hd,"sum");
	if((error = dlerror()) != NULL)
	{
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}

	f1(a,ARRAY_SIZE);
	
	printf("max = %4d\n",f2(a,ARRAY_SIZE));
	printf("sum = %4d\n",f3(a,ARRAY_SIZE));
	
	return 0;
}
