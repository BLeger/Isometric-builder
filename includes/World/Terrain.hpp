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
#include <Nazara/Math\Vector2.hpp>
#include <Nazara/Core/Color.hpp>

#include "../Config/TilesConfig.hpp"
#include "../Config/Tiles.hpp"
#include "TileMap.hpp"

#include <map>

class Terrain {
public:
	Terrain(Ndk::World& world, Nz::Vector2ui mapSize, int m_inferiorLevel = 0, int m_superiorLevel = 0);

	void EnableTile(int level, Nz::Vector2ui position, TileDef& tile);

	void DisableTile(int level, Nz::Vector2ui position);
	void DisableTiles();
	void DisableTiles(int level);

	void scale(float value);

private:
	void addMaterial(int level, Nz::MaterialRef& material, Nz::Vector2f imageSize, Nz::Vector2ui tileSize);
	unsigned int m_materialCount = 0;

	Nz::Vector2ui m_mapSize;
	int m_inferiorLevel;
	int m_superiorLevel;
	
	std::map<int, Ndk::EntityHandle> m_tileMapEntities;
	std::map<int, TileMapRef> m_tileMaps;
};

#endif // !TERRAIN_HPP
