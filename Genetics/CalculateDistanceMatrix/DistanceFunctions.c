//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

#include "DistanceFunctions.h"

// Function to calculate Euclidean distance between two individuals
double euclideanDistance(double* alleleFrequenciesX, double* alleleFrequenciesY, int numMarkers) {
    double distance = 0.0;
    // print allele frequencies for those two individuals
    for (int i = 0; i < numMarkers; ++i) {
        double frequencyDifference = alleleFrequenciesX[i] - alleleFrequenciesY[i];
        distance += frequencyDifference * frequencyDifference;
    }
    return sqrt(distance);
}
// Function to calculate allele frequencies
void calculateAlleleFrequencies(int* individual, int numMarkers, double* frequencies) {
    // Initialize frequency counts
    int count[3] = {0}; // 0, 1, 2 alleles

    // Count occurrences of each allele
    for (int i = 0; i < numMarkers; ++i) {
        count[individual[i]]++;
    }

    // Calculate frequencies
    for (int i = 0; i < 3; ++i) {
        frequencies[i] = (double)count[i] / numMarkers;
    }
}


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