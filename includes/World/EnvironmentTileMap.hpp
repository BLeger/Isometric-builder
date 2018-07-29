#ifndef ENVIRONMENT_TILE_MAP_H
#define ENVIRONMENT_TILE_MAP_H

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

#include "../Config/TilesConfig.hpp"

/*
This class will be used to draw tiles that can have 64 px height
on top of the main tilemap
*/
class EnvironmentTileMap {

public:
	EnvironmentTileMap(Ndk::World& world, Nz::Vector2ui mapSize);

	void disableTile(Nz::Vector2ui tilePosition);
	void enableTile(Nz::Vector2ui tilePosition, int tileIndex);

private:
	Nz::MaterialRef m_environmentTileSet;

	Nz::TileMapRef m_evenTileMap;
	Nz::TileMapRef m_oddTileMap;

	Ndk::EntityHandle m_evenEntity;
	Ndk::EntityHandle m_oddEntity;

	Nz::TileMapRef& getTMForCoords(Nz::Vector2ui tilePosition);
};

#endif // !ENVIRONMENT_TILE_MAP_H
