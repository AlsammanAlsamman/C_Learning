#!/bin/bash

############################################## About Author #########################################
# Created by: Alsamman M. Alsamman                                                                  #
# Emails: smahmoud [at] ageri.sci.eg or A.Alsamman [at] cgiar.org or SammanMohammed [at] gmail.com  #
# License: MIT License - https://opensource.org/licenses/MIT                                        #
# Disclaimer: The script comes with no warranty, use at your own risk                               #
# This script is not intended for commercial use                                                    #
#####################################################################################################



# check time taking to run the script

# start time
start=$(date +%s.%N)
./main
# end time
end=$(date +%s.%N)
# time difference
dt=$(echo "$end - $start" | bc)
echo "Time taken to run the script: $dt seconds"./