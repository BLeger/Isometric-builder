#ifndef TILE_DATA_H
#define TILE_DATA_H

#include "../Components/BuildingComponent.hpp"

enum TileType {
	SIMPLE_TILE, // Just a tile
	ENVIRONMENT_TILE,
	ROAD_TILE,
	WALL_TILE,
	WATER_TILE,
	BUILDING_ROOT, // A building is placed on this tile
	BUILDING_BODY // A building overlaps on this tile
};

struct TileData {
	TileType type;
	TileDef groundMaterial;
	TileDef origialGroundMaterial = groundMaterial;
	TileDef environmentMaterial = VOID;
	BuildingComponent* building = nullptr;
};

#endif // !TILE_DATA_H
