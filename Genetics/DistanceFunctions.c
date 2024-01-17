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