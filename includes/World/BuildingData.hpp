#ifndef BUILDING_DATA
#define BUILDING_DATA

#include <string>
#include <Nazara/Math\Vector2.hpp>

struct BuildingData {
	unsigned int ID;
	std::string materialName;
	Nz::Vector2ui size;
};

/*BuildingData house{
	0,
	"house.png",
	Nz::Vector2ui{2, 2}
};*/

#endif // !BUILDING_DATA
