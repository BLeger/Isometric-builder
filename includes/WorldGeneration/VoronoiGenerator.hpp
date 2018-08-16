#ifndef VORONOI_GENERATOR_H
#define VORONOI_GENERATOR_H

#include <NDK/Application.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Utility.hpp>

#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>

class VoronoiGenerator {

public:
	VoronoiGenerator(Nz::Vector2ui size);

	int getTile(Nz::Vector2ui position);
	void setTile(Nz::Vector2ui position, int tile);

	bool randomCenter();
	int randomTile(Nz::Vector2ui position);
	int nearestCenterTile(Nz::Vector2ui position);
	float distanceToEdges(Nz::Vector2ui position);

private:
	float distance(Nz::Vector2ui p1, Nz::Vector2ui p2);

	Nz::Vector2ui m_size;

	std::vector<int> m_map;
	std::vector<Nz::Vector2ui> m_centers;

	const int CENTERS_PROPORTION = 10;
	const int WATER_PROPORTION = 15;

	const int GRASS = 0;
	const int WATER = 1;
};

#endif // !VORONOI_GENERATOR_H
