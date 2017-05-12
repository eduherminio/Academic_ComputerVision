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
#include "./header/cv_library.hpp"

using namespace cv;
using namespace cv_lib;

#define SAVE    true
#define NOTSAVE false

int main(int argc, char* argv[])
{
  Mat myPic, myPic_grey;
  std::string picName;

  if(init_pic(argc, argv, picName, myPic) < 0)    return EXIT_FAILURE;

  cvtColor(myPic, myPic, CV_BGR2GRAY);
  show_pic(myPic, "Originalpicture");

  int _threshold= 100;

  manual_binarize(myPic, _threshold, SAVE);


  Mat myPic_grey0, myPic_grey1, myPic_grey2, myPic_grey3, myPic_grey4;

  threshold(myPic, myPic_grey0, _threshold, 255,0);
  show_pic(myPic_grey0, "Type0");
  threshold(myPic, myPic_grey1, _threshold, 255,1);
  show_pic(myPic_grey1, "Type1");
  threshold(myPic, myPic_grey2, _threshold, 255,2);
  show_pic(myPic_grey2, "Type2");
  threshold(myPic, myPic_grey3, _threshold, 255,3);
  show_pic(myPic_grey3, "Type3");
  threshold(myPic, myPic_grey4, _threshold, 255,4);
  show_pic(myPic_grey4, "Type4");


  waitKey(0);
  return EXIT_SUCCESS;
}
