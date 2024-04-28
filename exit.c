//Write a program to demonstrate the exit system call use with wait & fork sysem call.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process ID: %d\n", getpid());
        printf("Child: Exiting with status 42\n");
        exit(42); // Exit with status 42
    } else {
        // Parent process
        printf("Parent process ID: %d\n", getpid());
        printf("Parent: Waiting for child process to finish...\n");
        wait(&status); // Wait for the child process to terminate
        if (WIFEXITED(status)) {
            printf("Parent: Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child process did not exit normally\n");
        }
        printf("Parent: Done!\n");
    }

    return 0;
}
