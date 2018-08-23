#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <NDK/Application.hpp>
#include <NDK/Entity.hpp>
#include <NDK/State.hpp>
#include <NDK/StateMachine.hpp>
#include <NDK/World.hpp>
#include <NDK/Components.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <Nazara/Graphics/TileMap.hpp>
#include <Nazara/Math\Vector2.hpp>
#include <Nazara/Core/Color.hpp>

#include "../Config/TilesConfig.hpp"
#include "../Config/Tiles.hpp"

#include <map>

class Terrain {
public:
	Terrain(Ndk::World& world, Nz::Vector2ui mapSize, int m_inferiorLevel = 0, int m_superiorLevel = 0);

private:
	Nz::Vector2ui m_mapSize;
	int m_inferiorLevel;
	int m_superiorLevel;
	
	std::map<int, Ndk::EntityHandle> m_tileMapEntities;
	std::map<int, Nz::TileMapRef> m_tileMaps;
};

#endif // !TERRAIN_HPP
