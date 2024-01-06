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

#define ROWN 10
#define COLN 10
#define THREADSN 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
int rowCounter = 0;
void *rowSumRoutine(void *argv);
int **createMatrix();
int **initializeMatrix(int **matrix);
void printMatrix(int **matrix);
void freeMatrix(int **matrix);


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
 int *currentRow = (int*) malloc(sizeof(int));
 int **matrix = (int **)arg;

 pthread_mutex_lock(&mutex);
 *currentRow = rowCounter;
 rowCounter++;
 pthread_mutex_unlock(&mutex);
 size_t j;
 for (j = 0; j < COLN; j++)
 {
    *rowsum+=matrix[*currentRow][j];
 }
 printf("ROW: %d SUM:%d\n", *currentRow,*rowsum);
}



int main(int argc, char **argv)
{
    // create the matrix
    int **matrix = createMatrix();
    matrix = initializeMatrix(matrix);
    pthread_t threads[THREADSN];
    size_t i;
    for ( i = 0; i < THREADSN; i++)
    {
        pthread_create(threads + i , NULL, &rowSumRoutine,(void **)matrix);
    }
    for ( i = 0; i < THREADSN; i++)
    {
        pthread_join(*(threads + i) , NULL);
    }
    
    return 0;
}