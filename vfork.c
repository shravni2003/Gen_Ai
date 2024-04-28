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
        char *login = getlogin();
        if (login == NULL) {
            perror("getlogin");
            exit(1);
        }
        printf("Child: Login name: %s\n", login);
        exit(0);
    } else {
        // Parent process
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Parent: Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child process did not exit normally\n");
        }

        // Prompt for password
        char password[50];
        printf("Enter password: ");
        scanf("%s", password);
        printf("Parent: Password entered: %s\n", password);
    }

    return 0;
}
