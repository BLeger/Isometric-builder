#ifndef TILES_H
#define TILES_H

struct TileDef {
	int lineIndex;
	int tileIndex;
	std::string name{ "" };
	Nz::Vector2ui tileSize{ 1, 1 };

	bool operator==(const TileDef& rhs)
	{
		return lineIndex == rhs.lineIndex && tileIndex == rhs.tileIndex && tileSize == rhs.tileSize;
	}

	bool operator!=(const TileDef& rhs)
	{
		return lineIndex != rhs.lineIndex || tileIndex != rhs.tileIndex || tileSize != rhs.tileSize;
	}
};

const TileDef VOID{ -1, -1, "void" };

const TileDef GRASS { 0, 0, "grass" };
const TileDef WATER { 0, 1, "water" };
const TileDef DEEP_WATER { 0, 2, "deep_water" };
const TileDef ROAD{ 0, 3, "road" };
const TileDef SAND { 0, 4, "sand" };

// WALLS

const TileDef WALL{ 1, 0, "wall" };
const TileDef WALL_NO{ 1, 1, "wall_no" };
const TileDef WALL_NE{ 1, 2, "wall_ne" };
const TileDef WALL_SO{ 1, 3, "wall_so" };
const TileDef WALL_SE{ 1, 4, "wall_se" };
const TileDef WALL_NO_NE{ 1, 5, "wall_no_ne" };
const TileDef WALL_NO_SO{ 1, 6, "wall_no_so" };
const TileDef WALL_NO_SO_SE{ 1, 7, "wall_no_so_se" };
const TileDef WALL_NE_SE{ 1, 8, "wall_ne_se" };
const TileDef WALL_NE_SO{ 1, 9, "wall_ne_so" };
const TileDef WALL_SO_SE{ 1, 10, "wall_so_se" };
const TileDef WALL_NO_SE{ 1, 11, "wall_no_se" };

// TODO : ADD IMAGES :
const TileDef WALL_NE_SO_SE{ 1, 0, "wall_ne_so_se" };
const TileDef WALL_NO_NE_SE{ 1, 0, "wall_no_ne_se" };
const TileDef WALL_NO_NE_SO{ 1, 0, "wall_no_ne_so" };

const std::array<const TileDef, 15> WALLS {WALL, WALL_NO, WALL_NE, WALL_SO, WALL_SE,
WALL_NO_NE, WALL_NO_SO, WALL_NO_SO_SE, WALL_NE_SE, WALL_NE_SO, WALL_SO_SE, WALL_NO_SE,
WALL_NE_SO_SE, WALL_NO_NE_SE, WALL_NO_NE_SO };

const TileDef TREE{ 2, 0, "tree" };
const TileDef ROCK{ 2, 1, "rock" };


#endif // !TILES_H
