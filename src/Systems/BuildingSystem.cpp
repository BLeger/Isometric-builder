#include "..\..\includes\Systems\BuildingSystem.hpp"

Ndk::SystemIndex BuildingSystem::systemIndex;

BuildingSystem::BuildingSystem(WorldMap & worldMap, SpriteLibrary & spriteLib) :
	m_worldMap(worldMap), m_spriteLib(spriteLib)
{
	Requires<BuildingComponent, Ndk::GraphicsComponent, Ndk::NodeComponent>();
	SetUpdateOrder(5);
	SetMaximumUpdateRate(10.f);
	//SetUpdateRate(10.f);
}

void BuildingSystem::OnUpdate(float elapsed)
{
	for (auto& entity : GetEntities()) {
		BuildingComponent &building = entity->GetComponent<BuildingComponent>();

		if (building.needSpriteUpdate()) {
			Ndk::GraphicsComponent &gc = entity->GetComponent<Ndk::GraphicsComponent>();

			Nz::SpriteRef& spr = m_spriteLib.getSprite(building.getSpriteName());
			gc.Clear();
			gc.Attach(spr, building.getRenderOrder());

			building.updated(true);
		}
	}
}
