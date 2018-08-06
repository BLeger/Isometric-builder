#include "..\..\includes\Systems\WalkerSystem.hpp"

Ndk::SystemIndex WalkerSystem::systemIndex;

WalkerSystem::WalkerSystem(WorldMap& map) : m_worldMap(map)
{
	Requires<WalkerComponent, Ndk::GraphicsComponent, Ndk::NodeComponent>();
	SetUpdateOrder(5);
	SetMaximumUpdateRate(10.f);
	//SetUpdateRate(10.f);
}

void WalkerSystem::OnUpdate(float elapsed)
{
	for (auto& entity : GetEntities()) {
		
	}
}
