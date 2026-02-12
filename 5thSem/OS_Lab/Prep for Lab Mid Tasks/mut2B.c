#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SUB_ARRAY_COUNT 4
#define SUB_ARRAY_DIM 4
#define RANGE 10

int data_array[SUB_ARRAY_COUNT][SUB_ARRAY_DIM][SUB_ARRAY_DIM][SUB_ARRAY_DIM];
int global_histogram[RANGE] = {0};

pthread_mutex_t mutex;

/* PROVIDED — DO NOT MODIFY */
void init_data_array() {
    srand(0);
    for (int i = 0; i < SUB_ARRAY_COUNT; i++) {
        for (int j = 0; j < SUB_ARRAY_DIM; j++) {
            for (int k = 0; k < SUB_ARRAY_DIM; k++) {
                for (int l = 0; l < SUB_ARRAY_DIM; l++) {
                    data_array[i][j][k][l] = rand() % RANGE;
                }
            }
        }
    }
}

/* Thread function */
void* compute_histogram(void* arg) {
    int idx = *(int*)arg;

    int local_histogram[RANGE] = {0};

    // Step 1: Compute local histogram
    for (int j = 0; j < SUB_ARRAY_DIM; j++) {
        for (int k = 0; k < SUB_ARRAY_DIM; k++) {
            for (int l = 0; l < SUB_ARRAY_DIM; l++) {
                int value = data_array[idx][j][k][l];
                local_histogram[value]++;
            }
        }
    }

    // Step 2: Merge into global histogram
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < RANGE; i++) {
        global_histogram[i] += local_histogram[i];
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[SUB_ARRAY_COUNT];
    int indices[SUB_ARRAY_COUNT];

    pthread_mutex_init(&mutex, NULL);
    init_data_array();

    // Create threads
    for (int i = 0; i < SUB_ARRAY_COUNT; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, compute_histogram, &indices[i]);
    }

    // Join threads
    for (int i = 0; i < SUB_ARRAY_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    // Verification
    int total = 0;
    for (int i = 0; i < RANGE; i++) {
        total += global_histogram[i];
    }

    printf("Total count = %d\n", total);
    printf("Expected    = %d\n",
           SUB_ARRAY_COUNT * SUB_ARRAY_DIM * SUB_ARRAY_DIM * SUB_ARRAY_DIM);

    pthread_mutex_destroy(&mutex);
    return 0;
}
