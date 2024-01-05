//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 10
#define NUM_ROWS 10
#define NUM_COLS 10
void *sum_row(void *arg);
int **createMatrix();
int **fillMatrix(int **matrix);
void printMatrix(int **matrix);

int rowCounter = NUM_ROWS;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// create a rooutine to sum up the elements of a row

void *sum_row(void *arg)
{
    int *sum = (int*)malloc(sizeof(int));
    int *row = (int*)malloc(sizeof(int));
    *sum = 0;
    *row = 0;
    
    // get the matrix
    int **matrix = (int **)arg;
    pthread_mutex_lock(&mutex);
    row = &rowCounter;
    rowCounter--;
    pthread_mutex_unlock(&mutex);
    size_t i;
    for (i = 0; i < NUM_COLS; i++)
    {
        *sum += matrix[*row][i];
    }
    printf("Sum of row %d is %d\n", *row, *sum);
    
    pthread_exit(NULL);


}

int **createMatrix()
{
    int **matrix = (int **)malloc(NUM_ROWS * sizeof(int *));
    for (int i = 0; i < NUM_ROWS; i++)
    {
        matrix[i] = (int *)malloc(NUM_COLS * sizeof(int));
    }
    return matrix;
}
int **fillMatrix(int **matrix)
{
    srand(time(NULL));
    size_t i, j;
    for (i = 0; i < NUM_ROWS; i++)
    {
        for (j = 0; j < NUM_COLS; j++)
        {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}
void printMatrix(int **matrix)
{
    size_t i, j;
    for (i = 0; i < NUM_ROWS; i++)
    {
        for (j = 0; j < NUM_COLS; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
int main(int argc , char *argv[])
{
    // create a matrix of 1000 x 1000
    int **matrix = createMatrix();
    // fill the matrix with random numbers
    matrix = fillMatrix(matrix);
    // print the matrix
    printMatrix(matrix);
    // create 5 threads
    pthread_t threads[NUM_THREADS];
    // create 5 threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, sum_row, (void *)matrix);
    }
    // wait for the threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    // destroy the mutex
    pthread_mutex_destroy(&mutex);
    // free the matrix
    for (int i = 0; i < NUM_ROWS; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}