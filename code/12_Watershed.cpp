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

int main( int argc, char* argv[])
{
  std::vector<Mat>          v_Pic_color, v_Pic_final;
  std::vector<std::string>  v_picName;

  if(init_pic(argc, argv, v_picName, v_Pic_color) < 0)    return EXIT_FAILURE;

  for(const auto& Pic : v_Pic_color)
  {
    Mat greyPic, binPic, contourPic;
    std::vector< std::vector<Point> > v_contours;

    show_pic(Pic, "Original");
    blur(Pic, Pic, Size(3,3) );
    grey_pic(Pic, greyPic);
    int _thr= 150;  // ignored
    threshold(greyPic, binPic, _thr, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);

    show_pic(binPic, "BN");

    create_contours(binPic, contourPic, v_contours);

    Mat Pic_roi= Pic.clone();

    if((Pic_roi.channels())!=3)
      cvtColor(Pic_roi, Pic_roi, COLOR_GRAY2RGB);     // Transform the B&W pic in RGB

    std::vector<Rect> v_bounding_rect;
    const int min_area= 100;
    const double coef_x= 0.5, coef_y=0.5;
    for(int j=0; j<v_contours.size(); ++j)
    {
      if(contourArea(v_contours[j], false) > min_area)
        drawContours(Pic_roi, v_contours, j , RED, 2);

      auto b_Rect= boundingRect(v_contours[j]);

      if(b_Rect.height > coef_y*min_area && b_Rect.width > coef_x*min_area)
      {
        v_bounding_rect.push_back(b_Rect);
        rectangle(Pic_roi, b_Rect, BLUE, 1);
      }
    }
    show_pic(Pic_roi, "contours");

    int lefter, righter, lower, higher;
    Rect roi;
    get_roi_from_boundingRect(Pic_roi, v_bounding_rect, roi, lefter, righter, lower, higher);
    show_pic(Pic_roi, "ROI");
    fill_no_rectangle(Pic_roi, roi, WHITE);
    rectangle(Pic_roi, roi, GREEN, 2);
    show_pic(Pic_roi, "ROI applied");

    waitKey(0);


    Mat src=Pic(roi).clone();
    src=Pic.clone();

    Mat dist;
    distanceTransform(binPic, dist, CV_DIST_L2, 3);   // Normalize the distance image for range = {0.0, 1.0} so we can visualize and threshold it

    normalize(dist, dist, 0, 1., NORM_MINMAX);        // Threshold to obtain the peaks. This will be the markers for the foreground objects
    show_pic(dist, "Distance Transform Image");

    threshold(dist, dist, .4, 1., CV_THRESH_BINARY);

    Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
    dilate(dist, dist, kernel1);                      // Dilate a bit the dist image
    show_pic(dist, "Peaks");

    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);                   // Create the CV_8U version of the distance image. It is needed for findContours()

    std::vector<std::vector<Point> > contours;
    findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);    // Find total markers

    Mat markers = Mat::zeros(dist.size(), CV_32SC1);  // Create the marker image for the watershed algorithm

    for (int i=0; i<contours.size(); ++i)             // Draw the foreground markers
        drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i)+1), -1);

    circle(markers, Point(5,5), 3, CV_RGB(255,255,255), -1);  // Draw the background marker
    show_pic(markers*10000, "Markers");

    watershed(src, markers);                                  // Perform the watershed algorithm
    Mat mark = Mat::zeros(markers.size(), CV_8UC1);
    markers.convertTo(mark, CV_8UC1);
    bitwise_not(mark, mark);
    show_pic(mark, "Markers_v2");

    std::vector<Vec3b> colors;    // Generate random colors
    for (size_t i = 0; i < contours.size(); i++)
    {
        int b = theRNG().uniform(0, 255);
        int g = theRNG().uniform(0, 255);
        int r = theRNG().uniform(0, 255);
        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    Mat dst = Mat::zeros(markers.size(), CV_8UC3);  // Create the result image

    for (int i=0; i< markers.rows; ++i)          // Fill labeled objects with random colors
    {
        for (int j=0; j <markers.cols; ++j)
        {
            int index = markers.at<int>(i,j);
            if (index > 0 && index <= static_cast<int> (contours.size()))
                dst.at<Vec3b>(i,j) = colors[index-1];
            else
                dst.at<Vec3b>(i,j) = Vec3b(0,0,0);
        }
    }

    show_pic(dst, "Final");
    v_Pic_final.push_back(dst);

    waitKey(0);
    destroyAllWindows();
  }

    waitKey(0);

    return EXIT_SUCCESS;
}
