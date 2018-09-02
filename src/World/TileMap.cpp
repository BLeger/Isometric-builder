#include "../../includes/World/TileMap.hpp"

TileMap::TileMap(const Nz::Vector2ui& mapSize, const Nz::Vector2f& tileSize, std::size_t materialCount) :
	m_tiles(mapSize.x * mapSize.y),
	m_layers(materialCount),
	m_mapSize(mapSize),
	m_tileSize(tileSize)
{
	NazaraAssert(m_tiles.size() != 0U, "Invalid map size");
	NazaraAssert(m_tileSize.x > 0 && m_tileSize.y > 0, "Invalid tile size");
	NazaraAssert(m_layers.size() != 0U, "Invalid material count");

	ResetMaterials(materialCount);

	InvalidateBoundingVolume();
}

void TileMap::AddToRenderQueue(Nz::AbstractRenderQueue* renderQueue, const InstanceData& instanceData, const Nz::Recti & scissorRect) const
{
	const Nz::VertexStruct_XYZ_Color_UV* vertices = reinterpret_cast<const Nz::VertexStruct_XYZ_Color_UV*>(instanceData.data.data());

	std::size_t matCount = 0;
	std::size_t spriteCount = 0;
	for (const Layer& layer : m_layers)
	{
		renderQueue->AddSprites(instanceData.renderOrder, GetMaterial(matCount++), &vertices[4 * spriteCount], layer.tiles.size(), scissorRect);

		spriteCount += layer.tiles.size();
	}
}

std::unique_ptr<Nz::InstancedRenderable> TileMap::Clone() const
{
	return std::make_unique<TileMap>(*this);

}
Nz::Vector2f TileMap::GetSize() const
{
	return Nz::Vector2f(m_mapSize) * m_tileSize;
}

void TileMap::MakeBoundingVolume() const
{
	Nz::Vector2f size = GetSize();
	m_boundingVolume.Set(Nz::Vector3f(0.f), size.x*Nz::Vector3f::Right() + size.y*Nz::Vector3f::Down());
}

TileMapRef TileMap::New(const Nz::Vector2ui& mapSize, const Nz::Vector2f& tileSize, std::size_t materialCount)
{
	std::unique_ptr<TileMap> object(new TileMap(mapSize, tileSize, materialCount));
	object->SetPersistent(false);

	return object.release();
}
	
void TileMap::UpdateData(InstanceData* instanceData) const
{
	std::size_t spriteCount = 0;
	for (const Layer& layer : m_layers)
		spriteCount += layer.tiles.size();

	instanceData->data.resize(4 * spriteCount * sizeof(Nz::VertexStruct_XYZ_Color_UV));
	Nz::VertexStruct_XYZ_Color_UV* vertices = reinterpret_cast<Nz::VertexStruct_XYZ_Color_UV*>(instanceData->data.data());

	spriteCount = 0;
	for (const Layer& layer : m_layers)
	{
		Nz::SparsePtr<Nz::Color> colorPtr(&vertices[4 * spriteCount].color, sizeof(Nz::VertexStruct_XYZ_Color_UV));
		Nz::SparsePtr<Nz::Vector3f> posPtr(&vertices[4 * spriteCount].position, sizeof(Nz::VertexStruct_XYZ_Color_UV));
		Nz::SparsePtr<Nz::Vector2f> texCoordPtr(&vertices[4 * spriteCount].uv, sizeof(Nz::VertexStruct_XYZ_Color_UV));

		for (std::size_t tileIndex : layer.tiles)
		{
			const Tile& tile = m_tiles[tileIndex];
			NazaraAssert(tile.enabled, "Tile specified for rendering is not enabled");

			std::size_t x = tileIndex % m_mapSize.x;
			std::size_t y = tileIndex / m_mapSize.x;

			TileSize ts = tile.tileSize;

			Nz::Vector3f tileLeftBottomCorner;
			tileLeftBottomCorner.Set(x * m_tileSize.x + m_tileSize.x / 2.f * (y % 2), (y / 2.f * -m_tileSize.y) - m_tileSize.y, 0.f);

			// Move tiles that are higher than 1 down
			if (ts.tilesNumber.y > 1) {
				tileLeftBottomCorner.y -= m_tileSize.y * (1.f / ts.tilesNumber.y);
			}

			*colorPtr++ = tile.color;
			*posPtr++ = instanceData->transformMatrix.Transform(tileLeftBottomCorner + ts.imageSize.y * Nz::Vector3f::Up());
			*texCoordPtr++ = tile.textureCoords.GetCorner(Nz::RectCorner_LeftTop);

			*colorPtr++ = tile.color;
			*posPtr++ = instanceData->transformMatrix.Transform(tileLeftBottomCorner + ts.imageSize.x * Nz::Vector3f::Right() + ts.imageSize.y * Nz::Vector3f::Up());
			*texCoordPtr++ = tile.textureCoords.GetCorner(Nz::RectCorner_RightTop);

			*colorPtr++ = tile.color;
			*posPtr++ = instanceData->transformMatrix.Transform(tileLeftBottomCorner);
			*texCoordPtr++ = tile.textureCoords.GetCorner(Nz::RectCorner_LeftBottom);

			*colorPtr++ = tile.color;
			*posPtr++ = instanceData->transformMatrix.Transform(tileLeftBottomCorner + ts.imageSize.x * Nz::Vector3f::Right());
			*texCoordPtr++ = tile.textureCoords.GetCorner(Nz::RectCorner_RightBottom);
		}
		spriteCount += layer.tiles.size();
	}
}

void TileMap::DisableTile(const Nz::Vector2ui& tilePos)
{
	NazaraAssert(tilePos.x < m_mapSize.x && tilePos.y < m_mapSize.y, "Tile position is out of bounds");

	std::size_t tileIndex = tilePos.y * m_mapSize.x + tilePos.x;
	Tile& tile = m_tiles[tileIndex];
	tile.enabled = false;

	m_layers[tile.layerIndex].tiles.erase(tileIndex);

	InvalidateInstanceData(1U << tile.layerIndex);
}

/*!
* \brief Disable all tiles
*/
void TileMap::DisableTiles()
{
	for (Tile& tile : m_tiles)
		tile.enabled = false;

	for (Layer& layer : m_layers)
		layer.tiles.clear();

	InvalidateInstanceData(0xFFFFFFFF);
}

void TileMap::EnableTile(const Nz::Vector2ui& tilePos, const Nz::Rectf& coords, const TileSize& tileSize, const Nz::Color& color, std::size_t materialIndex)
{
	NazaraAssert(tilePos.x < m_mapSize.x && tilePos.y < m_mapSize.y, "Tile position is out of bounds");
	NazaraAssert(materialIndex < m_layers.size(), "Material out of bounds");

	int32_t invalidatedLayers = 1U << materialIndex;

	std::size_t tileIndex = tilePos.y * m_mapSize.x + tilePos.x;
	Tile& tile = m_tiles[tilePos.y * m_mapSize.x + tilePos.x];

	if (!tile.enabled) {
		m_layers[materialIndex].tiles.insert(tileIndex);
	}
	else if (materialIndex != tile.layerIndex)
	{
		m_layers[materialIndex].tiles.erase(tileIndex);
		m_layers[tile.layerIndex].tiles.insert(tileIndex);

		invalidatedLayers |= 1U << tile.layerIndex;
	}	

	tile.enabled = true;
	tile.color = color;
	tile.textureCoords = coords;
	tile.layerIndex = materialIndex;
	tile.tileSize = tileSize;

	InvalidateInstanceData(invalidatedLayers);
}

void TileMap::EnableTile(const Nz::Vector2ui& tilePos, const Nz::Rectui& texture, const TileSize& tileSize, const Nz::Color& color, std::size_t materialIndex)
{
	NazaraAssert(materialIndex < m_layers.size(), "Material out of bounds");

	const Nz::MaterialRef& material = GetMaterial(materialIndex);
	NazaraAssert(material->HasDiffuseMap(), "Material has no diffuse map");

	Nz::Texture* diffuseMap = material->GetDiffuseMap();
	float invWidth = 1.f / diffuseMap->GetWidth();
	float invHeight = 1.f / diffuseMap->GetHeight();

	Nz::Rectf unnormalizedCoords(invWidth * texture.x, invHeight * texture.y, invWidth * texture.width, invHeight * texture.height);
	EnableTile(tilePos, unnormalizedCoords, tileSize, color, materialIndex);
}