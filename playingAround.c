//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initMatrix(int **matrix, int rown, int coln)
{
    size_t i ;
    size_t j;
    for (i = 0; i < rown; i++)
    {
        for ( j = 0; j < coln; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

void printmatrix(int **matrix, int rown, int coln)
{
    size_t i ;
    size_t j;
    for (i = 0; i < rown; i++)
    {
        for ( j = 0; j < coln; j++)
        {
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }
}

int main (int argc, char **argv)
{
    srand(time(NULL));
    // create a matrix
    int rown = 10;
    int coln = 10;
    int **matrix = (int**) malloc(sizeof(int*) * rown);
    size_t i ;
    for (i = 0; i < rown; i++)
    {
        matrix[i] = (int *) malloc(sizeof(int) *coln);
    }
    initMatrix(matrix, rown,coln);
    printmatrix(matrix,rown,coln);  
    return 0;
}