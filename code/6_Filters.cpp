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
  std::vector<Mat>          v_Pic_grey;
  std::vector<Mat>          v_Pic_final;
  std::vector<std::string>  v_picName;

  // v_Pic_grey.resize(argc-1);
  v_Pic_final.resize(argc-1);
  Mat Pic_grey, Pic_dst;

  if(init_pic(argc, argv, v_picName, v_Pic) < 0)    return EXIT_FAILURE;


  for(int i=0; i<argc-1; ++i)  {
    // cvtColor(v_Pic[i], v_Pic_grey[i], CV_BGR2GRAY);
    std::string str(std::to_string(i+1));
    // show_pic(v_Pic_grey[i], "Original"+a);
    show_pic(v_Pic[i], "Original" + str);
  }

  float h= 25;
  float hColor= 11;
  int templateWindowSize= 7;
  int searchWindowSize= 21;

  for(int i=0; i<argc-1; ++i)  {
    fastNlMeansDenoisingColored(v_Pic[i], v_Pic_final[i], h, hColor, templateWindowSize, searchWindowSize);
        std::string a(std::to_string(i));
    show_pic(v_Pic_final[i], "Without "+a);
  }

  h=11;
  fastNlMeansDenoisingColored(v_Pic[argc-2], v_Pic_final[argc-2], h, hColor, templateWindowSize, searchWindowSize);
  show_pic(v_Pic_final[argc-2], "Without noise - h=11");

  waitKey(0);


  return EXIT_SUCCESS;
}
