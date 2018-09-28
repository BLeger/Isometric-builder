#include "../../includes/Utils/TextureManager.hpp"

TextureManager::TextureManager()
{
	// Simple tiles
	m_textureLines.push_back(TileSize{ Nz::Vector2ui {1, 1}, Nz::Vector2f{64.f, 32.f } });

	// Walls
	m_textureLines.push_back(TileSize{ Nz::Vector2ui{ 1, 1 }, Nz::Vector2f{ 64.f, 70.f } });

	// Env
	m_textureLines.push_back(TileSize{ Nz::Vector2ui{ 1, 1 }, Nz::Vector2f{ 64.f, 64.f } });

	// 2x2 Buildings
	m_textureLines.push_back(TileSize{ Nz::Vector2ui{ 2, 2 }, Nz::Vector2f{ 128.f, 138.f } });

	m_linePixelStart.push_back(0);
	for (int i = 1; i < m_textureLines.size(); i++) {
		m_linePixelStart.push_back(m_linePixelStart[i - 1] + m_textureLines[i - 1].imageSize.y);
	}
}

Nz::Rectui TextureManager::getTextureCoords(TileDef & tile)
{
	return getTextureCoords(tile.lineIndex, tile.tileIndex);
}

Nz::Rectui TextureManager::getTextureCoords(unsigned int lineIndex, unsigned int tileIndex)
{
	TileSize ts = getTileSize(lineIndex);
	float startAt = m_linePixelStart.at(lineIndex);

	Nz::Rectui texture{ tileIndex * (unsigned int) ts.imageSize.x, (unsigned int) startAt, (unsigned int) ts.imageSize.x, (unsigned int) ts.imageSize.y };
	return texture;
}

TileSize TextureManager::getTileSize(TileDef & tile)
{
	return getTileSize(tile.lineIndex);
}

TileSize TextureManager::getTileSize(unsigned int lineIndex)
{
	assert(m_textureLines.size() > lineIndex);
	return m_textureLines.at(lineIndex);
}

Nz::MaterialRef TextureManager::loadMaterial()
{
	Nz::MaterialRef tileset = Nz::Material::New();
	tileset->LoadFromFile("tiles/tileset.png");
	tileset->EnableBlending(true);
	tileset->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	tileset->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	tileset->EnableDepthWrite(false);

	return tileset;
}
