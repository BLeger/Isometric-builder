#ifndef WORLD_MAP_H
#define WORLD_MAP_H

#include <vector>
#include <iostream>
#include <map>

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

#include "TileData.hpp"
#include "Tile.hpp"
#include "Building.hpp"
#include "../Utils/isometric.hpp"

class WorldMap {

	using coordinates = Nz::Vector2i;

public:
	//WorldMap() {};
	WorldMap(int size_x, int size_y);
	void generateMap(TileData& defaultTile);

	Tile& getTile(int x, int y);

	void display(Ndk::World& world);
	void addBuilding(Building b, int x, int y);

	bool changeTile(int x, int y, TileData newTileData);

private:
	std::vector<Tile> m_tiles{};
	std::map<coordinates, Building> m_buildings{};

	const int m_size_x;
	const int m_size_y;
};

#endif // !WORLD_MAP_H
