#ifndef DRAWER_H
#define DRAWER_H

#include "Grid.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

cv::Mat draw(const Grid&);
void draw_hex(cv::Mat& img, const cv::Point2d& center, int size, const cv::Point2d& offset);

#endif // DRAWER_H