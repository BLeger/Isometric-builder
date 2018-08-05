#ifndef ENVIRONMENT_TILE_COMPONENT_H
#define ENVIRONMENT_TILE_COMPONENT_H

#include <NDK/Component.hpp>

struct EnvironmentTileComponent : public Ndk::Component<EnvironmentTileComponent>
{
	EnvironmentTileComponent();

	static Ndk::ComponentIndex componentIndex;
};

#endif