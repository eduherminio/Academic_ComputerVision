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
#include <cmath>

using namespace cv;

int main(int argc, char* argv[])
{
  Mat Pic_original, Pic_original2;
  Mat Pic_black(480,640, CV_8UC3, Scalar(0,0,0));    // 480x640 black canvas
  std::string picName;

  if(init_pic(argc, argv, picName, Pic_original) < 0)    return EXIT_FAILURE;
  Pic_original2= Pic_original.clone();

  int threshold1=15, threshold2=200;

  std::unique_ptr<Rect> p_light(std::move(light_rectangle(Pic_original, threshold1)));
  std::unique_ptr<Rect> p_lighter(std::move(light_rectangle(Pic_original, threshold2)));

  rectangle(Pic_original, *p_light, Scalar(0,0,255));     // Draws red rectangle over the original photo
  rectangle(Pic_original, *p_lighter, Scalar(0,255,0));   // Draws green rectangle over the original photo
  rectangle(Pic_black, *p_light, Scalar(0,0,255));        // Draws red rectancle on a black canvas
  rectangle(Pic_black, *p_lighter, Scalar(0,255,0));      // Draws green rectancle on a black canvas

  std::cout << "Red rectangle area:" << p_light->area() << std::endl;
  std::cout << "Green rectangle area:" << p_lighter->area() << std::endl;

  show_pic(Pic_original, "Picture with drawings");
  show_pic(Pic_black, "Show only rectangles");


  Mat Pic_reduced_abs, Pic_reduced_coef;

  Size2i newSize(640, 480);
  double reduction_coef=0.5;

  resize(Pic_original, Pic_reduced_abs, newSize);
  resize(Pic_original, Pic_reduced_coef, Size(), reduction_coef, reduction_coef, CV_INTER_LINEAR);

  show_pic(Pic_reduced_abs, "Small");
  show_pic(Pic_reduced_coef, "Small - correctly reduced");

  waitKey(0);

  save_pic(Pic_original, "original");
  save_pic(Pic_reduced_coef, "coef_reduction");
  save_pic(Pic_reduced_abs, "abs_reduction");


  return EXIT_SUCCESS;
}
