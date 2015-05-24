#ifndef DRAWER_H
#define DRAWER_H

#include "Grid.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

cv::Mat draw(const Grid&);

#endif // DRAWER_H