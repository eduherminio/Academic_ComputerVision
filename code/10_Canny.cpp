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
using namespace cv_lib;

int main( int argc, char** argv )
{
  std::vector<Mat>          v_Pic_color, v_Pic;
  std::vector<std::string>  v_picName;

  if(init_pic(argc, argv, v_picName, v_Pic_color) < 0)    return EXIT_FAILURE;
  grey_pic(v_Pic_color, v_Pic);

  for(const auto& Pic:v_Pic)
  {
    UserData instance;
    instance.Pic_src= Pic.clone();

    resize(instance.Pic_src, instance.Pic_src, Size(),0.5, 0.5, CV_INTER_LINEAR);

    blur(instance.Pic_src, instance.Pic_src, Size(3,3) );
    show_pic(instance.Pic_src, "Gray blurred");

    namedWindow("Colored contours",CV_WINDOW_AUTOSIZE);
    createTrackbar("Canny thresh:", "Colored contours", &instance.thresh, 255, thresh_trackbar, (void*) (&instance));
    thresh_trackbar(0, &instance);

    waitKey(0);

    destroyAllWindows();
}

  return EXIT_SUCCESS;;
}
