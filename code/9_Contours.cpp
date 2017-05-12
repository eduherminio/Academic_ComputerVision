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


#include <opencv2/opencv.hpp>
#include "./header/basic_operations.hpp"
#include "./header/cv_library.hpp"

using namespace cv;
using namespace cv_lib;

int main( int argc, char* argv[])
{
  std::vector<Mat>          v_Pic_color, v_Pic, v_Pic_bin, v_Pic_contour;
  std::vector <std::vector<std::vector<Point> > > v_contours;
  std::vector<std::string>  v_picName;

  if(init_pic(argc, argv, v_picName, v_Pic_color) < 0)    return EXIT_FAILURE;
  grey_pic(v_Pic_color, v_Pic);
  v_Pic_contour.resize(v_Pic.size());
  v_Pic_bin.resize(v_Pic.size());
  v_contours.resize(v_Pic.size());

  resize(v_Pic[2], v_Pic[2], Size(), 0.5, 0.5, CV_INTER_LINEAR);

  // show_pic(v_Pic);
  int _threshold= 200;

  for(int i=0; i<v_Pic.size(); ++i)
  {
    threshold(v_Pic[i], v_Pic_bin[i], _threshold, 255, CV_THRESH_BINARY_INV);
    create_contours(v_Pic_bin[i], v_Pic_contour[i], v_contours[i]);
  }

  show_pic(v_Pic_bin);
  waitKey(0);
  show_pic(v_Pic_contour);

  _threshold=150;
  threshold(v_Pic[0], v_Pic_bin[0], _threshold, 255, CV_THRESH_BINARY);               // Note: not inverted
  create_contours(v_Pic_bin[0], v_Pic_contour[0], v_contours[0]);
  show_pic(v_Pic_bin[0], "bin");
  show_pic(v_Pic_contour[0], "1_v2");

  waitKey(0);

  return EXIT_SUCCESS;
}
