#ifndef WALL_SYSTEM_H
#define WALL_SYSTEM_H

#include <NDK/System.hpp>
#include <NDK/Component.hpp>
#include "../Components/WallComponent.hpp"
#include "../World/WorldMap.hpp"
#include "../SpriteLibrary.hpp"
#include "../Utils/isometric.hpp"

class WallSystem : public Ndk::System<WallSystem>
{
public:
	WallSystem(WorldMap& map, SpriteLibrary& spriteLib);
	~WallSystem() = default;

	

	static Ndk::SystemIndex systemIndex;

private:
	WorldMap& m_worldMap;
	SpriteLibrary& m_spriteLib;

	TileDef getTileDef(std::string spriteName);

	void OnUpdate(float elapsed) override;
};

#endif // !WALL_SYSTEM_H
