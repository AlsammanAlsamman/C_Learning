
#include <pthread.h>


// Matrix functions
int **createMatrix();
int **initializeMatrix(int **matrix);
void printMatrix(int **matrix);
void freeMatrix(int **matrix);


// Thread functions
void *rowSumRoutine(void *argv);
pthread_t *createThreads(int n);
void freeThreads(pthread_t *threads);