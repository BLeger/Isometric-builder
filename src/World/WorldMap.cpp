#include "../../includes/World/WorldMap.hpp"

WorldMap::WorldMap(int size_x, int size_y) : m_size_x(size_x), m_size_y(size_y) {

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			m_tiles.push_back(Tile{TileType::Tile_1x1});
		}
	}
}

Tile& WorldMap::getTile(int x, int y) {
	return m_tiles.at(m_size_x * y + x);
}

void WorldMap::display(Ndk::World& world)
{
	for (int y = 0; y < m_size_y; y++) {
		for (int x = 0; x < m_size_x; x++) {
			Tile& tile = getTile(x, y);
			Nz::SpriteRef spr;
			spr = Nz::Sprite::New(tile.getMaterial());
			

			Ndk::EntityHandle test = world.CreateEntity();
			Ndk::NodeComponent &nodeComp = test->AddComponent<Ndk::NodeComponent>();
			Ndk::GraphicsComponent &GraphicsComp = test->AddComponent<Ndk::GraphicsComponent>();
			GraphicsComp.Attach(spr);

			float scale = 0.5f;
			float tile_width = 128.f;
			float tile_height = 64.f;

			nodeComp.SetScale(scale, scale);
			float height = y / 2.f * scale * tile_height;
			float width = x * scale * tile_width;

			if (y % 2 != 0) {
				// Odd line
				width += 0.5 * scale*tile_width;
			}
			
			nodeComp.SetPosition(width, height);
		}
	}
}
