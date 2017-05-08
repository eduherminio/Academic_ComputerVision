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
  std::vector<Mat>          v_Pic_color, v_Pic_grey, v_Pic_th, v_Pic_roi, v_Pic_final;
  std::vector<std::string>  v_picName;

  if(init_pic(argc, argv, v_picName, v_Pic_color) < 0)    return EXIT_FAILURE;
  fix_size(v_Pic_color);

  color_pic(v_Pic_color, v_Pic_color);
  grey_pic(v_Pic_color, v_Pic_grey);
  th_pic(v_Pic_grey, v_Pic_th);

  Mat aux= v_Pic_th[3].clone();
  // show_pic(v_Pic_th, "before");   // debug
  morpho_pic(v_Pic_th, v_Pic_th, 3, MORPH_CLOSE);
  morpho_pic(v_Pic_th, v_Pic_th, 1, MORPH_OPEN);
  // show_pic(v_Pic_th, "after");    // debug
  v_Pic_th[3]= aux.clone();       // In this case, no improvement exists

  waitKey(0);

  for(int num_pic=0; num_pic<v_Pic_th.size(); ++num_pic)
  {
    #define Pic_color v_Pic_color[num_pic]
    #define Pic_grey  v_Pic_grey[num_pic]
    #define Pic_th  v_Pic_th[num_pic]

    Mat Pic= Pic_color.clone();   // Color copy to show the user
    Mat Pic_WIP= Pic_th.clone();  // B&W copy to work
    Mat Pic_translated, Pic_rotated, Pic_roi;

    std::vector< std::vector<Point> > v_contours;
    create_contours(Pic_WIP, v_contours);

    std::vector<RotatedRect>  v_rotated_rect;
    std::vector<RotatedRect>  v_ellipse;
    v_rotated_rect.reserve(v_contours.size());
    v_ellipse.reserve(v_contours.size());
    v_Pic_roi.reserve(v_contours.size());

    int min_area= 100;
    const double coef_x= 0.3, coef_y=0.3;
    const double percentaje_true_contours= 0.65;
    const double min_circularity= 0.85;
    for(int j=0; j<v_contours.size(); ++j)
    {
      double area= contourArea(v_contours[j], false);
      double perimeter= arcLength(v_contours[j], true);

      auto rotated_rect= minAreaRect(v_contours[j]);
      if(area > min_area && rotated_rect.size.height > coef_y*min_area && rotated_rect.size.width > coef_x*min_area)
      {
        double circularity= 4*PI*area/(perimeter*perimeter);
        std::cout<<"Circularity: "  << circularity << std::endl;

        v_ellipse.push_back(fitEllipse(v_contours[j]));
        v_rotated_rect.push_back(rotated_rect);

        // drawContours(Pic, v_contours, j, RED, 1);                     // Debug
        // ellipse(Pic, v_ellipse.back(), YELLOW, 1);                    // Debug
        // Point2f rect_points[4]; rotated_rect.points(rect_points);     // Debug
        // draw_rectangle(Pic, rect_points, BLUE);                       // Debug


        // Translate it to the center, avoid any data loss in a future rotation

        Point2f pic_center(0.5*Pic.cols, 0.5*Pic.rows);
        float distance_to_center[2]= {pic_center.x - rotated_rect.center.x, pic_center.y-rotated_rect.center.y};
        float translation_matrix1 [2][3]={  1.0, 0.0 , distance_to_center[0],
                                            0.0, 1.0 , distance_to_center[1]   };

        Mat matTrasl(2, 3, CV_32FC1, translation_matrix1);
        warpAffine(Pic, Pic_translated, matTrasl, Pic.size());

        // show_pic(Pic_translated, "Pic_translated");                         // Debug

        // Rotate it

        if(circularity < min_circularity)
          rotate_pic(Pic_translated, Pic_rotated, pic_center, 90-abs(rotated_rect.angle));
        else
          Pic_rotated= Pic_translated.clone();

        cv::Rect roi(
          distance_to_center[0] + rotated_rect.center.x - (rotated_rect.size.height / 2),     // x
          distance_to_center[1] + rotated_rect.center.y - (rotated_rect.size.width / 2),      // y
          rotated_rect.size.height + 3,                                                       // width
          roi.height = rotated_rect.size.width + 3);                                          // height


        // rectangle(Pic_rotated, roi, GREEN, 1);                              // Debug
        // show_pic(Pic_rotated, "Pic_rotated");                               // Debug
        // Mat _rectangle_content;                                             // Debug
        // fill_no_rectangle(Pic_rotated, _rectangle_content, roi, WHITE);     // Debug
        // show_pic(_rectangle_content, "full");                               // Debug

        Pic_roi= Pic_rotated(roi).clone();
        if(num_pic!=3 && Pic_roi.rows > Pic_roi.cols) //
        {
          cv::transpose(Pic_roi, Pic_roi);      // source: http://stackoverflow.com/a/7825243/5459321
          cv::flip(Pic_roi, Pic_roi, 1);
        }
        else if(num_pic==3 && Pic_roi.rows < Pic_roi.cols && circularity < min_circularity)   // TO-DO: and no triangularity
        {
          cv::transpose(Pic_roi, Pic_roi);      // source: http://stackoverflow.com/a/7825243/5459321
          cv::flip(Pic_roi, Pic_roi, 1);
        }
        v_Pic_roi.push_back(Pic_roi);

        resize(Pic_roi, Pic_roi, Size(), 2, 2, CV_INTER_LANCZOS4);

        show_pic(Pic_roi, "Separated roi");
        show_pic(Pic, "Pic");

        waitKey(0);
      }

      if(j == v_contours.size()-1 && v_rotated_rect.size() < percentaje_true_contours*v_contours.size())
      {
        std::cout<<"number of objects: "<<v_rotated_rect.size()<<" < "<<percentaje_true_contours*v_contours.size()<<std::endl;

        min_area*=0.9;

        Pic= Pic_color.clone();
        v_rotated_rect.clear();
        v_ellipse.clear();
        j= -1;
      }
    }

    waitKey(0);
    destroyAllWindows();
  }

    waitKey(0);
    
    return EXIT_SUCCESS;
}
