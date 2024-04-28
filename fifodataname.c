// . Write a program using FIFO, to Send data from parent to child over a pipe. (named
// pipe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/myfifo"
#define BUFFER_SIZE 25

int main() {
	int fd; // File descriptor for the FIFO
	pid_t pid; // Process ID

	char buffer[BUFFER_SIZE]; // Buffer for reading from and writing to the FIFO

	// Create the FIFO
	mkfifo(FIFO_PATH, 0666);

	// Fork a child process
	pid = fork();

	if (pid < 0) {
    	perror("fork");
    	exit(EXIT_FAILURE);
	}

	if (pid > 0) { // Parent process
    	printf("Parent: Opening FIFO for writing...\n");
    	// Open the FIFO for writing
    	fd = open(FIFO_PATH, O_WRONLY);

    	printf("Parent: Writing data to the FIFO...\n");
    	// Write data to the FIFO
    	write(fd, "Hello, child!", 14);

    	close(fd); // Close the FIFO
    	printf("Parent: Data written to the FIFO.\n");
	} else { // Child process
    	printf("Child: Opening FIFO for reading...\n");
    	// Open the FIFO for reading
    	fd = open(FIFO_PATH, O_RDONLY);

    	printf("Child: Reading data from the FIFO...\n");
    	// Read data from the FIFO
    	read(fd, buffer, BUFFER_SIZE);
    	printf("Child: Received message: %s\n", buffer);

    	close(fd); // Close the FIFO
	}

	return 0;
}
