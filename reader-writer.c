// Write a program to implement reader-writers problem using semaphore

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, wrt;
int read_count = 0;

void *reader(void *arg) {
    while(1) {
        sem_wait(&mutex);
        read_count++;
        if(read_count == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);
        
        // Reading operation
        printf("Reading... Value: %d\n", *(int*)arg);

        sem_wait(&mutex);
        read_count--;
        if(read_count == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    while(1) {
        sem_wait(&wrt);
        
        // Writing operation
        *(int*)arg += 1;
        printf("Writing... New value: %d\n", *(int*)arg);

        sem_post(&wrt);
    }
}

int main() {
    pthread_t reader_thread, writer_thread;
    int shared_data = 0;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader and writer threads
    pthread_create(&reader_thread, NULL, reader, (void*)&shared_data);
    pthread_create(&writer_thread, NULL, writer, (void*)&shared_data);

    // Join threads
    pthread_join(reader_thread, NULL);
    pthread_join(writer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
// gcc -o reader_writer reader-writer.c -lpthread