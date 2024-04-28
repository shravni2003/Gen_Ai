//  Write 3 programs separately, 1st program will initialize the semaphore and display the
// semaphore ID. 2nd program will perform the P operation and print message accordingly. 3rd
// program will perform the V operation print the message accordingly for the same
// semaphore declared in the 1st program
//first run 1st program then 2 then 3 then again 2 for perfect and smooth output be happy enjoy
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key;
    int sem_id;

    // Generate a unique key
    if ((key = ftok(".", 'S')) == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a semaphore with key and initial value 1
    if ((sem_id = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666)) == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore initialized with ID: %d\n", sem_id);

    return 0;
}