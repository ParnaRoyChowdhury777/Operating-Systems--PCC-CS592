#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Semaphore for chopsticks
sem_t chopsticks[NUM_PHILOSOPHERS];

// Philosopher function
void *philosopher(void *arg) {
    int id = *(int *)arg;
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        
        // Pick up chopsticks (left and right)
        sem_wait(&chopsticks[id]); // Pick up left chopstick
        sem_wait(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]); // Pick up right chopstick

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(1); // Simulate eating time

        // Put down chopsticks
        sem_post(&chopsticks[id]); // Put down left chopstick
        sem_post(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]); // Put down right chopstick

        printf("Philosopher %d has finished eating and is thinking again.\n", id);
    }
    return NULL;
}

void handler(int signum) {
  printf("Terminating Program\n");
  exit(0);
}

int main() {
    signal(SIGINT, handler);
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize semaphores for chopsticks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &ids[i]) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    // Join philosopher threads (infinite loop, so this won't terminate)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores (unreachable in this program)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}
