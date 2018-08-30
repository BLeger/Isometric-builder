#ifndef TILE_DATA_H
#define TILE_DATA_H

enum TileType {
	SIMPLE_TILE, // Just a tile
	ROAD_TILE,
	WALL_TILE,
	BUILDING_ROOT, // A building is placed on this tile
	BUILDING_BODY // A building overlaps on this tile
};

struct TileData {
	TileType type;
	TileDef groundMaterial;
	TileDef origialGroundMaterial = groundMaterial;
	TileDef environmentMaterial = VOID;
	bool water = false;
	bool road = false;
};

#endif // !TILE_DATA_H
