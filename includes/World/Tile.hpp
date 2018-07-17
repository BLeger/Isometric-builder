#ifndef TILE_H
#define TILE_H

#include <NDK/Application.hpp>
#include <NDK/Entity.hpp>
#include <NDK/State.hpp>
#include <NDK/StateMachine.hpp>
#include <NDK/World.hpp>
#include <NDK/Components.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>

#include <string>
#include <iostream>

enum TileType {
	Tile_1x1,
	Object_NxN_Attach,
	Object_NxN_Body
};

struct TileData {
	TileType type;
	std::string name;
	std::string materialName;
	float heightOffset;
	int width;
	int height;
};

class Tile {

public:
	Tile() {};
	Tile(TileType type, std::string material, float heightOffset = 0.f);
	Tile(TileData& datas);

	void setTileDatas(TileData& datas); 

	void setType(TileType type);
	TileType getType();

	float getHeightOffset();

	void setMaterialName(std::string material);
	Nz::MaterialRef getMaterial();

private:
	float m_heightOffset;
	std::string m_materialName;
	TileType m_type;
};

#endif // !TILE_H
