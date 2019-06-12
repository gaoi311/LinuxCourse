#include<pthread.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

/*
    threads can share global variables between each other.
*/

char string[20] = " ";
void *thread_function(void *);

int main()
{
    pthread_t thread;

    pthread_create(&thread, NULL, thread_function, NULL);
	//initialize new thread
	strcpy(string, "main thread");
	printf("%s\n", string);

	pthread_join(thread, NULL);
	//wait thread to finish

    return 0;
}

void *thread_function(void* arg)
{
    strcpy(string, "child thread");
	printf("%s\n", string);
	pthread_exit(NULL);

}
