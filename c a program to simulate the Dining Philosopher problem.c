#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 10
#define MAX_EXECUTIONS 100

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int num_philosophers;
int num_executions;
int state[MAX_PHILOSOPHERS];
pthread_mutex_t forks[MAX_PHILOSOPHERS];
pthread_t threads[MAX_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *((int *) arg);
    int i, left, right;
    for (i = 0; i < num_executions; i++) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3);
        left = id;
        right = (id + 1) % num_philosophers;
        state[id] = HUNGRY;
        printf("Philosopher %d is hungry...\n", id);
        pthread_mutex_lock(&forks[left]);
        printf("Philosopher %d picked up left fork %d...\n", id, left);
        pthread_mutex_lock(&forks[right]);
        printf("Philosopher %d picked up right fork %d...\n", id, right);
        state[id] = EATING;
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 3);
        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d put down right fork %d...\n", id, right);
        pthread_mutex_unlock(&forks[left]);
        printf("Philosopher %d put down left fork %d...\n", id, left);
        state[id] = THINKING;
    }
    return NULL;
}

int main() {
    int i, id[MAX_PHILOSOPHERS];
    srand(time(NULL));
    printf("Enter the number of philosophers (max %d): ", MAX_PHILOSOPHERS);
    scanf("%d", &num_philosophers);
    if (num_philosophers > MAX_PHILOSOPHERS) {
        printf("Error: too many philosophers!\n");
        return 1;
    }
    printf("Enter the number of executions (max %d): ", MAX_EXECUTIONS);
    scanf("%d", &num_executions);
    for (i = 0; i < num_philosophers; i++) {
        id[i] = i;
        state[i] = THINKING;
        pthread_mutex_init(&forks[i], NULL);
        pthread_create(&threads[i], NULL, philosopher, &id[i]);
    }
    for (i = 0; i < num_philosophers; i++) {
        pthread_join(threads[i], NULL);
    }
    for (i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}
