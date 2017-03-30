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


#include "opencv2/opencv.hpp"
#include "./header/basic_operations.hpp"
#include "./header/cv_library.hpp"
#include <cmath>

using namespace cv;

#define SAVE    true
#define NOTSAVE false

void rotation_trackbar(int, void*);

struct Rotation_params
{
  Mat     Pic_src;
  Mat     Pic_dst;
  Point2i pt;
};

int main(int argc, char* argv[])
{
  Mat Pic_original, Pic_grey, Pic_interest1, Pic_trasl1, Pic_rotated, Pic_rotated_grey, Pic_cleared, Pic_trasl, Pic_scaled, Pic_final;         // Beware the order
  std::string picName;

  if(init_pic(argc, argv, picName, Pic_original) < 0)    return EXIT_FAILURE;
  show_pic(Pic_original, "Original");
  waitKey(0);
  cvtColor(Pic_original, Pic_grey, CV_BGR2GRAY);

// Camino 1:

  // Señalización de la zona de interés
  int threshold=85;
  int xleft, xright, yhigh, ylow;

  light_rectangle(Pic_grey, threshold, xleft, xright, yhigh, ylow); // ylow e yhigh segun las coordenadas tradicionales

  Rect rect(xleft, ylow, +abs(xleft-xright), +abs(yhigh-ylow)); // esquina_inferior.x, esquina_inferior.y, wide, height

  Pic_interest1= Pic_original.clone();
  rectangle(Pic_interest1, rect, Scalar(0,255,0));
  show_pic(Pic_interest1, "Zona de interes");
  waitKey(0);

  // Translado según la zona de interés 1
  float translation_matrix1 [2][3]={  1.0, 0.0 , (float)-xleft,
                                      0.0, 1.0 , (float)-ylow   };

  Mat matTrasl1(2, 3, CV_32FC1, translation_matrix1);        // translation

  warpAffine(Pic_interest1, Pic_trasl1, matTrasl1, Pic_rotated.size());
  show_pic(Pic_trasl1, "Desplazamiento 1");
  waitKey(0);

// Camino 2:
  int iAngulo = 180;
  namedWindow( "Imagen Rotada");
  Rotation_params rotation_data;
  rotation_data.Pic_src= Pic_original.clone();
  rotation_data.Pic_dst= rotation_data.Pic_src.clone();


  // Rotación en torno al centro de esa zona de interés, previa a la traslación (aunque no se vea)
  rotation_data.pt= {(int)(0.5*rect.width), (int)(0.5*rect.height)};

  createTrackbar("Angulo", "Imagen Rotada", &iAngulo, 360, rotation_trackbar, (void*) (&rotation_data));
  rotation_trackbar(iAngulo, &rotation_data);
  waitKey(0);

  // Mejor giramos en torno al centro de la imagen
  rotation_data.pt= {(int)(0.5*Pic_original.rows), (int)(0.5*Pic_original.cols)};
  iAngulo = 180;
  rotation_trackbar(iAngulo, &rotation_data);
  waitKey(0);

  Pic_rotated= rotation_data.Pic_dst.clone();

  // Señalización de la nueva zona de interés
  cvtColor(Pic_rotated, Pic_rotated_grey, CV_BGR2GRAY);
  light_rectangle(Pic_rotated_grey, threshold, xleft, xright, yhigh, ylow); // ylow e yhigh segun las coordenadas tradicionales
  Rect rect2(xleft, ylow, +abs(xleft-xright), +abs(yhigh-ylow)); // esquina_inferior.x, esquina_inferior.y, wide, height

  rectangle(Pic_rotated_grey, rect2, Scalar(0,0,255));
  show_pic(Pic_rotated_grey, "Zona de interes 2");

  rectangle(Pic_rotated, rect2, Scalar(0,0,255));
  waitKey(0);

// Ennegrecemos el fondo de la imagen, de manera que sólo lo que nos importa (interior del rectángulo) sea distinto de negro
  fill_no_rectangle(Pic_rotated, Pic_cleared, rect2);

  show_pic(Pic_cleared, "Zona de interés aislada");

  waitKey(0);


  // Traslación de la imagen
  float translation_matrix [2][3]={ 1.0, 0.0 , (float)-xleft,
                                    0.0, 1.0 , (float)-ylow   };

  Mat matTrasl2(2, 3, CV_32FC1, translation_matrix);        // translation

  warpAffine(Pic_cleared, Pic_trasl, matTrasl2, Pic_rotated.size());
  show_pic(Pic_trasl, "desplazado");
  waitKey(0);

  // Rescalado de la imagen
  float scale_matrix [2][3]=  { 1.5, 0.0 , 0,
                                0.0, 1.5 , 0  };

  Mat matScale(2, 3, CV_32FC1, scale_matrix);

// CV_INTER_NEAREST is not recognized, for some reason   ¯\_(ツ)_/¯

  warpAffine(Pic_trasl, Pic_scaled, matScale, Pic_scaled.size(), CV_INTER_LINEAR);  // Avg for enlargering
  show_pic(Pic_scaled, "Imagen rescalada 1");
  waitKey(0);

  warpAffine(Pic_trasl, Pic_scaled, matScale, Pic_scaled.size(), CV_INTER_AREA);    // Good for shrinking
  show_pic(Pic_scaled, "Imagen rescalada 2");
  waitKey(0);

  warpAffine(Pic_trasl, Pic_scaled, matScale, Pic_scaled.size(), CV_INTER_CUBIC);   // Good for enlargering
  show_pic(Pic_scaled, "Imagen rescalada 3");
  waitKey(0);

  warpAffine(Pic_trasl, Pic_scaled, matScale, Pic_scaled.size(), CV_INTER_LANCZOS4);
  show_pic(Pic_scaled, "Imagen rescalada 4");

  // También, recordemos:
/*
  double reduction_coef=1.5;
  resize(Pic_trasl, Pic_scaled, Size(), reduction_coef, reduction_coef, CV_INTER_LANCZOS4);
  show_pic(Pic_scaled, "Imagen rescalada 2");
*/

  waitKey(0);

  return EXIT_SUCCESS;
}


void rotation_trackbar(int iAngulo, void* userdata)
{
  Rotation_params rotation_data= *((Rotation_params*)userdata); // cast + de-reference

  Point centro= Point(rotation_data.pt.x, rotation_data.pt.y);
  Mat matrizRot = getRotationMatrix2D( centro, (iAngulo - 180), 1);
  warpAffine( rotation_data.Pic_src, rotation_data.Pic_dst, matrizRot, rotation_data.Pic_src.size() );
  imshow( "Imagen Rotada", rotation_data.Pic_dst);
}
