#include "..\..\includes\Components\ResidentialBuildingComponent.hpp"

Ndk::ComponentIndex ResidentialBuildingComponent::componentIndex;

ResidentialBuildingComponent::ResidentialBuildingComponent()
{
	m_inhabitants = 0;
	m_inhabitantsCapacity = 50;
}

unsigned int ResidentialBuildingComponent::getInhabitants()
{
	return m_inhabitants;
}

unsigned int ResidentialBuildingComponent::getInhabitantsCapacity()
{
	return m_inhabitantsCapacity;
}

bool ResidentialBuildingComponent::isFull()
{
	return m_inhabitants == m_inhabitantsCapacity;
}
