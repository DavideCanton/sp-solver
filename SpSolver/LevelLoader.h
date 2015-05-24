#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "Grid.h"
#include "Utils.h"

std::pair<Grid, PieceVec> load_level(std::string fname);

#endif // LEVELLOADER_H