#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to detect deadlock using Banker's Algorithm
void detectDeadlock(int alloc[P][R], int max[P][R], int avail[R]) {
    int need[P][R];
    bool finish[P] = {false};
    int work[R];

    // Calculate need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize work = available
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int k = 0; k < R; k++)
                        work[k] += alloc[p][k];
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            break; // Deadlock condition
        }
    }

    // Check for deadlocked processes
    bool deadlock = false;
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            printf("Process %d is in deadlock.\n", i);
            deadlock = true;
        }
    }

    if (!deadlock) {
        printf("No deadlock is detected.\n");
    }
}

// Sample input
int main() {
    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int avail[R] = {1, 0, 2};

    detectDeadlock(alloc, max, avail);
    return 0;
}
