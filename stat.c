///. Write a program to give statistics of a given file using stat system call. (few imp field like FAP, file type)
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Check if filename is provided as argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    char *filename = argv[1];
    struct stat file_stat;

    // Call stat system call to get file statistics
    if (stat(filename, &file_stat) < 0) {
        perror("stat");
        return 1;
    }

    // Print file statistics
    printf("File: %s\n", filename);
    printf("Size: %ld bytes\n", file_stat.st_size);
    printf("File type: ");

    // Determine file type
    switch (file_stat.st_mode & S_IFMT) {
        case S_IFREG:
            printf("Regular file\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFCHR:
            printf("Character device\n");
            break;
        case S_IFBLK:
            printf("Block device\n");
            break;
        case S_IFIFO:
            printf("FIFO/pipe\n");
            break;
        case S_IFLNK:
            printf("Symbolic link\n");
            break;
        case S_IFSOCK:
            printf("Socket\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }

    return 0;
}
