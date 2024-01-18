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
#define MARKERS 8
#define SAMPLES 10
double euclideanDistance(double* , double* , int );
void calculateAlleleFrequencies(int* , int , double*);
// double euclideanDistance(int* alleleFrequenciesX, int* alleleFrequenciesY, int numMarkers)
void calculateMarkerFreqForMatrix(int  [][MARKERS], int , int , double **);
// Function to print allele frequencies for a matrix
void printMarkerFreqForMatrix(double **, int , int );
// Function to calculate distance matrix
void calculateDistanceMatrix(double **, int, int , double **, int);
void createRandomMatrix(int [][MARKERS], int, int);