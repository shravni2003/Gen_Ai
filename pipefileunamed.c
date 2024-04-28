// 57. Write a program using PIPE, to Send file from parent to child over a pipe.
// (unnamed pipe )

//remeber give your file existing in the code other than receive.txt
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

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

    	printf("Parent: Reading file...\n");
    	FILE *file = fopen("receive.txt", "r");///here give your file
    	if (file == NULL) {
        	perror("fopen");
        	exit(EXIT_FAILURE);
    	}

    	printf("Parent: Writing file data to the pipe...\n");
    	ssize_t bytes_read;
    	while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        	write(pipefd[1], buffer, bytes_read);
    	}
    	close(pipefd[1]); // Close the writing end of the pipe in the parent
    	fclose(file);
    	printf("Parent: File data written to the pipe.\n");
	} else { // Child process
    	close(pipefd[1]); // Close the writing end of the pipe in the child

    	printf("Child: Reading data from the pipe...\n");
    	FILE *output_file = fopen("output.txt", "w");
    	if (output_file == NULL) {
        	perror("fopen");
        	exit(EXIT_FAILURE);
    	}

    	ssize_t bytes_read;
    	while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        	fwrite(buffer, 1, bytes_read, output_file);
    	}
    	fclose(output_file);
    	printf("Child: Data written to output.txt.\n");

    	close(pipefd[0]); // Close the reading end of the pipe in the child
	}

	return 0;
}


