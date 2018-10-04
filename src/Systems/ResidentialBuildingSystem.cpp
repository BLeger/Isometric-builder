#include "..\..\includes\Systems\ResidentialBuildingSystem.hpp"

Ndk::SystemIndex ResidentialBuildingSystem::systemIndex;

ResidentialBuildingSystem::ResidentialBuildingSystem(City &city, SpriteLibrary& spriteLib) : m_city(city), m_spriteLib(spriteLib)
{
	Requires<ResidentialBuildingComponent, BuildingComponent>();
	SetUpdateOrder(5);
	SetMaximumUpdateRate(10.f);
}

void ResidentialBuildingSystem::OnUpdate(float elapsed)
{
	WorldMap &map = m_city.getWorldMap();

	for (auto& entity : GetEntities()) {
		ResidentialBuildingComponent &res = entity->GetComponent<ResidentialBuildingComponent>();
		BuildingComponent &building = entity->GetComponent<BuildingComponent>();
	
		if (!res.isFull()) {

			WalkerComponent &wc = map.addWalker(Nz::Vector2ui{ 0, 0 }, m_spriteLib.getSprite("character_animations"));

			std::vector<Nz::Vector2ui> entryTiles = Isometric::buildingEntryTiles(building.getPosition(), building.getSize());

			bool entryTileAvailable = false;

			for (auto tile : entryTiles) {
				if (map.isPositionAvailable(tile)) {
					wc.setDestination(tile);
					entryTileAvailable = true;
					break;
				}
			}
			
			if (!entryTileAvailable)
				std::cout << "A building as no entry point available" << std::endl;

			res.test();
		}
	}
}
