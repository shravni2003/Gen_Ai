//Write a program to demonstrate the kill system call to send signals between related processes(fork)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void signal_handler(int signum) {
    printf("Signal received: %d\n", signum);
}

int main() {
    pid_t pid;
    
    // Register signal handler for SIGUSR1
    signal(SIGUSR1, signal_handler);
    
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process ID: %d\n", getpid());
        // Child process waits for signal
        while(1) {
            sleep(1); // Sleep to avoid busy-waiting
        }
    } else {
        // Parent process
        printf("Parent process ID: %d\n", getpid());
        sleep(2); // Give some time for the child process to start
        printf("Parent: Sending SIGUSR1 signal to child process...\n");
        // Send SIGUSR1 signal to child process
        kill(pid, SIGUSR1);
        printf("Parent: Signal sent!\n");
    }

    return 0;
}
