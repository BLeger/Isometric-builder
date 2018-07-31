#ifndef ENVIRONMENT_TILE_COMPONENT_H
#define ENVIRONMENT_TILE_COMPONENT_H

#include <NDK/Component.hpp>

#include <iostream>

struct EnvironmentTileComponent : public Ndk::Component<EnvironmentTileComponent>
{
	EnvironmentTileComponent();

	static Ndk::ComponentIndex componentIndex;

	void test() {
		std::cout << "test" << std::endl;
	}
};

#endif