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
#include <Nazara/Math/Vector2.hpp>

#include <string>
#include "../Utils/isometric.hpp"
#include "BuildingData.hpp"

class Building {

public:
	Building(BuildingData data, Nz::Vector2ui position);

	unsigned int getMaterialID();

	Nz::Vector2ui getSize();
	Nz::Vector2ui getPosition();

private:
	unsigned int m_materialID;
	Nz::Vector2ui m_size;
	Nz::Vector2ui m_position;
};

#endif // !BUILDING_H
