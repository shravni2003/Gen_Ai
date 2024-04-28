// 41. Write a program to demonstrate IPC using shared memory (shmget, shmat,
// shmdt). In this, one process will send A to Z/1 to 100 as input from user and another process will receive it.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024
#define KEY 1234

int main() {
    int shmid;
    char *shm;

 
    // Create the shared memory segment
    shmid = shmget(KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    shm = (char *) shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Fork a child process for input
    pid_t pid_input = fork();

    if (pid_input < 0) {
        perror("fork");
        exit(1);
    } else if (pid_input == 0) {
        // Child process for input
        printf("Enter 'A' to 'Z' or '1' to '100': ");
        fgets(shm, SHM_SIZE, stdin);
        exit(0);
    }

    // Wait for input process to complete
    waitpid(pid_input, NULL, 0);

    // Fork a child process for receiving
    pid_t pid_receive = fork();

    if (pid_receive < 0) {
        perror("fork");
        exit(1);
    } else if (pid_receive == 0) {
        // Child process for receiving
        printf("Received: %s", shm);
        exit(0);
    }

    // Wait for receiving process to complete
    waitpid(pid_receive, NULL, 0);

    // Detach from the shared memory segment
    if (shmdt(shm) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Destroy the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
//gcc IPC1.c -o shared_memory_ipc