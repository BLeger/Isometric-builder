#ifndef BUILDING_H
#define BUILDING_H

#include <NDK/Application.hpp>
#include <NDK/Entity.hpp>
#include <NDK/State.hpp>
#include <NDK/StateMachine.hpp>
#include <NDK/World.hpp>
#include <NDK/Components.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <Nazara\Math\Vector2.hpp>

#include <string>
#include "../Utils/isometric.hpp"
#include "TileData.hpp"

class Building {

public:
	Building(TileData& tile, Ndk::World& world, int drawingOrder);

	void setScale(float scale);
	void setPosition(Nz::Vector2f position);

	TileData& getTileData();
	std::string getMaterialName();
	float getHeightOffset();

	Nz::Vector2<int> getSize();

private:
	Ndk::EntityHandle m_entity;
	TileData& m_tileData;
	float m_heightOffset;
	std::string m_materialName;
	int m_size_x, m_size_y;
};

#endif // !BUILDING_H
