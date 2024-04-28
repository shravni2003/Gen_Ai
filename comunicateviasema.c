// 60. Write a program to illustrate the semaphore concept. Use fork so that 2 process running simultaneously and communicate via semaphore. (give diff between sem.h/semaphore.h)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

int main() {
	// Create a semaphore and initialize it to 1
	sem_t *sem = sem_open("/my_semaphore", O_CREAT, 0644, 1);
	if (sem == SEM_FAILED) {
    	perror("sem_open");
    	exit(EXIT_FAILURE);
	}

	// Fork a child process
	pid_t pid = fork();
	if (pid < 0) {
    	perror("fork");
    	exit(EXIT_FAILURE);
	} else if (pid == 0) { // Child process
    	printf("Child process trying to lock the semaphore...\n");
    	sem_wait(sem); // Lock the semaphore
    	printf("Child process locked the semaphore.\n");
    	sleep(2); // Simulate some work
    	sem_post(sem); // Unlock the semaphore
    	printf("Child process released the semaphore.\n");
	} else { // Parent process
    	printf("Parent process trying to lock the semaphore...\n");
    	sem_wait(sem); // Lock the semaphore
    	printf("Parent process locked the semaphore.\n");
    	sleep(2); // Simulate some work
    	sem_post(sem); // Unlock the semaphore
    	printf("Parent process released the semaphore.\n");
	}

	// Close and unlink the semaphore
	sem_close(sem);
	sem_unlink("/my_semaphore");

	return 0;
}





// The difference between sem.h and semaphore.h lies in their functionality, portability, and underlying implementations. Here's a comparison between the two:
// sem.h (System V Semaphores):
// Functionality:
// Provides functions like semget, semop, and semctl for semaphore creation, operation, and control.
// Allows for the creation of System V semaphores, which are managed using unique semaphore identifiers (semid).
// Portability:
// sem.h is part of the System V IPC (Inter-Process Communication) mechanisms.
// It may not be available on all systems, especially those that follow POSIX standards exclusively.
// Usage:
// Commonly used in older UNIX systems and legacy codebases.
// Not as widely supported across different platforms compared to POSIX semaphores.
// semaphore.h (POSIX Semaphores):
// Functionality:
// Provides functions like sem_init, sem_wait, sem_post, and sem_destroy for semaphore management.
// Allows for the creation of POSIX semaphores, which are managed using pointers to sem_t structures.
// Portability:
// semaphore.h is part of the POSIX standard (POSIX.1-2001 and later revisions).
// It is more widely supported across different UNIX-like systems and modern operating systems.
// Usage:
// Preferred choice for new projects and modern codebases due to its standardization and portability.
// Offers a more consistent and intuitive interface compared to System V semaphores.
// Summary:
// sem.h is associated with S
// ystem V semaphores and provides functions for semaphore management specific to System V IPC mechanisms. It is less portable and not as widely used in modern applications.
// semaphore.h is part of the POSIX standard and provides a more modern and portable interface for semaphore management. It is the preferred choice for new projects and is widely supported across different platforms