#include "../../includes/World/Building.hpp"

Building::Building(TileData& tile) :
m_size_x(tile.width),
m_size_y(tile.height),
m_materialName(tile.materialName),
m_tileData(tile)
{

}

TileData & Building::getTileData()
{
	return m_tileData;
}

std::string Building::getMaterialName()
{
	return m_materialName;
}

Nz::Vector2<int> Building::getSize()
{
	return Nz::Vector2<int>(m_size_x, m_size_y);
}
