#ifndef WALL_COMPONENT_H
#define WALL_COMPONENT_H

#include <NDK/Component.hpp>
#include <Nazara/Math/Vector2.hpp>

struct WallComponent : public Ndk::Component<WallComponent>
{
	WallComponent(Nz::Vector2ui position);

	static Ndk::ComponentIndex componentIndex;

	Nz::Vector2ui m_position;
};

#endif