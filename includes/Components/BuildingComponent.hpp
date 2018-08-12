#ifndef BUILDING_COMPONENT_H
#define BUILDING_COMPONENT_H

#include <NDK/Component.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <NDK/Application.hpp>

#include <string>

struct BuildingComponent : public Ndk::Component<BuildingComponent>
{
	BuildingComponent(Nz::Vector2ui position, Nz::Vector2ui size, std::string name);

	unsigned int getState();
	std::string getName();
	bool needSpriteUpdate();

	Nz::Vector2ui getPosition();
	Nz::Vector2ui getSize();

	std::string getSpriteName();

	void updated(bool b = true);

	int getRenderOrder();
	void setRenderOrder(int order);

	static Ndk::ComponentIndex componentIndex;

private:
	int m_renderOrder = 0;
	unsigned int m_state;
	std::string m_name;

	Nz::Vector2ui m_position;
	Nz::Vector2ui m_size;

	bool m_needSpriteUpdate;
};

#endif