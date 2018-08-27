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

	int numberOfMaterials = 2;

	for (int level = m_inferiorLevel; level < m_superiorLevel + 1; level++) {
		// Create entity
		m_groundTileMapEntities.insert(std::make_pair(level, world.CreateEntity()));
		Ndk::GraphicsComponent &groundGC = m_groundTileMapEntities[level]->AddComponent<Ndk::GraphicsComponent>();
		Ndk::NodeComponent &groundNC = m_groundTileMapEntities[level]->AddComponent<Ndk::NodeComponent>();

		m_environmentTileMapEntities.insert(std::make_pair(level, world.CreateEntity()));
		Ndk::GraphicsComponent &envGC = m_environmentTileMapEntities[level]->AddComponent<Ndk::GraphicsComponent>();
		Ndk::NodeComponent &envNC = m_environmentTileMapEntities[level]->AddComponent<Ndk::NodeComponent>();

		groundNC.SetPosition(Nz::Vector3f{ 0.f, mainTileSizef.y * level, 0.f });
		envNC.SetPosition(Nz::Vector3f{ 0.f, mainTileSizef.y * level, 0.f });

		// Create tilemap
		m_groundTileMaps.insert(std::make_pair(level, TileMap::New(m_mapSize, mainTileSizef, numberOfMaterials)));
		m_environmentTileMaps.insert(std::make_pair(level, TileMap::New(m_mapSize, mainTileSizef, numberOfMaterials)));
		
		// Add materials
		addMaterial(level, tileset_64_32, Nz::Vector2f{ 64.f, 32.f }, Nz::Vector2ui{ 1, 1 });
		addMaterial(level, tileset_64_64, Nz::Vector2f{ 64.f, 64.f }, Nz::Vector2ui{ 1, 1 });

		groundGC.Attach(m_groundTileMaps[level]);
		envGC.Attach(m_environmentTileMaps[level]);
	}
}

void Terrain::EnableGroundTile(int level, Nz::Vector2ui position, TileDef& tile)
{
	EnableTile(m_groundTileMaps.at(level), position, tile);
}

void Terrain::EnableEnvironmentTile(int level, Nz::Vector2ui position, TileDef & tile)
{
	EnableTile(m_environmentTileMaps.at(level), position, tile);
}

void Terrain::DisableGroundTile(int level, Nz::Vector2ui position)
{
	DisableTile(m_groundTileMaps.at(level), position);
}

void Terrain::DisableEnvironmentTile(int level, Nz::Vector2ui position)
{
	DisableTile(m_environmentTileMaps.at(level), position);
}

void Terrain::DisableTiles()
{
	for (int level = m_inferiorLevel; level < m_superiorLevel + 1; level++) {
		DisableTiles(level);
	}
}

void Terrain::DisableTiles(int level)
{
	m_groundTileMaps[level]->DisableTiles();
	m_environmentTileMaps[level]->DisableTiles();
}

void Terrain::scale(float value)
{
	for (int level = m_inferiorLevel; level < m_superiorLevel + 1; level++) {
		Ndk::EntityHandle& ground = m_groundTileMapEntities.at(level);
		Ndk::EntityHandle& environment = m_environmentTileMapEntities.at(level);

		Ndk::NodeComponent &groundNC = ground->GetComponent<Ndk::NodeComponent>();
		Ndk::NodeComponent &envNC = environment->GetComponent<Ndk::NodeComponent>();

		groundNC.SetScale(value);
		envNC.SetScale(value);
	}
}

void Terrain::EnableTile(TileMapRef& tilemap, Nz::Vector2ui position, TileDef & tile)
{
	assert(tilemap->GetMaterialCount() > tile.materialIndex);
	tilemap->DisableTile(position);
	tilemap->EnableTile(position, tile.tileIndex, Nz::Color::White, tile.materialIndex);
}

void Terrain::DisableTile(TileMapRef & tilemap, Nz::Vector2ui position)
{
	tilemap->DisableTile(position);
}

void Terrain::addMaterial(int level, Nz::MaterialRef& material, Nz::Vector2f imageSize, Nz::Vector2ui tileSize)
{
	m_groundTileMaps[level]->SetMaterial(m_materialCount, material);
	m_groundTileMaps[level]->setMaterialData(m_materialCount, imageSize, tileSize);

	m_environmentTileMaps[level]->SetMaterial(m_materialCount, material);
	m_environmentTileMaps[level]->setMaterialData(m_materialCount, imageSize, tileSize);

	m_materialCount++;
}