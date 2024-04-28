// 58. Write a program using FIFO, to Send file from parent to child over a pipe. (named pipe)


//give any existing fiel in your device as the input in the code itself then run
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/myfifo"
#define BUFFER_SIZE 1024

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
    	printf("Parent: Opening file for reading...\n");
    	FILE *file = fopen("receive.txt", "r");
    	if (file == NULL) {
        	perror("fopen");
        	exit(EXIT_FAILURE);
    	}

    	printf("Parent: Opening FIFO for writing...\n");
    	// Open the FIFO for writing
    	fd = open(FIFO_PATH, O_WRONLY);
    	if (fd == -1) {
        	perror("open");
        	exit(EXIT_FAILURE);
    	}

    	printf("Parent: Writing file data to the FIFO...\n");
    	ssize_t bytes_read;
    	while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        	write(fd, buffer, bytes_read);
    	}
    	close(fd); // Close the FIFO
    	fclose(file);
    	printf("Parent: File data written to the FIFO.\n");
	} else { // Child process
    	printf("Child: Opening FIFO for reading...\n");
    	// Open the FIFO for reading
    	fd = open(FIFO_PATH, O_RDONLY);
    	if (fd == -1) {
        	perror("open");
        	exit(EXIT_FAILURE);
    	}

    	printf("Child: Creating file for writing...\n");
    	FILE *output_file = fopen("output.txt", "w");
    	if (output_file == NULL) {
        	perror("fopen");
        	exit(EXIT_FAILURE);
    	}

    	printf("Child: Reading data from the FIFO...\n");
    	ssize_t bytes_read;
    	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        	fwrite(buffer, 1, bytes_read, output_file);
    	}
    	fclose(output_file);
    	printf("Child: Data written to output.txt.\n");

    	close(fd); // Close the FIFO
	}

	return 0;
}
