// Write program to implement producer consumer problem using semaphore.h in C/JAVA


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item = 1;
    while(1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        // Produce item
        printf("Producing item %d\n", item);
        buffer[item-1] = item;
        item++;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    while(1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // Consume item
        int item = buffer[0];
        printf("Consuming item %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Join threads
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

//gcc -o producer_consumer sema.c -lpthread
