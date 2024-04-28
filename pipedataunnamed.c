// Write a program using PIPE, to Send data from parent to child over a pipe.
// (unnamed pipe )


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 25

int main() {
	int pipefd[2]; // File descriptors for the pipe
	pid_t pid; // Process ID

	char buffer[BUFFER_SIZE]; // Buffer for reading from and writing to the pipe

	// Create the pipe
	if (pipe(pipefd) == -1) {
    	perror("pipe");
    	exit(EXIT_FAILURE);
	}

	// Fork a child process
	pid = fork();

	if (pid < 0) {
    	perror("fork");
    	exit(EXIT_FAILURE);
	}

	if (pid > 0) { // Parent process
    	close(pipefd[0]); // Close the reading end of the pipe in the parent

    	printf("Parent: Writing data to the pipe...\n");
    	// Write data to the pipe
    	write(pipefd[1], "Hello, child!", 14);

    	close(pipefd[1]); // Close the writing end of the pipe in the parent
    	printf("Parent: Data written to the pipe.\n");
	} else { // Child process
    	close(pipefd[1]); // Close the writing end of the pipe in the child

    	printf("Child: Reading data from the pipe...\n");
    	// Read data from the pipe
    	read(pipefd[0], buffer, BUFFER_SIZE);
    	printf("Child: Received message: %s\n", buffer);

    	close(pipefd[0]); // Close the reading end of the pipe in the child
	}

	return 0;
}
