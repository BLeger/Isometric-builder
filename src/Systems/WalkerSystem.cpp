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
	float mapScale = m_worldMap.getScale();
	Nz::Vector2f cameraOffset = m_worldMap.getCameraOffset();

	for (auto& entity : GetEntities()) {
 		WalkerComponent &walker = entity->GetComponent<WalkerComponent>();
		Ndk::NodeComponent &nc = entity->GetComponent<Ndk::NodeComponent>();

		// Display the walker at it's new position
		nc.SetScale(mapScale);
		nc.SetPosition(Nz::Vector2f{ (float)walker.m_pixelPosition.x * mapScale + cameraOffset.x, (float)walker.m_pixelPosition.y * mapScale + cameraOffset.y });
		
		// Update the tile position
		walker.m_tilePosition = Isometric::getCellClicked(walker.m_pixelPosition, mapScale, cameraOffset);
	}
}
