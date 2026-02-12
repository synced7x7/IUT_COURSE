#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_nav;
sem_t sem_launch;

// Fuel system thread
void *fuel(void *arg)
{
    sleep(1); // random start delay
    printf("[Fuel Thread] Fuel system activated. Signal sent.\n");
    sem_post(&sem_nav);   // Signal navigation
    return NULL;
}

// Navigation system thread
void *navigation(void *arg)
{
    printf("[Navigation Thread] Waiting for fuel system...\n");
    sem_wait(&sem_nav);   // Wait for fuel
    printf("[Navigation Thread] Navigation system online. Signal sent.\n");
    sem_post(&sem_launch); // Signal launch
    return NULL;
}

// Launch system thread
void *launch(void *arg)
{
    printf("[Launch Thread] Waiting for navigation system...\n");
    sem_wait(&sem_launch); // Wait for navigation
    printf("[Launch Thread] Launch sequence initiated!\n");
    return NULL;
}

int main()
{
    pthread_t t_fuel, t_nav, t_launch;

    sem_init(&sem_nav, 0, 0);
    sem_init(&sem_launch, 0, 0);

    pthread_create(&t_nav, NULL, navigation, NULL);
    pthread_create(&t_launch, NULL, launch, NULL);
    pthread_create(&t_fuel, NULL, fuel, NULL);

    pthread_join(t_fuel, NULL);
    pthread_join(t_nav, NULL);
    pthread_join(t_launch, NULL);

    sem_destroy(&sem_nav);
    sem_destroy(&sem_launch);

    return 0;
}
