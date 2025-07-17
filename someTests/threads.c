#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
// #include "tlpi_hdr.h"

// void *prints_test()
// {
// 	printf("prints threads !\n");
// }

// void *prints_test_1()
// {
// 	pthread_t t3;
// 	pthread_create(&t3, NULL, &prints_test, NULL);
// 	pthread_join(t3, NULL);
// 	printf("prints threads !\n");
// 	pthread_exit(NULL);
// }



// int main()
// {
// 	pthread_t t1;
// 	pthread_t t2;

// 	printf("stars of the program\n");
// 	// sleep(3);
	
// 	pthread_create(&t1, NULL, &prints_test, NULL);
// 	pthread_create(&t2, NULL, &prints_test_1, NULL);
// 	pthread_cancel(t1);
// 	// pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	// pthread_cancel();
// 	return (0);
// }


// static void *threadFunc(void *arg)
// {
	// char *s = (char *) arg;
	// printf("%s", s);
	// return (void *) strlen(s);
// }
// 
// int	main(int argc, char *argv[])
// {
	// pthread_t thr;
 	// pthread_attr_t attr;
 	// int s;
// 
	//  s = pthread_attr_init(&attr); /* Assigns default values */
 	// if (s != 0)
 		// errExitEN(s, "pthread_attr_init");
 	// s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
 	// if (s != 0)
 		// errExitEN(s, "pthread_attr_setdetachstate");
 	// s = pthread_create(&thr, &attr, threadFunc, (void *) 1);
 	// if (s != 0)
 		// errExitEN(s, "pthread_create");
 	// s = pthread_attr_destroy(&attr); /* No longer needed */
 	// if (s != 0)
 		// errExitEN(s, "pthread_attr_destroy");
// }


//  example 3

// typedef struct _profil
// {
// 	int *max_int;
// 	int 
// }

// void *print_something()
// {
// 	int *randome;
// 	randome = malloc(sizeof(int));
// 	*randome = (rand() % 6) + 1;
// 	return ((void *) randome);
// }

// void *while_it()
// {
// 	int i;
// 	int *result;

// 	result = malloc(sizeof(int));
// 	*result = 0;
// 	i = 0;
// 	while (i < 7)
// 	{
// 		*result += i;
// 		i++;
// 	}
// 	return ((void *) result);
// }
// int main()
// {
// 	pthread_t p1;
// 	pthread_t p2;
// 	int *random;
// 	int *fract;
// 	// void	*pt_exit;

// 	srand(time(0));
// 	printf("the start of the programme\n");
// 	sleep(1);
// 	pthread_create(&p1, NULL, &print_something, NULL);
// 	pthread_create(&p2, NULL, &while_it, NULL);
// 	pthread_join(p1, (void **)&random);
// 	pthread_join(p2, (void **)&fract);
// 	printf("the randome number is %d\n", *random);
// 	printf("the fract number is %d\n", *fract);
// 	free(random);
// 	free(fract);
// 	return (0);
// }

//  example 4 


// int iv = 0;
// void	*routine(void *args)
// {
// 	int arr[11] = {0,1,2,3,4,5,6,7,8,9, 10};
// 	int index = *(int*)args;
// 	while (iv < index)
// 	{
		
// 	}
// 	printf("the number is %d\n", arr[index]);
// 	iv += 2;
// 	free(args);
// 	return 0;
// }

// int main()
// {
// 	pthread_t t1[10];
// 	int i;
// 	int *number;

// 	i = 0;
// 	while (i < 10)
// 	{
// 		number = malloc(sizeof(int));
// 		*number = i;
// 		if (i % 2 == 0)
// 			pthread_create(&t1[i], NULL, &routine, number);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 10)
// 	{
// 		if (i % 2 == 0)
// 			pthread_join(t1[i], NULL);
// 		i++;
// 	}
	
// }


//  example 5

static int glob = 0;
static void	*threadFunc(void *arg)
{
 int loops = *((int *) arg);
 int loc, j;
 for (j = 0; j < loops; j++) {
	loc = glob;
	loc++;
	glob = loc;
 }
 return NULL;
}

int	main(int argc, char *argv[])
{
 pthread_t t1, t2;
 int loops, s;

 loops = 1000000;
 s = pthread_create(&t1, NULL, threadFunc, &loops);
 if (s != 0)
	 perror("err");
 s = pthread_create(&t2, NULL, threadFunc, &loops);
 if (s != 0)
 	perror("err");
 s = pthread_join(t1, NULL);
 if (s != 0)
 	perror("err");
 s = pthread_join(t2, NULL);
 if (s != 0)
 	perror("err");
 printf("glob = %d\n", glob);
 exit(EXIT_SUCCESS);
}



