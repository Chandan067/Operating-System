#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 3

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int produced_items = 4;
    for (int i = 0; i < produced_items; i++) {
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&buffer_not_full, &mutex);
        }
        
        // Produce an item
        int item = i + 1;
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        
        printf("Producer produced item %d\n", item);
        
        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&mutex);
    }
    
    return NULL;
}

void *consumer(void *arg) {
    pthread_mutex_lock(&mutex);
    
    while (count == 0) {
        pthread_cond_wait(&buffer_not_empty, &mutex);
    }
    
    // Consume an item
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    
    printf("Consumer consumed item %d\n", item);
    
    pthread_cond_signal(&buffer_not_full);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Create the threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // Consume an item in the beginning and show that the buffer is EMPTY
    pthread_mutex_lock(&mutex);
    while (count == 0) {
        pthread_cond_wait(&buffer_not_empty, &mutex);
    }
    printf("Buffer is not empty. Consumer consumes an item.\n");
    pthread_mutex_unlock(&mutex);
    
    // Join the threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    return 0;
}
