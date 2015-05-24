#include "Coords.h"
#include "Utils.h"
#include "Grid.h"
#include "Piece.h"
#include "LevelDetect.h"
#include "Solver.h"
#include "Drawer.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 3 && argc != 4)
	{
		std::cerr << "Parametri non validi!" << std::endl;
		return EXIT_FAILURE;
	}

	Grid grid;
	PieceVec pieces;
	float factor = strtof(argv[2], NULL);
	//float factor = 2.0f;

	//std::tie(grid, pieces) = detectLevel("C:\\Users\\Davide\\Downloads\\music\\original6.png", 2.0f);
	std::tie(grid, pieces) = detectLevel(argv[1], factor);

	std::cout << "Grid of " << grid.get_content().size() << " cells detected." << std::endl;
	std::cout << "Pieces found:" << std::endl;
	for (Piece& p : pieces)
		std::cout << p << std::endl;

	Solver solver(&grid, pieces);
	solver.solve();

	std::cout << "Positions found:" << std::endl;
	for (auto& pair : grid.get_pieces())
		std::cout << pair.first << " @ " << pair.second << std::endl;

	cv::Mat img = draw(grid);

	if (argc == 3)
	{
		cv::imshow("Solution", img);
		cv::waitKey(0);
	}
	else
		cv::imwrite(argv[3], img);

	return EXIT_SUCCESS;
}