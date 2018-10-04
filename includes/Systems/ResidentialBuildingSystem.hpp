#ifndef RESIDENTIAL_BUILDING_SYSTEM_H
#define RESIDENTIAL_BUILDING_SYSTEM_H

#include <NDK/System.hpp>
#include <NDK/Component.hpp>
#include "../Components/ResidentialBuildingComponent.hpp"
#include "../World/WorldMap.hpp"
#include "../City/City.hpp"
#include "../Utils/isometric.hpp"

#include <iostream>

class ResidentialBuildingSystem : public Ndk::System<ResidentialBuildingSystem>
{
public:
	ResidentialBuildingSystem(City &city, SpriteLibrary& spriteLib);
	~ResidentialBuildingSystem() = default;

	static Ndk::SystemIndex systemIndex;

private:
	City &m_city;
	SpriteLibrary &m_spriteLib;

	void OnUpdate(float elapsed) override;
};

#endif // !RESIDENTIAL_BUILDING_SYSTEM_H
