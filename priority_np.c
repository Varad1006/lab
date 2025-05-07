#include <stdio.h>

struct Process {
    int id, bt, priority, wt, tat;
};

void swap(struct Process* a, struct Process* b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Burst Time and Priority for P%d: ", p[i].id);
        scanf("%d %d", &p[i].bt, &p[i].priority);
    }

    // Sort by priority (higher number = higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].priority > p[i].priority)
                swap(&p[i], &p[j]);
        }
    }

    p[0].wt = 0;
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
    }

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
    }

    printf("\nProcess\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\n", p[i].id, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }

    return 0;
}
