#ifndef WALKER_COMPONENT_H
#define WALKER_COMPONENT_H

#include <NDK/Component.hpp>
#include <Nazara/Math/Vector2.hpp>

struct WalkerComponent : public Ndk::Component<WalkerComponent>
{
	WalkerComponent(Nz::Vector2ui position);

	static Ndk::ComponentIndex componentIndex;

	float m_speed;

	Nz::Vector2ui m_tilePosition;
	Nz::Vector2f m_relativePosition; // Position in the tile
};

#endif