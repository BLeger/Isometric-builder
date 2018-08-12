#ifndef BUILDING_SYSTEM_H
#define BUILDING_SYSTEM_H

#include <NDK/System.hpp>
#include <NDK/Component.hpp>
#include "../Components/BuildingComponent.hpp"
#include "../World/WorldMap.hpp"
#include "../SpriteLibrary.hpp"
#include "../Utils/isometric.hpp"

#include <iostream>

class BuildingSystem : public Ndk::System<BuildingSystem>
{
public:
	BuildingSystem(WorldMap& worldMap, SpriteLibrary& spriteLib);
	~BuildingSystem() = default;

	static Ndk::SystemIndex systemIndex;

private:
	WorldMap& m_worldMap;
	SpriteLibrary& m_spriteLib;

	void OnUpdate(float elapsed) override;
};

#endif // !BUILDING_SYSTEM_H
