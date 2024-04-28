// 43. Write a program to demonstrate IPC using shared memory (shmget, shmat, shmdt). In this, one process will take numbers as input from user and second process will sort the numbers and put back to shared memory. Third process will display the shared memory.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHM_SIZE 1024 // Size of shared memory segment

int main() {
	key_t key = ftok(".", 'A'); // Generate a unique key
	int shmid; // Shared memory ID
	int *shm_ptr; // Pointer to shared memory
	int numbers[100]; // Array to store numbers
	int num_count; // Number of numbers entered by user
	int i;

	// Create a shared memory segment
	shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
	if (shmid == -1) {
    	perror("shmget");
    	exit(1);
	}

	// Attach the shared memory segment to the process's address space
	shm_ptr = (int *) shmat(shmid, NULL, 0);
	if (shm_ptr == (int *) -1) {
    	perror("shmat");
    	exit(1);
	}

	// Prompt the user to enter numbers
	printf("Enter the number of numbers (up to 100): ");
	scanf("%d", &num_count);

	printf("Enter %d numbers:\n", num_count);
	for (i = 0; i < num_count; i++) {
    	scanf("%d", &numbers[i]);
	}

	// Write input numbers to shared memory
	for (i = 0; i < num_count; i++) {
    	shm_ptr[i] = numbers[i];
	}

	// Fork a child process to sort numbers in shared memory
	pid_t pid = fork();
	if (pid == -1) {
    	perror("fork");
    	exit(1);
	} else if (pid == 0) { // Child process
    	// Sort numbers in shared memory using bubble sort algorithm
    	for (i = 0; i < num_count - 1; i++) {
        	for (int j = 0; j < num_count - i - 1; j++) {
            	if (shm_ptr[j] > shm_ptr[j + 1]) {
                	// Swap numbers if they are in the wrong order
                	int temp = shm_ptr[j];
                	shm_ptr[j] = shm_ptr[j + 1];
                	shm_ptr[j + 1] = temp;
            	}
        	}
    	}
    	exit(0);
	} else { // Parent process
    	wait(NULL); // Wait for the child process to finish sorting

    	// Fork another child process to display sorted numbers
    	pid_t pid2 = fork();
    	if (pid2 == -1) {
        	perror("fork");
        	exit(1);
    	} else if (pid2 == 0) { // Child process
        	printf("Sorted numbers in shared memory:\n");
        	for (i = 0; i < num_count; i++) {
            	printf("%d ", shm_ptr[i]);
        	}
        	printf("\n");
        	exit(0);
    	} else { // Parent process
        	wait(NULL); // Wait for the second child process to finish

        	// Detach the shared memory segment
        	if (shmdt(shm_ptr) == -1) {
            	perror("shmdt");
            	exit(1);
        	}

        	// Remove the shared memory segment
        	if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            	perror("shmctl");
            	exit(1);
        	}
    	}
	}

	return 0;
}
