#include "Solver.h"
#include <algorithm>
#include <iostream>

using ScoreCoordsPair = std::pair < int, Coords >;
using ScoreCoordsPairVec = std::vector < ScoreCoordsPair >;
using Place = std::pair < int, ScoreCoordsPairVec >;

auto NULL_PAIR = std::make_pair(-1, ScoreCoordsPairVec());

void Solver::solve()
{
	auto comparer = [](const Piece& p1, const Piece& p2) -> bool
	{
		return p1.get_arity() > p2.get_arity();
	};

	std::sort(pieces.begin(), pieces.end(), comparer);
	std::vector<Place> places(pieces.size());

	for (int it_count = 0;; ++it_count)
	{
		std::cout << "Iteration " << it_count << std::endl;
		std::fill(places.begin(), places.end(), NULL_PAIR);

		int cur_piece = 0;

		do
		{
			if (cur_piece == pieces.size())
				--cur_piece;
			if (cur_piece < 0)
			{
				g->empty();
				break;
			}

			Piece& piece = pieces.at(cur_piece);
			Coords cell_max;

			if (places[cur_piece].first < 0)
			{
				ScoreCoordsPairVec& cells_max = places[cur_piece].second;
				for (auto& pairs : g->get_content())
				{
					const Coords& available = pairs.first;
					if (!pairs.second.empty)
						continue;
					int cnt = g->covered_count(available, piece);
					cells_max.push_back(std::make_pair(cnt, available));
				}
				std::sort(cells_max.begin(), cells_max.end(), [](const ScoreCoordsPair& p1, const ScoreCoordsPair& p2) -> bool
				{
					return p1.first > p2.first;
				});
				places[cur_piece].first = 1;
				cell_max = cells_max[0].second;
			}
			else
			{
				g->remove_piece(piece);
				int ind;
				ScoreCoordsPairVec cells_max;
				std::tie(ind, cells_max) = places[cur_piece];

				if (ind == cells_max.size())
				{
					--cur_piece;
					continue;
				}

				cell_max = cells_max[ind].second;
				++places[cur_piece].first;
				for (unsigned i = cur_piece + 1; i < places.size(); ++i)
					places[i] = NULL_PAIR;
			}

			g->place_piece(cell_max, piece);

			if (this->callback)
				this->callback(it_count);

			++cur_piece;

		} while (!g->is_full() || cur_piece != pieces.size());

		if (g->is_full())
			return;

		if (!std::next_permutation(pieces.begin(), pieces.end(), comparer))
			break;
	}

	if (!g->is_full())
		g->empty();
}

void Solver::set_callback(SolverCallback cb)
{
	this->callback = cb;
}
