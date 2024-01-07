//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################
#include <stdio.h>
#include <math.h>

// Function to calculate Euclidean distance between two samples
double euclideanDistance(int* sample1, int* sample2, int numMarkers) {
    double distance = 0.0;

    for (int i = 0; i < numMarkers; ++i) {
        double markerDifference = sample1[i] - sample2[i];
        distance += markerDifference * markerDifference;
    }

    return sqrt(distance);
}

int main() {
    // Number of markers
    int numMarkers = 10;

    // Sample data (genotypes for each marker)
    int sample1[] = {1, 0, 2, 1, 0, 2, 0, 1, 1, 2};
    int sample2[] = {0, 1, 2, 0, 1, 1, 2, 0, 2, 1};

    // Calculate Euclidean distance
    double distance = euclideanDistance(sample1, sample2, numMarkers);

    // Print the result
    printf("Euclidean distance between the two samples: %f\n", distance);

    return 0;
}
