#pragma once

#include <vector>
#include "Grid.h"
#include "Piece.h"
#include "Utils.h"

class Solver
{
public:
	Solver(Grid* g, const PieceVec& pieces) : g(g)
	{
		this->pieces = PieceVec(pieces);
	}

	~Solver()
	{
	}

	void solve();

private:
	Grid* g;
	PieceVec pieces;
};

