#include "../../includes/World/Building.hpp"

Building::Building(BuildingData data, Nz::Vector2ui position) :
m_materialID(data.ID),
m_size(data.size),
m_position(position)
{

}

unsigned int Building::getMaterialID()
{
	return m_materialID;
}

Nz::Vector2ui Building::getSize()
{
	return m_size;
}

Nz::Vector2ui Building::getPosition()
{
	return m_position;
}
