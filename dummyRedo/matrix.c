#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "matrixFunctions.c"

typedef struct { 
int rown;
int **matrix;
} MatrixArgs;


void *sumRow(void *args)
{
	MatrixArgs *matrixargs = (MatrixArgs *) args;
	printf("Current Row : %d\n",matrixargs->rown);
	int *sum = (int *)malloc(sizeof(int ));
	*sum = 0;
	size_t i;
	for (i = 0; i < COLN; i += 1)
	{
		*sum += matrixargs->matrix[i][matrixargs->rown];
	}
	//printMatrix(matrixargs->matrix);
	printf("%d\n",*sum);
}
int main (int argc, char ** argv)
{
	srand(time(NULL));
	int ** matrix = createMatrix();
	initMatrix(matrix);
	//printMatrix(matrix);
	//MatrixArgs *matrixargs =(MatrixArgs *) malloc(sizeof(MatrixArgs));
	//matrixargs-> rown  = 10;
	//matrixargs->matrix = matrix;
	// create an array of matrixargs
	MatrixArgs *rowargs = (MatrixArgs *) malloc(sizeof(MatrixArgs) * ROWN);
	pthread_t threads[ROWN];
	size_t i;
	for (i = 0; i < ROWN; i += 1)
	{
		// create matrixarg 
		rowargs[i].rown = 10;
		rowargs[i].matrix = matrix;
		pthread_create(threads+i,NULL, sumRow,(void *) &rowargs[i]);
	} 
	size_t j;
	for (j = 0; j < ROWN; j += 1)
	{
		pthread_join(threads[j],NULL);
	}
	
	//sumRow((void *) matrixargs);
	return 0;
}
