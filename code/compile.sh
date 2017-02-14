#!/bin/bash
set -e
source filedata.txt
export env_filename=$filename
cd .. && mkdir -p build && cd build
cmake ../code  &> /dev/null
make -B
./$filename $imagename $imagename2 $imagename3



# set -e
#   Any subsequent(*) commands failing makes the shell script to exit.

# source filedata.txt
#   Reads variables from filedata.txt

# &> /dev/null
#   Suppreses output

# echo $filename > filename.txt
#   aux. file to be read by CMakeList.txt

# rm filename.txt
#   deletion of aux. file

# BASEDIR=$(dirname "$0")
#   creates BASEDIR variable to host script directory

# mkdir -p
#   creates a folder only if it doesn't exist


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