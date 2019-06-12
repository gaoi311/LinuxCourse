#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"

int main(){
		int running = 1;
		void *shared_memory = (void *)0;
		struct shared_use_st *shared_stuff;
		char buffer[BUFSIZ];
		int shmid;

		shmid = shmget((key_t)2222, sizeof(struct shared_use_st), 0666| IPC_CREAT);

		shared_memory = shmat(shmid, (void *)0, 0);
		printf("Memory attached at %X\n", (int)shared_memory);

		shared_stuff = (struct shared_use_st *)shared_memory;
		while(running){
				while(shared_stuff->written_by_you == 1){
						sleep(1);
						printf("waiting for client...\n");
				}

				printf("Enter some text:");
				fgets(buffer, BUFSIZ, stdin);

				strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
				shared_stuff->written_by_you = 1;

				if(strncmp(buffer, "end", 3) == 0){
						running = 0;
				}
		}
		
		if(shmdt(shared_memory) == -1){
				exit(EXIT_FAILURE);
		}

		if(shmctl(shmid, IPC_RMID, 0) == -1)
				exit(EXIT_FAILURE);

		exit(EXIT_SUCCESS);
}
