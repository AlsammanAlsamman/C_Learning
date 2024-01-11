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
    int *rows = (int *) arg;
    // print thread rows

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

int **ThreadsRows(int threadShare, int leftRows, int max_threads)
{    
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
void printThreadsRows(int **threadRows,  int threadShare, int leftRows,int max_threads)
{

    // print threads rows
    size_t i;
    for (i = 0; i < max_threads; i++)
    {
        while (threadRows[i][0] != -1)
        {
            printf("%d\t", threadRows[i][0]);
            threadRows[i]++;
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    // create the matrix
    int **matrix = createMatrix();
    initializeMatrix(matrix);
    
    // calculate the number of threads
    int max_threads = MAX_THREADS;
    // if th threads number is bigger than the rows number then use the rows number
    if(ROWN < max_threads)
    {
        max_threads = ROWN;
    }
    
    // Calculate the number of thread share
    int threadShare = 1;
    while (ROWN / threadShare > max_threads)
    {
        threadShare++;
    }
    printf("bestThreadShare: %d\n", threadShare);
    int leftRows = ROWN - (threadShare * max_threads); 
    printf("leftRows: %d\n", leftRows);
    
    int **threadRows = ThreadsRows(threadShare, leftRows, max_threads);
    printThreadsRows(threadRows, threadShare, leftRows, max_threads);
    // create the threads
    pthread_t *threads = createThreads(max_threads);

    // freeMatrix(matrix);
    return 0;
}