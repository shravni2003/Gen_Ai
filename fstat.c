//Write a program to give statistics of a given file using fstat system call. (few imp field like FAP, file type)
//run by ./a.out any file name
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    struct stat fileStat;

    // Use fstat to get file statistics
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    if (fstat(fd, &fileStat) < 0) {
        perror("Error getting file status");
        close(fd);
        return 1;
    }
    close(fd);

    printf("File type: ");
    if (S_ISREG(fileStat.st_mode))
        printf("Regular file\n");
    else if (S_ISDIR(fileStat.st_mode))
        printf("Directory\n");
    else if (S_ISCHR(fileStat.st_mode))
        printf("Character device\n");
    else if (S_ISBLK(fileStat.st_mode))
        printf("Block device\n");
    else if (S_ISFIFO(fileStat.st_mode))
        printf("FIFO/pipe\n");
    else if (S_ISLNK(fileStat.st_mode))
        printf("Symbolic link\n");
    else if (S_ISSOCK(fileStat.st_mode))
        printf("Socket\n");
    else
        printf("Unknown file type\n");

    printf("File access permissions (FAP): %o\n", fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
    printf("File size: %ld bytes\n", fileStat.st_size);
    printf("Inode number: %ld\n", fileStat.st_ino);
    printf("Device ID of containing device: %ld\n", fileStat.st_dev);
    printf("Number of hard links: %ld\n", fileStat.st_nlink);

    return 0;
}
