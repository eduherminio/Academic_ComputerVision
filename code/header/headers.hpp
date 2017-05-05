#ifndef HEADERS
#define HEADERS

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <cassert>
#include <random>
#include <chrono>

#include "opencv2/opencv.hpp"

#define MAX_HEIGHT  512
#define MAX_WIDTH   1024

#define HISTO_SIZE    256     // 256 grey levels
#define HISTO_WIDTH   1024    // 4 units/level
#define HISTO_HEIGHT  512

#define BLACK         Scalar(0, 0, 0)
#define PSEUDO_BLACK  Scalar(1, 1, 1)
#define WHITE         Scalar(255, 255, 255)
#define RED           Scalar(0, 0, 255)
#define GREEN         Scalar(0, 255, 0)
#define BLUE          Scalar(255, 0, 0)
#define ORANGE        Scalar(0, 128, 255)
#define YELLOW        Scalar(0, 255, 255)
#define PINK          Scalar(128, 0, 255)
#define PURPLE        Scalar(102, 0, 205)

const double PI= 3.14159264;

#endif // HEADERS
