// compile with:  gcc -g main.c ringbuf.c -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#include "ringbuf.h"

struct BoundedBuffer {
    struct RingBuffer *buf;
    pthread_mutex_t mtx;
    sem_t empty;
    sem_t full;
};

struct BoundedBuffer *buf_new(int size) {
    struct BoundedBuffer *buf = malloc(sizeof(struct BoundedBuffer));
    buf->buf = rb_new(size);

    pthread_mutex_init(&buf->mtx, NULL);
    // TODO: initialize semaphores
    sem_init(&buf->full, 0, 0);
    sem_init(&buf->empty, 0, buf->buf->capacity);

    return buf;
}

void buf_destroy(struct BoundedBuffer *buf) {
    rb_destroy(buf->buf);
    pthread_mutex_destroy(&buf->mtx);
    sem_destroy(&buf->empty);
    sem_destroy(&buf->full);
    free(buf);
}

void buf_push(struct BoundedBuffer *buf, int val) {
    // TODO: wait for there to be room in the buffer
    // TODO: make sure there is no concurrent access to the buffer internals
    sem_wait(&buf->empty);

    pthread_mutex_lock(&buf->mtx);

    rb_push(buf->buf, val);

    pthread_mutex_unlock(&buf->mtx);

    // TODO: signal that there are new elements in the buffer
    sem_post(&buf->full);
}

int buf_pop(struct BoundedBuffer *buf) {
    // TODO: same, but different?
    sem_wait(&buf->full);

    pthread_mutex_lock(&buf->mtx);

    int val = rb_pop(buf->buf);

    pthread_mutex_unlock(&buf->mtx);

    sem_post(&buf->empty);

    return val;
}


void *producer(void *args) {
    struct BoundedBuffer *buf = (struct BoundedBuffer *) (args);

    for (int i = 0; i < 10; i++) {
        nanosleep(&(struct timespec) {0, 100 * 1000 * 1000}, NULL);
        printf("[producer]: pushing %d\n", i);
        buf_push(buf, i);
    }
    return NULL;
}

_Noreturn void *consumer(void *args) {
    struct BoundedBuffer *buf = (struct BoundedBuffer *) (args);

    // give the producer a 1-second head start
    nanosleep(&(struct timespec) {1, 0}, NULL);
    for (;;) {
        int val = buf_pop(buf);
        printf("[consumer]: %d\n", val);
        nanosleep(&(struct timespec) {0, 50 * 1000 * 1000}, NULL);
    }
}

int main() {
    struct BoundedBuffer *buf = buf_new(5);

    pthread_t producer_thr;
    pthread_t consumer_thr;
    pthread_create(&producer_thr, NULL, producer, buf);
    pthread_create(&consumer_thr, NULL, consumer, buf);

    pthread_join(producer_thr, NULL);
    pthread_cancel(consumer_thr);

    buf_destroy(buf);

    return 0;
}
