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

class Building {

public:
	Building(int size_x, int size_y, std::string materialName);

	void setMaterialName(std::string material);
	std::string getMaterialName();

	Nz::Vector2<int> getSize();

private:
	std::string m_materialName;
	int m_size_x, m_size_y;
};

#endif // !BUILDING_H
