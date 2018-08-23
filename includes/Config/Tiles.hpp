#ifndef TILES_H
#define TILES_H

struct TileDef {
	int materialIndex;
	int tileIndex;
	Nz::Vector2ui tileSize{ 1, 1 };

	bool operator==(const TileDef& rhs)
	{
		return materialIndex == rhs.materialIndex && tileIndex == rhs.tileIndex && tileSize == rhs.tileSize;
	}
};

const TileDef GRASS { 0, 0 };
const TileDef WATER { 0, 1 };
const TileDef DEEP_WATER { 0, 2 };
//const TileDef ROAD{ 0, 3 };
const TileDef SAND { 0, 4 };

const TileDef TREE{ 1, 0 };

#endif // !TILES_H
