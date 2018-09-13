#include "..\..\includes\Systems\BuildingSystem.hpp"

Ndk::SystemIndex BuildingSystem::systemIndex;

BuildingSystem::BuildingSystem(WorldMap & worldMap) : m_worldMap(worldMap)
{
	Requires<BuildingComponent>();
	SetUpdateOrder(5);
	SetMaximumUpdateRate(10.f);
	//SetUpdateRate(10.f);
}

void BuildingSystem::OnUpdate(float elapsed)
{
	for (auto& entity : GetEntities()) {
		BuildingComponent &building = entity->GetComponent<BuildingComponent>();

		if (building.needSpriteUpdate()) {
			m_worldMap.setTileDef(building.getPosition(), building.getTileDef());
			building.updated(true);
		}
	}
}
