#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t forks[N];             // One semaphore for each fork
sem_t mutex;                // Semaphore to prevent deadlock

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3);  // Simulate thinking

        sem_wait(&mutex);          // Prevent deadlock
        sem_wait(&forks[left]);    // Pick up left fork
        sem_wait(&forks[right]);   // Pick up right fork
        sem_post(&mutex);

        printf("Philosopher %d is eating 🍝\n", id);
        sleep(rand() % 2);         // Simulate eating

        sem_post(&forks[left]);    // Put down left fork
        sem_post(&forks[right]);   // Put down right fork

        printf("Philosopher %d has finished eating.\n", id);
    }
}

int main() {
    pthread_t threads[N];
    int ids[N];

    // Initialize semaphores
    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    sem_init(&mutex, 0, 1);

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all threads
    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    // Cleanup
    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);
    sem_destroy(&mutex);

    return 0;
}
