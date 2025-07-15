#include <unistd.h>
#include <stdio.h>


int main()
{
	int pid = getppid();
	printf("pid is %d\n", pid);	
}