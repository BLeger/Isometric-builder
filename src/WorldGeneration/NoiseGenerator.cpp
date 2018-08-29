#include "../../includes/WorldGeneration/NoiseGenerator.hpp"

NoiseGenerator::NoiseGenerator(Nz::Vector2ui size) : m_size(size)
{
	// Generate a height map for tiles
	{
		Nz::Perlin perlin = initPerlin();
		
		std::vector<Nz::Vector2ui> elevatedTiles;

		float freq = 1.f;
		for (float y = 0; y < size.y; y++) {
			for (float x = 0; x < size.x; x++) {
				float nx = x / size.x - 0.5f;
				float ny = y / size.y - 0.5f;

				float height = perlin.Get(1.f * nx, 1.f * ny, 1.f) + 0.5f * perlin.Get(2.f * nx, 2.f * ny, 1.f) + 0.25f * perlin.Get(4.f * nx, 4.f * ny, 1.f);

				TileDef tile = GRASS;
				int elevation = 0;
				if (height < -0.3f) {
					tile = DEEP_WATER;
				}
				else if (height < -0.2f) {
					tile = WATER;
				}
				else if (height < -0.15f) {
					tile = SAND;
				}

				if (height > 0.35f) {
					elevation = 1;
					elevatedTiles.push_back(Nz::Vector2ui{ (unsigned int)x, (unsigned int)y });
				}

				m_heightMap.push_back(elevation);
				m_map.push_back(tile);
			}
		}

		for (auto position : elevatedTiles) {
			std::vector<Nz::Vector2ui> surrondings = Isometric::getSurroundingTiles(position);

			for (auto p : surrondings) {
				if (p.x >= 0 && p.x < m_size.x && p.y >= 0 && p.y < m_size.y) {
					if (getHeight(p) == getHeight(position) - 1)
						m_envMap.insert(std::make_pair(p, ROCK));
				}
			}
		}
	}

	
	

	// Generating trees
	Nz::Perlin perlin = initPerlin();

	float freq = 10.f;
	for (float y = 0; y < size.y; y++) {
		for (float x = 0; x < size.x; x++) {
			Nz::Vector2ui position { (unsigned int)x, (unsigned int)y };
			if (getTile(position) == GRASS) {
				float nx = x / size.x - 0.5f;
				float ny = y / size.y - 0.5f;

				float height = perlin.Get(10.f * nx, 10.f * ny, 1.f);
				if (height > 0.25f) {
					int random = randomInt(0, 100);
					if (random < 20) {
						//m_envMap.insert(std::make_pair(position, TREE));
					}
				}
			}
		}
	}
}

TileDef NoiseGenerator::getTile(Nz::Vector2ui position)
{
	assert(position.x >= 0 && position.x < m_size.x);
	assert(position.y >= 0 && position.y < m_size.y);

	return m_map.at(m_size.x * position.y + position.x);
}

void NoiseGenerator::setTile(Nz::Vector2ui position, TileDef tile)
{
	assert(position.x >= 0 && position.x < m_size.x);
	assert(position.y >= 0 && position.y < m_size.y);

	m_map[m_size.x * position.y + position.x] = tile;
}

int NoiseGenerator::getHeight(Nz::Vector2ui position)
{
	assert(position.x >= 0 && position.x < m_size.x);
	assert(position.y >= 0 && position.y < m_size.y);

	return m_heightMap.at(m_size.x * position.y + position.x);
}

bool NoiseGenerator::hasEnvTile(Nz::Vector2ui position)
{
	return m_envMap.find(position) != m_envMap.end();
}

TileDef NoiseGenerator::getEnvTile(Nz::Vector2ui position)
{
	assert(hasEnvTile(position));
	return m_envMap.at(position);
}

Nz::Perlin NoiseGenerator::initPerlin()
{
	// Seeding the perlin
	int seed = randomInt(0, 222248877);

	Nz::Perlin perlin{ (unsigned int)seed };
	return perlin;
}

int NoiseGenerator::randomInt(int min, int max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(min, max);

	int random = uni(rng);
	return random;
}
