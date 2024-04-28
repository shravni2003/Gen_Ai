//Write a program to use alarm and signal sytem call(check i/p from user within time)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signum) {
    printf("Time's up! You did not enter any input.\n");
    exit(0);
}

int main() {
    char input[100];
    
    // Register signal handler for SIGALRM
    signal(SIGALRM, alarm_handler);
    
    printf("Enter your input within 5 seconds: ");
    
    // Set alarm for 5 seconds
    alarm(5);
    
    // Read user input
    fgets(input, sizeof(input), stdin);
    
    // Cancel the alarm
    alarm(0);
    
    printf("You entered: %s", input);
    
    return 0;
}
