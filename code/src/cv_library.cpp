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
  else
    Pic_grey= Pic_original.clone();
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

void set_Brightness_Contrast(const Mat& Pic_original, const int& brightness, const int& contrast, Mat& Pic_final) {
    double alpha, beta, delta;
    if( contrast > 0 )
    {
        delta = 127. * contrast/100;
        alpha = 255./(255. - delta*2);
        beta  = alpha*(brightness - delta);
    }
    else
    {
        delta = -128. * contrast/100;
        alpha = (256. - delta*2)/255.;
        beta  = alpha*brightness + delta;
    }

    Pic_original.convertTo(Pic_final, CV_8U, alpha, beta);    // imgGrisResult(x,y) = saturate_cast<uchar> (alpha*imgGris(x,y) + beta);
}

void create_contours(const Mat& Pic_src, Mat& Pic_dst, std::vector<std::vector<Point>>& contours)   {
  Pic_dst=Pic_src.clone();

  findContours(
    Pic_src,
    contours,
    // std::vector<Vec4i> hierarchy; // Optional in OpenCV 3.2
    CV_RETR_EXTERNAL,
    CV_CHAIN_APPROX_NONE
    // 	Point  	offset = Point()
  );
  drawContours(Pic_dst,contours,0,Scalar(255),CV_FILLED);
  std::cout << "Located regions: " <<  contours.size() << std::endl;
  // show_pic(Pic_dst);
}


void create_histo (const Mat& Pic, Mat& hist, Scalar color)  { // General function
  if((Pic.channels())>1 && color== BLACK)  {
    std::cout<<"Something's probably wrong"<<std::endl;
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

  cv::calcHist(&Pic,
               1,		        // number of pics
               channels,	  // channels used
               cv::Mat(),   // no mask
               hist,		    // histograma resultante
               1,			      // 1D
               histSize,	  // number of elements in hist
               ranges		    // pixel range value
              );

  if(color==BLACK)
  {
    Mat Pic_histo( HISTO_HEIGHT, HISTO_WIDTH, CV_8UC3, WHITE );
    draw_histo(Pic_histo, hist, color);

    show_histo(Pic_histo);
  }
}

void create_histo (const Mat& Pic, Mat& hist) {   // 1 pic, 1 hist -> We can assume user wants a B&W histogram
  Mat Pic_grey= Pic.clone();

  if((Pic_grey.channels())>1)  {
    cvtColor(Pic, Pic_grey, CV_BGR2GRAY);
  }

  create_histo(Pic_grey, hist, BLACK);
}

void create_histo (const Mat& Pic, std::vector<Mat>& v_hist)   {    // 1 pic, vector of hist -> We assume yser wabts a RGB histogram
  Mat Pic_color= Pic.clone();
  if((Pic.channels())!=3)  {
    std::cout<<"\n***BEWARE: not a color pic!***\n"<<std::endl;
    cvtColor(Pic,Pic_color,COLOR_GRAY2RGB);     // Transform the B&W pic in RGB
  }

  Mat Pic_histo( HISTO_HEIGHT, HISTO_WIDTH, CV_8UC3, WHITE );
  std::vector<Mat> v_BGR;
  v_BGR.resize(3);
  v_hist.resize(3);
  split(Pic_color, v_BGR);

  create_histo(v_BGR[0],  v_hist[0], BLUE);
  create_histo(v_BGR[1],  v_hist[1], GREEN);
  create_histo(v_BGR[2],  v_hist[2], RED);

  draw_histo(Pic_histo,   v_hist[0], BLUE);
  draw_histo(Pic_histo,   v_hist[1], GREEN);
  draw_histo(Pic_histo,   v_hist[2], RED);

  show_histo(Pic_histo);
}

void create_histo (const std::vector<Mat>& v_Pic, std::vector<Mat>& v_hist) { // Does NOT return all hist
  bool BW= true;
  for(const auto& Pic:v_Pic)  {
    if((Pic.channels()) == 3)      // If one of them is color Pic, creates RGB histograms
    {
      BW= false;
      break;
    }
  }
  if(BW==true)
  {
    v_hist.resize(v_Pic.size());
    for(int iter=0; iter<v_Pic.size(); ++iter)
    {
      create_histo(v_Pic[iter], v_hist[iter]);
    }
  }
  else    // Only case when not all hists are going to be returned - TO-CHECK
  {
    for(const auto& Pic:v_Pic)
    {
      create_histo(Pic, v_hist);
    }
  }
}


void draw_histo   (Mat& Pic_histo, const Mat& histo, const Scalar color)  {
  int ratio = cvRound( (double) HISTO_WIDTH/HISTO_SIZE );

  normalize(histo, histo, 0, HISTO_HEIGHT, NORM_MINMAX);  // histo -> [0, HISTO_HEIGHT]

  for( int i = 1; i < HISTO_SIZE; i++ )   // Lines which join the ends of the bars
  {
    line( Pic_histo,
      Point( (i-1) * ratio, HISTO_HEIGHT - cvRound(histo.at<float>(i-1)) ),
      Point(  i * ratio,    HISTO_HEIGHT - cvRound(histo.at<float>(i)) ),
      color, 2, 8, 0  );
  }
}

void show_histo   (Mat& Pic_histo)  {
  static int n_pic;

  Rect rect(0, 0, HISTO_WIDTH-1, HISTO_HEIGHT-1);
  rectangle(Pic_histo, rect, Scalar(100,100,100));

  show_pic(Pic_histo, stringify(Pic_histo) + std::to_string(n_pic));
  n_pic++;  // To show one per picture
}


void rotation_trackbar(int, void* userdata) {
  UserData user_data= *((UserData*)userdata); // cast + de-reference
  user_data.angle-=180;
  Point centro= Point(user_data.pt.x, user_data.pt.y);
  Mat matrizRot = getRotationMatrix2D( centro, (user_data.angle), 1);
  warpAffine( user_data.Pic_src, user_data.Pic_dst, matrizRot, user_data.Pic_src.size() );
  imshow( "Imagen Rotada", user_data.Pic_dst);
}

void brightness_contrast_trackbar(int, void* userdata)   {
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
