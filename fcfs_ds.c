#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, totalHeadMovement = 0, currentHead;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter the disk requests (track numbers):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of disk head: ");
    scanf("%d", &currentHead);

    printf("\nSequence of head movement:\n");
    for (i = 0; i < n; i++) {
        printf("Head moves from %d to %d\n", currentHead, requests[i]);
        totalHeadMovement += abs(requests[i] - currentHead);
        currentHead = requests[i];
    }

    printf("\nTotal head movement = %d\n", totalHeadMovement);
    
    return 0;
}
