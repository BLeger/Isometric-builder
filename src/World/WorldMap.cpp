#include "../../includes/World/WorldMap.hpp"

WorldMap::WorldMap(int size_x, int size_y) : m_size_x(size_x), m_size_y(size_y) {

	

}

void WorldMap::generateMap(Ndk::World& world, TileData& defaultTile) {
	int drawingOrder = 0;
	for (int i = 0; i < m_size_x; i++) {
		for (int j = 0; j < m_size_y; j++) {
			m_tiles.push_back(Tile{ defaultTile, world, drawingOrder });
			drawingOrder++;
		}
	}
}

Tile& WorldMap::getTile(int x, int y) {
	return m_tiles.at(m_size_x * y + x);
}

void WorldMap::display(Ndk::World& world)
{
	int drawingOrder = 0;

	for (int y = 0; y < m_size_y; y++) {
		for (int x = 0; x < m_size_x; x++) {
			Tile& tile = getTile(x, y);
			float height_offset = tile.getHeightOffset();

			tile.setScale(m_scale);

			float xPos = m_width_offset + (x * m_scale * m_tile_width);
			float yPos = (y / 2.f * m_scale * m_tile_height);

			if (y % 2 != 0) {
				// Odd line are shifted
				xPos += 0.5 * m_scale*m_tile_width;
			}

			tile.setPosition(Nz::Vector2f(xPos, yPos));
		}
	}

	/*auto it = m_buildings.begin();
	while (it != m_buildings.end()) {
		coordinates position = (*it).first;
		Building b = (*it).second;

		TileData& tileData = b.getTileData();
		float height_offset = tileData.heightOffset;

		displaySprite(world, Isometric::createMaterial(b.getMaterialName()), position, height_offset, drawingOrder);
		drawingOrder++;

		it++;
	}*/
}

void WorldMap::displaySprite(Ndk::World& world, Nz::MaterialRef material, Nz::Vector2i position, float height_offset, int drawingOrder)
{
	/*Nz::SpriteRef spr;
	spr = Nz::Sprite::New(material);
	spr->SetOrigin(Nz::Vector3f(0.f, height_offset, 0.f));

	// Create the entity
	Ndk::EntityHandle test = world.CreateEntity();
	Ndk::NodeComponent &nodeComp = test->AddComponent<Ndk::NodeComponent>();
	Ndk::GraphicsComponent &GraphicsComp = test->AddComponent<Ndk::GraphicsComponent>();
	GraphicsComp.Attach(spr, drawingOrder);*/

	/*nodeComp.SetScale(m_scale, m_scale);

	// Coordinates of the tile
	float xPos = m_width_offset + (position.x * m_scale * m_tile_width);
	float yPos = (position.y / 2.f * m_scale * m_tile_height);

	if (position.y % 2 != 0) {
		// Odd line are shifted
		xPos += 0.5 * m_scale*m_tile_width;
	}

	nodeComp.SetPosition(xPos, yPos + height_offset);

	if (position.x == 0 && position.y == 0) {
		t = test;
	}*/
}

void WorldMap::addBuilding(Building b, int x, int y) {
	Nz::Vector2<int> buildingSize = b.getSize();

	// Get the coordinates of all the cell occupied by the building
	std::vector<Nz::Vector2<int>> cells = Isometric::square(x, y, buildingSize.x, buildingSize.y);

	// All the cells occupied by the building are converted to body cells
	for (Nz::Vector2<int> cell : cells) {
		Tile& bodyTile = getTile(cell.x, cell.y);
		//bodyTile.setType(TileType::Object_NxN_Body);
	}

	// The main cell of the building displays the building
	//Tile& attachTile = getTile(x, y);
	//attachTile.setType(TileType::Object_NxN_Attach);
	//attachTile.setTileDatas(b.getTileData());

	m_buildings.insert(std::make_pair(coordinates{ x, y }, b));
}

bool WorldMap::changeTile(int x, int y, TileData newTileData)
{
	if (false) {
		// Condition d'impossibilité de changement
		return false;
	}

	Tile& tile = getTile(x, y);
	tile.setTileDatas(newTileData);

	return true;
}

void WorldMap::zoom(int delta)
{
	m_scale += delta * 0.1;

	if (m_scale > m_max_scale)
		m_scale = m_max_scale;

	if (m_scale < m_min_scale)
		m_scale = m_min_scale;

}

void WorldMap::test()
{
	Ndk::NodeComponent& tt = t->GetComponent<Ndk::NodeComponent>();
	tt.SetPosition(200.f, 200.f);
	
}
