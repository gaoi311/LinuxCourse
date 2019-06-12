#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

/*
    if main thread ends without using exit/return, this will not force child thread to exit.
*/

void *thread_function(void *);

int main(int argc,char *argv[])
{
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);
    pthread_exit(NULL);  //main thread finished, but not exit/return
    for(int i=0; i<5; i++)
    {
        printf("I'm\033[1;33m main thread\033[0m: num is\033[1;33m %d\033[0m\n", i);
        sleep(1);
    }
    return 0;
}

void *thread_function(void *arg)
{
    int i;
    for(i=0; i<5; i++)
    {
        printf("I'm\033[1;31m child thread\033[0m: num is\033[1;31m %d\033[0m\n", i);
        sleep(1);
    }
}
