#include "../../includes/Components/BuildingComponent.hpp"

Ndk::ComponentIndex BuildingComponent::componentIndex;


BuildingComponent::BuildingComponent(Nz::Vector2ui position, Nz::Vector2ui size, std::string name) :
	m_position(position), m_size(size), m_name(name)
{
	m_state = 0;
	m_needSpriteUpdate = true;
}

unsigned int BuildingComponent::getState()
{
	return m_state;
}

std::string BuildingComponent::getName()
{
	return m_name;
}

bool BuildingComponent::needSpriteUpdate()
{
	return m_needSpriteUpdate;
}

Nz::Vector2ui BuildingComponent::getPosition()
{
	return m_position;
}

Nz::Vector2ui BuildingComponent::getSize()
{
	return m_size;
}

std::string BuildingComponent::getSpriteName()
{
	return m_name + "_" + std::to_string(m_state);
}
