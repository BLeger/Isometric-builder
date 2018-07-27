#include "..\..\includes\World\EnvironmentTileMap.hpp"

EnvironmentTileMap::EnvironmentTileMap(Ndk::World & world)
{
	// TILESET 
	m_environmentTileSet = Nz::Material::New();
	m_environmentTileSet->LoadFromFile("tiles/test.png");
	m_environmentTileSet->EnableBlending(true);
	m_environmentTileSet->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	m_environmentTileSet->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	m_environmentTileSet->EnableDepthWrite(false);

	Nz::Rectui treeRect{ 0 * environmentTileSize.x, 0u, environmentTileSize.x, environmentTileSize.y };
	Nz::Rectui stoneRect{ 1 * environmentTileSize.x, 0u, environmentTileSize.x, environmentTileSize.y };

	// Even lines tilemap
	// TODO : REPLACE 20 AND 10 IN NEXT LINE
	m_evenTileMap = Nz::TileMap::New(Nz::Vector2ui{ 20, 10 }, Nz::Vector2f{ (float)environmentTileSize.x, (float)environmentTileSize.y });
	m_evenTileMap->EnableIsometricMode(true);
	m_evenTileMap->SetMaterial(0, m_environmentTileSet);

	m_evenEntity = world.CreateEntity();
	Ndk::NodeComponent &evenNode = m_evenEntity->AddComponent<Ndk::NodeComponent>();
	Ndk::GraphicsComponent &evenGraphics = m_evenEntity->AddComponent<Ndk::GraphicsComponent>();
	evenGraphics.Attach(m_evenTileMap);
	evenNode.SetPosition(Nz::Vector3f(0.f, -1.f * environmentTileSize.y / 2.f, 0.f));

	// Odds lines tilemap
	m_oddTileMap = Nz::TileMap::New(Nz::Vector2ui{ 20, 10 }, Nz::Vector2f{ (float)environmentTileSize.x, (float)environmentTileSize.y });
	m_oddTileMap->EnableIsometricMode(true);
	m_oddTileMap->SetMaterial(0, m_environmentTileSet);

	m_oddEntity = world.CreateEntity();
	Ndk::NodeComponent &oddNode = m_oddEntity->AddComponent<Ndk::NodeComponent>();
	Ndk::GraphicsComponent &oddGraphics = m_oddEntity->AddComponent<Ndk::GraphicsComponent>();
	oddGraphics.Attach(m_oddTileMap);
	oddNode.SetPosition(Nz::Vector3f(32.f, -1.f * environmentTileSize.y / 4.f, 0.f));




	m_evenTileMap->EnableTile(Nz::Vector2ui(0, 0), treeRect);
	m_oddTileMap->EnableTile(Nz::Vector2ui(0, 0), treeRect);





}
