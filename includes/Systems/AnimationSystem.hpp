#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include <NDK/System.hpp>
#include <NDK/Component.hpp>
#include "../Components/AnimationComponent.hpp"
#include "../World/WorldMap.hpp"
#include "../SpriteLibrary.hpp"
#include "../Utils/isometric.hpp"

#include <iostream>

class AnimationSystem : public Ndk::System<AnimationSystem>
{
public:
	AnimationSystem();
	~AnimationSystem() = default;

	static Ndk::SystemIndex systemIndex;

private:
	void OnUpdate(float elapsed) override;
};

#endif // !ANIMATION_SYSTEM_H
