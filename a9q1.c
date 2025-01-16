#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;

void *tf1(void *arg) {
	while(1) {
		sem_wait(&mutex);
		printf("ba");
		sem_post(&mutex);
		usleep(5000);
	}
	pthread_exit(NULL);
}

void *tf2(void *arg) {
	while(1) {
		sem_wait(&mutex);
		printf("ab");
		sem_post(&mutex);
		usleep(5000);
	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{ 
	sem_init(&mutex, 0, 1);
	pthread_t th1;
	pthread_t th2;
	pthread_create(&th1, NULL, tf1, NULL);
	pthread_create(&th2, NULL, tf2, NULL);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	sem_destroy(&mutex);
	return EXIT_SUCCESS;
}
