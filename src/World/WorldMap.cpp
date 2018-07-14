#include "../../includes/World/WorldMap.hpp"

WorldMap::WorldMap(int size_x, int size_y) : m_size_x(size_x), m_size_y(size_y) {

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			m_tiles.push_back(Tile{});
		}
	}
}

Tile& WorldMap::getTile(int x, int y) {
	return m_tiles.at(m_size_x * y + x);
}