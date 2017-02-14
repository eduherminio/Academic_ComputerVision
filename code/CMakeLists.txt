file(GLOB_RECURSE SOURCES
	header_files/*.h
	src/*.cpp
)

set(filename $ENV{env_filename})

cmake_minimum_required(VERSION 2.8)
project( filename )
find_package( OpenCV REQUIRED )
add_executable( ${filename} ${filename}.cpp ${SOURCES})
target_link_libraries( ${filename} ${OpenCV_LIBS} )


# set(namefile "0_Intro")
#   creates a variable named namefile

# set(filename $ENV{namefile})
#   accesses an environment variable
#file(STRINGS "filename.txt" filename)
#   creates a variable named filename from the content of filename.txt
#   filename.txt should only have the content of the variable inside
#   (not variable="content")


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
