#ifndef RESIDENTIAL_BUILDING_COMPONENT_H
#define RESIDENTIAL_BUILDING_COMPONENT_H

#include <NDK/Component.hpp>
#include <Nazara/Math/Vector2.hpp>

struct ResidentialBuildingComponent : public Ndk::Component<ResidentialBuildingComponent>
{
	ResidentialBuildingComponent();

	static Ndk::ComponentIndex componentIndex;

	unsigned int getInhabitants();
	unsigned int getInhabitantsCapacity();
	bool isFull();

	void test() {
		m_inhabitants = m_inhabitantsCapacity;
	}

private:
	unsigned int m_inhabitants;
	unsigned int m_inhabitantsCapacity;

};

#endif