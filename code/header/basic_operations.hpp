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

using namespace cv;

#define stringify( name ) # name  // returns a string with the name of the variable
#define CHL 100   // Char length

int init_pic(int argc, char* argv[], std::string & strpicName, Mat & myPic);
int init_pic(int argc, char* argv[], std::vector<std::string> & strpicName, std::vector<Mat> & myPic);
void print_info(const Mat & myPic, const std::string & picName);


void show_pic(const Mat & myPic);
// void show_pic(const Mat & myPic, bool save);

void show_pic(const Mat & myPic, std::string name);
void show_pic(const Mat & myPic, std::string name, bool save);


void save_pic(const Mat& Pic);
void save_pic(const Mat& Pic, std::string str);

#endif  // BASIC_OPERATIONS
