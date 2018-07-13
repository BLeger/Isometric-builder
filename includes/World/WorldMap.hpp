#ifndef WORLD_MAP_H
#define WORLD_MAP_H

#include<vector>

#include "Tile.hpp"

class WorldMap {

public:
	WorldMap(int size_x, int size_y);

private:
	std::vector<Tile> tiles{};

	const int m_size_x;
	const int m_size_y;
};

#endif // !WORLD_MAP_H
