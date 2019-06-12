#include<pthread.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

/*
    Child thread will end if main thread use exit/return to finish.
*/

void *thread_function(void *arg);

int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);
    sleep(3);
    printf("I'm main thread. Oh, i end\n");
    return 0;
}

void *thread_function(void* arg)
{
    int i;
    printf("I'm child thread\n");
    for(i=0; i<5; i++)
    {
        printf("i is %d\n", i);
        sleep(1);
    }
}
