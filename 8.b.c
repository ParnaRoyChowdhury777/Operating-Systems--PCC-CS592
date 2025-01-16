#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *summation(void *arg) {
    int n = *((int *)arg);
    int x, s = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &x);
        s += x;
    }

    // Return the sum as a pointer to an integer
    int *result = malloc(sizeof(int));
    *result = s;
     pthread_exit((void *)result);
    
}

int main() {
    int n;
    printf("Enter N: ");
    scanf("%d", &n);

    pthread_t th;
    pthread_create(&th, NULL, summation, &n);

    // Get the result from the thread
    int *result;
    pthread_join(th, (void **)&result);

    printf("Sum: %d\n", *result);
    free(result); // Free the allocated memory

    return EXIT_SUCCESS;
}

