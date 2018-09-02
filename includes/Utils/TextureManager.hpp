#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <NDK/Application.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>

#include "../Config/Tiles.hpp"

#include <iostream>

struct TileSize {
	Nz::Vector2ui tilesNumber;
	Nz::Vector2f imageSize;
};

class TextureManager {

public:
	TextureManager();

	Nz::Rectui getTextureCoords(TileDef& tile);
	Nz::Rectui getTextureCoords(unsigned int lineIndex, unsigned int tileIndex);

	TileSize getTileSize(TileDef& tile);
	TileSize getTileSize(unsigned int lineIndex);

	Nz::MaterialRef loadMaterial();

private:
	std::vector<float> m_linePixelStart;
	std::vector<TileSize> m_textureLines;
};

#endif // !TEXTURE_MANAGER_HPP
