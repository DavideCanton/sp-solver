#ifndef LEVELDETECT_H
#define LEVELDETECT_H

#include "Grid.h"
#include "Utils.h"

std::pair<Grid, PieceVec> detectLevel(std::string fname, float factor);

#endif // LEVELDETECT_H