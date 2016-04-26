#pragma once

#include <unordered_map>
#include "Piece.h"
#include "Coords.h"
#include "Utils.h"
#include <algorithm>

struct CellData
{
	bool empty;
	const Piece* piece;

	CellData() : empty(true), piece(nullptr)
	{
	}

	explicit CellData(const Piece& p) : empty(false), piece(&p)
	{
	}

	explicit CellData(bool empty) : empty(empty), piece(nullptr)
	{
	}
};

const CellData GRID_EMPTY_CELL = CellData();
const CellData GRID_FILLED_CELL = CellData(false);
#define GRID_PIECE_CELL(p) CellData((p))

class Grid
{
public:
	Grid() : min_q(INT_MAX), max_q(INT_MIN), min_r(INT_MAX), max_r(INT_MIN)
	{
	}

	virtual ~Grid()
	{
	}

	bool contains(const Coords& c) const
	{
		return content.find(c) != content.end();
	}

	const CellData& operator[](const Coords& c) const
	{
		return content.find(c)->second;
	}

	void set_el(const Coords& c, const CellData& val)
	{
		content[c] = val;
		if (c.get_q() < min_q) min_q = c.get_q();
		if (c.get_q() > max_q) max_q = c.get_q();
		if (c.get_r() < min_r) min_r = c.get_r();
		if (c.get_r() > max_r) max_r = c.get_r();		
	}

	int get_min_q() const { return min_q; }

	int get_max_q() const { return max_q; }

	int get_min_r() const { return min_r; }

	int get_max_r() const { return max_r; }

	bool is_full() const;
	bool place_piece(const Coords& c, const Piece& p);
	bool remove_piece(const Piece& p);
	int covered_count(const Coords& c, const Piece& p) const;
	void empty();

	const std::unordered_map < Piece, Coords >& get_pieces() const
	{
		return pieces;
	}

	const std::unordered_map < Coords, CellData >& get_content() const
	{
		return content;
	}

private:
	std::unordered_map < Coords, CellData > content;
	std::unordered_map < Piece, Coords > pieces;
	int min_q, max_q, min_r, max_r;

	void cover(const Coords& c, const Piece& p);
	void recompute_cover();
};
