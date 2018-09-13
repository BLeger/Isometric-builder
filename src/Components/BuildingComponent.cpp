#include "../../includes/Components/BuildingComponent.hpp"

Ndk::ComponentIndex BuildingComponent::componentIndex;


BuildingComponent::BuildingComponent(Nz::Vector2ui position, const TileDef tile) :
	m_position(position), m_tileDef(tile)
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
	return m_tileDef.name;
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
	return m_tileDef.tileSize;
}

TileDef BuildingComponent::getTileDef()
{
	return m_tileDef;
}

void BuildingComponent::updated(bool b)
{
	m_needSpriteUpdate = b;
}
