#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 3
#define NUM_THREADS 3

int matrixA[MATRIX_SIZE][MATRIX_SIZE];
int matrixB[MATRIX_SIZE][MATRIX_SIZE];
int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

//Counter paired with  mutex that protects the counter
int calcCounter = 0;
pthread_mutex_t exampleMutex;

typedef struct {
    int row;
    int col;
} thread_data_t;

void *multiply(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        resultMatrix[data->row][data->col] += matrixA[data->row][i] * matrixB[i][data->col];
        //Lock and unlock mutex accordingly to alter the counter
        pthread_mutex_lock(&exampleMutex);
        calcCounter++;
        pthread_mutex_unlock(&exampleMutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];

    //Initialize mutex on thread
    pthread_mutex_init(&exampleMutex, NULL);

    // Initialize matrices A and B
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }

    // Create threads to compute the result matrix
    int thread_count = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            thread_data[thread_count].row = i;
            thread_data[thread_count].col = j;
            pthread_create(&threads[thread_count], NULL, multiply, (void *)&thread_data[thread_count]);
            thread_count++;

            if (thread_count >= NUM_THREADS)
                thread_count = 0;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the result matrix
    printf("Result Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", resultMatrix[i][j]);
        }
        printf("\n");
    }

    //Output counter value
    printf("Calculations: %d\n", calcCounter);

    //Clean up allocated memory for mutex
    pthread_mutex_destroy(&exampleMutex);

    return 0;
}
