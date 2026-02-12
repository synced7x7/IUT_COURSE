#include <stdio.h>
#include <stdbool.h>

#define N 5 // Number of Processes
#define M 3 // Number of Resource Types

bool isSafe(int alloc[N][M], int max[N][M], int avail[M], int safeSeq[N]) {

    int need[N][M];
    bool finish[N];

    // 1. Calculate NEED matrix = MAX - ALLOCATION
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // 2. Initialize finish array
    for (int i = 0; i < N; i++)
        finish[i] = false;

    // 3. Initialize work = available
    int work[M];
    for (int j = 0; j < M; j++)
        work[j] = avail[j];

    int count = 0;

    // 4. Try to find processes that can finish
    while (count < N) {

        bool found = false;

        for (int i = 0; i < N; i++) {

            if (!finish[i]) {

                bool possible = true;

                // Check if need <= work
                for (int j = 0; j < M; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                // If possible → simulate execution
                if (possible) {

                    for (int j = 0; j < M; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process found → unsafe state
        if (!found)
            return false;
    }

    return true;
}

int main() {

    int alloc[N][M] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[N][M] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // SAFE CASE
    int avail[M] = {3, 3, 2};

    // UNSAFE CASE (uncomment to test)
    // int avail[M] = {0, 2, 0};

    int safeSeq[N];

    if (isSafe(alloc, max, avail, safeSeq)) {

        printf("System is in SAFE state.\nSafe Sequence: ");

        for (int i = 0; i < N; i++)
            printf("P%d%s", safeSeq[i], (i == N-1 ? "\n" : " -> "));
    }
    else {
        printf("System is in UNSAFE state (Deadlock potential).\n");
    }

    return 0;
}
