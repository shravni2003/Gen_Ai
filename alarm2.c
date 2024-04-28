//Write a program for alarm clock using alarm and signal system call.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signum) {
    printf("Alarm! Time's up!\n");
    exit(0);
}

int main() {
    int seconds;
    
    // Register signal handler for SIGALRM
    signal(SIGALRM, alarm_handler);
    
    printf("Enter the number of seconds for the alarm: ");
    scanf("%d", &seconds);
    
    printf("Alarm set for %d seconds.\n", seconds);
    
    // Set alarm for specified number of seconds
    alarm(seconds);
    
    // Pause the program until the alarm goes off
    pause();
    
    return 0;
}
