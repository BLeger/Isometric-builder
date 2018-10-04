#ifndef CITY_HPP
#define CITY_HPP

#include "../World/WorldMap.hpp"

class City {

public:
	City(WorldMap& worldMap);

	WorldMap& getWorldMap();

private:
	WorldMap &m_worldMap;

	int m_money;
	unsigned int m_inhabitants;

};


#endif // !CITY_HPP
