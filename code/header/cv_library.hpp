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


#ifndef CV_LIBRARY
#define CV_LIBRARY

#include "headers.hpp"
#include "basic_operations.hpp"

using namespace cv;

struct UserData   {  // Used in trackbars
  Mat Pic_src;
  Mat Pic_dst;
  Point2i pt;
  Mat hist;
  int angle=      180;
  int brightness= 100;
  int contrast=   100;
};

void grey_pic(const Mat& Pic_original,          Mat& Pic_grey);
void grey_pic(const std::vector<Mat>& v_Pic,    std::vector<Mat>& v_Pic_grey);
void manual_binarize  (const Mat& myPic, const int threshold, const bool save);
std::unique_ptr<Rect> light_rectangle (const Mat& myPic, const int threshold);
void set_Brightness_Contrast(const Mat& Pic_original, const int& brightness, const int& contrast, Mat& Pic_final);
void light_rectangle  (const Mat& Pic_original, const int threshold, int& xleft, int& xright, int& yhigh, int& ylow);
void fill_no_rectangle(const Mat& Pic_original, Mat& Pic_clean, Rect rectangulo);
void create_histo     (const Mat& Pic, Mat& hist, Scalar color);
void create_histo     (const Mat& Pic, Mat& hist);
void create_histo     (const Mat& Pic, std::vector<Mat>& v_hist);
void create_histo     (const std::vector<Mat>& v_Pic, std::vector<Mat>& v_hist);
void draw_histo       (Mat& Pic_histo, const Mat& histo, const Scalar color);
void show_histo       (Mat& Pic_histo);

void rotation_trackbar(int, void*);
void brightness_contrast_trackbar(int, void* userdata);

#endif // CV_LIBRARY
