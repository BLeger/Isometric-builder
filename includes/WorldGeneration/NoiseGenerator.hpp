#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include <NDK/Application.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/Noise/Perlin.hpp>

#include "../Config/Tiles.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>

class NoiseGenerator {

public:
	NoiseGenerator(Nz::Vector2ui size);

	int getTile(Nz::Vector2ui position);
	void setTile(Nz::Vector2ui position, int tile);

private:

	Nz::Vector2ui m_size;

	std::vector<int> m_map;
};

#endif // !NOISE_GENERATOR_H
