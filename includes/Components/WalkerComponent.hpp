#ifndef WALKER_COMPONENT_H
#define WALKER_COMPONENT_H

#include <NDK/Component.hpp>
#include <Nazara/Math/Vector2.hpp>

#include "../Utils/isometric.hpp"

#include <queue>

struct WalkerComponent : public Ndk::Component<WalkerComponent>
{
	WalkerComponent(Nz::Vector2ui position);

	static Ndk::ComponentIndex componentIndex;

	int m_speed;

	Nz::Vector2ui m_tilePosition;
	Nz::Vector2ui m_pixelPosition; // Position on the screen assuming scale = 1 and cameraOffset is null

	std::queue<Nz::Vector2ui> m_path;
};

#endif