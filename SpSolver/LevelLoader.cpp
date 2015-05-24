#include "LevelLoader.h"
#include "Coords.h"
#include "Piece.h"
#include <fstream>
#include <sstream>

void fillVec(const std::string& line, PieceVec& v)
{
	std::istringstream iss(line);
	for (int p; iss >> p;)	
		v.push_back(make_piece(p));
}

std::pair<Grid, PieceVec> load_level(std::string fname)
{
	std::ifstream ifs(fname);

	std::string line;
	std::getline(ifs, line);

	PieceVec p;
	fillVec(line, p);

	Grid g;
	while (std::getline(ifs, line))
	{
		std::istringstream iss(line);
		int q, r;
		iss >> q;
		iss >> r;

		Coords c(q, r);
		g.set_el(c, GRID_EMPTY_CELL);
	}

	return std::make_pair(g, p);
}