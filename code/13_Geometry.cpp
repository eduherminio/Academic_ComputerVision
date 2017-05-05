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
#include <cassert>

using namespace cv;

int main( int argc, char* argv[])
{
  std::vector<Mat>          v_Pic_color, v_Pic_grey, v_Pic_th, v_Pic_final;
  std::vector<std::string>  v_picName;

  if(init_pic(argc, argv, v_picName, v_Pic_color) < 0)    return EXIT_FAILURE;
  fix_size(v_Pic_color);

  color_pic(v_Pic_color, v_Pic_color);
  grey_pic(v_Pic_color, v_Pic_grey);
  th_pic(v_Pic_grey, v_Pic_th);
    // show_pic(v_Pic_color[3], v_picName[3]+"color");
    // show_pic(v_Pic_th[3], v_picName[3] + " sin transformaciones morfológicas");
  morpho_pic(v_Pic_th, v_Pic_th, 3, MORPH_CLOSE);
  morpho_pic(v_Pic_th, v_Pic_th, 1, MORPH_OPEN);
    // show_pic(v_Pic_th[3], v_picName[3] + " closing + opening");

  waitKey(0);

  for(int i=0; i<v_Pic_th.size(); ++i)
  {
    #define Pic_color v_Pic_color[i]
    #define Pic_grey  v_Pic_grey[i]
    #define Pic_th  v_Pic_th[i]

    Mat Pic= Pic_color.clone();   // Color copy to show the user
    Mat Pic_WIP= Pic_th.clone();  // B&W copy to work

    std::vector< std::vector<Point> > v_contours;
    create_contours(Pic_WIP, v_contours);

    std::vector<Rect>         v_bounding_rect;
    std::vector<RotatedRect>  v_bounding_rotated_rect;
    std::vector<RotatedRect>  v_ellipse_rect;
    v_bounding_rect.reserve(v_contours.size());
    v_bounding_rotated_rect.reserve(v_contours.size());
    v_ellipse_rect.reserve(v_contours.size());

    int min_area= 100;
    const double coef_x= 0.5, coef_y=0.5;
    const double percentaje_true_contours= 0.80;
    for(int j=0; j<v_contours.size(); ++j)
    {
      std::vector< std::vector<Point> > v_contours_poly(v_contours.size());
      double perimeter= arcLength(v_contours[j], true); // true: closed perimeter
      double perimeter_2= perimeter*perimeter;
      double area= contourArea(v_contours[j], false);
      if(area > min_area)
      {
        drawContours(Pic, v_contours, j, RED, 2);

        v_ellipse_rect.push_back(fitEllipse(v_contours[j]));
        v_bounding_rotated_rect.push_back(minAreaRect(v_contours[j]));

        std::cout<<"Perimeter: "        << perimeter                    <<std::endl;
        std::cout<<"Area: "             << area                         <<std::endl;
        std::cout<<"Circularity: "      << 4*PI*area/perimeter_2        <<std::endl;
        std::cout<<"Angle: "            << v_ellipse_rect.back().angle  <<std::endl;
        std::cout<<std::endl;
        // Rectangularidad - TO-DO

        ellipse(Pic, v_ellipse_rect.back(), GREEN, 2);

        Point2f rect_points[4]; v_bounding_rotated_rect.back().points(rect_points);
        for(int k=0; k<4; ++k)
          line(Pic, rect_points[k], rect_points[(k+1)%4], PURPLE, 1);

        approxPolyDP(Mat(v_contours[j]), v_contours_poly[j], 3, true);
        // auto b_Rect_poly= v_contours_poly[j];
        drawContours(Pic, v_contours_poly, j, BLACK, 1);
      }

      auto b_Rect= boundingRect(v_contours[j]);
      if(b_Rect.height > coef_y*min_area && b_Rect.width > coef_x*min_area)
      {
        v_bounding_rect.push_back(b_Rect);
        rectangle(Pic, b_Rect, BLUE, 1);
      }
      else if(v_bounding_rotated_rect.size())
      {
        v_bounding_rotated_rect.pop_back();
        v_ellipse_rect.pop_back();
      }

      show_pic(Pic, "contours");
      show_pic(Pic_WIP, "WIP");

      if(j == v_contours.size()-1 && v_bounding_rect.size() < percentaje_true_contours*v_contours.size())
      {
        min_area*=0.9;

        Pic= Pic_color.clone();
        v_bounding_rect.clear();
        v_bounding_rotated_rect.clear();
        v_ellipse_rect.clear();
        j= -1;
      }
      waitKey(0);
    }

    // assert(v_bounding_rect.size() == v_bounding_rotated_rect.size());  // TO-CHECK
    // assert(v_ellipse_rect.size()  == v_bounding_rotated_rect.size());

    Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
    Point anchor1 = Point(-1,-1);
    Mat Pic2;
    dilate(Pic_WIP, Pic2, kernel1, anchor1, 4);
    erode(Pic2, Pic2, kernel1, anchor1, 5);

    show_pic(Pic2, "WIP2");
      // bitwise_not ( Pic2, Pic2 );

    fill_no_rectangles(Pic, v_bounding_rect, WHITE);

    Rect roi;
    get_roi_from_boundingRect(Pic, v_bounding_rect, roi);
    rectangle(Pic, roi, ORANGE, 1);

    show_pic(Pic, "ROI");

    waitKey(0);


    destroyAllWindows();
  }

    waitKey(0);
    return 0;
}
