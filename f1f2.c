// 46. Write a program to ensure that function f1 should executed before executing function f2
// using semaphore. (Ex. Program should ask for username before entering password).

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Define semaphore
sem_t semaphore;

void f1() {
	printf("Enter username: ");
	char username[100];
	scanf("%s", username);
	// Simulate processing username
	printf("Processing username: %s\n", username);
}

void f2() {
	printf("Enter password: ");
	char password[100];
	scanf("%s", password);
	// Simulate processing password
	printf("Processing password: %s\n", password);
}

void *thread_function(void *arg) {
	// Wait for semaphore
	sem_wait(&semaphore);
	f1();
	// Post semaphore
	sem_post(&semaphore);
	f2();
	return NULL;
}

int main() {
	// Initialize semaphore
	sem_init(&semaphore, 0, 1);

	pthread_t thread;
	// Create a thread
	if (pthread_create(&thread, NULL, thread_function, NULL)) {
    	fprintf(stderr, "Error creating thread\n");
    	return 1;
	}

	// Join the thread
	if (pthread_join(thread, NULL)) {
    	fprintf(stderr, "Error joining thread\n");
    	return 1;
	}

	// Destroy semaphore
	sem_destroy(&semaphore);

	return 0;
}
