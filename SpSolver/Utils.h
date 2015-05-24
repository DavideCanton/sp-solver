#ifndef UTILS_H
#define UTILS_H

#include "Piece.h"
#include "Coords.h"
#include <vector>
#include <string>
#include "Grid.h"

using CoordsVec = std::vector < Coords >;
using PieceVec = std::vector < Piece >;

Coords get_direction(int index);
Coords get_direction(std::string direction);
int get_dir_index(std::string direction);

CoordsVec get_neighbors(const Coords& c);

Piece make_piece(int index);
Piece make_piece(std::vector<int> dirs);

#endif // UTILS_H