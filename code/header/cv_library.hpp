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


#ifndef CV_LIBRARY
#define CV_LIBRARY

#include "opencv2/opencv.hpp"
#include "basic_operations.hpp"
#include <iostream>
#include <string>
#include <utility>
using namespace cv;

#define stringify( name ) # name  // returns a string with the name of the variable

void manual_binarize(const Mat & myPic, const int threshold, const bool save);
std::unique_ptr<Rect> light_rectangle(const Mat & myPic, const int threshold);
void light_rectangle(const Mat & Pic_original, const int threshold, int & xleft, int &xright, int &yhigh, int & ylow);

#endif // CV_LIBRARY
