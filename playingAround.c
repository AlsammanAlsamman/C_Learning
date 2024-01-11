//############################################# About Author #########################################
// Created by: Alsamman M. Alsamman                                                                  #
// Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
// License: MIT License - https://opensource.org/licenses/MIT                                        #
// Disclaimer: The script comes with no warranty, use at your own risk                               #
// This script is not intended for commercial use                                                    #
//####################################################################################################
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
void *routine(int *x)
{
    *x = *x +1;
}
int main(int argc, char **argv)
{
    int x = 10;
    routine(&x);
    printf("%d",x);
    return 0;
}