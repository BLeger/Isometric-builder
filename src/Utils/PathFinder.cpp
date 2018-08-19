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
	node s{ start, 0, Isometric::manhattanDistance(start, end) };
	openList.push(s);

	std::cout << (Nz::Vector2ui{ 0, 0 } == Nz::Vector2ui{ 0, 0 }) << std::endl;

	std::deque<Nz::Vector2ui> path{};

	while (!openList.empty()) {
		node best = openList.top();
		std::cout << best.position.x << "- " << best.position.y << std::endl;
		openList.pop();

		if (best.position == end) {
			// Best path found
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
			if (std::find(closedList.begin(), closedList.end(), pos) == closedList.end()) {
				// If the position has not been explored yet
				node newNode{ pos, best.base_cost + 1, Isometric::manhattanDistance(pos, end) };
				openList.push(newNode);
				predecessors.insert(std::make_pair(pos, best.position));
			}
		}

		closedList.push_back(best.position);
	}

	return path;
}
