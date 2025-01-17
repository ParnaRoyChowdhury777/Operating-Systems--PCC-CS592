#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<math.h>
#include<unistd.h>

#define THREAD_COUNT 10

typedef struct {
	int start, end, key;
}threadData;

int isPrime(int n) {
	if(n < 2)
		return 0;
	for(int i=2; i * i <= n; i++) {
		if(n % i == 0)
			return 0;
	}
	return 1;
}

void *myThread(void *arg) {
	threadData *td = (threadData*)arg;
	printf("\nFrom Thread - %d\n", td->key);
	int flag = 0;
	for(int i=td->start; i<=td->end; i++) {
		if(isPrime(i)) {
			printf("%d ",i);
			flag = 1;
		}
	}
	if(flag == 0)
		printf("No prime number from this thread\n");
	printf("\n");
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int N;
	printf("\nEnter N: ");
	scanf("%d",&N);
	
	if(N <= 1) {
		printf("Invalid value of N\n");
	} else {

	pthread_t threads[THREAD_COUNT];
	threadData threaddata[THREAD_COUNT];
	
	int range = N/THREAD_COUNT;

	for(int i=0; i<THREAD_COUNT; i++) {
		threaddata[i].start = i * range + 1;
		threaddata[i].end = (i == THREAD_COUNT - 1) ? N : (i + 1) * range;
		threaddata[i].key = i + 1;
	}

	for(int i=0; i<THREAD_COUNT; i++) {
		pthread_create(&threads[i], NULL, myThread, &threaddata[i]);
		usleep(5000);
	}

	for(int i=0; i<THREAD_COUNT; i++) {
		pthread_join(threads[i], NULL);
	}
}
	return 0;
}
