#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/*
   in this codes, threads look like being executed serially in the critical sections.
*/

pthread_mutex_t lock;
void *thread_function1(void *);
void *thread_function2(void *);
int num = 0;

int main(){
		pthread_t thread1;
		pthread_t thread2;

		pthread_mutex_init(&lock, NULL);
		//initialize a mutex

		pthread_create(&thread1, NULL, thread_function1, NULL);
		pthread_create(&thread2, NULL, thread_function2, NULL);
		//create 2 child threads

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		//wait for threads to finish

		pthread_mutex_destroy(&lock);
		//destroy mutex

		exit(0);
}

void *thread_function1(void *arg){
		int i = 0;
		while(i < 10000){
				pthread_mutex_lock(&lock);
				//locking mutex we initialized, now, the variable num only can be used by this thread

				num += 1;
				printf("I'm\033[1;31m thread1\033[0m, num is\033[1;31m %d\033[0m\n", num);
				i += 1;

				pthread_mutex_unlock(&lock);
				//unlocking, then, num can be accessed by all threads

				sleep(0.1);
		}
}

void *thread_function2(void *arg){
		int i = 0;
		while(i < 10000){
				pthread_mutex_lock(&lock);
				//locking mutex we initialized, now, the variable num only can be used by this thread

				num += 1;
				printf("I'm\033[1;33m thread2\033[0m, num is\033[1;33m %d\033[0m\n", num);
				i += 1;

				pthread_mutex_unlock(&lock);
				//unlocking, then, num can be accessed by all threads

				sleep(0.1);
		}
} 
