#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char message[] = "Hello World";
void *thread_function(void *arg);

int main(){
	int res;
	pthread_t a_thread;  //thread type, to refer to one thread
	void *thread_result; 
	res = pthread_create(&a_thread, NULL, thread_function, (void *)message);  //function of creating thread
	if(res != 0){
		perror("Thread create failed.");
		exit(EXIT_FAILURE);
	}
	printf("***I'm main thread, waitng for thread to finish...\n");
	res = pthread_join(a_thread, &thread_result);  
	//Waiting for thread to finish( like wait() in process ), and &thread_result is the address of pthread_exit()'s return value's address,
	//namely, address of string 'Thank you for the CPU time'. Meanwhile, the main thread not continue until child exits.
	if(res != 0){
		perror("Thread join failed.");
		exit(EXIT_FAILURE);
	}
	printf("***I'm main thread, thread joined, it returned %s\n", (char *)thread_result);
	printf("***I'm main thread, message is now %s\n", message);
	exit(EXIT_SUCCESS);
}

void *thread_function(void *arg){  //inlet function of new thread
	printf("---I'm child thread, thread_function is running. Argument was %s\n",(char *)arg);
	sleep(3);
	printf("\t\t\033[1;31;40m I'm child thread who has slept for 3s\033[0m\n");
	strcpy(message, "Bye!");
	printf("---I'm child thread, i will end...\n");
	pthread_exit("Thank you for the CPU time.");  //return a pointer, must point global variable or heap
}
