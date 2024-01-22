//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

#include "DistanceFunctions.h"

//############################################# Genetics Functions #########################################
// Function to calculate allele frequencies
// input: individual data (genotype), number of markers
// output: allele frequencies of 3 alleles states (0, 1, 2)
void calculateAlleleFrequencies(int* individual, int numMarkers, double* frequencies) {
    // Initialize frequency counts to 0
    int count[3] = {0}; // 0, 1, 2 alleles
    size_t i;
    // Count occurrences of each allele
    for (i = 0; i < numMarkers; ++i) {
        count[individual[i]]++;
        // because you have 3 alleles (0, 1, 2) and you want to count the number of each allele
    }
    // Calculate frequencies
    for (i = 0; i < 3; ++i) {
        frequencies[i] = (double)count[i] / numMarkers;
    }
}

// // Function to calculate Euclidean distance between two individuals
// double euclideanDistance(double* alleleFrequenciesX, double* alleleFrequenciesY, int numMarkers) {
//     double distance = 0.0;
//     // print allele frequencies for those two individuals
//     for (int i = 0; i < numMarkers; ++i) {
//         double frequencyDifference = alleleFrequenciesX[i] - alleleFrequenciesY[i];
//         distance += frequencyDifference * frequencyDifference;
//     }
//     return sqrt(distance);
// }

// // double euclideanDistance(int* alleleFrequenciesX, int* alleleFrequenciesY, int numMarkers)
// void calculateMarkerFreqForMatrix(int matrix[][MARKERS], int numSamples, int numMarkers, double **markerFrequencies)
// {
//     // loop across samples
//     for (int i = 0; i < numSamples; ++i)
//     {
//         // calculate allele frequencies for the ith sample
//         calculateAlleleFrequencies(matrix[i], numMarkers, markerFrequencies[i]);
//     }
// }


// // Function to calculate distance matrix
// void calculateDistanceMatrix(double **markerFrequencies, int numSamples, int numMarkers, double **distanceMatrix, int completeMatrix)
// {
//     size_t i, j;
//     // loop across samples
//     for (i = 0; i < numSamples; ++i)
//     {
//         for (j = i + 1; j < numSamples; ++j)
//         {
            
//             // calculate Euclidean distance between the ith and jth samples
//             double distance = euclideanDistance(markerFrequencies[i], markerFrequencies[j], numMarkers);
//             // store the distance in the distance matrix
//             distanceMatrix[i][j] = distance;
//         }
//     }
//     // flip the distance matrix
//     if(!completeMatrix)
//     {
//         for (i = 0; i < numSamples; ++i)
//         {
//             for (j = 0; j < i; ++j)
//             {
//                 distanceMatrix[i][j] = distanceMatrix[j][i];
//             }
//         }
//     }
// }

int ** createRandomMatrix(int numSamples, int numMarkers)
{
    // create a random matrix
    int **matrix = (int **)malloc(numSamples * sizeof(int *));
    size_t i;
    for (i = 0; i < numSamples; ++i)
    {
        matrix[i] = (int *)malloc(sizeof(int) * numMarkers);
        memset(matrix[i], 0, sizeof(int) * numMarkers);
    }
    for (i = 0; i < numSamples; ++i)
    {
        for (size_t j = 0; j < numMarkers; ++j)
        {
            matrix[i][j] = rand() % 3;
        }
    }
    return matrix;
}


///////////////////////////////////////// print functions /////////////////////////////////////////

// Function to print allele frequencies for a matrix
void printMatrixDouble(double **matrix, int xL , int yL)
{
    for (int i = 0; i < xL; ++i)
    {
        for (int j = 0; j < yL; ++j)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printMatrixInt(int **matrix, int xL , int yL)
{
    for (int i = 0; i < xL; ++i)
    {
        for (int j = 0; j < yL; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


///////////////////////////////////////// read and write functions /////////////////////////////////////////
void readMatrixFromFile(char *filename , int **matrix)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // read matrix from file line by line with fscanf
    char c ;
    int sample = 0;
    int marker = 0;
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')
        {
            sample++;
            marker = 0;
            continue;
        }
        int value = c - '0';
        matrix[sample][marker] = value;
        marker++;
    }
    fclose(fp);
}

void writeMatrix2File(char *filename , int **matrix, int xL , int yL, char sep)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // write matrix to file line by line with fprintf
    size_t i, j;
    for ( i = 0; i < xL; i++)
    {
        for ( j = 0; j < yL; j++)
        {
            fprintf(fp, "%d", matrix[i][j]);
            if (j != yL - 1)
                fprintf(fp, "%c", sep);
        }
        if (i != xL - 1)
            fprintf(fp, "\n");
    }
    fclose(fp);
}

void writeMatrixDouble2File(char *filename , double **matrix, int xL , int yL, char sep)
{
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    // write matrix to file line by line with fprintf
    size_t i, j;
    for ( i = 0; i < xL; i++)
    {
        for ( j = 0; j < yL; j++)
        {
            fprintf(fp, "%f", matrix[i][j]);
            if (j != yL - 1)
                fprintf(fp, "%c", sep);
        }
        if (i != xL - 1)
            fprintf(fp, "\n");
    }
    fclose(fp);
}
// ///////////////////////////////////////// PTHREADS /////////////////////////////////////////


// int **RowsPerThreads(int max_threads, int ROWN)
// {   

//     // calculate the number of rows per thread
//     int threadShare = ROWN / max_threads;
//     // can we have a better thread share?
//     int leftRows = ROWN - threadShare * max_threads;
//     // if the leftrRows is less than 0, then the threadShare is too big
//     if (leftRows < 0)
//     {
//         threadShare--;
//         leftRows = ROWN - threadShare * max_threads;
//     }
    
//     printf("max_threads: %d\n", max_threads);
//     printf("ROWN: %d\n", ROWN);
//     printf("threadShare: %d\n", threadShare * max_threads);
//     printf("bestThreadShare: %d\n", threadShare);
//     printf("leftRows: %d\n", leftRows);

//     // create an array of rows for each thread
//     int **threadRows = (int **) malloc(sizeof(int *) * max_threads);
//     // for each thread
//     size_t i;
//     for (i = 0; i < max_threads; i++)
//     {
//         // create an array of rows
//         threadRows[i] = (int *) malloc(sizeof(int) * threadShare + 1); // +1 for the sentinel
//         // for each row
//         size_t j;
//         for (j = 0; j < threadShare; j++)
//         {
//             // add the row to the thread
//             threadRows[i][j] = i * threadShare + j;
//         }
//         // add a sentinel
//         threadRows[i][threadShare] = -1;
//     }
//     // add the left rows to the last thread
//     if (leftRows > 0)
//     {
//         // reallocate the last thread
//         int lastThreadNewSize = threadShare + leftRows + 1; // +1 for the sentinel
//         threadRows[max_threads - 1] = (int *) realloc(threadRows[max_threads - 1], sizeof(int) * lastThreadNewSize);
//         // add the left rows to the last thread
//         size_t j;
//         for (j = 0; j < leftRows; j++)
//         {
//             threadRows[max_threads - 1][j + threadShare] = max_threads * threadShare + j;
//         }
//         // add a sentinel
//         threadRows[max_threads - 1][lastThreadNewSize - 1] = -1;
//     }
//     return threadRows;
// }


int **RowsPerThreads(int max_threads, int ROWN)
{   
    // create an array of rows numbers
    int *rows = (int *) malloc(sizeof(int) * ROWN+1); // +1 for the sentinel
    // for each row
    size_t i;
    for (i = 0; i < ROWN; i++)
    {
        // add the row to the thread
        rows[i] = i;
    }
    // add a sentinel
    rows[ROWN] = -1;
    
    // distribute the rows to the threads
    int **threadRows = (int **) malloc(sizeof(int *) * max_threads);
    int threadShare = ROWN / max_threads + 10;
    // create an array of rows for each thread
    for (i = 0; i < max_threads; i++)
    {
        // create an array of rows
        threadRows[i] = (int *) malloc(sizeof(int) * threadShare);
    }
    // distribute the rows to the threads
    int thread = 0;
    int threadrow = 0;
    int row = 0;
    while(rows[0] != -1)
    {
        while (thread < max_threads && rows[0] != -1)
        {
            // printf("thread: %d, row: %d\n", thread, rows[0]);
            threadRows[thread][threadrow] = rows[0];
            threadRows[thread][threadrow+1] = -1;
            rows++;
            row++;
            thread++;
        }
        thread = 0;
        threadrow++;
    }
    return threadRows;
}


void printThreadsRows(int **rows_per_threads, int max_threads)
{
    size_t i;
    for (i = 0; i < max_threads; i++)
    {
        while (rows_per_threads[i][0] != -1)
        {
            printf("%d ", rows_per_threads[i][0]);
            rows_per_threads[i]++;
        }
        printf("\n");
    }
}

pthread_t *createThreads(int n)
{
    pthread_t *threads = (pthread_t *) malloc(sizeof(pthread_t) * n);
    return threads;
}

int *fittedThreadNumber()
{
    // ********* calculate the number of threads
    int max_threads = MAX_THREADS;
    // if the threads number is bigger than the rows number then use the rows number
    if(SAMPLES < max_threads)
    {
        max_threads = SAMPLES;
    }
    int *fitNumber = (int*)malloc(sizeof(int));
    *fitNumber = max_threads;
    return fitNumber;
}

/// Routines for threads
// Function to calculate allele frequencies
// input: individual data (genotype), number of markers
// output: allele frequencies of 3 alleles states (0, 1, 2)
// void* calculateAlleleFrequencies_Threads(void* args) {
void* calculateAlleleFrequencies_Threads(void *args) {
    // use the barier to wait for all threads to finish
    // int matrix[][MARKERS], int *targetRows, double **markerFrequencies
    // cast the arguments
    thread_freq_args *arguments = (thread_freq_args *) args;
    int* targetRows = arguments->individuals;
    int **matrix = arguments->matrix;
    double** markerFrequencies = arguments->freqMatrix;
    
    // print target rows
    while(targetRows[0] != -1)
    {
        // printf("%d ", targetRows[0]);
        // calculate allele frequencies for the ith sample
        calculateAlleleFrequencies(matrix[targetRows[0]], MARKERS, markerFrequencies[targetRows[0]]);
        targetRows++;
    }
    // printf("Thread finished\n");

}