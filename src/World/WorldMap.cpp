#include "../../includes/World/WorldMap.hpp"

WorldMap::WorldMap(int size_x, int size_y) : m_size_x(size_x), m_size_y(size_y) {

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			m_tiles.push_back(Tile{TileType::Tile_1x1, "tile"});
		}
	}

	Tile& t = getTile(2, 2);
	t.setType(TileType::Object_NxN_Attach);
	t.setMaterialName("big_tile");

	Tile& t2 = getTile(3, 2);
	t2.setType(TileType::Object_NxN_Body);

	Tile& t3 = getTile(2, 1);
	t3.setType(TileType::Object_NxN_Body);

	Tile& t4 = getTile(2, 3);
	t4.setType(TileType::Object_NxN_Body);
}

Tile& WorldMap::getTile(int x, int y) {
	return m_tiles.at(m_size_x * y + x);
}

void WorldMap::display(Ndk::World& world)
{
	float scale = 0.5f;
	float tile_width = 128.f;
	float tile_height = 64.f;

	for (int y = 0; y < m_size_y; y++) {
		// y coordinate of the line
		float yPos = y / 2.f * scale * tile_height;

		for (int x = 0; x < m_size_x; x++) {
			Tile& tile = getTile(x, y);
			TileType type = tile.getType();

			if (type == TileType::Tile_1x1 || type == TileType::Object_NxN_Attach) {
				Nz::SpriteRef spr;
				spr = Nz::Sprite::New(tile.getMaterial());

				// Create the entity
				Ndk::EntityHandle test = world.CreateEntity();
				Ndk::NodeComponent &nodeComp = test->AddComponent<Ndk::NodeComponent>();
				Ndk::GraphicsComponent &GraphicsComp = test->AddComponent<Ndk::GraphicsComponent>();
				GraphicsComp.Attach(spr);

				nodeComp.SetScale(scale, scale);

				// x coordinate of the tile
				float xPos = x * scale * tile_width;
				if (y % 2 != 0) {
					// Odd line are shifted
					xPos += 0.5 * scale*tile_width;
				}

				nodeComp.SetPosition(xPos, yPos);
			}
		}
	}
}

void WorldMap::addBuilding(Building b, int x, int y) {
	Nz::Vector2<int> buildingSize = b.getSize();

	Tile& t = getTile(x, y);
	t.setType(TileType::Object_NxN_Attach);
	t.setMaterialName(b.getMaterialName());
}
