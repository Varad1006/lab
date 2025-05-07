#include <stdio.h>

struct Process {
    int id, bt, rt, at, priority;
};

int main() {
    int n, completed = 0, time = 0, min_pri, shortest = -1;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int is_completed[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for P%d: ", p[i].id);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].rt = p[i].bt;
        is_completed[i] = 0;
    }

    printf("\nGantt Chart:\n");

    while (completed != n) {
        min_pri = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !is_completed[i]) {
                if (min_pri == -1 || p[i].priority > p[min_pri].priority)
                    min_pri = i;
            }
        }

        if (min_pri != -1) {
            printf("P%d(%d) ", p[min_pri].id, time);
            p[min_pri].rt--;
            if (p[min_pri].rt == 0) {
                completed++;
                is_completed[min_pri] = 1;
            }
        }
        time++;
    }

    return 0;
}
