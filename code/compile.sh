#!/bin/bash
clear
set -e
n_cores=`cat /proc/cpuinfo | grep processor | wc -l`
let "n_cores++"
source filedata.txt
export env_filename=$filename
mkdir -p build && cd build
cmake ..  &> /dev/null 
make -j$n_cores -b
./$filename $imagename1 $imagename2 $imagename3 $imagename4 $imagename5



# set -e
#   Any subsequent(*) commands failing makes the shell script to exit.

# source filedata.txt
#   Reads variables from filedata.txt

# mkdir -p
#   creates a folder only if it doesn't exist

# &> /dev/null
#   Suppreses output

# make -j N
#   For minimum build times, you want to use a value of N that is one more than the number of cores on the machine


#
# Author:      Eduardo Cáceres de la Calle
# Subject:     Visión Artificial
# Degree:      Industrial Electronics and Automatic Control Engineering
# University:  Universidad de Valladolid (UVa) - EII
#
# Code written in 2017, during my first contact with OpenCV.
# Uploaded for educational purposes only.
#
#
