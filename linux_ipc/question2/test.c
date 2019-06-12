/**
 * Copyright (C), 2019-2019
 * FileName: sys_v_semaphore.c
 * Author:   高毅 gaoi
 * Date:     6/10/19
 * Description: sys_v_semaphore
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SEM_PRODUCT 0
#define SEM_SPACE 1
#define SEM_MUTEX 2

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

/* initialize a semaphore set consists of three semaphores of product with 0, space with 100 and mutex with 1 */
static void init();

/* set values for above three semaphores */
static void set_semaphores_all(union semun sem_union);

/* delete all semaphores */
static void del_semaphores();

/* operation p which has a parameter specifies the semnum-th semaphore of the semaphore set*/
static void semaphore_p(int semnum);

/* operation v which has a parameter specifies the semnum-th semaphore of the semaphore set*/
static void semaphore_v(int semnum);

/* producer */
void producer();

/* consumer */
void consumer();

static int sem_id;

int main() {

    init();
    /* fork one child process as a consumer and parent process is a producer */
    int pid = fork();
    if (pid > 0)
        producer();
    if (pid == 0)
        consumer();

    exit(0);
}

/* initialize a semaphore set consists of three semaphores of product with 0, space with 100 and mutex with 1 */
void init() {
    union semun sem_union;
    srand((unsigned int) getpid());
    /* The semget() system call returns the System V semaphore set identifier associated with the argument key */
    sem_id = semget((key_t) 1234, 3, 0666 | IPC_CREAT);
    /* sem_array contains three values which will set each the three semaphores in the semaphore set */
    unsigned short sem_array[3] = {0, 100, 1};
    sem_union.array = sem_array;
    set_semaphores_all(sem_union);

    printf("product init is\033[1;35m %d\033[0m\n", semctl(sem_id, SEM_PRODUCT, GETVAL));
    printf("space init is\033[1;35m %d\033[0m\n", semctl(sem_id, SEM_SPACE, GETVAL));
    printf("-------start-------\n");
}

/* producer */
void producer() {
    while (1) {
        semaphore_p(SEM_SPACE);  // operation p of space
        semaphore_p(SEM_MUTEX);  // lock mutex
        printf("One\033[1;31m produced\033[0m,\033[1;31m %d\033[0m products and\033[1;31m %d\033[0m spaces left\n",
               semctl(sem_id, SEM_PRODUCT, GETVAL) + 1, semctl(sem_id, SEM_SPACE, GETVAL));
		//printf("%d\t%d\n", getpid(), getppid());
        semaphore_v(SEM_MUTEX);  // unlock mutex
        semaphore_v(SEM_PRODUCT);  // operation v of product
        sleep(rand() % 3);
    }

    del_semaphores();

}

/* consumer */
void consumer() {
    while (1) {
        semaphore_p(SEM_PRODUCT);  // operation p product
        semaphore_p(SEM_MUTEX);  // lock mutex
        printf("One\033[1;34m consumed\033[0m,\033[1;34m %d\033[0m products and\033[1;34m %d\033[0m spaces left\n",
               semctl(sem_id, SEM_PRODUCT, GETVAL), semctl(sem_id, SEM_SPACE, GETVAL) + 1);
		//printf("%d\t%d\n", getpid(), getppid());
        semaphore_v(SEM_MUTEX);  // unlock mutex
        semaphore_v(SEM_SPACE);  // operation v space
        sleep(rand() % 5);
    }

}

/* set values for above three semaphores */
static void set_semaphores_all(union semun sem_union) {
    if (semctl(sem_id, 0, SETALL, sem_union) == -1) {  // the 2th argument semnum will be ingored if the cmd is SETALL
        fprintf(stderr, "set_semaphores_all failed\n");
        exit(EXIT_FAILURE);
    }
}

/* delete all semaphores */
static void del_semaphores(void) {
    if (semctl(sem_id, 0, IPC_RMID) == -1)  // the 2th argument semnum will be ingored if the cmd is IPC_RMID
        fprintf(stderr, "Failed to delete semaphore\n");
}

/* operation p which has a parameter specifies the semnum-th semaphore of the semaphore set*/
static void semaphore_p(int semnum) {
    /*
     * sem_num is the position of a semaphore in the semaphore set
     * sem_op, -1 is operation p
     * sem_flg is often SEM_UNDO, which will be automatically undo when the process terminates
     *
     * */
    struct sembuf sem_buf_p;
    sem_buf_p.sem_num = semnum;
    sem_buf_p.sem_op = -1;
    sem_buf_p.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_buf_p, 1) == -1) {
        fprintf(stderr, "semaphore_p failed\n");
        exit(EXIT_FAILURE);
    }
}

/* operation v which has a parameter specifies the semnum-th semaphore of the semaphore set*/
static void semaphore_v(int semnum) {
    /*
     * sem_num is the position of a semaphore in the semaphore set
     * sem_op, 1 is operation v
     * sem_flg is often SEM_UNDO, which will be automatically undo when the process terminates
     *
     * */
    struct sembuf sem_buf_v;
    sem_buf_v.sem_num = semnum;
    sem_buf_v.sem_op = 1;
    sem_buf_v.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_buf_v, 1) == -1) {
        fprintf(stderr, "semaphore_v failed\n");
        exit(EXIT_FAILURE);
    }
}
