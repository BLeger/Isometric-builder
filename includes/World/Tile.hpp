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

#include "../Utils/isometric.hpp"
#include "TileData.hpp"
#include "Building.hpp"

class Tile {

public:
	Tile() {};
	//Tile(TileType type, std::string material, float heightOffset = 0.f);
	Tile(TileData& datas, Ndk::World& world, int drawingOrder);

	void setScale(float scale);
	void setPosition(Nz::Vector2f position);

	void setTileDatas(TileData& datas); 

	//void setType(TileType type);
	//TileType getType();

	float getHeightOffset();

	std::string getMaterialName();

private:
	Ndk::EntityHandle m_entity;
	float m_heightOffset;
	std::string m_materialName;
	int m_drawingOrder;
	//TileType m_type;

	Building* b;
};

#endif // !TILE_H
