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
#include "./header_files/basic_operations.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
  Mat myPic, myPic_grey;
  string picName;

  if(init_pic(argc, argv, picName, myPic) < 0)
    return EXIT_FAILURE;

  cout << "OpenCV version: " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << endl;
  // cout << "OpenCV: " << getBuildInformation();

  print_info(myPic, picName);

  namedWindow("Example picture", WINDOW_AUTOSIZE);
  imshow("Example picture", myPic);

  cvtColor(myPic, myPic_grey, CV_BGR2GRAY);

  namedWindow("Modified picture", WINDOW_AUTOSIZE);
  imshow("Modified picture", myPic_grey);

  waitKey(0);

  return EXIT_SUCCESS;
}
