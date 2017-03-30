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

static void brightness_contrast_trackbar(int initial, void* userdata);

struct UserData
{
  Mat Pic_src;
  Mat Pic_dst;
  Mat hist;
  int brightness= 100;
  int contrast=   100;
};

int main( int argc, char* argv[])
{
  std::vector<Mat>          v_Pic, v_Pic_grey;
  std::vector<std::string>  v_picName;
  Mat histo;

  if(init_pic(argc, argv, v_picName, v_Pic) < 0)    return EXIT_FAILURE;
  grey_pic(v_Pic, v_Pic_grey);
  show_pic(v_Pic_grey[0]);
  create_histo(v_Pic[0], histo, BLACK);

  namedWindow("Select brightness & contrast");
  UserData user_data;
  user_data.Pic_src= v_Pic_grey[0].clone();

  createTrackbar("Brightness","Select brightness & contrast", &user_data.brightness,  user_data.brightness*2, brightness_contrast_trackbar, (void*) (&user_data));
  createTrackbar("Contrast",  "Select brightness & contrast", &user_data.contrast,    user_data.contrast*2,   brightness_contrast_trackbar, (void*) (&user_data));

  brightness_contrast_trackbar(user_data.brightness, &user_data);

  waitKey(0);

  destroyWindow("Select brightness & contrast");


  waitKey(0);
  return EXIT_SUCCESS;
}

static void brightness_contrast_trackbar(int, void* userdata)   {
  UserData user_data= *((UserData*)userdata);   // cast + de-reference

  user_data.brightness-=100;    // [-100, +100]
  user_data.contrast-=100;      //  [-100, +100]

  set_Brightness_Contrast(user_data.Pic_src, user_data.brightness, user_data.contrast, user_data.Pic_dst);

  create_histo(user_data.Pic_dst, user_data.hist, PSEUDO_BLACK);  // BLACK would make it call to draw_histo & show_pic every time
  Mat Pic_histo( HISTO_HEIGHT, HISTO_WIDTH, CV_8UC3, WHITE );
  draw_histo(Pic_histo, user_data.hist, RED);

  show_pic(Pic_histo, "Histogram");
  show_pic(user_data.Pic_dst, "Pic");
}
