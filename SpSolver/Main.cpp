#include "Coords.h"
#include "Utils.h"
#include "Grid.h"
#include "Piece.h"
#include "LevelDetect.h"
#include "Solver.h"
#include "Drawer.h"
#include <iostream>

#define DEBUG 1
#define DRAW_EVERY_IT 0

void execute(Grid& grid, PieceVec& pieces, int argc, char** argv)
{
	std::cout << "Grid of " << grid.get_content().size() << " cells detected." << std::endl;
	std::cout << "Pieces found:" << std::endl;
	for (Piece& p : pieces)
		std::cout << p << std::endl;

	Solver solver(&grid, pieces);

#if DRAW_EVERY_IT
	solver.set_callback([&grid](int iteration) {
		cv::Mat img = draw(grid);

		std::ostringstream oss;
		oss << "Iteration " << iteration;

		std::string title = oss.str();

		cv::imshow(title, img);
		cv::waitKey(0);
	});
#endif

	solver.solve();

	std::cout << "Positions found:" << std::endl;
	for (auto& pair : grid.get_pieces())
		std::cout << pair.first << " @ " << pair.second << std::endl;

	cv::Mat img = draw(grid);

	int max_argc =
#ifdef DEBUG
		2
#else
		3
#endif
		;

	if (argc != max_argc)
	{
		cv::imshow("Solution", img);
		cv::waitKey(0);
	}
	else
		cv::imwrite(argv[max_argc], img);
}

int main(int argc, char** argv)
{
#ifndef DEBUG
	if (argc != 3 && argc != 4)
	{
		std::cerr << "Parametri non validi!" << std::endl;
		return EXIT_FAILURE;
	}
#endif

	Grid grid;
	PieceVec pieces;
	LevelDetectorConfig config;	
	LevelDetector detector(config);

#ifdef DEBUG
	std::tie(grid, pieces) = detector.detectLevel("C:\\Users\\Davide\\Documents\\Screenshot_2017-04-15-13-20-00.png");
#else
	config.factor = strtof(argv[2], nullptr);
	std::tie(grid, pieces) = detector.detectLevel(argv[1]);
#endif 

	execute(grid, pieces, argc, argv);

	return EXIT_SUCCESS;
}

