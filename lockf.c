// 62. Write a program to demonstrate the lockf system call for locking.

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

    // Lock a portion of the file
    printf("Locking the file...\n");
    if (lockf(fd, F_LOCK, 0) == -1) {
        perror("lockf");
        exit(EXIT_FAILURE);
    }

    printf("File locked successfully.\n");

    // Write to the file (this operation is now protected by the lock)
    printf("Writing to the file...\n");
    if (write(fd, "Hello, lockf!\n", 14) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("Data written successfully.\n");

    // Unlock the file
    printf("Unlocking the file...\n");
    if (lockf(fd, F_ULOCK, 0) == -1) {
        perror("lockf");
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
