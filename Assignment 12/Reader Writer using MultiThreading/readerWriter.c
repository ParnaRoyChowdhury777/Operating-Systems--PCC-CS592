#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

#define NUM_READERS 3
#define NUM_WRITERS 2
#define FILE_NAME "shared_file.txt"

sem_t resource_access;    // Semaphore to manage access to the file
sem_t read_count_access;  // Semaphore to manage access to read_count
int read_count = 0;       // Number of active readers


void write_to_file(const char* data) {
    FILE* file = fopen(FILE_NAME, "a"); // Open the file in append mode
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", data); // Write data to the file
    fclose(file); // Close the file
}


void read_from_file(int reader_id) {
    FILE* file = fopen(FILE_NAME, "r"); // Open the file in read mode
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Reader %d read: %s", reader_id, buffer); // Print the file's content
    }
    fclose(file); // Close the file
}

void* reader(void* id) {
    int reader_id = *(int*)id;
    while (1) {
     
        printf("Reader %d is waiting to read\n",reader_id);
        sem_wait(&read_count_access);
        read_count++;
        if (read_count == 1) {
            sem_wait(&resource_access); // First reader locks the resource
        }
        sem_post(&read_count_access);

      
        printf("Reader %d is READING from the file.\n", reader_id);
        read_from_file(reader_id); // Read the file content
        sleep(1); // Simulate reading time

  
        sem_wait(&read_count_access);
        read_count--;
        if (read_count == 0) {
            sem_post(&resource_access); // Last reader unlocks the resource
        }
        sem_post(&read_count_access);
        printf("Reader %d finishes\n", reader_id);

        sleep(2); // Simulate time between reads
    }
    pthread_exit(NULL);
}

void* writer(void* id) {
    int writer_id = *(int*)id;
    while (1) {
        // Writer entry
        printf("Writer %d is WAITING to write.\n", writer_id);
        sem_wait(&resource_access); // Lock the resource

        // Writing to the shared file
        printf("Writer %d is WRITING to the file.\n", writer_id);
        char data[50];
        sprintf(data, "Writer %d wrote this line.", writer_id);
        write_to_file(data); // Write to the file
        sleep(1); // Simulate writing time

        sem_post(&resource_access); // Unlock the resource
        printf("Writer %d has FINISHED writing.\n", writer_id);

        sleep(2); // Simulate time between writes
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&resource_access, 0, 1);
    sem_init(&read_count_access, 0, 1);

    // Create the shared file and initialize it
    FILE* file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Shared File Initialized.\n");
    fclose(file);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    sem_destroy(&resource_access);
    sem_destroy(&read_count_access);

    return 0;
}

