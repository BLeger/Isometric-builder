#ifndef TILE_H
#define TILE_H

enum TileType {
	Tile_1x1,
	Object_NxN_Attach,
	Object_NxN_Body
};

class Tile {

public:
	Tile(TileType type);

private:
	TileType m_type;
};

#endif // !TILE_H
