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


#ifndef BASIC_OPERATIONS_HPP_INCLUDED
#define BASIC_OPERATIONS_HPP_INCLUDED


#include "headers.hpp"

using namespace cv;

namespace cv_lib
{
  #define stringify(name) # name  // returns a string with the name of the variable
  const int CHL= 100;   // Char length

  bool double_equals(double a, double b, double epsilon = 0.001);

  int init_pic(const int& argc, char* argv[], std::string& strpicName,              Mat& myPic);
  int init_pic(const int& argc, char* argv[], std::vector<std::string>& strpicName, std::vector<Mat>& myPic);

  void print_info(const Mat& myPic);
  void print_info(const std::vector<Mat>& v_Pic);
  void print_info(const Mat& myPic,               const std::string& picName);
  void print_info(const std::vector<Mat>& v_Pic,  const std::vector<std::string>& v_picName );


  void show_pic(const Mat& myPic);
  void show_pic(const std::vector<Mat>& v_Pic);
  void show_pic(const std::vector<Mat>& v_Pic, std::string name);
  // void show_pic(const Mat& myPic, bool save);

  void show_pic(const Mat& myPic,               const std::string name);
  void show_pic(const std::vector<Mat>& v_Pic,  const std::vector<std::string>& name);

  void show_pic(const Mat& myPic,               const std::string name, const bool save);


  void save_pic(const Mat& Pic);
  void save_pic(const Mat& Pic, const std::string str);
}

#endif  // BASIC_OPERATIONS_HPP_INCLUDED
