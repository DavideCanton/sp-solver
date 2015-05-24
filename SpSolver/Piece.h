#pragma once

#include <string>
#include <ostream>
#include <vector>

class Piece
{
public:
	Piece(std::vector<int> dirs, std::string aspect);
	virtual ~Piece();
	
	const std::vector<int>& getDirs() const
	{
		return dirs;
	}

	int get_arity() const
	{
		return arity;
	}

	const std::string& get_aspect() const
	{
		return aspect;
	}

	friend std::ostream& operator<<(std::ostream& o, const Piece& p)
	{
		o << "Piece[" << p._id << "]" << " " << p.aspect;
		return o;
	}

	size_t get_hash() const
	{
		return _id;
	}

	Piece clone() const;

	bool operator==(const Piece& p) const
	{
		return _id == p._id;
	}

	bool operator!=(const Piece& p) const
	{
		return !(*this == p);
	}


private:
	static int ID;
	int _id;
	std::vector<int> dirs;
	std::string aspect;
	int arity;
};

namespace std
{
	template <>
	struct hash<Piece>
	{
		size_t operator()(const Piece& p) const
		{
			return p.get_hash();
		}
	};
}