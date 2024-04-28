//Write a program to demonstrate the variations exec system call.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Using execl
    printf("Using execl\n");
    execl("/bin/ls", "ls", "-l", NULL);
    
    // Using execv
    printf("Using execv\n");
    char *args[] = {"ls", "-l", NULL};
    execv("/bin/ls", args);
    
    // Using execle
    printf("Using execle\n");
    char *env[] = {"PATH=/bin", NULL};
    execle("/bin/ls", "ls", "-l", NULL, env);
    
    // Using execve
    printf("Using execve\n");
    char *argv[] = {"ls", "-l", NULL};
    char *envp[] = {"PATH=/bin", NULL};
    execve("/bin/ls", argv, envp);
    
    // If any exec call fails
    perror("exec");
    return 1;
}
