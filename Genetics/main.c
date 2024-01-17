//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

// About calculating distance matrix for a set of individuals

#include "DistanceFunctions.h"
#define MARKERS 8
#define SAMPLES 10

// double euclideanDistance(int* alleleFrequenciesX, int* alleleFrequenciesY, int numMarkers)
void calculateMarkerFreqForMatrix(int matrix[][MARKERS], int numSamples, int numMarkers, double **markerFrequencies)
{
    // loop across samples
    for (int i = 0; i < numSamples; ++i)
    {
        // calculate allele frequencies for the ith sample
        calculateAlleleFrequencies(matrix[i], numMarkers, markerFrequencies[i]);
    }
}
// Function to print allele frequencies for a matrix
void printMarkerFreqForMatrix(double **markerFrequencies, int numSamples, int numMarkers)
{
    // loop across samples
    for (int i = 0; i < numSamples; ++i)
    {
        // print allele frequencies for the ith sample
        printf("Allele frequencies of the %dth individual: %f, %f, %f\n", i, markerFrequencies[i][0], markerFrequencies[i][1], markerFrequencies[i][2]);
    }
}
// Function to calculate distance matrix
void calculateDistanceMatrix(double **markerFrequencies, int numSamples, int numMarkers, double **distanceMatrix, int completeMatrix)
{
    size_t i, j;
    // loop across samples
    for (i = 0; i < numSamples; ++i)
    {
        for (j = i + 1; j < numSamples; ++j)
        {
            
            // calculate Euclidean distance between the ith and jth samples
            double distance = euclideanDistance(markerFrequencies[i], markerFrequencies[j], numMarkers);
            // store the distance in the distance matrix
            distanceMatrix[i][j] = distance;
        }
    }
    // flip the distance matrix
    if(!completeMatrix)
    {
        for (i = 0; i < numSamples; ++i)
        {
            for (j = 0; j < i; ++j)
            {
                distanceMatrix[i][j] = distanceMatrix[j][i];
            }
        }
    }
}

void createRandomMatrix(int matrix[][MARKERS], int numSamples, int numMarkers)
{
    for (int i = 0; i < numSamples; ++i)
    {
        for (int j = 0; j < numMarkers; ++j)
        {
            matrix[i][j] = rand() % 3;
        }
    }
}


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