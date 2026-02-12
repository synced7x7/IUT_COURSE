#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_power_done;
sem_t sem_comm_done;

void* power_thread(void* arg) {
    sleep(1);
    printf("[Power Thread] Power Initialized. Signal sent.\n");
    sem_post(&sem_power_done);
    return NULL;
}

void* comm_thread(void* arg) {
    printf("[Comm Thread] Waiting for Signal...\n");
    sem_wait(&sem_power_done);
    sleep(1);
    printf("[Comm Thread] Communication Initialized. Signal sent.\n");
    sem_post(&sem_comm_done);
    return NULL;
}

void* control_thread(void* arg) {
    printf("[Control Thread] Waiting for Signal...\n");
    sem_wait(&sem_comm_done);
    sleep(1);
    printf("[Control Thread] Control System Initialized.\n");
    return NULL;
}

int main() {
    pthread_t power, comm, control;

    sem_init(&sem_power_done, 0, 0);
    sem_init(&sem_comm_done, 0, 0);

    // Random start order
    pthread_create(&control, NULL, control_thread, NULL);
    pthread_create(&comm, NULL, comm_thread, NULL);
    pthread_create(&power, NULL, power_thread, NULL);

    pthread_join(power, NULL);
    pthread_join(comm, NULL);
    pthread_join(control, NULL);

    sem_destroy(&sem_power_done);
    sem_destroy(&sem_comm_done);

    return 0;
}
