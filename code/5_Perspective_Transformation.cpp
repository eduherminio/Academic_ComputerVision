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
#include "./header/cv_basic_operations.hpp"
#include "./header/cv_library.hpp"

using namespace cv;
using namespace cv_lib;

void mouseEvent(int evt, int x, int y, int flags, void* param);

int main( int argc, char* argv[])
{
  std::vector<Mat>          v_Pic;
  std::vector<std::string>  v_picName;

  if(init_pic(argc, argv, v_picName, v_Pic) < 0)
    return EXIT_FAILURE;


  Mat Pic_final, Pic_finalInv;

  Mat matPersp(2,3,CV_32FC1);
  Mat matPerspInv(2,3,CV_32FC1);


  double reduction_coef= 0.5;

  for(auto& x:v_Pic) {

    resize(x, x, Size(), reduction_coef, reduction_coef, CV_INTER_LANCZOS4);

    Point2f corrected_points[4], perspective_points[4];

    std::string window_name("Marca los 4 puntos, comenzando por el vertice superior izquierdo, y pulse una tecla");
    show_pic(x, window_name);
    setMouseCallback(window_name, mouseEvent,  perspective_points);
    waitKey(0);
    destroyWindow(window_name);

    float lado= sqrt(pow(perspective_points[0].x - perspective_points[1].x, 2) + pow(perspective_points[0].y - perspective_points[1].y, 2));

    corrected_points[0]= { 0                            ,     0                             };
    corrected_points[1]= { corrected_points[0].x + lado ,     corrected_points[0].y         };
    corrected_points[2]= { corrected_points[1].x        ,     corrected_points[1].y + lado  };
    corrected_points[3]= { corrected_points[2].x - lado ,     corrected_points[2].y         };

  /*
    namedWindow("Marca esquinas rectangulo en mismo orden");
    imshow( "Marca esquinas rectangulo en mismo orden", v_Pic[1] );
    setMouseCallback("Marca esquinas rectangulo en mismo orden", mouseEvent,  corrected_points);
    imshow("Marca esquinas rectangulo en mismo orden", v_Pic[1]);
    waitKey(0);
    destroyWindow("Marca esquinas rectangulo en mismo orden");
  */

    //Calculamos la matriz que lleva de los perspective_points marcados a los corrected_points deducidos
    matPersp=getPerspectiveTransform(perspective_points, corrected_points);

    //Aplicamos la transformacion
    warpPerspective(x, Pic_final, matPersp, x.size());

    Rect Rectangle(0,0, lado, lado);
    rectangle(Pic_final, Rectangle, Scalar(0,0,255));

    show_pic(Pic_final, "Sin perspectiva");

    // Anti-transformamos para ver si obtenemos la imagen y el rectángulo original
    invert(matPersp, matPerspInv);
    warpPerspective(Pic_final, Pic_finalInv, matPerspInv, Pic_final.size());

    show_pic(Pic_finalInv, "Imagen final invertida");

    waitKey(0);

    reduction_coef*=2;  // 2nd pic
  }

  return EXIT_SUCCESS;
}

void mouseEvent(int evt, int x, int y, int flags, void* param)
{
    static int numPunto=0;
    Point2f* puntos = (Point2f*) param;
    if (numPunto==4)
      numPunto=0;

    if (evt == EVENT_LBUTTONDOWN) {
        puntos[numPunto]=Point2f(x,y);
        numPunto++;
        std::cout << "Punto " << numPunto <<" ( " << x <<" , " << y << " ) "<< std::endl;
    }
}
