#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate Euclidean distance between two individuals
double euclideanDistance(int* alleleFrequenciesX, int* alleleFrequenciesY, int numMarkers) {
    double distance = 0.0;

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


int main() {
    // Number of markers
    int numMarkers = 10;

    // Alleles the xth and yth individuals
    int xthIndividual[] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    int ythIndividual[] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    // calculate frequencies
    double alleleFrequenciesX[3];
    double alleleFrequenciesY[3];
    calculateAlleleFrequencies(xthIndividual, numMarkers, alleleFrequenciesX);
    calculateAlleleFrequencies(ythIndividual, numMarkers, alleleFrequenciesY);
    printf("Allele frequencies of the xth individual: %f, %f, %f\n", alleleFrequenciesX[0], alleleFrequenciesX[1], alleleFrequenciesX[2]);
    printf("Allele frequencies of the yth individual: %f, %f, %f\n", alleleFrequenciesY[0], alleleFrequenciesY[1], alleleFrequenciesY[2]);
    // calculate Euclidean distance
    double distance = euclideanDistance(xthIndividual, ythIndividual, numMarkers);
    printf("Euclidean distance between the xth and yth individuals: %f\n", distance);

    
    
    return 0;
}
