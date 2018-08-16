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
	//Nz::Simplex simplex{ (unsigned int)seed };

	float hmin = 2.f;
	float hmax = -2.f;

	// Generate a height map
	float freq = 0.5f;
	for (float y = 0; y < size.y; y++) {
		for (float x = 0; x < size.x; x++) {
			float nx = x / size.x - 0.5f;
			float ny = y / size.y - 0.5f;

			//std::cout << nx << " - " << ny << std::endl;
			//std::cout << perlin.Get(nx, ny, 1.f) << std::endl;
			float height = perlin.Get(freq * nx, freq * ny, 1.f);

			if (height < hmin)
				hmin = height;

			if (height > hmax)
				hmax = height;

			//std::cout << height << std::endl;
			if (height < -0.2f) {
				m_map.push_back(WATER);
			}
			else {
				m_map.push_back(GRASS);
			}
		}
	}

	std::cout << "Min : " << hmin << std::endl;
	std::cout << "Max : " << hmax << std::endl;


	
}

int NoiseGenerator::getTile(Nz::Vector2ui position)
{
	return m_map.at(m_size.x * position.y + position.x);
}

void NoiseGenerator::setTile(Nz::Vector2ui position, int tile)
{
	m_map[m_size.x * position.y + position.x] = tile;
}