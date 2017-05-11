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
#include "./header/basic_operations.hpp"
#include "./header/cv_library.hpp"

using namespace cv;
using namespace cv_lib;

#define SAVE    true
#define NOTSAVE false

int main(int argc, char* argv[])
{
  Mat Pic_original, BGR[3];         // Beware the order
  std::string picName;

  if(init_pic(argc, argv, picName, Pic_original) < 0)    return EXIT_FAILURE;

  resize(Pic_original, Pic_original, Size(), 0.5, 0.5);
  split(Pic_original, BGR);

  show_pic(Pic_original, "Original");
  show_pic(BGR[0], "Blue", SAVE);
  show_pic(BGR[1], "Green", SAVE);
  show_pic(BGR[2], "Red", SAVE);

  waitKey(0);

  return EXIT_SUCCESS;
}
