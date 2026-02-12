#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

#define CLIENTS 6

sem_t server;                 // Counting semaphore
pthread_mutex_t mutex;        // Mutex for shared data
bool serving[CLIENTS] = {0};  // Track which clients are served

// Client thread
void *client(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&server); // Request server access

    pthread_mutex_lock(&mutex);
    serving[id] = true;
    pthread_mutex_unlock(&mutex);

    sleep(1); // Client uses server

    pthread_mutex_lock(&mutex);
    serving[id] = false;
    pthread_mutex_unlock(&mutex);

    sem_post(&server); // Release server

    return NULL;
}

// Monitor thread
void *monitor(void *arg)
{
    for (int i = 0; i < 8; i++) {
        pthread_mutex_lock(&mutex);

        for (int j = 0; j < CLIENTS; j++) {
            printf("C%d=%s ", j + 1, serving[j] ? "True" : "False");
        }
        printf("\n");

        pthread_mutex_unlock(&mutex);
        usleep(300000); // 300 ms delay
    }
    return NULL;
}

int main()
{
    pthread_t clients[CLIENTS], monitorThread;
    int ids[CLIENTS];

    sem_init(&server, 0, 3);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&monitorThread, NULL, monitor, NULL);

    for (int i = 0; i < CLIENTS; i++) {
        ids[i] = i;
        pthread_create(&clients[i], NULL, client, &ids[i]);
    }

    for (int i = 0; i < CLIENTS; i++) {
        pthread_join(clients[i], NULL);
    }

    pthread_join(monitorThread, NULL);

    sem_destroy(&server);
    pthread_mutex_destroy(&mutex);

    return 0;
}
