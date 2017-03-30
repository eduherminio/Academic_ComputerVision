#ifndef HEADERS
#define HEADERS

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

#include "opencv2/opencv.hpp"

#define HISTO_SIZE    256     // 256 grey levels
#define HISTO_WIDTH   1024    // 4 units/level
#define HISTO_HEIGHT  512

#define BLACK         Scalar(0, 0, 0)
#define PSEUDO_BLACK  Scalar(1, 1, 1)
#define WHITE         Scalar(255, 255, 255)
#define RED           Scalar(0, 0, 255)
#define GREEN         Scalar(0, 255, 0)
#define BLUE          Scalar(255, 0, 0)


#endif // HEADERS
