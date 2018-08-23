#include "..\..\includes\World\Terrain.hpp"

Terrain::Terrain(Ndk::World& world, Nz::Vector2ui mapSize, int m_inferiorLevel, int m_superiorLevel) :
	m_inferiorLevel(m_inferiorLevel), m_superiorLevel(m_superiorLevel), m_mapSize(mapSize)
{
	Nz::MaterialRef tileset = Nz::Material::New();
	tileset->LoadFromFile("tiles/tileset.png");
	tileset->EnableBlending(true);
	tileset->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	tileset->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	tileset->EnableDepthWrite(false);

	for (int level = m_inferiorLevel; level < m_superiorLevel + 1; level++) {
		// Create entity
		m_tileMapEntities.insert(std::make_pair(level, world.CreateEntity()));
		Ndk::GraphicsComponent &gc = m_tileMapEntities[level]->AddComponent<Ndk::GraphicsComponent>();
		Ndk::NodeComponent &nc = m_tileMapEntities[level]->AddComponent<Ndk::NodeComponent>();

		// Create tilemap
		m_tileMaps.insert(std::make_pair(level, Nz::TileMap::New(m_mapSize, mainTileSizef)));
		m_tileMaps[level]->SetMaterial(0, tileset);

		gc.Attach(m_tileMaps[level]);
	}
}
