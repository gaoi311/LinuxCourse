#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

int aa=100;

int main()
{
	int res;
	pthread_t a_thread;
	void *thread_result;
	int share_int = 10;

	res = pthread_create(&a_thread,NULL,thread_function,(void *)&share_int);
	sleep(5);
	share_int = -10;
	if(res != 0){
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for thread to finish...\n");
	res = pthread_join(a_thread,&thread_result);
	if(res != 0){
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined,it returned %s\n",(char *)thread_result);
	printf("share_int is now %d\n",share_int);
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg){
	printf("thread_function is running.Argument was %d\n",*(int *)arg);
	printf("aa=%d\n",aa);
//	sleep(3);
	*(int *)arg = *(int *)arg * 10;
	pthread_exit("Thank you for the CPU time");
}
