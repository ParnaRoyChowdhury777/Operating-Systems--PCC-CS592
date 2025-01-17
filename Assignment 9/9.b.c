#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>


//int isPrime(void *args) {
void *isPrime(void *args) {
	int flag = 1;
	int *result = malloc(sizeof(int));
	
	int n = *((int *)args);
	if (n < 2) {
		flag = 0;
	} else {
		for (int i=2; i<=sqrt(n); i++) {
			if (n % i == 0) {
				flag = 0;
				break;
			}
		}
	}
	
	*result = flag;
	pthread_exit((void *)result);
}


int main (int argc, char *argv[]) {

	pthread_t th;

	int n, *result;
	printf("Enter number: ");
	scanf("%d", &n);

	//pthread_create(&th, NULL, (void *)isPrime, (void *)&n);
	pthread_create(&th, NULL, isPrime, &n);
	
	pthread_join(th, (void**)&result);

	if (*result == 1) {
		printf("PRIME\n");
	} else {
		printf("NOT PRIME\n");
	}

}
