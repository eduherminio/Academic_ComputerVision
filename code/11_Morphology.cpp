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
  std::vector<Mat>          v_Pic_color, v_Pic_grey, v_Pic_BW, v_Pic_dst;
  std::vector<std::string>  v_picName;

  if(init_pic(argc, argv, v_picName, v_Pic_color) < 0)    return EXIT_FAILURE;
  grey_pic  (v_Pic_color, v_Pic_grey);
  color_pic (v_Pic_color, v_Pic_dst); // To show results
  v_Pic_dst.resize(v_Pic_color.size());
  v_Pic_BW.resize(v_Pic_color.size());

  std::cout<<"1: Morphology general example"<<std::endl<<"2: Object counting"<<std::endl;
  int selection;
  do
  {
    std::cin>> selection;
  } while(selection!=1 && selection!=2);

  if        (selection==1)      {
    // Params to pass (same as default ones defined in morpho_pic, so used only as an example)
    Mat kernel= Mat::ones(3, 3, CV_32F);
    Point anchor= Point(-1, -1);
    int iter=5;

    Mat Pic_BW;
    Mat Pic_dst= v_Pic_color.back().clone();
    show_pic(Pic_dst, "Original");
    threshold(v_Pic_grey.back(), Pic_BW, 100, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);  // OTSU
    show_pic(Pic_BW, "Binarized");
    // morphologyEx(Pic_BW, Pic_dst, MORPH_XXXX, kernel, anchor, iter);   // Instead of calling this function directly

    // Opening: Removing small bright regions
    morpho_pic(Pic_BW, Pic_dst, iter, MORPH_OPEN, kernel);          // default kernel & anchor
      show_pic(Pic_dst, "MORPH_OPEN");
      show_pic(Pic_BW-Pic_dst, "resta MORPH_OPEN= Tophat");
    // morpho_pic(Pic_BW, Pic_dst, iter, MORPH_TOPHAT);   // It would recalculate Pic_dst
    //   show_pic(Pic_dst, "Tophat");
    waitKey(0);

    // Closing: remove small dark regions
    morpho_pic(Pic_BW, Pic_dst, iter, MORPH_CLOSE, anchor); // default kernel
      show_pic(Pic_dst, "MORPH_CLOSE");
      show_pic(Pic_dst-Pic_BW, "resta MORPH_CLOSE= Blackhat");
    // morpho_pic(Pic_BW, Pic_dst, iter, MORPH_BLACKHAT, kernel); // default anchor   // It would recalculate Pic_dst
    //   show_pic(Pic_dst, "Blackhat");
    waitKey(0);

    // Gradient: useful for getting outlines of objects
    morpho_pic(Pic_BW, Pic_dst, iter, MORPH_GRADIENT, kernel, anchor);    // No default params
      show_pic(Pic_dst, "MORPH_GRADIENT");
      show_pic(Pic_dst-Pic_BW, "resta MORPH_GRADIENT");
    waitKey(0);
  }
  else if   (selection==2)      {
    int iter_1= 10;
    Mat kernel_1= getStructuringElement(MORPH_CROSS, Size(3, 3));   // CV_8UC
    int iter_2= 5;
    Mat kernel_2= Mat::ones(3, 3, CV_32F);

    for(int i=0; i<v_Pic_BW.size()-1; ++i)    // Opening: Removing small bright regions
    {
      // Mat histo;
      // create_histo(v_Pic_BW[i], histo);    // Helps to choose threshold value

      // threshold(v_Pic_grey[i], v_Pic_BW[i], 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
      const int thr_value= 100;
      threshold(v_Pic_grey[i], v_Pic_BW[i], thr_value, 255, CV_THRESH_BINARY_INV);
        show_pic(v_Pic_color[i], "Original");
        show_pic(v_Pic_BW[i], "Binarized");

      waitKey(0);

      Mat Pic_morpho_1= v_Pic_BW[i].clone();
      Mat v_Pic_aux= v_Pic_dst[i].clone();
      morpho_pic(v_Pic_BW[i], Pic_morpho_1, iter_1, MORPH_OPEN, kernel_1);          // default anchor
        show_pic(Pic_morpho_1, "MORPH_OPEN 1");
        // show_pic(v_Pic_BW[i]-Pic_morpho_1, "resta MORPH_OPEN= Tophat");
        // morpho_pic(Pic_BW, Pic_dst, iter, MORPH_TOPHAT);   // It would recalculate Pic_dst
      count_objects(Pic_morpho_1, v_Pic_aux);
        show_pic(v_Pic_aux, "dst 1");

      waitKey(0);

      if(i==2)
        iter_2= 10;   // Not enough
      Mat Pic_morpho_2= Pic_morpho_1.clone();
      morpho_pic(Pic_morpho_2, Pic_morpho_2, iter_2, MORPH_OPEN, kernel_2);
        show_pic(Pic_morpho_2, "MORPH_OPEN 2");
      count_objects(Pic_morpho_2, v_Pic_dst[i]);
        show_pic(v_Pic_dst[i], "dst 2");

      waitKey(0);
      destroyAllWindows();
    }
  }
  else
    std::cout<<"¯|_(ツ)_|¯"<<std::endl;

  return EXIT_SUCCESS;
}
