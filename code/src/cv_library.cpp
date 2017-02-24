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


#include "../header/cv_library.hpp"

void manual_binarize(const Mat & myPic, const int threshold, const bool save) {
  Mat binPic= myPic.clone();

  for(int i=0; i<binPic.rows; i++)    {
    uchar* ptrRow=      binPic.ptr<uchar>(i);
    for(int j=0; j<binPic.cols; j++)  {
      double grey_level= *(ptrRow+j);
      if(grey_level < threshold)
        *(ptrRow+j)= 0;
      else
        *(ptrRow+j)= 255;
      // std::cout<<grey_level<<" ";
    }
    // std::cout<<std::endl;
  }

  show_pic(binPic, "Black & White");

  if(save== true)
  {
   std::string newName(stringify(myPic));
    newName += "_B&W.jpg";  // Fundamental to add the extension
    imwrite(newName, binPic);
  }
}

std::unique_ptr<Rect> light_rectangle(const Mat & Pic_original, const int threshold)
{
  Mat Pic_grey;
  cvtColor(Pic_original, Pic_grey, CV_BGR2GRAY);

  int righter=0, lower=0, lefter= 999, higher=999, grey_level;

  for(int i=0; i<Pic_grey.rows; ++i)      // from low to high
  {
    uchar *p_row= Pic_grey.ptr<uchar>(i);
    for(int j=0; j<Pic_grey.cols; ++j)  // from left to right
    {    
      grey_level= p_row[j];
      // std::cout<<i<<" "<<j<<" "<<grey_level<<std::endl;
      if(grey_level>threshold)  {
          if(j>righter)   righter=  j;
          if(i>lower)     lower=    i;

          if(j<lefter)    lefter=   j;
          if(i<higher)    higher=   i;
      }
    }
  }

  // std::cout<<righter<<" "<<lower<<std::endl;
  // std::cout<<lefter<<" "<<higher<<std::endl;

  return std::unique_ptr<Rect> (new Rect(lefter, higher, +abs(lefter-righter), +abs(higher-lower))); // origin.x, origin.y, wide, height
}
