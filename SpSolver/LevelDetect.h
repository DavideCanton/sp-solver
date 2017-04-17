#ifndef LEVELDETECT_H
#define LEVELDETECT_H

#include "Grid.h"
#include "Utils.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class LevelDetectorConfig
{
public:
	float factor = 2.0f;
	int min_radius = 25;
	int max_radius = 50;
	int min_line_length = 50;
	int max_line_gap = 50;
	int limit_gap = 80;
	int hough_circles_param = 30;
	int hough_lines_threshold = 25;
	bool display_pieces = false;
};

class LevelDetector
{
public:
	LevelDetector(const LevelDetectorConfig& config);

	std::pair<Grid, PieceVec> detectLevel(std::string fname);

private:
	const LevelDetectorConfig& config;

	std::vector<cv::Vec3f> detectCircles(cv::Mat& img, int offset);
	bool near_border(int x, int limit, int threshold);
	std::vector<int> detectPieces(cv::Mat& img, cv::Mat& img_gray);
};

#endif // LEVELDETECT_H