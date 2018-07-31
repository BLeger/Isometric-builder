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
#include <Nazara/Graphics/TileMap.hpp>
#include <Nazara/Math\Vector2.hpp>
#include <Nazara/Core/Color.hpp>

#include "../Config/TilesConfig.hpp"
#include "TileData.hpp"
#include "Building.hpp"
#include "../Utils/isometric.hpp"

#include "../Components/EnvironmentTileComponent.hpp"

class WorldMap {
	
public:
	//WorldMap() {};
	WorldMap(Nz::Vector2ui size, Ndk::World& world);

	TileData& getTile(Nz::Vector2ui position);

	void addEnvironmentTile(Nz::Vector2ui position, Nz::SpriteRef sprite);
	void removeEnvironmentTile(Nz::Vector2ui position);

	void update();
	void addBuilding(Building b, int x, int y);

	bool changeTile(int x, int y, TileData newTileData);

	void zoom(int delta);

private:
	Ndk::World& m_worldRef;

	std::vector<TileData> m_tiles{};
	std::map<Nz::Vector2ui, Ndk::EntityHandle> m_entities{};

	Nz::TileMapRef m_tileMap;

	const Nz::Vector2ui m_size;

	float m_scale = 0.5f;
	const float m_max_scale = 0.8f;
	const float m_min_scale = 0.2f;

	const Nz::Vector2ui m_tileSize {64, 32};

	const float m_width_offset = 0.0f;
};

#endif // !WORLD_MAP_H
