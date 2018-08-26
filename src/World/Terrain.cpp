#include "..\..\includes\World\Terrain.hpp"

Terrain::Terrain(Ndk::World& world, Nz::Vector2ui mapSize, int m_inferiorLevel, int m_superiorLevel) :
	m_inferiorLevel(m_inferiorLevel), m_superiorLevel(m_superiorLevel), m_mapSize(mapSize)
{
	Nz::MaterialRef tileset_64_32 = Nz::Material::New();
	tileset_64_32->LoadFromFile("tiles/64_32_tileset.png");
	tileset_64_32->EnableBlending(true);
	tileset_64_32->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	tileset_64_32->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	tileset_64_32->EnableDepthWrite(false);

	Nz::MaterialRef tileset_64_64 = Nz::Material::New();
	tileset_64_64->LoadFromFile("tiles/64_64_tileset.png");
	tileset_64_64->EnableBlending(true);
	tileset_64_64->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	tileset_64_64->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	tileset_64_64->EnableDepthWrite(false);

	for (int level = m_inferiorLevel; level < m_superiorLevel + 1; level++) {
		// Create entity
		m_tileMapEntities.insert(std::make_pair(level, world.CreateEntity()));
		Ndk::GraphicsComponent &gc = m_tileMapEntities[level]->AddComponent<Ndk::GraphicsComponent>();
		Ndk::NodeComponent &nc = m_tileMapEntities[level]->AddComponent<Ndk::NodeComponent>();

		nc.SetPosition(Nz::Vector3f{ 0.f, mainTileSizef.y * level, 0.f });

		// Create tilemap
		m_tileMaps.insert(std::make_pair(level, TileMap::New(m_mapSize, mainTileSizef, 2)));
		
		// Add materials
		addMaterial(level, tileset_64_32, Nz::Vector2f{ 64.f, 32.f }, Nz::Vector2ui{ 1, 1 });
		addMaterial(level, tileset_64_64, Nz::Vector2f{ 64.f, 64.f }, Nz::Vector2ui{ 1, 1 });

		gc.Attach(m_tileMaps[level]);
	}
}

void Terrain::EnableTile(int level, Nz::Vector2ui position, TileDef& tile)
{
	assert(m_tileMaps[level]->GetMaterialCount() > tile.materialIndex);
	DisableTile(level, position);
	m_tileMaps[level]->EnableTile(position, tile.tileIndex, Nz::Color::White, tile.materialIndex);
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

void Terrain::scale(float value)
{
	auto it = m_tileMapEntities.begin();

	while (it != m_tileMapEntities.end()) {
		Ndk::EntityHandle& entity = (*it).second;
		Ndk::NodeComponent &nc = entity->GetComponent<Ndk::NodeComponent>();
		nc.SetScale(value);
		it++;
	}
}

void Terrain::addMaterial(int level, Nz::MaterialRef& material, Nz::Vector2f imageSize, Nz::Vector2ui tileSize)
{
	m_tileMaps[level]->SetMaterial(m_materialCount, material);
	m_tileMaps[level]->setMaterialData(m_materialCount, imageSize, tileSize);

	m_materialCount++;
}
