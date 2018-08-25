#ifndef TILE_DATA_H
#define TILE_DATA_H

enum TileType {
	SIMPLE_TILE, // Just a tile
	ENV_TILE, // Tile + a texture (like a tree) on it
	ROAD_TILE,
	BUILDING_ROOT, // A building is placed on this tile
	BUILDING_BODY // A building overlaps on this tile
};

struct TileData {
	TileType type;
	TileDef material;
	TileDef origialMaterial = material;
	bool water = false;
	bool road = false;
};

#endif // !TILE_DATA_H
