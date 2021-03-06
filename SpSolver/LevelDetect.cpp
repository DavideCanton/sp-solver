#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <set>
#include "Coords.h"
#include "LevelDetect.h"
#include "Drawer.h"

using namespace std;
using namespace cv;

Scalar PIECE_COLOR = CV_RGB(65, 33, 145);

LevelDetector::LevelDetector(const LevelDetectorConfig& config) : config(config)
{
}

vector<Vec3f> LevelDetector::detectCircles(Mat& img, int offset)
{
	vector<Vec3f> circles;

	HoughCircles(img(Rect(0, offset, img.cols, img.rows - offset)),
		circles, CV_HOUGH_GRADIENT, 1, img.rows / 32, this->config.hough_circles_param, this->config.hough_circles_param, 
		this->config.min_radius, this->config.max_radius);

	return circles;
}

bool LevelDetector::near_border(int x, int limit, int threshold = 10)
{
	return abs(x - limit) < threshold;
}

vector<int> LevelDetector::detectPieces(Mat& img, Mat& img_gray)
{
	vector<Vec4i> lines;

	Mat img_gray_d;

	Canny(img_gray, img_gray_d, 40, 120);

	HoughLinesP(img_gray_d, lines, 1, CV_PI / 180 * 30, 
		this->config.hough_lines_threshold, this->config.min_line_length, this->config.max_line_gap);

	Vec3b v = img.at<Vec3b>(img.cols / 2, img.rows / 2);
	Scalar centerColor = Scalar(v[0], v[1], v[2]);

	set<int> dirs;
	if (norm(centerColor - PIECE_COLOR) < 10)
	{
		for (Vec4i c : lines)
		{
			bool in_border = false;

			if (near_border(c[0], 0) && near_border(c[2], 0))
				in_border = true;
			if (near_border(c[0], img.cols) && near_border(c[2], img.cols))
				in_border = true;
			if (near_border(c[1], 0) && near_border(c[3], 0))
				in_border = true;
			if (near_border(c[1], img.rows) && near_border(c[3], img.rows))
				in_border = true;

			auto color = in_border ? CV_RGB(255, 0, 0) : CV_RGB(0, 255, 0);
			line(img, Point2i(c[0], c[1]), Point2i(c[2], c[3]), color);

			if (in_border) continue;

			float m = static_cast<float>(c[3] - c[1]) / (c[2] - c[0]);
			if (isfinite(m))
			{
				if (fabs(m) < 1e-8)
				{
					dirs.insert(get_dir_index("w"));
					dirs.insert(get_dir_index("e"));
				}
				else if (m < 0)
				{
					dirs.insert(get_dir_index("sw"));
					dirs.insert(get_dir_index("ne"));
				}
				else
				{
					dirs.insert(get_dir_index("nw"));
					dirs.insert(get_dir_index("se"));
				}
			}
		}
	}

	if (config.display_pieces && !dirs.empty()) { 
		imshow("Piece", img); waitKey(0);
	}

	return vector<int>(dirs.begin(), dirs.end());
}

std::pair<Grid, PieceVec> LevelDetector::detectLevel(std::string fname)
{
	Mat src, src_gray;

	// Read the image
	src = imread(fname, 1);

	if (!src.data)
		throw std::logic_error("Invalid image");

	int offset = 0;
	int limit = src.rows / 4 - this->config.limit_gap;
	// Convert it to gray
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles = detectCircles(src_gray, offset);

	Vec3f start;
	float avg_radius = 0;
	int n = 0;

	for (Vec3f p : circles)
		if (p[1] > limit)
		{
			start = p;
			avg_radius += p[2];
			++n;
		}

	avg_radius /= n;
	avg_radius *= config.factor;

	Grid grid;
	PieceVec pv;

	for (Vec3f p : circles)
	{
		if (p[1] > limit)
		{
			Point2d center(p[0], p[1]);
			Point2d size(avg_radius, avg_radius);

			p -= start;

			double q = (p[0] * sqrt(3.0) / 3 - p[1] / 3.0) / avg_radius;
			double r = p[1] * 2.0 / 3 / avg_radius;

			grid.set_el(Coords(q, r), GRID_EMPTY_CELL);

			//draw_hex(src, center, (int) size.x, Point2d(0, offset));
		}
		else
		{
			Point2d center(p[0], p[1]);
			int radius = static_cast<int>(p[2]);
			circle(src, center, radius, 0);

			Rect bounding_rect(center - Point2d(radius, radius), Size(2 * radius, 2 * radius));
			vector<int> dirs = detectPieces(src(bounding_rect), src_gray(bounding_rect));
			if (!dirs.empty())
			{
				Piece p = make_piece(dirs);
				pv.push_back(p);
			}
		}
	}

	return make_pair(grid, pv);
}