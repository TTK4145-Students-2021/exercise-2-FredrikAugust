#include <pthread.h>
#include <stdio.h>

int i = 0;

/**
 * Reasoning:
 *   We use a mutex because we want to simply keep track of whether or not the thread has access to our resource.
 *   We could also use a binary semaphore, but a mutex is more semantically correct, and cleaner.
 */
pthread_mutex_t lock;

void *incrementingThreadFunction(void* num) {
    for (int j = 0; j < 11337; j++) {
        pthread_mutex_lock(&lock);   // Acquire lock
        (*(int*)num)++;              // Critical work
        pthread_mutex_unlock(&lock); // Release lock
    }

    return NULL;
}

void *decrementingThreadFunction(void* num) {
    for (int j = 0; j < 10000; j++) {
        pthread_mutex_lock(&lock);
        (*(int*)num)--;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}


int main() {
    pthread_mutex_init(&lock, NULL);

    pthread_t incrementingThread, decrementingThread;

    pthread_create(&incrementingThread, NULL, incrementingThreadFunction, &i);
    pthread_create(&decrementingThread, NULL, decrementingThreadFunction, &i);

    pthread_join(incrementingThread, NULL);
    pthread_join(decrementingThread, NULL);

    printf("The magic number is: %d\n", i);

    pthread_mutex_destroy(&lock);

    return 0;
}
