//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################
#include <stdio.h>
#include <math.h>

#define ROWS 6
#define COLS 3

// Function to calculate Euclidean distance between two samples
double euclideanDistance(double matrix[][COLS], int row1, int row2, int numMarkers) {
    double distance = 0.0;

    for (int i = 0; i < numMarkers; ++i) {
        double markerDifference = matrix[row1][i] - matrix[row2][i];
        distance += markerDifference * markerDifference;
    }

    return sqrt(distance);
}

int main() {
    // Number of markers
    int numMarkers = COLS;

    // Data matrix
    double dataMatrix[ROWS][COLS] = {
        {1.0, 0.0, 0.0},
        {0.5, 0.5, 0.0},
        {0.5, 0.0, 0.5},
        {0.0, 1.0, 0.0},
        {0.0, 0.5, 0.5},
        {0.0, 0.0, 1.0}
    };

    // Calculate Euclidean distance between samples
    int sample1 = 0;
    int sample2 = 3;
    double distance = euclideanDistance(dataMatrix, sample1, sample2, numMarkers);

    // calculate Euclidean distance for all pairs of samples
    for (int i = 0; i < ROWS; ++i) {
        for (int j = i + 1; j < ROWS; ++j) {
            double distance = euclideanDistance(dataMatrix, i, j, numMarkers);
            printf("%f\t", distance);
        }
        printf("\n");
    }
    return 0;
}
