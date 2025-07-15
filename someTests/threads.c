#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *prints_test()
{
	printf("prints threads !\n");
}

void *prints_test_1()
{
	pthread_t t3;
	pthread_create(&t3, NULL, &prints_test, NULL);
	pthread_join(t3, NULL);
	printf("prints threads !\n");
	pthread_exit(NULL);
}

int main()
{
	pthread_t t1;
	pthread_t t2;

	printf("stars of the program\n");
	// sleep(3);
	
	pthread_create(&t1, NULL, &prints_test, NULL);
	pthread_create(&t2, NULL, &prints_test_1, NULL);
	pthread_cancel(t1);
	// pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	// pthread_cancel();
	return (0);
}