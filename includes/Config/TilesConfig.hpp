#ifndef TILES_CONFIG_H
#define TILES_CONFIG_H

#include <Nazara/Math\Vector2.hpp>

const Nz::Vector2ui mainTileSize{ 64, 32 };
const Nz::Vector2f mainTileSizef{ (float)mainTileSize.x, (float)mainTileSize.y };
const Nz::Vector2ui environmentTileSize{ 64, 64 };

#endif // !TILES_CONFIG_H