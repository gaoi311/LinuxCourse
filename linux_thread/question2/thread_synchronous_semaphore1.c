#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/*
   use semaphore to synchronize the parking and unparking. If quantity of parked place is greater than MAX_PLACE, 
   it is not allowed to park until the quantity is decreased to less than MAX_PLACE.
*/

#define MAX_PLACE 10  //max quantity of park place
void *thread_function_park(void *);
void *thread_function_unpark(void *);
pthread_t thread_unpark;  //unparking thread
pthread_t thread_park1;   //parking1 thread
//pthread_t thread_park2;   //parking2 thread
sem_t semaphore;
int parkeds = 0;  //current quantity of parked place

int main(){
		int res;
		res = sem_init(&semaphore, 0, MAX_PLACE);
		//initialize semaphore with value of MAX_PLACE 
		res = pthread_create(&thread_unpark, NULL, thread_function_unpark, NULL);
		res = pthread_create(&thread_park1, NULL, thread_function_park, NULL);
//		res = pthread_create(&thread_park2, NULL, thread_function_park, NULL);
		//initialize threads
		pthread_join(thread_unpark, NULL);
		pthread_join(thread_park1, NULL);
//		pthread_join(thread_park2, NULL);
		//wait for threads to finish
		sem_destroy(&semaphore);
		//destroy semaphore
		exit(0);
}		

void *thread_function_park(void *arg){
		while(1){
				short time = rand() % 3 + 1;  //generate a random integer between 0 and 3
				if(parkeds < MAX_PLACE){  //if quantity of parkeds is less than MAX_PLACE, then
						parkeds++;  //quantity of parkeds increases, and
						printf("One car\033[1;31m parked\033[0m just now.\033[1;31m %d\033[0m places left.\n", MAX_PLACE - parkeds);
						sem_wait(&semaphore);  //semaphore decrease.
				}
				sleep(time);
		}
}

void *thread_function_unpark(void *arg){
		while(1){
				short time = rand() % 5 + 1;  //generate a random integer between 0 and 5
				if(parkeds > 0){  //if quantity of parkeds is greater than 0, then	
						parkeds--;  //parkeds decrease, and
						printf("One car\033[1;33m unparked\033[0m just now.\033[1;33m %d\033[0m places left.\n", MAX_PLACE - parkeds);
						sem_post(&semaphore);  //semaphore increase
				}
				sleep(time);
		}
}
