#include "Piece.h"

Piece::Piece(std::vector<int> dirs, std::string aspect) : aspect(aspect), dirs(dirs)
{
	arity = dirs.size() / 2;
	_id = ID++;
}

Piece Piece::clone() const
{
	Piece p2(*this);
	p2._id = ID++;
	return p2;
}

Piece::~Piece()
{
}

int Piece::ID = 0;