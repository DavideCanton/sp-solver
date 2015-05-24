#include "Drawer.h"
#include <sstream>

using namespace cv;

std::vector<Point2d> get_vertexes(const Point2d& center, int size)
{
	std::vector<Point2d> v;
	for (int i = 0; i < 6; ++i)
	{
		double angle = 2 * CV_PI / 6 * (i + 0.5);
		v.push_back(Point2d(center.x + size * cos(angle), center.y + size * sin(angle)));
	}

	return v;
}

Point2d coord_to_pixel(const Coords& cell, int size)
{
	double x = size * sqrt(3.0) * (cell.get_q() + cell.get_r() / 2.0);
	double y = size * 1.5 * cell.get_r();
	return Point2d(x, y);
}

void draw_hex(Mat& img, const Point2d& center, int size, const Point2d& offset)
{
	std::vector<Point2d> vertexes = get_vertexes(center, size);
	for (int i = 0; i < 6; ++i)
	{
		int n = (i + 1) % 6;
		line(img, vertexes[i] + offset, vertexes[n] + offset, 0);
	}
}

void draw_text(Mat& img, const Point2d& center, const std::string& text, const Point2d& offset)
{
	Size2i size = getTextSize(text, FONT_HERSHEY_PLAIN, 1, 0, 0);
	size.width /= 2;
	size.height /= 2;
	putText(img, text, center + offset - Point2d(size), FONT_HERSHEY_PLAIN, 1, 0);
}

Mat draw(const Grid& grid)
{
	Size2i size(800, 600);
	int size_hex = 30;

	int h = (grid.get_max_r() - grid.get_min_r()) * size_hex * 2;
	int w = (int)((grid.get_max_q() - grid.get_min_q()) * size_hex * sqrt(3.0));

	Point2d offset(size.width / 2.0 - w / 2.0, size.height / 2.0 - h / 2.0);	

	Mat img = Mat::zeros(size, CV_8UC1);
	img.setTo(255);

	for (auto& pair : grid.get_content())
	{
		const Coords& cell = pair.first;
		Coords cell_norm(cell.get_q() - grid.get_min_q(), cell.get_r() - grid.get_min_r());
		Point2d center = coord_to_pixel(cell_norm, size_hex);
		draw_hex(img, center, size_hex, offset);

		if (!pair.second.empty)
		{
			if (pair.second.piece)
				draw_text(img, center, pair.second.piece->get_aspect(), offset);
			else
				draw_text(img, center, "O", offset);
		}
		else if (grid.get_pieces().empty())
		{
			std::ostringstream oss;
			oss << cell_norm;
			draw_text(img, center, oss.str(), offset);
		}
	}

	return img;
}