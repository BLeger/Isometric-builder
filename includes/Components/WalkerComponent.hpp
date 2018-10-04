#ifndef WALKER_COMPONENT_HPP
#define WALKER_COMPONENT_HPP

#include <NDK/Component.hpp>
#include <Nazara/Math/Vector2.hpp>

#include "../Utils/isometric.hpp"
#include <deque>

struct WalkerComponent : public Ndk::Component<WalkerComponent>
{
	WalkerComponent(Nz::Vector2ui position);
	void setDestination(Nz::Vector2ui destination);

	static Ndk::ComponentIndex componentIndex;

	int m_speed;

	Nz::Vector2ui m_tilePosition;
	Nz::Vector2ui m_pixelPosition; // Position on the screen assuming scale = 1 and cameraOffset is null

	Nz::Vector2ui m_destination;

	bool m_isDestinationReachable = true;
	std::deque<Nz::Vector2ui> m_path;
};

#endif