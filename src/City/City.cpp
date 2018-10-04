#include "..\..\includes\City\City.hpp"

City::City(WorldMap & worldMap) : m_worldMap(worldMap)
{

}

WorldMap& City::getWorldMap()
{
	return m_worldMap;
}
