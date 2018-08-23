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

		nc.SetPosition(Nz::Vector3f{ 0.f, mainTileSizef.y * level, 0.f });

		// Create tilemap
		m_tileMaps.insert(std::make_pair(level, TileMap::New(m_mapSize, mainTileSizef)));
		
		// Add materials
		m_tileMaps[level]->SetMaterial(0, tileset);
		m_tileMaps[level]->setMaterialData(0, Nz::Vector2f{ 64.f, 32.f }, Nz::Vector2ui{ 1, 1 });

		gc.Attach(m_tileMaps[level]);
	}
}

void Terrain::EnableTile(int level, Nz::Vector2ui position, TileDef tile)
{
	Nz::Rectui texture{ tile.tileIndex * mainTileSize.x, 0u, mainTileSize.x, mainTileSize.y };
	m_tileMaps[level]->EnableTile(position, texture, Nz::Color::White, tile.materialIndex);
}

void Terrain::DisableTile(int level, Nz::Vector2ui position)
{
	m_tileMaps[level]->DisableTile(position);
}

void Terrain::DisableTiles()
{
	for (int level = m_inferiorLevel; level < m_superiorLevel + 1; level++) {
		DisableTiles(level);
	}
}

void Terrain::DisableTiles(int level)
{
	m_tileMaps[level]->DisableTiles();
}
