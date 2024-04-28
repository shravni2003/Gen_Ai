#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key;
    int sem_id;
    struct sembuf sem_op;

    // Get the key
    if ((key = ftok(".", 'S')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the semaphore ID
    if ((sem_id = semget(key, 1, 0)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Perform the V operation
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    if (semop(sem_id, &sem_op, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }

    printf("V operation performed successfully\n");

    return 0;
}