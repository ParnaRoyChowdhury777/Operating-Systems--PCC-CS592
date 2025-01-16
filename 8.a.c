#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *summation(void *arg) {

	int n, s=0, x;
	printf("Enter N: ");
	scanf("%d", &n);
	
	for (int i=0; i< n; i++) {
		printf("Enter number %d: ", i);
		scanf("%d", &x);
		s += x;
	}
	printf("Sum: %d\n", s);
	pthread_exit(NULL);
}


int main (int argc, char *argv[]) {
	

	pthread_t thread; 
	pthread_create(&thread, NULL, summation, NULL);
	
	pthread_join(thread, NULL);

	return EXIT_SUCCESS;

}
