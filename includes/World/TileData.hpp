#ifndef TILE_DATA_H
#define TILE_DATA_H

#include <string>

enum TileType {
	Tile_1x1,
	Object_NxN_Attach,
	Object_NxN_Body
};

struct TileData {
	TileType type;
	std::string materialName;
	float heightOffset;
	int width;
	int height;
};

#endif // !TILE_DATA_H
