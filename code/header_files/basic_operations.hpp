/*
 * Author:      Eduardo Cáceres de la Calle
 * Subject:     Visión Artificial
 * Degree:      Industrial Electronics and Automatic Control Engineering
 * University:  Universidad de Valladolid (UVa) - EII
 *
 * Code written in 2017, during my first contact with OpenCV.
 * Uploaded for educational purposes only.
 *
 */


#ifndef BASIC_OPERATIONS
#define BASIC_OPERATIONS

#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

#define CHL 100   // Char length

int init_pic(int argc, char* argv[], string &, Mat & mypic);
void print_info(const Mat & myPic, const string & picName);

#endif
