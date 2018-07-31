#include "../../includes/World/WorldMap.hpp"

WorldMap::WorldMap(Nz::Vector2ui size, Ndk::World& world) : m_size(size), m_worldRef(world) {

	Nz::MaterialRef tileset = Nz::Material::New();
	tileset->LoadFromFile("tiles/tileset.png");
	tileset->EnableBlending(true);
	tileset->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	tileset->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	tileset->EnableDepthWrite(false);

	m_tileMap = Nz::TileMap::New(size, Nz::Vector2f{ (float)mainTileSize.x, (float)mainTileSize.y });
	m_tileMap->EnableIsometricMode(true);

	m_tileMap->SetMaterial(0, tileset);

	m_tileMapEntity = world.CreateEntity();

	Ndk::NodeComponent &nodeComp = m_tileMapEntity->AddComponent<Ndk::NodeComponent>();
	nodeComp.SetPosition(Nz::Vector3f{ m_cameraOffset.x, m_cameraOffset.y, 0.f });

	Ndk::GraphicsComponent &graphicsComp = m_tileMapEntity->AddComponent<Ndk::GraphicsComponent>();
	graphicsComp.Attach(m_tileMap);

	for (int x = 0; x < m_size.x; x++) {
		for (int y = 0; y < m_size.y; y++) {
			m_tiles.push_back(TileData{ TileType::SIMPLE_TILE, 0});
		}
	}
	
	update();
}


TileData& WorldMap::getTile(Nz::Vector2ui position) {
	return m_tiles.at(m_size.x * position.y + position.x);
}

void WorldMap::addEnvironmentTile(Nz::Vector2ui position, Nz::SpriteRef sprite)
{
	if (m_entities.find(position) != m_entities.end()) {
		// There is already a tile at this place
		std::cout << "Err: tile already occupied" << std::endl;
		return;
	}

	// Update the tile's data
	getTile(position).type = TileType::ENV_TILE;

	Ndk::EntityHandle entity = m_worldRef.CreateEntity();
	Ndk::NodeComponent &nc = entity->AddComponent<Ndk::NodeComponent>();

	Nz::Vector2i pixelPosition = Isometric::getCellPixelCoordinates(position, m_scale);
	nc.SetPosition(m_cameraOffset);

	Ndk::GraphicsComponent &gc = entity->AddComponent<Ndk::GraphicsComponent>();
	gc.Attach(sprite);

	EnvironmentTileComponent &t = entity->AddComponent<EnvironmentTileComponent>();
	m_entities.insert(std::make_pair(position, entity));
}

void WorldMap::removeEnvironmentTile(Nz::Vector2ui position)
{
	if (m_entities.find(position) == m_entities.end()) {
		// There is already a tile at this place
		std::cout << "Err: this tile is not occupied" << std::endl;
		return;
	}

	// Update the tile's data
	TileData& tile = getTile(position);

	if (tile.type != TileType::ENV_TILE) {
		std::cout << "Err: this tile is not environment" << std::endl;
		return;
	}

	tile.type = TileType::SIMPLE_TILE;

	// Detach and destroy the entity
	Ndk::EntityHandle entity = m_entities.at(position);
	Ndk::GraphicsComponent &gc = entity->GetComponent<Ndk::GraphicsComponent>();
	gc.Clear();
	entity->Kill();

	// Remove the entity from the map
	m_entities.erase(m_entities.find(position));
}

void WorldMap::update()
{
	Ndk::NodeComponent &tileMapNode = m_tileMapEntity->GetComponent<Ndk::NodeComponent>();
	tileMapNode.SetScale(m_scale);
	tileMapNode.SetPosition(m_cameraOffset);

	for (unsigned int y = 0; y < m_size.y; y++) {
		for (unsigned int x = 0; x < m_size.x; x++) {
			Nz::Vector2ui position{ x, y };
			TileData& tile = getTile(position);
			
			// Display or not the tile
			if (tile.type == TileType::SIMPLE_TILE || tile.type == TileType::ENV_TILE) {
				Nz::Rectui textureRect{ tile.tileMaterialIndex * mainTileSize.x, 0u, mainTileSize.x, mainTileSize.y };
				m_tileMap->EnableTile(position, textureRect);
			}
			else {
				m_tileMap->DisableTile(position);
			}
		}
	}

	auto it = m_entities.begin();
	while (it != m_entities.end()) {
		Nz::Vector2ui tilePosition = (*it).first;
		Ndk::EntityHandle entity = (*it).second;

		Nz::Vector2i pixelPosition = Isometric::getCellPixelCoordinates(tilePosition, m_scale, m_cameraOffset);
		Ndk::NodeComponent &nc = entity->GetComponent<Ndk::NodeComponent>();
		nc.SetScale(m_scale);
		nc.SetPosition(Nz::Vector3f{ (float)pixelPosition.x, (float)pixelPosition.y, 0.f });

		it++;
	}
}

void WorldMap::addBuilding(Building b, int x, int y) {
	/*Nz::Vector2<int> buildingSize = b.getSize();

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

	m_buildings.insert(std::make_pair(coordinates{ x, y }, b));*/
}

bool WorldMap::changeTile(int x, int y, TileData newTileData)
{
	if (false) {
		// Condition d'impossibilité de changement
		return false;
	}

	//Tile& tile = getTile(x, y);
	//tile.setTileDatas(newTileData);

	return true;
}

float WorldMap::getScale()
{
	return m_scale;
}

void WorldMap::zoom(int delta)
{
	m_scale += delta * 0.1;

	if (m_scale > m_maxScale)
		m_scale = m_maxScale;

	if (m_scale < m_minScale)
		m_scale = m_minScale;

	update();
}

Nz::Vector2f WorldMap::getCameraOffset()
{
	return m_cameraOffset;
}

