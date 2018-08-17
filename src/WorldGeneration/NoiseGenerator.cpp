#include "../../includes/WorldGeneration/NoiseGenerator.hpp"

NoiseGenerator::NoiseGenerator(Nz::Vector2ui size) : m_size(size)
{
	// Seeding the perlin
	int min = 0;
	int max = 222248877;

	std::random_device rd;
	std::mt19937 rng(rd());    
	std::uniform_int_distribution<int> uni(min, max);
	int seed = uni(rng);

	Nz::Perlin perlin{ (unsigned int)seed };

	std::map<Nz::Vector2ui, float> heightMap;

	// Generate a height map
	float freq = 1.f;
	for (float y = 0; y < size.y; y++) {
		for (float x = 0; x < size.x; x++) {
			float nx = x / size.x - 0.5f;
			float ny = y / size.y - 0.5f;

			float height = perlin.Get(1.f * nx, 1.f * ny, 1.f)  + 0.5f * perlin.Get(2.f * nx, 2.f * ny, 1.f) + 0.25f * perlin.Get(4.f * nx, 4.f * ny, 1.f);
			heightMap.insert(std::make_pair(Nz::Vector2ui{(unsigned int)x, (unsigned int)y}, height));

			int tile = -1;
			if (height < -0.3f) {
				tile = DEEP_WATER;
			}
			else if (height < -0.2f) {
				tile = WATER;
			}
			else if (height < -0.15f) {
				tile = SAND;
			}
			else {
				tile = GRASS;
			}

			m_map.push_back(tile);
		}
	}
}

int NoiseGenerator::getTile(Nz::Vector2ui position)
{
	return m_map.at(m_size.x * position.y + position.x);
}

void NoiseGenerator::setTile(Nz::Vector2ui position, int tile)
{
	m_map[m_size.x * position.y + position.x] = tile;
}