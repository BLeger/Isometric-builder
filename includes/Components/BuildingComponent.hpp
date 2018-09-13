#ifndef BUILDING_COMPONENT_H
#define BUILDING_COMPONENT_H

#include <NDK/Component.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <NDK/Application.hpp>

#include <string>

#include "../../includes/Config/Tiles.hpp"

struct BuildingComponent : public Ndk::Component<BuildingComponent>
{
	BuildingComponent(Nz::Vector2ui position, const TileDef tile);

	unsigned int getState();
	std::string getName();
	bool needSpriteUpdate();

	Nz::Vector2ui getPosition();
	Nz::Vector2ui getSize();
	TileDef getTileDef();

	void updated(bool b = true);

	static Ndk::ComponentIndex componentIndex;

private:
	unsigned int m_state;

	Nz::Vector2ui m_position;

	TileDef m_tileDef;

	bool m_needSpriteUpdate;
};

#endif