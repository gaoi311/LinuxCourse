#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_function1(int *);
void *thread_function2(int *);

int x = 0;

int main(){

		int pid = fork();
		//create new process

		if(pid == 0){  //child process
				x += 10;
				pthread_t thread1;
				pthread_create(&thread1, NULL, thread_function1, &x);
				pthread_join(thread1, NULL);
		}
		else{  //parent process
				x += 50;
				pthread_t thread2;
				pthread_create(&thread2, NULL, thread_function2, &x);
				pthread_join(thread2, NULL);
		}
		
		printf("****%d, %p\n", x, &x);

		return 0;

}

void *thread_function1(int *arg){
		printf("\033[1;31mthread_child_before\033[0m: n is \033[1;31m%d\033[0m\n", *arg);
		printf("\033[1;31mthread_child_after\033[0m: n is \033[1;31m%d\033[0m\n, %p\n", *arg + 10, &arg);
		pthread_exit(NULL);
}

void *thread_function2(int *arg){
		printf("\033[1;33mthread_parent_before\033[0m: n is \033[1;33m%d\033[0m\n", *arg);
		printf("\033[1;33mthread_parent_after\033[0m: n is \033[1;33m%d\033[0m\n, %p\n", *arg + 50, &arg);
		pthread_exit(NULL);
}







/*
void *thread_function1(int *arg){
		printf("thread1: n is %d, at %p\n", *arg, arg);
		pthread_exit(NULL);
}

void *thread_function2(int *arg){
		printf("thread2: n is %d, at %p\n", *arg, arg);
		pthread_exit(NULL);
}
*/
