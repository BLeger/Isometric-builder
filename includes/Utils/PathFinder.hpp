#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "../World/WorldMap.hpp"
#include "Direction.hpp"

#include <algorithm>

struct node{
	Nz::Vector2ui position;
	float base_cost;
	float heuristic_cost;
	int numberOfTurns;
	Direction comeFrom;
};

class CompareNodes {
public:
	bool operator() (const node& lhs, const node&rhs) const
	{
		return (lhs.base_cost + lhs.heuristic_cost + (lhs.numberOfTurns * 0) > rhs.base_cost + rhs.heuristic_cost + (rhs.numberOfTurns * 0));
	}
};

class PathFinder {

typedef std::priority_queue<node, std::vector<node>, CompareNodes> priorityNodeQueue;

public:
	PathFinder(WorldMap& map);

	std::deque<Nz::Vector2ui> findPath(Nz::Vector2ui start, Nz::Vector2ui end);

	
private:
	WorldMap& m_worldMap;
};

#endif // !PATH_FINDER_H
