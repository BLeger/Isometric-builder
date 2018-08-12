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

	for (unsigned int x = 0; x < m_size.x; x++) {
		for (unsigned int y = 0; y < m_size.y; y++) {
			m_tiles.push_back(TileData{ TileType::SIMPLE_TILE, 0});
		}
	}
	
	update();
}


TileData& WorldMap::getTile(Nz::Vector2ui position) {
	assert(position.x < m_size.x);
	assert(position.y < m_size.y);

	return m_tiles.at(m_size.x * position.y + position.x);
}

bool WorldMap::createEntity(Nz::Vector2ui position)
{
	if (!isPositionAvailable(position)) {
		std::cout << "Err: tile already occupied" << std::endl;
		return false;
	}
		
	// Update the tile's data
	getTile(position).type = TileType::ENV_TILE;

	Ndk::EntityHandle entity = m_worldRef.CreateEntity();
	Ndk::NodeComponent &nc = entity->AddComponent<Ndk::NodeComponent>();

	entity->AddComponent<Ndk::GraphicsComponent>();
	m_entities.insert(std::make_pair(position, entity));

	return true;
}

bool WorldMap::deleteEntity(Nz::Vector2ui position)
{
	if (isPositionAvailable(position)) {
		// There is already a tile at this place
		std::cout << "Err: this tile is not occupied" << std::endl;
		return false;
	}

	// Update the tile's data
	TileData& tile = getTile(position);

	if (tile.type != TileType::ENV_TILE) {
		std::cout << "Err: this tile is not environment" << std::endl;
		return false;
	}

	tile.type = TileType::SIMPLE_TILE;

	// Detach and destroy the entity
	Ndk::EntityHandle entity = m_entities.at(position);
	Ndk::GraphicsComponent &gc = entity->GetComponent<Ndk::GraphicsComponent>();
	gc.Clear();
	entity->Kill();

	// Remove the entity from the map
	m_entities.erase(m_entities.find(position));

	return true;
}

void WorldMap::addEnvironmentTile(Nz::Vector2ui position, Nz::SpriteRef sprite)
{
	if (createEntity(position)) {
		Ndk::EntityHandle& entity = m_entities.at(position);
		Ndk::GraphicsComponent &gc = entity->GetComponent<Ndk::GraphicsComponent>();
		gc.Attach(sprite, position.y);

		entity->AddComponent<EnvironmentTileComponent>();
	}
}

void WorldMap::removeEnvironmentTile(Nz::Vector2ui position)
{
	deleteEntity(position);
}

void WorldMap::addWall(Nz::Vector2ui position)
{
	if (createEntity(position)) {
		Ndk::EntityHandle& entity = m_entities.at(position);

		entity->AddComponent<WallComponent>(position);
	}

	updateSurrondingsWalls(position);
}

void WorldMap::removeWall(Nz::Vector2ui position)
{
	deleteEntity(position);
	updateSurrondingsWalls(position);
}

bool WorldMap::isWall(Nz::Vector2ui position)
{
	if (!isPositionCorrect(position) || isPositionAvailable(position))
		return false;

	Ndk::EntityHandle& entity = m_entities.at(position);
	return entity->HasComponent<WallComponent>();
}

void WorldMap::updateSurrondingsWalls(Nz::Vector2ui position)
{
	std::vector<Nz::Vector2ui> surrondings = Isometric::getSurroundingTiles(position);

	for (Nz::Vector2ui pos : surrondings) {
		if (isWall(pos)) {
			Ndk::EntityHandle& entity = m_entities.at(pos);
			WallComponent &wall = entity->GetComponent<WallComponent>();
			wall.m_needsUpdate = true;
		}
	}
}

void WorldMap::addWalker(Nz::Vector2ui position, Nz::SpriteRef& sprite)
{
	Ndk::EntityHandle entity = m_worldRef.CreateEntity();
	Ndk::NodeComponent &nc = entity->AddComponent<Ndk::NodeComponent>();

	Nz::Vector2ui pixelPosition = Isometric::getCellPixelCoordinates(position, m_scale);
	nc.SetPosition(m_cameraOffset);

	Ndk::GraphicsComponent &gc = entity->AddComponent<Ndk::GraphicsComponent>();
	entity->AddComponent<WalkerComponent>(position);
	AnimationComponent &ac = entity->AddComponent<AnimationComponent>(sprite, Nz::Vector2f{ 43.f, 64.f });

	gc.Attach(ac.getSprite());
	ac.enable();
	m_walkers.push_back(entity);
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

		Nz::Vector2ui pixelPosition = Isometric::getCellPixelCoordinates(tilePosition, m_scale, m_cameraOffset);
		Ndk::NodeComponent &nc = entity->GetComponent<Ndk::NodeComponent>();
		nc.SetScale(m_scale);
		nc.SetPosition(Nz::Vector3f{ (float)pixelPosition.x, (float)pixelPosition.y, 0.f });

		it++;
	}
}

bool WorldMap::isPositionCorrect(Nz::Vector2ui position)
{
	return position.x >= 0 && position.y >= 0 && position.x < m_size.x && position.y < m_size.y;
}

bool WorldMap::isPositionAvailable(Nz::Vector2ui position)
{
	if (!isPositionCorrect(position))
		return false;

	return m_entities.find(position) == m_entities.end();
}

bool WorldMap::isWalkable(Nz::Vector2ui position)
{
	std::cerr << "isWalkable function not implemented";
	return true;
}

void WorldMap::addBuilding(Nz::Vector2ui position, std::string name, Nz::Vector2ui size) 
{
	if (!isPositionAvailable(position)) {
		std::cout << "Err: tile already occupied" << std::endl;
		return;
	}

	// Update the data of all the tiles below the building
	std::vector<Nz::Vector2ui> cells = Isometric::square(position, size);
	for (Nz::Vector2ui pos : cells) {
		getTile(pos).type = TileType::BUILDING_BODY;
		// TODO : Add a ref to the building root
	}

	getTile(position).type = TileType::BUILDING_ROOT;

	Ndk::EntityHandle entity = m_worldRef.CreateEntity();
	entity->AddComponent<Ndk::NodeComponent>();
	entity->AddComponent<Ndk::GraphicsComponent>();
	entity->AddComponent<BuildingComponent>(position, size, name);

	m_buildings.insert(std::make_pair(position, entity));
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

void WorldMap::zoom(float delta)
{
	m_scale += delta * 0.1f;

	if (m_scale > m_maxScale)
		m_scale = m_maxScale;

	if (m_scale < m_minScale)
		m_scale = m_minScale;

	update();
}

void WorldMap::moveCamera(Nz::Vector2f offset)
{
	m_cameraOffset += offset;
}

Nz::Vector2f WorldMap::getCameraOffset()
{
	return m_cameraOffset;
}

