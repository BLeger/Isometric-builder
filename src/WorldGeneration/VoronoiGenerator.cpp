#include "../../includes/WorldGeneration/VoronoiGenerator.hpp"

VoronoiGenerator::VoronoiGenerator(Nz::Vector2ui size) : m_size(size)
{
	// First, generating the centers
	for (unsigned int y = 0; y < size.y; y++) {
		for (unsigned int x = 0; x < size.x; x++) {
			Nz::Vector2ui position{x, y};
			if (randomCenter()) {
				m_map.push_back(randomTile(position));
				m_centers.push_back(position);
			}
			else {
				m_map.push_back(-1);
			}
		}
	}

	// Then fill the map
	for (unsigned int y = 0; y < size.y; y++) {
		for (unsigned int x = 0; x < size.x; x++) {
			Nz::Vector2ui position{ x, y };

			int tile = getTile(position);
			if (tile == -1) {
				setTile(position, nearestCenterTile(position));
			}
		}
	}
}

int VoronoiGenerator::getTile(Nz::Vector2ui position)
{
	return m_map.at(m_size.x * position.y + position.x);
}

void VoronoiGenerator::setTile(Nz::Vector2ui position, int tile)
{
	m_map[m_size.x * position.y + position.x] = tile;
}

bool VoronoiGenerator::randomCenter()
{
	int min = 0;
	int max = 1000;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);

	int random = uni(rng);

	if (random <= CENTERS_PROPORTION)
		return true;

	return false;
}

int VoronoiGenerator::randomTile(Nz::Vector2ui position)
{
	int min = 0;
	int max = 1000;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);

	float distToEdge = distanceToEdges(position);
	float relativeToEdge = distToEdge / std::max(m_size.x, m_size.y);
	std::cout << relativeToEdge << std::endl;
	int random = uni(rng);

	if (random <= WATER_PROPORTION / relativeToEdge) {
		return WATER;
	}
	else {
		return GRASS;
	}
}

int VoronoiGenerator::nearestCenterTile(Nz::Vector2ui position)
{
	float minDistance = 999999999999999999.f;
	Nz::Vector2ui nearestCenter{ 0, 0 };

	for (Nz::Vector2ui center : m_centers) {
		float dist = distance(position, center);
		if (dist < minDistance) {
			minDistance = dist;
			nearestCenter = center;
		}
	}

	return getTile(nearestCenter);
}

float VoronoiGenerator::distanceToEdges(Nz::Vector2ui position)
{
	std::vector<int> distances;

	distances.push_back(position.x);
	distances.push_back(position.y);
	distances.push_back(m_size.x - position.x);
	distances.push_back(m_size.y - position.y);

	int minDist = m_size.x + m_size.y;

	for (int dist : distances) {
		if (dist < minDist)
			minDist = dist;
	}

	return minDist;
}

float VoronoiGenerator::distance(Nz::Vector2ui p1, Nz::Vector2ui p2)
{
	return sqrt(pow((int)p2.x - (int)p1.x, 2) + pow((int)p2.y - (int)p1.y, 2));
}
