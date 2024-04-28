// 59. Write a program using PIPE, to convert uppercase to lowercase filter to read command/from file
//change the input file int he code 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int main() {
	int pipefd[2]; // File descriptors for the pipe
	pid_t pid; // Process ID

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

	if (pid > 0) { // Parent process (reads from file)
    	close(pipefd[0]); // Close the reading end of the pipe in the parent

    	printf("Parent: Reading from file and writing to pipe...\n");
    	FILE *file = fopen("file2.txt", "r");
    	if (file == NULL) {
        	perror("fopen");
        	exit(EXIT_FAILURE);
    	}

    	char buffer[BUFFER_SIZE];
    	ssize_t bytes_read;
    	while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        	write(pipefd[1], buffer, bytes_read);
    	}
    	close(pipefd[1]); // Close the writing end of the pipe in the parent
    	fclose(file);
	} else { // Child process (converts uppercase to lowercase)
    	close(pipefd[1]); // Close the writing end of the pipe in the child

    	printf("Child: Converting uppercase to lowercase...\n");
    	char buffer[BUFFER_SIZE];
    	ssize_t bytes_read;
    	while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        	for (int i = 0; i < bytes_read; ++i) {
            	if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
                	buffer[i] = buffer[i] + 32; // Convert uppercase to lowercase
            	}
        	}
        	write(STDOUT_FILENO, buffer, bytes_read); // Write to standard output
    	}
    	close(pipefd[0]); // Close the reading end of the pipe in the child
	}

	return 0;
}
