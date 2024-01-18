//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

// About calculating distance matrix for a set of individuals

#include "DistanceFunctions.h"

int main()
{
    srand(time(NULL));
    int matrix[SAMPLES][MARKERS];
    createRandomMatrix(matrix, SAMPLES, MARKERS);
    // create a pointer to the matrix of allele frequencies
    double **markerFrequencies = (double **)malloc(SAMPLES * sizeof(double *));
    for (int i = 0; i < SAMPLES; ++i)
    {
        markerFrequencies[i] = (double *)malloc(sizeof(double) * 3);
        memset(markerFrequencies[i], 0, sizeof(double) * 3);
    }
    // calculate allele frequencies for the matrix
    calculateMarkerFreqForMatrix(matrix, SAMPLES, MARKERS, markerFrequencies);
    // printMarkerFreqForMatrix(markerFrequencies, SAMPLES, MARKERS);
    // create a pointer to the distance matrix
    double **distanceMatrix = (double **)malloc(SAMPLES * sizeof(double *));
    for (int i = 0; i < SAMPLES; ++i)
    {
        distanceMatrix[i] = (double *)malloc(sizeof(double) * SAMPLES);
        memset(distanceMatrix[i], 0, sizeof(double) * SAMPLES);
    }
    // calculate distance matrix
    calculateDistanceMatrix(markerFrequencies, SAMPLES, MARKERS, distanceMatrix, 0);

    // print distance matrix
    for (int i = 0; i < SAMPLES; ++i)
    {
        for (int j = 0; j < SAMPLES; ++j)
        {
            printf("%f ", distanceMatrix[i][j]);
        }
        printf("\n");
    }
    
    // free memory
    for (int i = 0; i < SAMPLES; ++i)
    {
        free(markerFrequencies[i]);
        free(distanceMatrix[i]);
    }
    free(markerFrequencies);
    free(distanceMatrix);
    return 0;
}