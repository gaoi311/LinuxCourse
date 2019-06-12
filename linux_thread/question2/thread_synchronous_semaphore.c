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
pthread_t thread_park;   //parking1 thread
sem_t semaphore_empty;
sem_t semaphore_full;
pthread_mutex_t lock;
int parkeds = 0;  //current quantity of parked place

int main(){
		sem_init(&semaphore_empty, 0, MAX_PLACE);  //quantity of unparked place
		sem_init(&semaphore_full, 0, 0);  //quantity of parked place
		pthread_mutex_init(&lock, NULL);
		//initialize semaphore and mutex

		pthread_create(&thread_unpark, NULL, thread_function_unpark, NULL);
		pthread_create(&thread_park, NULL, thread_function_park, NULL);
		//initialize threads

		pthread_join(thread_unpark, NULL);
		pthread_join(thread_park, NULL);
		//wait for threads to finish

		sem_destroy(&semaphore_empty);
		sem_destroy(&semaphore_full);
		pthread_mutex_destroy(&lock);
		//destroy semaphore and mutex

		exit(0);
}		

void *thread_function_park(void *arg){
		while(1){
				short time = rand() % 3 + 1;  //generate a random integer between 0 and 3

		  		sem_wait(&semaphore_empty);  //wait if quantity of unparkeds is less than or equal to 0, else,
				pthread_mutex_lock(&lock);  //lock mutex,
				parkeds++;  //quantity of parkeds increases, and
				printf("One car\033[1;31m parked\033[0m just now.\033[1;31m %d\033[0m places left.\n", MAX_PLACE - parkeds);
				pthread_mutex_unlock(&lock);  //unlock mutex,
				sem_post(&semaphore_full);  //semaphore_full increase.
			
				sleep(time);
		}
}

void *thread_function_unpark(void *arg){
		while(1){
				short time = rand() % 5 + 1;  //generate a random integer between 0 and 5

				sem_wait(&semaphore_full);  //wait if quantity of parkeds is less than or equal to 0, else,
				pthread_mutex_lock(&lock);  //lock mutex,
				parkeds--;  //parkeds decrease, and
				printf("One car\033[1;33m unparked\033[0m just now.\033[1;33m %d\033[0m places left.\n", MAX_PLACE - parkeds);
				pthread_mutex_unlock(&lock);  //unlock mutex,
				sem_post(&semaphore_empty);  //semaphore increase

				sleep(time);
		}
}
