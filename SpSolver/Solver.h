#pragma once

#include <functional>
#include <vector>
#include "Grid.h"
#include "Piece.h"
#include "Utils.h"

using SolverCallback = std::function<void(int)>;

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

	void set_callback(SolverCallback);

private:
	Grid* g;
	PieceVec pieces;
	SolverCallback callback;
};

