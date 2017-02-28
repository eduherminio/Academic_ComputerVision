#include "opencv2/opencv.hpp"
#include "./header/basic_operations.hpp"
#include "./header/cv_library.hpp"
#include <cmath>

using namespace cv;

#define SAVE    true
#define NOTSAVE false

void rotation_trackbar(int, void*);


int main(int argc, char* argv[])
{
  Mat Pic_original, Pic_grey, Pic_resized, Pic_trasl, Pic_scaled, Pic_final;         // Beware the order
  std::string picName;

  if(init_pic(argc, argv, picName, Pic_original) < 0)    return EXIT_FAILURE;
  show_pic(Pic_original, "Original");
  cvtColor(Pic_original, Pic_grey, CV_BGR2GRAY);

  int threshold=75;
  int xleft, xright, yhigh, ylow;

  light_rectangle(Pic_original, threshold, xleft, xright, yhigh, ylow); // ylow e yhigh segun las coordenadas tradicionales

  Rect rect(xleft, ylow, +abs(xleft-xright), +abs(yhigh-ylow)); // esquina_inferior.x, esquina_inferior.y, wide, height

  rectangle(Pic_original, rect, Scalar(0,255,0));
  waitKey(0);
  show_pic(Pic_original, "Zona de interes");

  float translation_matrix [2][3]={ 1.0, 0.0 , (float)-xleft,
                                    0.0, 1.0 , (float)-ylow   };

  Mat matTrasl(2, 3, CV_32FC1, translation_matrix);        // translation

  warpAffine(Pic_original, Pic_trasl, matTrasl, Pic_original.size());
  waitKey(0);
  show_pic(Pic_trasl, "desplazado");

  float scale_matrix [2][3]=  { 1.5, 0.0 , 0,
                                0.0, 1.5 , 0  };

  Mat matScale(2, 3, CV_32FC1, scale_matrix);        //donde guardaremos el escalado

  warpAffine(Pic_trasl, Pic_scaled, matScale, Pic_original.size());
  waitKey(0);
  show_pic(Pic_scaled, "escalado");

  // Mat matRot(2, 3, CV_32FC1);


  int iAngulo = 180;
  namedWindow( "Imagen Rotada");
  createTrackbar("Angulo", "Imagen Rotada", &iAngulo, 360, rotation_trackbar, (void*) (&Pic_scaled));

  rotation_trackbar(iAngulo, &Pic_scaled);
  // Point2f srcTri[3];
  // Point2f dstTri[3];

  // Mat rot_mat( 2, 3, CV_32FC1 );
  // Mat warp_mat( 2, 3, CV_32FC1 );
  // Mat warp_dst, warp_rotate_dst;

  // warp_dst= Mat::zeros(Pic_grey.rows, Pic_grey.cols, Pic_grey.type());

  // Pic_resized= cv2.resize(Pic_original, 2, 2);
  // Pointer2f center;
  // double angle, scale;

//   Mat Rotation_mat= getRotationMatrix2D(center, angle, scale);
//   show_pic(Rotation_mat, "rotated");

  waitKey(0);

  return EXIT_SUCCESS;
}


void rotation_trackbar(int iAngulo, void *userdata)
{
  Mat Pic_scaled = *((Mat*)userdata);
  Mat imgRotada;
  Point centro= Point(0.5*Pic_scaled.rows, 0.5*Pic_scaled.cols);
  Mat matrizRot = getRotationMatrix2D( centro, (iAngulo - 180), 1 ); //1 es la escala
  warpAffine( Pic_scaled, imgRotada, matrizRot, Pic_scaled.size() );
  imshow( "Imagen Rotada", imgRotada );
}
