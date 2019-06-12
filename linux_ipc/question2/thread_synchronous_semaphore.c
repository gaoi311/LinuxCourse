#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/*
   use semaphore to synchronize the producer and consumer. If quantity of products is greater than MAX_PRODUCT, 
   it is not allowed to produce until the quantity is decreased to less than MAX_PRODUCT.
*/

#define MAX_PRODUCT 100  //max quantity of product

void *thread_function_producer(void *);

void *thread_function_consumer(void *);

pthread_t thread_producer;  //producer thread
pthread_t thread_consumer;   //consumer thread
sem_t semaphore_empty;
sem_t semaphore_full;
pthread_mutex_t lock;
int product = 0;  //current quantity of product

int main() {
    //initialize semaphore and mutex
    sem_init(&semaphore_empty, 0, MAX_PRODUCT);  //quantity of spaces
    sem_init(&semaphore_full, 0, 0);  //quantity of product
    pthread_mutex_init(&lock, NULL);

    //initialize threads
    pthread_create(&thread_producer, NULL, thread_function_producer, NULL);
    pthread_create(&thread_consumer, NULL, thread_function_consumer, NULL);

    //wait for threads to finish
    pthread_join(thread_producer, NULL);
    pthread_join(thread_consumer, NULL);

    //destroy semaphore and mutex
    sem_destroy(&semaphore_empty);
    sem_destroy(&semaphore_full);
    pthread_mutex_destroy(&lock);

    exit(0);
}

void *thread_function_producer(void *arg) {
    while (1) {
        short time = rand() % 3;  //generate a random integer between 0 and 3

        sem_wait(&semaphore_empty);  //wait if quantity of spaces is less than or equal to 0, else,
        pthread_mutex_lock(&lock);  //lock mutex,
        ++product;  //quantity of product increases, and
        printf("One\033[1;31m produced\033[0m,\033[1;31m %d\033[0m products and\033[1;31m %d\033[0m spaces left.\n",
               product, MAX_PRODUCT - product);
		//printf("%d\n", getpid());
        pthread_mutex_unlock(&lock);  //unlock mutex,
        sem_post(&semaphore_full);  //semaphore_full increase.

        sleep(time);
    }
}

void *thread_function_consumer(void *arg) {
    while (1) {
        short time = rand() % 5;  //generate a random integer between 0 and 5

        sem_wait(&semaphore_full);  //wait if quantity of product is less than or equal to 0, else,
        pthread_mutex_lock(&lock);  //lock mutex,
        --product;  //products decrease, and
        pthread_mutex_unlock(&lock);  //unlock mutex,
        printf("One\033[1;34m consumed\033[0m,\033[1;34m %d\033[0m products and\033[1;34m %d\033[0m spaces left.\n",
               product, MAX_PRODUCT - product);
		//printf("%d\n", getpid());
        sem_post(&semaphore_empty);  //semaphore increase

        sleep(time);
    }
}
