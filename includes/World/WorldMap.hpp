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
#include "../Utils/isometric.hpp"
#include "../WorldGeneration/NoiseGenerator.hpp"

#include "../Components/EnvironmentTileComponent.hpp"
#include "../Components/WallComponent.hpp"
#include "../Components/WalkerComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/BuildingComponent.hpp"


class WorldMap {
	
public:
	//WorldMap() {};
	WorldMap(Nz::Vector2ui size, Ndk::World& world);
	void generateTerrain();

	TileData& getTile(Nz::Vector2ui position);

	bool createEntity(Nz::Vector2ui position);
	bool deleteEntity(Nz::Vector2ui position);

	void addEnvironmentTile(Nz::Vector2ui position, Nz::SpriteRef sprite);
	void removeEnvironmentTile(Nz::Vector2ui position);

	void addRoad(Nz::Vector2ui position);
	void removeRoad(Nz::Vector2ui position);

	void addWall(Nz::Vector2ui position);
	void removeWall(Nz::Vector2ui position);
	bool isWall(Nz::Vector2ui position);
	void updateSurrondingsWalls(Nz::Vector2ui position);

	void addWalker(Nz::Vector2ui position, Nz::SpriteRef& sprite);

	void update();
	void updateTile(Nz::Vector2ui position);

	bool isPositionCorrect(Nz::Vector2ui position);
	bool isPositionAvailable(Nz::Vector2ui position);
	bool isWalkable(Nz::Vector2ui position);

	void addBuilding(Nz::Vector2ui position, std::string name, Nz::Vector2ui size);

	bool changeTile(int x, int y, TileData newTileData);

	float getScale();
	void zoom(float delta);

	void setCameraOffset(Nz::Vector2f offset);
	Nz::Vector2f getCameraOffset();

private:
	Ndk::World& m_worldRef;

	std::vector<TileData> m_tiles{};
	std::map<Nz::Vector2ui, Ndk::EntityHandle> m_entities{};
	std::map<Nz::Vector2ui, Ndk::EntityHandle> m_buildings{};
	std::vector<Ndk::EntityHandle> m_walkers{};

	Nz::TileMapRef m_tileMap;
	Ndk::EntityHandle m_tileMapEntity;

	const Nz::Vector2ui m_size;

	float m_scale = 1.f;
	const float m_maxScale = 1.5f;
	const float m_minScale = 0.1f;

	Nz::Vector2f m_cameraOffset{ 0.f, 0.f };
};

#endif // !WORLD_MAP_H
