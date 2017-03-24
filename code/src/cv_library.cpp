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

void grey_pic(const Mat& Pic_original, Mat& Pic_grey)    {
  if((Pic_original.channels())>1)  {
    cvtColor(Pic_original, Pic_grey, CV_BGR2GRAY);
  }
}

void grey_pic(const std::vector<Mat>& v_Pic, std::vector<Mat>& v_Pic_grey)    {
  v_Pic_grey.resize(v_Pic.size());

  for(int i=0; i<v_Pic.size(); ++i)
  {
    grey_pic(v_Pic[i], v_Pic_grey[i]);
  }
}

void manual_binarize(const Mat& myPic, const int threshold, const bool save) {
  Mat binPic= myPic.clone();

  for(int i=0; i<binPic.rows; i++)
  {
    uchar* ptrRow=      binPic.ptr<uchar>(i);
    for(int j=0; j<binPic.cols; j++)
    {
      double grey_level= *(ptrRow+j);
      if(grey_level < threshold)
        *(ptrRow+j)= 0;
      else
        *(ptrRow+j)= 255;
      // std::cout<<grey_level<<" ";
    }
    // std::cout<<std::endl;
  }

  show_pic(binPic, "Black& White");

  if(save== true)
  {
   std::string newName(stringify(myPic));
    newName += "_B&W.jpg";  // Fundamental to add the extension
    imwrite(newName, binPic);
  }
}

std::unique_ptr<Rect> light_rectangle(const Mat& Pic_original, const int threshold)  {
  Mat Pic_grey= Pic_original.clone();
  if((Pic_original.channels())>1)  {
    cvtColor(Pic_original, Pic_grey, CV_BGR2GRAY);
  }

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

  return std::unique_ptr<Rect> (new Rect(lefter, higher, +abs(lefter-righter), +abs(higher-lower))); // esquina_inferior.x, esquina_inferior.y, wide, height
}

void light_rectangle(const Mat& Pic_original, const int threshold, int& xleft, int& xright, int& yhigh, int& ylow) {
  Mat Pic_grey= Pic_original.clone();
  if((Pic_original.channels())>1)  {
    cvtColor(Pic_original, Pic_grey, CV_BGR2GRAY);
  }
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
  xleft=  lefter;
  xright= righter;
  yhigh=  lower;
  ylow=   higher;
}

void fill_no_rectangle(const Mat& Pic_original, Mat& Pic_clean, Rect rectangulo)  {
  Pic_clean= Pic_original.clone();

  for(int i=0; i<Pic_clean.rows; ++i)      // from low to high
  {
    for(int j=0; j<Pic_clean.cols; ++j)  // from left to right
    {
      Point2i Pixel(j,i); // TO-CHECK
      if(!Pixel.inside(rectangulo)) {
        Point3_<uchar>* p = Pic_clean.ptr<Point3_<uchar> >(i,j);
        p->x=0;
        p->y=0;
        p->z=0;
        // p_row[j]= 0; // We need
      }
    }
  }
}

void create_histo (const Mat& Pic, Mat& hist) {
  Mat Pic_grey= Pic.clone();

  if((Pic_grey.channels())>1)  {
    cvtColor(Pic, Pic_grey, CV_BGR2GRAY);
  }

  int histSize[1];
  float hranges[2];
  const float* ranges[1];
  int channels[1];

  histSize[0]= 256;         // size
  hranges[0]= 0.0;          // min_value
  hranges[1]= 256.0;        // max_value
  ranges[0]= hranges;       // ranges
  channels[0]= 0;           // channel 0

  cv::calcHist(&Pic_grey,
               1,		        // number of pics
               channels,	  // channels used
               cv::Mat(),   // no mask
               hist,		    // histograma resultante
               1,			      // 1D
               histSize,	  // number of elements in hist
               ranges		    // pixel range value
              );


  show_histo(hist, Scalar( 0,0,0) );
}

void create_histo (const std::vector<Mat>& v_Pic, std::vector<Mat>& v_hist) {
  v_hist.resize(v_Pic.size());
  for(int iter=0; iter<v_Pic.size(); ++iter)  {
    create_histo(v_Pic.at(iter), v_hist.at(iter));
  }
}

void show_histo   (const Mat& histo, const Scalar color)  {
  static int n_pic;
  n_pic++;

  Mat Pic_histo( HISTO_HEIGHT, HISTO_WIDTH, CV_8UC3, Scalar( 255,255,255) );

  int ratio = cvRound( (double) HISTO_WIDTH/HISTO_SIZE );

  normalize(histo, histo, 0, HISTO_HEIGHT, NORM_MINMAX);  // histo -> [0, HISTO_HEIGHT]

  for( int i = 1; i < HISTO_SIZE; i++ )   // Lines which join the ends of the bars
  {
    line( Pic_histo,
      Point( (i-1) * ratio, HISTO_HEIGHT - cvRound(histo.at<float>(i-1)) ),
      Point(  i * ratio,    HISTO_HEIGHT - cvRound(histo.at<float>(i)) ),
      color, 2, 8, 0  );
  }

  Rect rect(0, 0, HISTO_WIDTH-1, HISTO_HEIGHT-1);
  rectangle(Pic_histo, rect, Scalar(0,0,255));

  show_pic(Pic_histo, stringify(Pic_histo) + std::to_string(n_pic));
}
