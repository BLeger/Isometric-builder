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
	Terrain(Ndk::World& world, Nz::Vector2ui mapSize, int inferiorLevel, int superiorLevel);

	void EnableGroundTile(Nz::Vector2ui position, TileDef& tile, Nz::Color color = Nz::Color::White);
	void EnableEnvironmentTile( Nz::Vector2ui position, TileDef& tile, Nz::Color color = Nz::Color::White);

	void DisableGroundTile(Nz::Vector2ui position);
	void DisableEnvironmentTile( Nz::Vector2ui position);

	void DisableTiles();
	void DisableTiles(int level);

	void setHeight(Nz::Vector2ui position, int height);
	int getHeight(Nz::Vector2ui position);

	void scale(float value);

private:
	void EnableTile(TileMapRef& tilemap, Nz::Vector2ui position, TileDef& tile, Nz::Color color = Nz::Color::White);
	void DisableTile(TileMapRef& tilemap, Nz::Vector2ui position);

	void addMaterial(int level, Nz::MaterialRef& material, Nz::Vector2f imageSize, Nz::Vector2ui tileSize);
	unsigned int m_materialCount = 0;

	Nz::Vector2ui m_mapSize;
	int m_inferiorLevel;
	int m_superiorLevel;

	std::vector<int> m_heightMap;

	std::map<int, Ndk::EntityHandle> m_groundTileMapEntities;
	std::map<int, TileMapRef> m_groundTileMaps;

	std::map<int, Ndk::EntityHandle> m_environmentTileMapEntities;
	std::map<int, TileMapRef> m_environmentTileMaps;
};

#endif // !TERRAIN_HPP
