#include <stdio.h>          // For input/output functions
#include <pthread.h>        // For using POSIX threads
#include <semaphore.h>      // For using semaphores
#include <unistd.h>         // For sleep and other POSIX functions

// Declare a semaphore 'wrt' to control write access
sem_t wrt;

// Declare a mutex to protect the 'numreader' variable
pthread_mutex_t mutex;

// Shared variable 'cnt' initialized to 1
int cnt = 1;

// Counter to keep track of the number of active readers
int numreader = 0;

// Writer thread function
void *writer(void *wno) {
    sem_wait(&wrt); // Request exclusive access to write (wait on semaphore)
    
    // Writing: modify the shared variable
    cnt = cnt * 2;
    printf("Writer %d modified count to %d\n", (*((int *)wno)), cnt);
    
    sem_post(&wrt); // Release exclusive access after writing
}

// Reader thread function
void *reader(void *rno) {
    pthread_mutex_lock(&mutex); // Lock mutex before updating numreader

    numreader++; // A new reader enters

    // If this is the first reader, block writers
    if (numreader == 1)
        sem_wait(&wrt); // Wait on the write semaphore

    pthread_mutex_unlock(&mutex); // Unlock mutex after updating numreader

    // Reading: access the shared variable
    printf("Reader %d: read count as %d\n", *((int *)rno), cnt);

    pthread_mutex_lock(&mutex); // Lock mutex before updating numreader

    numreader--; // One reader leaves

    // If this is the last reader, allow writers
    if (numreader == 0)
        sem_post(&wrt); // Release the write semaphore

    pthread_mutex_unlock(&mutex); // Unlock mutex
}

// Main function
int main() {
    pthread_t read[10], write[5]; // Declare thread IDs for readers and writers

    pthread_mutex_init(&mutex, NULL); // Initialize mutex
    sem_init(&wrt, 0, 1); // Initialize semaphore 'wrt' with value 1 (binary semaphore)

    int a[10];
    for (int i = 0; i < 10; i++) {
        a[i] = i + 1; // Assign IDs to readers and writers
    }

    // Create 5 writer and 5 reader threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, writer, (void *)&a[i]); // Create writer thread
        pthread_create(&read[i], NULL, reader, (void *)&a[i]);  // Create reader thread
    }

    // Wait for all threads to finish execution
    for (int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL); // Wait for writer thread to complete
        pthread_join(read[i], NULL);  // Wait for reader thread to complete
    }

    pthread_mutex_destroy(&mutex); // Destroy the mutex
    sem_destroy(&wrt);             // Destroy the semaphore

    return 0; // Exit the program
}
