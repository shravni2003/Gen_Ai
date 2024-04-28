//  Write a program to demonstrate the flock system call for locking
//change filename with your file

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME "file7.txt"

int main() {
    // Open a file for writing
    int fd = open(FILENAME, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Lock the file
    printf("Locking the file...\n");
    struct flock fl;
    fl.l_type = F_WRLCK;    // Write lock
    fl.l_whence = SEEK_SET; // Relative to the start of the file
    fl.l_start = 0;         // Start from the beginning of the file
    fl.l_len = 0;           // Lock the entire file

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    printf("File locked successfully.\n");

    // Write to the file (this operation is now protected by the lock)
    printf("Writing to the file...\n");
    if (write(fd, "Hello, flock!\n", 14) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("Data written successfully.\n");

    // Unlock the file
    printf("Unlocking the file...\n");
    fl.l_type = F_UNLCK; // Unlock
    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    printf("File unlocked successfully.\n");

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
