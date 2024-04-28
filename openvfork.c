//Write a program to open any application using vfork sysem call
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = vfork();

    if (pid < 0) {
        fprintf(stderr, "vfork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        execlp("pwd", "pwd", NULL);
        // If execlp fails
        perror("execlp");
        exit(1);
    } else {
        // Parent process
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Parent: Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child process did not exit normally\n");
        }
    }

    return 0;
}
