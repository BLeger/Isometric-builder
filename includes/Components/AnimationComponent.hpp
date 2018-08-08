#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <NDK/Component.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <NDK/Application.hpp>

struct AnimationComponent : public Ndk::Component<AnimationComponent>
{
	AnimationComponent(Nz::SpriteRef& sprite, Nz::Vector2f imgSize, unsigned int animationLine = 0);

	void enable(bool b = true);
	void disable();

	void addTime(float elapsed);
	bool timeToStep();
	void incrementStep();

	Nz::SpriteRef& getSprite();

	static Ndk::ComponentIndex componentIndex;

private:

	Nz::SpriteRef& m_sprite;
	Nz::Vector2f m_imageSize; // Size of each image on the sprite
	unsigned int m_animationLine; // Line of the animation on the sprite

	bool m_enabled;
	unsigned int m_currentStep;
	unsigned int m_numberOfSteps;

	float m_timeSinceStepChange;
};

#endif