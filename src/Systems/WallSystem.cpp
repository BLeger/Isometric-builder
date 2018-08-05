#include "..\..\includes\Systems\WallSystem.hpp"

Ndk::SystemIndex WallSystem::systemIndex;

WallSystem::WallSystem(WorldMap& map, SpriteLibrary& spriteLib) : m_worldMap(map), m_spriteLib(spriteLib)
{
	Requires<WallComponent, Ndk::GraphicsComponent, Ndk::NodeComponent>();
	SetUpdateOrder(5);
	SetMaximumUpdateRate(10.f);
	//SetUpdateRate(10.f);
}

void WallSystem::OnUpdate(float elapsed)
{
	for (auto& e : GetEntities()) {

	}
}
