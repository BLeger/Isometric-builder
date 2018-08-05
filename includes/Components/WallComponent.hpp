#ifndef WALL_COMPONENT_H
#define WALL_COMPONENT_H

#include <NDK/Component.hpp>

struct WallComponent : public Ndk::Component<WallComponent>
{
	WallComponent();

	static Ndk::ComponentIndex componentIndex;
};

#endif