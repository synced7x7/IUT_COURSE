#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Shared balances
int A = 1000, B = 1000, C = 1000;

// Mutexes
pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexC = PTHREAD_MUTEX_INITIALIZER;

// Transfer function
void transfer(int *from, int *to, int amount,
              pthread_mutex_t *fromMutex,
              pthread_mutex_t *toMutex,
              const char *fromName,
              const char *toName)
{
    pthread_mutex_lock(fromMutex);
    pthread_mutex_lock(toMutex);

    if (*from >= amount) {
        printf("Transfer START: %d from %s -> %s\n", amount, fromName, toName);
        *from -= amount;
        *to += amount;
        printf("Transfer END  : %d from %s -> %s\n", amount, fromName, toName);
    }

    pthread_mutex_unlock(toMutex);
    pthread_mutex_unlock(fromMutex);
}

// Thread T1: A → B
void *T1(void *arg)
{
    for (int i = 0; i < 10; i++) {
        transfer(&A, &B, 100, &mutexA, &mutexB, "A", "B");
    }
    printf("T1 DONE | A=%d B=%d C=%d\n", A, B, C);
    return NULL;
}

// Thread T2: B → C
void *T2(void *arg)
{
    for (int i = 0; i < 20; i++) {
        transfer(&B, &C, 50, &mutexB, &mutexC, "B", "C");
    }
    printf("T2 DONE | A=%d B=%d C=%d\n", A, B, C);
    return NULL;
}

// Thread T3: C → A
void *T3(void *arg)
{
    for (int i = 0; i < 40; i++) {
        transfer(&C, &A, 25, &mutexC, &mutexA, "C", "A");
    }
    printf("T3 DONE | A=%d B=%d C=%d\n", A, B, C);
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, T1, NULL);
    pthread_create(&t2, NULL, T2, NULL);
    pthread_create(&t3, NULL, T3, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\nFINAL BALANCES\n");
    printf("A = %d, B = %d, C = %d\n", A, B, C);
    printf("Total = %d\n", A + B + C);

    return 0;
}
