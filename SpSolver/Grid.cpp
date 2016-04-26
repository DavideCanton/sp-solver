#include "Grid.h"

bool Grid::is_full() const
{
	for (auto& pair : content)
		if (pair.second.empty)
			return false;
	return true;
}

bool Grid::place_piece(const Coords& c, const Piece& p)
{
	CellData& cd = content.find(c)->second;
	if (!cd.empty)
		return false;	
	cd.piece = &p;
	cd.empty = false;
	pieces.insert(std::make_pair(p, c));
	cover(c, p);
	return true;
}

bool Grid::remove_piece(const Piece& p)
{
	auto it = pieces.find(p);
	if (it == pieces.end()) // not present
		return false;

	const Coords& c = it->second;
	content[c].empty = true;
	content[c].piece = nullptr;
	pieces.erase(p);
	recompute_cover();

	return false;
}

int Grid::covered_count(const Coords& c, const Piece& p) const
{
	int cnt = 1;
	for (int dir : p.getDirs())
	{
		Coords dirc = get_direction(dir);
		Coords cur = c + dirc;
		while (this->contains(cur))
		{
			++cnt;
			cur += dirc;
		}
	}
	return cnt;
}

void Grid::empty()
{
	pieces.clear();
	for (auto& pair : content)
	{
		pair.second.empty = true;
		pair.second.piece = nullptr;
	}
}

void Grid::cover(const Coords& c, const Piece& p)
{
	for (auto dir : p.getDirs())
	{
		Coords direction = get_direction(dir);
		Coords cur = c + direction;
		while (true)
		{
			auto pair = content.find(cur);
			if (pair == content.end() || pair->second.piece)
				break;
			pair->second.empty = false;
			cur += direction;
		}
	}
}

void Grid::recompute_cover()
{
	for (auto& pair : content)
	{
		pair.second.empty = true;
		pair.second.piece = nullptr;
	}

	PieceVec pv;
	for (auto& pair : pieces)
		pv.push_back(pair.first);

	std::sort(pv.begin(), pv.end(), [](const Piece& p1, const Piece& p2) -> bool
	{
		return p1.get_arity() > p2.get_arity();
	});

	for (Piece& p : pv)
	{
		auto pair = pieces.find(p);
		Coords& c = pair->second;
		this->place_piece(c, pair->first);
	}
}