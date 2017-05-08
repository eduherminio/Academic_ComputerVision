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

  morpho_pic(v_Pic_th, v_Pic_th, 3, MORPH_CLOSE);
  morpho_pic(v_Pic_th, v_Pic_th, 1, MORPH_OPEN);

  waitKey(0);

  for(int num_pic=0; num_pic<v_Pic_th.size(); ++num_pic)
  {
    #define Pic_color v_Pic_color[num_pic]
    #define Pic_grey  v_Pic_grey[num_pic]
    #define Pic_th  v_Pic_th[num_pic]

    Mat Pic= Pic_color.clone();   // Color copy to show the user
    Mat Pic_WIP= Pic_th.clone();  // B&W copy to work

    std::vector< std::vector<Point> > v_contours;
    create_contours(Pic_WIP, v_contours);

    std::vector<RotatedRect>  v_rotated_rect;
    std::vector<RotatedRect>  v_ellipse;
    v_rotated_rect.reserve(v_contours.size());
    v_ellipse.reserve(v_contours.size());

    int min_area= 100;
    const double coef_x= 0.5, coef_y=0.5;
    const double percentaje_true_contours= 0.80;
    for(int j=0; j<v_contours.size(); ++j)
    {
      double area= contourArea(v_contours[j], false);
      double perimeter= arcLength(v_contours[j], true);

      auto rotated_rect= minAreaRect(v_contours[j]);
      if(area > min_area && rotated_rect.size.height > coef_y*min_area && rotated_rect.size.width > coef_x*min_area)
      {
        v_ellipse.push_back(fitEllipse(v_contours[j]));
        v_rotated_rect.push_back(rotated_rect);

        // drawContours(Pic, v_contours, j, RED, 1);                    // Debug
        // ellipse(Pic, v_ellipse.bacdk(), RED, 1);                     // Debug
        // Point2f rect_points[4]; rotated_rect.points(rect_points);    // Debug
        // draw_rectangle(Pic, rect_points, BLUE);                      // Debug

        // Rotate the picture so
        Mat rotatedPic;
        rotate_pic(Pic, rotatedPic, rotated_rect.center, 90-abs(rotated_rect.angle));     // TO-CHECK:
        // It's safer to rotate it around the center of the picture, but rotated_rect can't be rotated that easily
        // We would need to be able to locate rotated_rect.center after rotating the whole pic

// Trial:
        // std::vector<cv::Point2f> center {rotated_rect.center};
        // Mat mat_center(center);
        // std::cout<<mat_center.at<Point2f>(0,0).x<<" "<<mat_center.at<Point2f>(0,0).x<<std::endl;
        //
        // rotate_pic(mat_center, mat_center, rotated_rect.center, 90-abs(rotated_rect.angle));
        // std::cout<<mat_center.at<Point2f>(0,0).x<<" "<<mat_center.at<Point2f>(0,0).x<<std::endl;

// Idea:
        // rotate_pic(Pic, rotatedPic, cv::Point2f(0.5*Pic.rows, 0.5*Pic.cols), 90-abs(rotated_rect.angle));
        // Point2f center= rotated_rect.center;
        // <rotate point>
        // add to x: point_rotated.x - point.x
        // add to y: point_rotated.x - point.x

        cv::Rect roi;
        roi.x = rotated_rect.center.x - (rotated_rect.size.height / 2);   // TO-CHECK: why exchange width and height?
        roi.y = rotated_rect.center.y - (rotated_rect.size.width / 2);
        roi.width = rotated_rect.size.height + 3;
        roi.height = rotated_rect.size.width + 3;

        // rectangle(rotatedPic, roi, GREEN, 1);                              // Debug
        // show_pic(rotatedPic, "Rotated_pic");                               // Debug
        // Mat _rectangle_content;   // Debug
        // fill_no_rectangle(rotatedPic, _rectangle_content, roi, WHITE);     // Debug
        // show_pic(_rectangle_content, "full");                              // Debug

        Mat m_rectangle= rotatedPic(roi).clone();

        if(m_rectangle.rows > m_rectangle.cols) //
        {
          cv::transpose(m_rectangle, m_rectangle);      // source: http://stackoverflow.com/a/7825243/5459321
          cv::flip(m_rectangle, m_rectangle, 1);
        }

        resize(m_rectangle, m_rectangle, Size(), 2, 2, CV_INTER_LANCZOS4);

        show_pic(m_rectangle, "single");
        show_pic(Pic, "Pic");

        waitKey(0);
      }

      if(j == v_contours.size()-1 && v_rotated_rect.size() < percentaje_true_contours*v_contours.size())
      {
        min_area*=0.9;

        Pic= Pic_color.clone();
        v_rotated_rect.clear();
        v_ellipse.clear();
        j= -1;
        std::cout<<"min_area "<<v_rotated_rect.size()<<" < "<<v_contours.size();
      }
    }

    waitKey(0);


    destroyAllWindows();
  }

    waitKey(0);
    return 0;
}
