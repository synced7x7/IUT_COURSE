#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t hydrogen_sem;
sem_t oxygen_sem;
sem_t barrier;

void* hydrogen(void* arg) {
    printf("H Ready\n");
    sem_post(&hydrogen_sem);
    sem_wait(&barrier);
    return NULL;
}

void* oxygen(void* arg) {
    printf("O Ready\n");

    // Wait for two hydrogens
    sem_wait(&hydrogen_sem);
    sem_wait(&hydrogen_sem);

    printf("Bond Formed!\n");

    // Release both hydrogens
    sem_post(&barrier);
    sem_post(&barrier);

    return NULL;
}

int main() {
    pthread_t h1, h2, o1;

    sem_init(&hydrogen_sem, 0, 0);
    sem_init(&oxygen_sem, 0, 0);
    sem_init(&barrier, 0, 0);

    pthread_create(&h1, NULL, hydrogen, NULL);
    pthread_create(&h2, NULL, hydrogen, NULL);
    sleep(1);
    pthread_create(&o1, NULL, oxygen, NULL);

    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    pthread_join(o1, NULL);

    sem_destroy(&hydrogen_sem);
    sem_destroy(&oxygen_sem);
    sem_destroy(&barrier);

    return 0;
}
