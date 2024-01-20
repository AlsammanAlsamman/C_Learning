#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define ROWN 16
#define COLN 10
#define MAX_THREADS 7

typedef struct ThreadArgs
{
    int **matrix;
    int *rows;
} ThreadArgs;
// Matrix functions
int **createMatrix();
void initializeMatrix(int **matrix);
void printMatrix(int **matrix);
void freeMatrix(int **matrix);
void *rowSumRoutine(void *argv);
pthread_t *createThreads(int n);
