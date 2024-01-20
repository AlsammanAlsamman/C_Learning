//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#define MARKERS 50
#define SAMPLES 50
#define MAX_THREADS 5


// genettic functions
int **createRandomMatrix(int, int);


// double euclideanDistance(double* , double* , int );
void calculateAlleleFrequencies(int* , int , double*);
// // double euclideanDistance(int* alleleFrequenciesX, int* alleleFrequenciesY, int numMarkers)
// void calculateMarkerFreqForMatrix(int  [][MARKERS], int , int , double **);
// // Function to calculate distance matrix
// void calculateDistanceMatrix(double **, int, int , double **, int);

// print functions
// Function to print allele frequencies for a matrix
void printMatrixDouble(double **matrix, int xL , int yL);
void printMatrixInt(int **, int xL , int yL);

// // Functions for threads
int **RowsPerThreads(int, int);
void printThreadsRows(int **rows_per_threads, int max_threads);
pthread_t *createThreads(int n);
int *fittedThreadNumber();

// Threads arguments
typedef struct
{
  int *individuals;
  int **matrix;
  double **freqMatrix;
} thread_freq_args;

void* calculateAlleleFrequencies_Threads( void *args);