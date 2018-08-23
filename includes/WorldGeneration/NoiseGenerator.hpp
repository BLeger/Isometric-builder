#ifndef NOISE_GENERATOR_H
#define NOISE_GENERATOR_H

#include <NDK/Application.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/Noise/Perlin.hpp>

#include "../Config/Tiles.hpp"
#include "../Config/Env.hpp"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>

class NoiseGenerator {

public:
	NoiseGenerator(Nz::Vector2ui size);

	int getTile(Nz::Vector2ui position);
	void setTile(Nz::Vector2ui position, int tile);

	bool hasEnvTile(Nz::Vector2ui position);
	int getEnvTile(Nz::Vector2ui position);

private:
	Nz::Perlin initPerlin();
	int randomInt(int min, int max);

	Nz::Vector2ui m_size;

	std::vector<int> m_map;
	std::map<Nz::Vector2ui, int> m_envMap;
};

#endif // !NOISE_GENERATOR_H
