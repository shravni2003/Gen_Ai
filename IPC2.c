// . Write a program to demonstrate IPC using shared memory (shmget, shmat,
// shmdt). In this, one process will send from file A to Z/1 to 100 as input from user
// and another process will receive it in file. (use same directory and different name
// files

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SHM_SIZE 1024
#define FILENAME_SEND "send.txt"
#define FILENAME_RECEIVE "receive.txt"
#define KEY 12345

int main() {
    int shmid;
   
    char *shm;
    FILE *file_send, *file_receive;


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

    // Open the file for sending data
    file_send = fopen(FILENAME_SEND, "w");
    if (file_send == NULL) {
        perror("fopen");
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
        fprintf(file_send, "%s", shm); // Write data to file
        fclose(file_send);
        exit(0);
    }

    // Wait for input process to complete
    waitpid(pid_input, NULL, 0);

    // Open the file for receiving data
    file_receive = fopen(FILENAME_RECEIVE, "w");
    if (file_receive == NULL) {
        perror("fopen");
        exit(1);
    }

    // Fork a child process for receiving
    pid_t pid_receive = fork();

    if (pid_receive < 0) {
        perror("fork");
        exit(1);
    } else if (pid_receive == 0) {
        // Child process for receiving
        file_send = fopen(FILENAME_SEND, "r");
        if (file_send == NULL) {
            perror("fopen");
            exit(1);
        }

        fgets(shm, SHM_SIZE, file_send); // Read data from file to shm
        fprintf(file_receive, "%s", shm); // Write data to another file
        fclose(file_send);
        fclose(file_receive);
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