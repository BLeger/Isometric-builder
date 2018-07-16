#include "../../includes/World/WorldMap.hpp"

WorldMap::WorldMap(int size_x, int size_y) : m_size_x(size_x), m_size_y(size_y) {

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			m_tiles.push_back(Tile{TileType::Tile_1x1, "tile"});
		}
	}

	Building b{ 1, 1, "tree" };
	addBuilding(b, 2, 2);
}

Tile& WorldMap::getTile(int x, int y) {
	return m_tiles.at(m_size_x * y + x);
}

void WorldMap::display(Ndk::World& world)
{
	float scale = 0.5f;
	float tile_width = 133.f;
	float tile_height = 80.f;

	float width_offset = 0.0f;
		
	int i = 0;

	for (int y = 0; y < m_size_y; y++) {
		// y coordinate of the line
		float yPos = (y / 2.f * scale * tile_height);

		for (int x = 0; x < m_size_x; x++) {
			Tile& tile = getTile(x, y);
			TileType type = tile.getType();

			float height_offset = tile.getHeightOffset();

			if (type == TileType::Tile_1x1 || type == TileType::Object_NxN_Attach) {
				Nz::SpriteRef spr;
				spr = Nz::Sprite::New(tile.getMaterial());
				spr->SetOrigin(Nz::Vector3f(0.f, tile_height, 0.f));
				if (x == 2 && y == 2) {
					spr->SetOrigin(Nz::Vector3f(0.f, 160, 0.f));
				}

				// Create the entity
				Ndk::EntityHandle test = world.CreateEntity();
				Ndk::NodeComponent &nodeComp = test->AddComponent<Ndk::NodeComponent>();
				Ndk::GraphicsComponent &GraphicsComp = test->AddComponent<Ndk::GraphicsComponent>();
				GraphicsComp.Attach(spr, i);
				i++;

				nodeComp.SetScale(scale, scale);

				// x coordinate of the tile
				float xPos = width_offset + (x * scale * tile_width);
				if (y % 2 != 0) {
					// Odd line are shifted
					xPos += 0.5 * scale*tile_width;
				}

				nodeComp.SetPosition(xPos, yPos + height_offset);
			}
		}
	}
}

void WorldMap::addBuilding(Building b, int x, int y) {
	Nz::Vector2<int> buildingSize = b.getSize();

	// Get the coordinates of all the cell occupied by the building
	std::vector<Nz::Vector2<int>> cells = Isometric::square(x, y, buildingSize.x, buildingSize.y);

	// All the cells occupied by the building are converted to body cells
	for (Nz::Vector2<int> cell : cells) {
		Tile& bodyTile = getTile(cell.x, cell.y);
		bodyTile.setType(TileType::Object_NxN_Body);
	}

	// The main cell of the building displays the building
	Tile& attachTile = getTile(x, y);
	attachTile.setType(TileType::Object_NxN_Attach);
	attachTile.setMaterialName(b.getMaterialName());
}
