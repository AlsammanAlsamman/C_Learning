//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ROWN 10000
#define COLN 10000
#define MAX_THREADS 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
int rowCounter = 0;

void *rowSumRoutine(void *argv);
int **createMatrix();
int **initializeMatrix(int **matrix);
void printMatrix(int **matrix);
void freeMatrix(int **matrix);
pthread_t *createThreads(int n);
void freeThreads(pthread_t *threads);

int **createMatrix()
{
    int **matrix = (int **) malloc(sizeof(int*) * ROWN);
    size_t i ;
    for (i = 0; i < ROWN; i++)
    {
        matrix[i] = (int *) malloc(sizeof(int) * COLN);
    }
    return matrix;
}
void printMatrix(int **matrix)
{
    size_t i;
    size_t j;
    for (i = 0; i < ROWN; i++)
    {
        for ( j = 0; j < COLN; j++)
        {
            printf("%d\t",matrix[j][i]);
        }
        printf("\n");
    }
    
}
int **initializeMatrix(int **matrix)
{
    srand(time(NULL));
    size_t i ;
    size_t j;
    for (i = 0; i < ROWN; i++)
    {
        for ( j = 0; j < COLN; j++)
        {
            matrix[i][j] = rand() % 2;
        }
    }
    return matrix;
}

void * rowSumRoutine(void *arg)
{
 int *rowsum = (int*) malloc(sizeof(int));
 *rowsum = 0;

 int *currentRow = (int*) malloc(sizeof(int));
 int **matrix = (int **)arg;

 pthread_mutex_lock(&mutex);
 *currentRow = rowCounter;
 rowCounter++;
 pthread_mutex_unlock(&mutex);
 sleep(1);
 if(*currentRow < ROWN)
 {
  size_t i;
  for(i = 0; i < COLN; i++)
  {
   *rowsum += matrix[*currentRow][i];
  }
  printf("Row %d sum: %d\n", *currentRow, *rowsum);
 }
 else
 {
  printf("No more rows to process\n");
  exit(0);
 }
 
 
 free(rowsum);
 free(currentRow);
}

void freeMatrix(int **matrix)
{
    size_t i;
    for (i = 0; i < ROWN; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

pthread_t *createThreads(int n)
{
    pthread_t *threads = (pthread_t *) malloc(sizeof(pthread_t) * n);
    return threads;
}

void freeThreads(pthread_t *threads)
{
    free(threads);
}


int main(int argc, char **argv)
{
    // create the matrix
    int **matrix = createMatrix();
    matrix = initializeMatrix(matrix);
    printf("rowCounter: %d\n", rowCounter);
    // while there are rows to process
    while (rowCounter >= 0)
    {
        // create threads
        pthread_t *threads = createThreads(MAX_THREADS);
        // for each thread
        size_t i;
        for (i = 0; i < MAX_THREADS; i++)
        {
            // create a thread
            pthread_create(&threads[i], NULL, rowSumRoutine, (void *)matrix);
        }
        // for each thread
        for (i = 0; i < MAX_THREADS; i++)
        {
            // wait for the thread to finish
            pthread_join(threads[i], NULL);
        }
        // free the threads
        freeThreads(threads);
    }

    freeMatrix(matrix);
    return 0;
}