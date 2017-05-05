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
  std::vector< std::vector<Point> > contours;
  int angle=      180;
  int brightness= 100;
  int contrast=   100;
  int thresh=     100;
};

void grey_pic(const Mat& Pic_original,          Mat& Pic_grey);
void grey_pic(const std::vector<Mat>& v_Pic,    std::vector<Mat>& v_Pic_grey);
void color_pic(const Mat& Pic_original,         Mat& Pic_color);
void color_pic(const std::vector<Mat>& v_Pic,   std::vector<Mat>& v_Pic_color);
void manual_binarize  (const Mat& myPic, const int threshold, const bool save);
void th_pic(const Mat& Pic_original, Mat& Pic_th, const int _th=125, const int type= CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
void th_pic(const std::vector<Mat>& v_Pic_original, std::vector<Mat>& v_Pic_th, const int _th=125, const int type= CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
void rescale_pic(const Mat& Pic_original, Mat& Pic_rescaled, const float coef);
void fix_size(const Mat& Pic_original, Mat& Pic_rescaled);
void fix_size(Mat& Pic);
void fix_size(std::vector<Mat>& Pic);
std::unique_ptr<Rect> light_rectangle (const Mat& myPic, const int threshold);
void light_rectangle  (const Mat& Pic_original, const int threshold, int& xleft, int& xright, int& yhigh, int& ylow);
void fill_no_rectangle(const Mat& Pic_original, Mat& Pic_clean, const Rect& _rectangle, const Scalar& color= BLACK);
void fill_no_rectangle(Mat& Pic, const Rect& _rectangle, const Scalar& color= BLACK);
void fill_no_rectangles(const Mat& Pic_original, Mat& Pic_clean, const std::vector<Rect>& v_rectangle, const Scalar& color= BLACK);
void fill_no_rectangles(Mat& Pic, const std::vector<Rect>& v_rectangle, const Scalar& color= BLACK);
void get_roi_from_boundingRect(const Mat& Pic, const std::vector<Rect>& v_bounding_rect, Rect& roi, int& lefter, int& righter, int& lower, int& higher);
void get_roi_from_boundingRect(const Mat& Pic, const std::vector<Rect>& v_bounding_rect, Rect& roi);
void set_Brightness_Contrast(const Mat& Pic_original, const int& brightness, const int& contrast, Mat& Pic_final);
void create_contours(const Mat& Pic_src, Mat& Pic_dst, std::vector<std::vector<Point>>& contours);
void create_contours(Mat& Pic, std::vector<std::vector<Point>>& contours);
int count_objects(const Mat& Pic, Mat& Pic_dst);
void morpho_pic(const Mat& src,                 Mat& dst,                 int iter, cv::MorphTypes type, Mat kernel=Mat::ones(3, 3, CV_32F),  Point anchor= Point(-1, -1));
void morpho_pic(const std::vector<Mat>& v_src,  std::vector<Mat>& v_dst,  int iter, cv::MorphTypes type, Mat kernel=Mat::ones(3, 3, CV_32F),  Point anchor= Point(-1, -1));
void morpho_pic(const Mat& src,                 Mat& dst,                 int iter, cv::MorphTypes type, Point anchor, Mat kernel=Mat::ones(3, 3, CV_32F));
void morpho_pic(const std::vector<Mat>& v_src,  std::vector<Mat>& v_dst,  int iter, cv::MorphTypes type, Point anchor, Mat kernel=Mat::ones(3, 3, CV_32F));

// Histograms
void create_histo     (const Mat& Pic, Mat& hist, Scalar color);
void create_histo     (const Mat& Pic, Mat& hist);
void create_histo     (const Mat& Pic, std::vector<Mat>& v_hist);
void create_histo     (const std::vector<Mat>& v_Pic, std::vector<Mat>& v_hist);
void draw_histo       (Mat& Pic_histo, const Mat& histo, const Scalar color);
void show_histo       (Mat& Pic_histo);

// Trackbars
void rotation_trackbar            (int, void* userdata);
void brightness_contrast_trackbar (int, void* userdata);
void thresh_trackbar              (int, void* userdata);

#endif // CV_LIBRARY
