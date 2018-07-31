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

	bool isPositionCorrect(Nz::Vector2ui position);
	void addBuilding(Building b, int x, int y);

	bool changeTile(int x, int y, TileData newTileData);

	float getScale();
	void zoom(int delta);

	Nz::Vector2f getCameraOffset();

private:
	Ndk::World& m_worldRef;

	std::vector<TileData> m_tiles{};
	std::map<Nz::Vector2ui, Ndk::EntityHandle> m_entities{};

	Nz::TileMapRef m_tileMap;
	Ndk::EntityHandle m_tileMapEntity;

	const Nz::Vector2ui m_size;

	float m_scale = 1.f;
	const float m_maxScale = 1.5f;
	const float m_minScale = 0.5f;

	Nz::Vector2f m_cameraOffset{ 0.f, 0.f };
};

#endif // !WORLD_MAP_H
