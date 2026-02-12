#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex;

char high_logs[10][50];
char low_logs[10][50];
int high_count = 0, low_count = 0;

void* high_priority(void* msg) {
    pthread_mutex_lock(&mutex);
    strcpy(high_logs[high_count++], (char*)msg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* low_priority(void* msg) {
    pthread_mutex_lock(&mutex);
    strcpy(low_logs[low_count++], (char*)msg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, low_priority, "Network OK");
    pthread_create(&t2, NULL, high_priority, "Disk Failure");
    pthread_create(&t3, NULL, low_priority, "User Login");
    pthread_create(&t4, NULL, high_priority, "Power Surge");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    // Buffer dump
    for (int i = 0; i < high_count; i++)
        printf("[HIGH] %s\n", high_logs[i]);

    for (int i = 0; i < low_count; i++)
        printf("[LOW] %s\n", low_logs[i]);

    pthread_mutex_destroy(&mutex);
    return 0;
}
