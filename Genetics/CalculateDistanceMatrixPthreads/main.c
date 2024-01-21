//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

#include "DistanceFunctions.h"

int main()
{   
    // pthread_barrier_init(&barrier, NULL, MAX_THREADS);
    // initialize random seed
    srand(time(NULL));
    // create random matrix
    int **matrix = createRandomMatrix(SAMPLES, MARKERS);
    // write matrix to file geno.txt
    writeMatrix2File("geno.txt", matrix, SAMPLES, MARKERS, ' ');
    // // create matrix
    // int **matrix = (int **)malloc(SAMPLES * sizeof(int *));
    // for (int i = 0; i < SAMPLES; ++i)
    // {
    //     matrix[i] = (int *)malloc(sizeof(int) * MARKERS);
    //     memset(matrix[i], 0, sizeof(int) * MARKERS);
    // }
    
    // // read matrix from file geno.txt
    // readMatrixFromFile("geno.txt", matrix);
    // // // print matrix    
    // printMatrixInt(matrix, SAMPLES, MARKERS);
    
    // divide matrix into threads
    int *fitNumber = fittedThreadNumber();
    int **rows_per_threads = RowsPerThreads(*fitNumber, SAMPLES);
    // printThreadsRows(rows_per_threads, *fitNumber);

    // create matrix for frequencies
    double **markerFrequencies = (double **)malloc(SAMPLES * sizeof(double *));
    for (int i = 0; i < SAMPLES; ++i)
    {
        markerFrequencies[i] = (double *)malloc(sizeof(double) * 3);
        memset(markerFrequencies[i], 0, sizeof(double) * 3);
    }
    // printMatrixDouble(markerFrequencies, SAMPLES, 3);
    // create threads
    pthread_t *threads = createThreads(*fitNumber);
    // create arguments for threads
    thread_freq_args *args = (thread_freq_args *)malloc(sizeof(thread_freq_args) * *fitNumber);
    for (int i = 0; i < *fitNumber; ++i)
    {
        args[i].individuals =  rows_per_threads[i];
        args[i].matrix = matrix;
        args[i].freqMatrix = markerFrequencies;
    }
    size_t i;
    for (i = 0; i < *fitNumber; ++i)
    {
     int *i_ptr = (int *)malloc(sizeof(int));
         *i_ptr = i;
    pthread_create(&threads[i], NULL, calculateAlleleFrequencies_Threads, &args[*i_ptr]);
    }
    // wait for threads to finish
    for (i = 0; i < *fitNumber; ++i)
    {
        pthread_join(threads[i], NULL);
    }   
    // write matrix to file freq.txt
    // writeMatrix2File("freq.txt", markerFrequencies, SAMPLES, 3, '\t');
    printMatrixDouble(markerFrequencies, SAMPLES, 3);
    return 0;
}