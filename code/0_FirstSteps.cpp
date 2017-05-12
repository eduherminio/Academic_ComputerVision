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


#include "opencv2/opencv.hpp"
#include "./header/cv_basic_operations.hpp"

using namespace cv;
using namespace cv_lib;

int main(int argc, char* argv[])
{
  Mat myPic, myPic_grey;
  std::string picName;

  if(init_pic(argc, argv, picName, myPic) < 0)    return EXIT_FAILURE;

  print_info(myPic, picName);

  show_pic(myPic, "Original picture");
  cvtColor(myPic, myPic_grey, CV_BGR2GRAY);
  show_pic(myPic_grey, "Modified picture");

  imwrite( "greyParrots.jpg", myPic_grey );        //graba img de gris en disco

  waitKey(0);

  return EXIT_SUCCESS;
}
