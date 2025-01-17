#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to hold array and its size
typedef struct {
    int *array;
    int size;
} ArrayData;

// Selection sort in ascending order
void selectionSortAscending(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        // Swap the found minimum element with the first element
        int temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
}

// Selection sort in descending order
void selectionSortDescending(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] > array[maxIndex]) {
                maxIndex = j;
            }
        }
        // Swap the found maximum element with the first element
        int temp = array[maxIndex];
        array[maxIndex] = array[i];
        array[i] = temp;
    }
}

// Thread function for sorting in ascending order
void* sortAscending(void* arg) {
    ArrayData* data = (ArrayData*)arg;
    selectionSortAscending(data->array, data->size);
    pthread_exit(data->array);  // Return sorted array to main
}

// Thread function for sorting in descending order
void* sortDescending(void* arg) {
    ArrayData* data = (ArrayData*)arg;
    selectionSortDescending(data->array, data->size);
    pthread_exit(data->array);  // Return sorted array to main
}

int main() {
    int n, i;
    
    // Read the size of the array
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    
    // Read the array elements
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Determine the sizes of each half
    int halfSize1 = n / 2;
    int halfSize2 = n - halfSize1;
    
    // Dynamically allocate memory for each half
    int *firstHalf = malloc(halfSize1 * sizeof(int));
    int *secondHalf = malloc(halfSize2 * sizeof(int));
    
    // Split the array into two halves
    for (i = 0; i < halfSize1; i++) {
        firstHalf[i] = arr[i];
    }
    for (i = 0; i < halfSize2; i++) {
        secondHalf[i] = arr[halfSize1 + i];
    }
    
    // Prepare data structures to pass to threads
    ArrayData data1 = {firstHalf, halfSize1};
    ArrayData data2 = {secondHalf, halfSize2};
    
    // Declare thread IDs
    pthread_t thread1, thread2;
    
    // Create threads
    pthread_create(&thread1, NULL, sortAscending, &data1);
    pthread_create(&thread2, NULL, sortDescending, &data2);
    
    // Capture returned sorted arrays
    int *sortedAscending;
    int *sortedDescending;
    
    pthread_join(thread1, (void**)&sortedAscending);
    pthread_join(thread2, (void**)&sortedDescending);
    
    // Print the sorted arrays
    printf("First half sorted in ascending order: ");
    for (i = 0; i < halfSize1; i++) {
        printf("%d ", sortedAscending[i]);
    }
    printf("\n");

    printf("Second half sorted in descending order: ");
    for (i = 0; i < halfSize2; i++) {
        printf("%d ", sortedDescending[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(firstHalf);
    free(secondHalf);

    return 0;
}