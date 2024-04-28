//Write a multithread program in linux to use the pthread library  use this to run this file gcc -pthread pthread.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

void *print_message(void *thread_id) {
    long tid;
    tid = (long)thread_id;
    printf("Thread %ld: Hello, World!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Main: Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_message, (void *)t);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(-1);
        }
    }

    pthread_exit(NULL);
}
