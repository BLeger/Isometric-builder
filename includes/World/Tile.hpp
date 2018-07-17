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

#include "TileData.hpp"
#include "Building.hpp"

class Tile {

public:
	Tile() {};
	Tile(TileType type, std::string material, float heightOffset = 0.f);
	Tile(TileData& datas);

	void setTileDatas(TileData& datas); 

	void setType(TileType type);
	TileType getType();

	float getHeightOffset();

	std::string getMaterialName();

private:
	float m_heightOffset;
	std::string m_materialName;
	TileType m_type;

	Building* b;
};

#endif // !TILE_H
