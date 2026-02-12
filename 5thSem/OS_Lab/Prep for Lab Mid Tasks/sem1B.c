#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int data = 0;
int read_count = 0;

sem_t mutex;
sem_t write_block;

// Reader thread
void *reader(void *arg)
{
    int id = *(int *)arg;
    printf("[Reader %d] Waiting to read...\n", id);

    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&write_block); // first reader blocks writer
    sem_post(&mutex);

    printf("[Reader %d] Reading data: %d\n", id, data);
    sleep(1);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&write_block); // last reader releases writer
    sem_post(&mutex);

    return NULL;
}

// Writer thread
void *writer(void *arg)
{
    int id = *(int *)arg;
    printf("[Writer %d] Waiting to write...\n", id);

    sem_wait(&write_block);
    printf("[Writer %d] Writing data...\n", id);
    data++;
    sleep(1);
    printf("[Writer %d] Updated data to %d\n", id, data);
    sem_post(&write_block);

    return NULL;
}

int main()
{
    pthread_t r1, r2, r3, w1;
    int id1 = 1, id2 = 2, id3 = 3, wid = 1;

    sem_init(&mutex, 0, 1);
    sem_init(&write_block, 0, 1);

    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&w1, NULL, writer, &wid);
    pthread_create(&r3, NULL, reader, &id3);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);
    pthread_join(r3, NULL);

    sem_destroy(&mutex);
    sem_destroy(&write_block);

    return 0;
}
