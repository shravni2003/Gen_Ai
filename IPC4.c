// Write a program in which different processes will perform different operation on shared
// memory. Operation: create memory, delete, attach/ detach(using shmget, shmat, shmdt).

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
	char *shm_ptr; // Pointer to shared memory

	// Fork a child process to create shared memory
	pid_t pid_create = fork();
	if (pid_create == -1) {
    	perror("fork");
    	exit(1);
	} else if (pid_create == 0) { // Child process to create memory
    	// Create a shared memory segment
    	shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    	if (shmid == -1) {
        	perror("shmget");
        	exit(1);
    	}
    	printf("Shared memory segment created\n");
    	exit(0);
	} else { // Parent process
    	wait(NULL); // Wait for the child process to finish creating memory

    	// Fork another child process to attach to shared memory
    	pid_t pid_attach = fork();
    	if (pid_attach == -1) {
        	perror("fork");
        	exit(1);
    	} else if (pid_attach == 0) { // Child process to attach memory
        	// Attach the shared memory segment to the process's address space
        	shmid = shmget(key, SHM_SIZE, 0666); // Get existing shared memory ID
        	if (shmid == -1) {
            	perror("shmget");
            	exit(1);
        	}
        	shm_ptr = shmat(shmid, NULL, 0);
        	if (shm_ptr == (char *) -1) {
            	perror("shmat");
            	exit(1);
        	}
        	printf("Attached to shared memory segment\n");
        	exit(0);
    	} else { // Parent process
        	wait(NULL); // Wait for the child process to finish attaching memory

        	// Fork another child process to detach from shared memory
        	pid_t pid_detach = fork();
        	if (pid_detach == -1) {
            	perror("fork");
            	exit(1);
        	} else if (pid_detach == 0) { // Child process to detach memory
            	// Detach the shared memory segment from the process's address space
            	shmid = shmget(key, SHM_SIZE, 0666); // Get existing shared memory ID
            	if (shmid == -1) {
                	perror("shmget");
                	exit(1);
            	}
            	shm_ptr = shmat(shmid, NULL, 0);
            	if (shm_ptr == (char *) -1) {
                	perror("shmat");
                	exit(1);
            	}
            	if (shmdt(shm_ptr) == -1) {
                	perror("shmdt");
                	exit(1);
            	}
            	printf("Detached from shared memory segment\n");
            	exit(0);
        	} else { // Parent process
            	wait(NULL); // Wait for the child process to finish detaching memory

            	// Fork another child process to delete shared memory
            	pid_t pid_delete = fork();
            	if (pid_delete == -1) {
                	perror("fork");
                	exit(1);
            	} else if (pid_delete == 0) { // Child process to delete memory
                	// Remove the shared memory segment
                	shmid = shmget(key, SHM_SIZE, 0666); // Get existing shared memory ID
                	if (shmid == -1) {
                    	perror("shmget");
                    	exit(1);
                	}
                	if (shmctl(shmid, IPC_RMID, NULL) == -1) {
                    	perror("shmctl");
                    	exit(1);
                	}
                	printf("Shared memory segment deleted\n");
                	exit(0);
            	} else { // Parent process
                	wait(NULL); // Wait for the child process to finish deleting memory
            	}
        	}
    	}
	}

	return 0;
}
