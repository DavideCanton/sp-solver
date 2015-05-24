#include "Utils.h"
#include <exception>
#include <algorithm>

#define DIRS_SIZE 6
static Coords _DIRECTIONS[DIRS_SIZE] = { Coords(1, 0), // E
Coords(1, -1), // NE
Coords(0, -1), // NW
Coords(-1, 0), // W
Coords(-1, 1), // SW
Coords(0, 1) }; // SE

Coords get_direction(int index)
{
	return _DIRECTIONS[index];
}

Coords get_direction(std::string direction)
{
	int index = get_dir_index(direction);
	if (index < 0)
		throw std::logic_error("Stringa non valida!");
	else
		return _DIRECTIONS[index];
}

int get_dir_index(std::string direction)
{
	if (direction == "e")
		return 0;
	if (direction == "ne")
		return 1;
	if (direction == "nw")
		return 2;
	if (direction == "w")
		return 3;
	if (direction == "sw")
		return 4;
	if (direction == "se")
		return 5;
	return -1;
}

CoordsVec get_neighbors(const Coords& c)
{
	CoordsVec vec;
	for (int i = 0; i < DIRS_SIZE; ++i)
	{
		Coords c2 = c + _DIRECTIONS[i];
		vec.push_back(c2);
	}
	return vec;
}

#define PIECES_SIZE 7
static Piece _PIECES[PIECES_SIZE] = { Piece(std::vector < int > { 0, 3 }, "--"),
Piece(std::vector < int > { 2, 5 }, "\\"),
Piece(std::vector < int > { 1, 4 }, "/"),
Piece(std::vector < int > { 0, 2, 3, 5 }, "-\\-"),
Piece(std::vector < int > { 0, 1, 3, 4 }, "-/-"),
Piece(std::vector < int > { 1, 2, 4, 5 }, "X"),
Piece(std::vector < int > { 0, 1, 2, 3, 4, 5 }, "*") };

Piece make_piece(int index)
{
	if (index < 0 || index >= PIECES_SIZE)
		throw std::logic_error("Invalid index");
	return _PIECES[index].clone();
}


Piece make_piece(std::vector<int> dirs)
{
	for (int i = 0; i < PIECES_SIZE; ++i)
	{
		Piece p = _PIECES[i];
		if (p.getDirs() == dirs)
			return p.clone();
	}
	throw std::logic_error("Piece not found");
}