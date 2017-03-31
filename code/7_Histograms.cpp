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
#include <vector>
#include <string>

using namespace cv;

int main( int argc, char* argv[])
{
  std::vector<Mat>          v_Pic;
  std::vector<std::string>  v_picName;
  std::vector<Mat>          v_histo;

  if(init_pic(argc, argv, v_picName, v_Pic) < 0)    return EXIT_FAILURE;
  show_pic(v_Pic, v_picName);
  v_histo.resize(v_Pic.size());

  create_histo(v_Pic[0], v_histo[0]); // B&W histo (internal RGB -> B&W conversion, if needed)
  create_histo(v_Pic[0], v_histo);    // RGB histo (internal B&W -> RGB conversion, if needed)
  create_histo(v_Pic, v_histo);       // B&W histo if ALL of them are B&W, otherwise RGB histo


  waitKey(0);

  return EXIT_SUCCESS;
}
