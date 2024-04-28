//Write a program to open any application using fork sysem call.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h> 


int main() {
   pid_t pid;


   printf("Parent process ID: %d\n", getpid());


   pid = fork();


   if (pid < 0) {
       fprintf(stderr, "Fork failed\n");
       return 1;
   } else if (pid == 0) {  
       printf("Child process ID: %d\n", getpid());
       execlp("ls", "ls", "-l", NULL); 
       perror("exec");
       exit(1);
   } else {  
       wait(NULL);
       printf("Child process finished\n");
   }


   return 0;
}