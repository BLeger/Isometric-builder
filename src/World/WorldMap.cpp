#include "../../includes/World/WorldMap.hpp"

WorldMap::WorldMap(Nz::Vector2i size, Ndk::World& world) : m_size(size) {

	Nz::MaterialRef tileset = Nz::Material::New();
	tileset->LoadFromFile("tiles/tileset.png");
	tileset->EnableBlending(true);
	tileset->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	tileset->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	tileset->EnableDepthWrite(false);

	m_tileMap = Nz::TileMap::New(Nz::Vector2ui{ 10, 10 }, Nz::Vector2f{ (float)m_tileSize.x, (float)m_tileSize.y });
	m_tileMap->EnableIsometricMode(true);

	m_tileMap->SetMaterial(0, tileset);
	Nz::Rectui tileRectGrass{ 0 * m_tileSize.x, 0u, m_tileSize.x, m_tileSize.y };
	Nz::Rectui tileRectWater{ 1 * m_tileSize.x, 0u, m_tileSize.x, m_tileSize.y };
	m_tileMap->EnableTiles(tileRectGrass);
	m_tileMap->EnableTile(Nz::Vector2ui{ 1, 1 }, tileRectWater);

	Ndk::EntityHandle m_entity = world.CreateEntity();
	Ndk::NodeComponent &nodeComp = m_entity->AddComponent<Ndk::NodeComponent>();
	Ndk::GraphicsComponent &GraphicsComp = m_entity->AddComponent<Ndk::GraphicsComponent>();
	GraphicsComp.Attach(m_tileMap);
}


Tile& WorldMap::getTile(int x, int y) {
	return m_tiles.at(m_size.x * y + x);
}

void WorldMap::display(Ndk::World& world)
{
	int drawingOrder = 0;

	for (int y = 0; y < m_size.y; y++) {
		for (int x = 0; x < m_size.x; x++) {
			Tile& tile = getTile(x, y);
			float height_offset = tile.getHeightOffset();

			tile.setScale(m_scale);

			float xPos = m_width_offset + (x * m_scale * m_tileSize.x);
			float yPos = (y / 2.f * m_scale * m_tileSize.y);

			if (y % 2 != 0) {
				// Odd line are shifted
				xPos += 0.5 * m_scale*m_tileSize.x;
			}

			tile.setPosition(Nz::Vector2f(xPos, yPos + height_offset));
		}
	}

	auto it = m_buildings.begin();
	while (it != m_buildings.end()) {
		coordinates position = (*it).first;
		Building b = (*it).second;

		float height_offset = b.getHeightOffset();
		std::cout << height_offset << std::endl;

		float xPos = m_width_offset + (position.x * m_scale * m_tileSize.x);
		float yPos = (position.y / 2.f * m_scale * m_tileSize.y);

		if (position.y % 2 != 0) {
			// Odd line are shifted
			xPos += 0.5 * m_scale*m_tileSize.x;
		}

		b.setScale(m_scale);
		b.setPosition(Nz::Vector2f(xPos, yPos + height_offset));

		it++;
	}
}

void WorldMap::addBuilding(Building b, int x, int y) {
	Nz::Vector2<int> buildingSize = b.getSize();

	// Get the coordinates of all the cell occupied by the building
	std::vector<Nz::Vector2<int>> cells = Isometric::square(Nz::Vector2i(x, y), buildingSize.x, buildingSize.y);

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

