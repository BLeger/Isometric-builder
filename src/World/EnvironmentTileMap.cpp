#include "..\..\includes\World\EnvironmentTileMap.hpp"

EnvironmentTileMap::EnvironmentTileMap(Ndk::World & world, Nz::Vector2ui mapSize)
{
	unsigned int numberOfEvenLines = mapSize.y / 2;
	unsigned int numberOfOddLines = mapSize.y / 2;
	if (mapSize.y % 2 == 0) {
		numberOfOddLines--;
	}

	// TILESET 
	m_environmentTileSet = Nz::Material::New();
	m_environmentTileSet->LoadFromFile("tiles/water64.png");
	m_environmentTileSet->EnableBlending(true);
	m_environmentTileSet->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	m_environmentTileSet->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	m_environmentTileSet->EnableDepthWrite(false);

	Nz::Rectui treeRect{ 0 * environmentTileSize.x, 0u, environmentTileSize.x, environmentTileSize.y };
	Nz::Rectui stoneRect{ 1 * environmentTileSize.x, 0u, environmentTileSize.x, environmentTileSize.y };

	// Even lines tilemap
	m_evenTileMap = Nz::TileMap::New(Nz::Vector2ui{ mapSize.x, numberOfEvenLines }, Nz::Vector2f{ (float)environmentTileSize.x, (float)environmentTileSize.y });
	//m_evenTileMap->EnableIsometricMode(true);
	m_evenTileMap->SetMaterial(0, m_environmentTileSet);

	m_evenEntity = world.CreateEntity();
	Ndk::NodeComponent &evenNode = m_evenEntity->AddComponent<Ndk::NodeComponent>();
	Ndk::GraphicsComponent &evenGraphics = m_evenEntity->AddComponent<Ndk::GraphicsComponent>();
	evenGraphics.Attach(m_evenTileMap, 1);
	evenNode.SetPosition(Nz::Vector3f(0.f, -32.f, 0.f));

	// Odds lines tilemap
	m_oddTileMap = Nz::TileMap::New(Nz::Vector2ui{ mapSize.x, numberOfOddLines }, Nz::Vector2f{ (float)environmentTileSize.x, (float)environmentTileSize.y });
	m_oddTileMap->EnableIsometricMode(true);
	m_oddTileMap->SetMaterial(0, m_environmentTileSet);

	m_oddEntity = world.CreateEntity();
	Ndk::NodeComponent &oddNode = m_oddEntity->AddComponent<Ndk::NodeComponent>();
	Ndk::GraphicsComponent &oddGraphics = m_oddEntity->AddComponent<Ndk::GraphicsComponent>();
	oddGraphics.Attach(m_oddTileMap, 1);
	oddNode.SetPosition(Nz::Vector3f(32.f, -16.f, 0.f));

	m_evenTileMap->EnableTiles(treeRect);
	//m_oddTileMap->EnableTiles(treeRect);
}

void EnvironmentTileMap::disableTile(Nz::Vector2ui tilePosition)
{
	Nz::TileMapRef& tm = getTMForCoords(tilePosition);
	tm->DisableTile(tilePosition);
}

void EnvironmentTileMap::enableTile(Nz::Vector2ui tilePosition, int tileIndex)
{
	Nz::TileMapRef& tm = getTMForCoords(tilePosition);

	Nz::Rectui textureRect{ tileIndex * environmentTileSize.x, 0u, environmentTileSize.x, environmentTileSize.y };
	tm->EnableTile(tilePosition, textureRect);
}

Nz::TileMapRef & EnvironmentTileMap::getTMForCoords(Nz::Vector2ui tilePosition)
{
	if (tilePosition.y % 2 == 0)
		return m_evenTileMap;
	return m_oddTileMap;
}
