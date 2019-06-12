#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*
   in this codes, threads are not synchronous. The gloable variable num will be modified incorrectly.
*/

void *thread_function1(void *);
void *thread_function2(void *);
int num = 0;  //global variable to count the times of accumulation

int main(){
		pthread_t thread1;
		pthread_t thread2;

		pthread_create(&thread1, NULL, thread_function1, NULL);
		pthread_create(&thread2, NULL, thread_function2, NULL);
		//initialize thread
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		//wait for thread to finish
		exit(0);
}

void *thread_function1(void *arg){
		for(int i=0; i<10000; i++){
				num += 1;
				printf("I'm\033[1;31m thread1\033[0m, num is\033[1;31m %d\033[0m\n", num);
				sleep(0.01);
		}
		return NULL;
}

void *thread_function2(void *arg){
		for(int i=0; i<10000; i++){
				num += 1;
				printf("I'm\033[1;33m thread2\033[0m, num is\033[1;33m %d\033[0m\n", num);
				sleep(0.01);
		}
		return NULL;
} 
