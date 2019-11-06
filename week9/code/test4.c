#include"my.h"
static void __attribute__((constructor)) before_main()
{
	printf("---------Before Main-----------\n");
}

static void __attribute__((destructor)) after_main()
{
	printf("---------After Main-----------\n");
}
static void callback1(void)
{
	printf("callback1 is running!\n");
}
static void callback2(void)
{
	printf("callback2 is running!\n");
}
static void callback3(void)
{
	printf("callback3 is running!\n");
}
int main(void)
{
	atexit(callback1);
	atexit(callback2);
	atexit(callback3);
	printf("Main:\n");
	
	return 0;
}
