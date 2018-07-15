#include "../../includes/World/Building.hpp"

Building::Building(int size_x, int size_y, std::string materialName) :
m_size_x(size_x),
m_size_y(size_y),
m_materialName(materialName) 
{

}

std::string Building::getMaterialName()
{
	return m_materialName;
}

Nz::Vector2<int> Building::getSize()
{
	return Nz::Vector2<int>(m_size_x, m_size_y);
}
