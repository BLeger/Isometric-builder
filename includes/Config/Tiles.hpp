#ifndef TILES_H
#define TILES_H

struct TileDef {
	int materialIndex;
	int tileIndex;
	std::string name{ "" };
	Nz::Vector2ui tileSize{ 1, 1 };

	bool operator==(const TileDef& rhs)
	{
		return materialIndex == rhs.materialIndex && tileIndex == rhs.tileIndex && tileSize == rhs.tileSize;
	}
};

const TileDef GRASS { 0, 0, "grass" };
const TileDef WATER { 0, 1, "water" };
const TileDef DEEP_WATER { 0, 2, "deep_water" };
const TileDef ROAD{ 0, 3, "road" };
const TileDef SAND { 0, 4, "sand" };

const TileDef TREE{ 1, 0, "tree" };

#endif // !TILES_H
