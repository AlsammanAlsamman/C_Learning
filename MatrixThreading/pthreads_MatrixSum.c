//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "matrixthread.h"
#include <math.h>

#define ROWN 15
#define COLN 10
#define MAX_THREADS 7

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 


typedef struct ThreadArgs
{
    int **matrix;
    int *rows;
} ThreadArgs;


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

void freeMatrix(int **matrix)
{
    size_t i;
    for (i = 0; i < ROWN; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
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

void initializeMatrix(int **matrix)
{
    srand(time(NULL));
    size_t i, j;
    for (i = 0; i < ROWN; i++)
    {
        for ( j = 0; j < COLN; j++)
        {
            matrix[i][j] = rand() % 2;
        }
    }
}


void * rowSumRoutine(void *arg)
{
    // get the thread arguments
    ThreadArgs *args = (ThreadArgs *) arg;
    int **matrix = args->matrix;
    int *rows = args->rows;
    // create a sum variable
    int *sum = (int *) malloc(sizeof(int));
    *sum = 0;
    // calculate the sum of the columns
    while (rows[0] != -1)
    {
        size_t i;
        for (i = 0; i < COLN; i++)
        {
            *sum += matrix[rows[0]][i];
        }
        rows++;
    }
    // print the sum
    printf("sum: %d\n", *sum);
    // free the thread arguments
    free(args);
    // exit the thread
    pthread_exit(NULL);
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
int **ThreadsRows(int max_threads)
{    
    // start with minimum row number per thread
    int threadShare = 1;
    while (ROWN / threadShare > max_threads)
    {
        threadShare++;
    }
    int leftRows = ROWN - (threadShare * max_threads); 
    
    printf("bestThreadShare: %d\n", threadShare);
    printf("leftRows: %d\n", leftRows);

    // create an array of rows for each thread
    int **threadRows = (int **) malloc(sizeof(int *) * max_threads);
    // for each thread
    size_t i;
    for (i = 0; i < max_threads; i++)
    {
        // create an array of rows
        threadRows[i] = (int *) malloc(sizeof(int) * threadShare + 1); // +1 for the sentinel
        // for each row
        size_t j;
        for (j = 0; j < threadShare; j++)
        {
            // add the row to the thread
            threadRows[i][j] = i * threadShare + j;
        }
        // add a sentinel
        threadRows[i][threadShare] = -1;
    }
    // add the left rows to the last thread
    if (leftRows > 0)
    {
        // reallocate the last thread
        int lastThreadNewSize = threadShare + leftRows + 1; // +1 for the sentinel
        threadRows[max_threads - 1] = (int *) realloc(threadRows[max_threads - 1], sizeof(int) * lastThreadNewSize);
        // add the left rows to the last thread
        size_t j;
        for (j = 0; j < leftRows; j++)
        {
            threadRows[max_threads - 1][j + threadShare] = max_threads * threadShare + j;
        }
        // add a sentinel
        threadRows[max_threads - 1][lastThreadNewSize - 1] = -1;
    }
    return threadRows;
}
void printThreadsRows(int **threadRows, int threadnumber)
{

    // print threads rows
    size_t i;
    for (i = 0; i < threadnumber; i++)
    {
        while (threadRows[i][0] != -1)
        {
            printf("%d\t", threadRows[i][0]);
            threadRows[i]++;
        }
        printf("\n");
    }
}
int *fittedThreadNumber()
{
    // ********* calculate the number of threads
    int max_threads = MAX_THREADS;
    // if the threads number is bigger than the rows number then use the rows number
    if(ROWN < max_threads)
    {
        max_threads = ROWN;
    }
    int *fitNumber = (int*)malloc(sizeof(int));
    *fitNumber = max_threads;
    return fitNumber;
}
int main(int argc, char **argv)
{
    // create the matrix
    int **matrix = createMatrix();
    initializeMatrix(matrix);

    int *threadnumber = fittedThreadNumber();
    printf("%d\n",*threadnumber);
    int **threadRows = ThreadsRows(*threadnumber);
    // printThreadsRows(threadRows,*threadnumber);
    // create the threads
    pthread_t *threads = createThreads(*threadnumber);
    // create an array of threads arguments
    ThreadArgs **args = (ThreadArgs **) malloc(sizeof(ThreadArgs *) * *threadnumber);
    // create the threads arguments
    size_t i;
    for (i = 0; i < *threadnumber; i++)
    {
        // create the thread arguments
        args[i] = (ThreadArgs *) malloc(sizeof(ThreadArgs));
        // add the matrix to the thread arguments
        args[i]->matrix = matrix;
        // add the rows to the thread arguments
        args[i]->rows = threadRows[i];
        // create the thread
        pthread_create(&threads[i], NULL, rowSumRoutine, args[i]);
    }
    // wait for the threads to finish
    for (i = 0; i < *threadnumber; i++)
    {
        pthread_join(threads[i], NULL);
    }
    freeMatrix(matrix);
    return 0;
}