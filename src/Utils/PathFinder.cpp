#include "..\..\includes\Utils\PathFinder.hpp"

PathFinder::PathFinder(WorldMap & map) : m_worldMap(map)
{

}

std::deque<Nz::Vector2ui> PathFinder::findPath(Nz::Vector2ui start, Nz::Vector2ui end)
{
	priorityNodeQueue openList{};
	std::vector<Nz::Vector2ui> closedList{};
	std::map<Nz::Vector2ui, Nz::Vector2ui> predecessors{};

	// Adding the start node with a cost of 0 and it's heuristic cost to get to end
	node s{ start, 0, Isometric::manhattanStaggeredDistance(start, end), 0, Direction::NONE };
	openList.push(s);

	std::deque<Nz::Vector2ui> path{};

	while (!openList.empty()) {
		node best = openList.top();
		openList.pop();

		if (best.position == end) {
			Nz::Vector2ui currentPosition = best.position;
			path.push_front(currentPosition);
			while (currentPosition != start) {
				currentPosition = predecessors[currentPosition];
				path.push_front(currentPosition);
			}

			return path;
		}

		// Generating successors
		std::vector<Nz::Vector2ui> surrondings = Isometric::getSurroundingTiles(best.position);
		for (Nz::Vector2ui pos : surrondings) {
			if (m_worldMap.isPositionCorrect(pos) && m_worldMap.isPositionAvailable(pos) && std::find(closedList.begin(), closedList.end(), pos) == closedList.end()) {
				closedList.push_back(pos);
				// If the position has not been explored yet
				Direction dir = Isometric::getDirection(best.position, pos);
				int turns = best.numberOfTurns;
				if (dir != best.comeFrom && best.comeFrom != Direction::NONE) {
					turns++;
				}

				node newNode{ pos, best.base_cost + 1, Isometric::manhattanStaggeredDistance(pos, end), turns, dir };
				openList.push(newNode);
				predecessors.insert(std::make_pair(pos, best.position));
			}
		}
	}

	return path;
}
