#include "../../includes/Components/AnimationComponent.hpp"

Ndk::ComponentIndex AnimationComponent::componentIndex;


AnimationComponent::AnimationComponent(Nz::SpriteRef & sprite, Nz::Vector2f imgSize, unsigned int animationLine) :
	m_sprite(sprite), m_imageSize(imgSize), m_animationLine(animationLine)
{
	m_currentStep = 0;
	m_numberOfSteps = sprite->GetSize().x / imgSize.x;
	m_timeSinceStepChange = 0;
	m_enabled = false;

	m_sprite->SetSize(m_imageSize);
	m_sprite->SetTextureRect(Nz::Rectui{ 0, 0, (unsigned int)(m_imageSize.x), (unsigned int)(m_imageSize.y) });
}

void AnimationComponent::enable(bool b)
{
	m_enabled = b;
}

void AnimationComponent::disable()
{
	m_enabled = false;
}

bool AnimationComponent::isEnabled()
{
	return m_enabled;
}

void AnimationComponent::addTime(float elapsed)
{
	m_timeSinceStepChange += elapsed;
}

bool AnimationComponent::timeToStep()
{
	return m_timeSinceStepChange > 0.3;
}

void AnimationComponent::incrementStep()
{
	m_currentStep++;

	if (m_currentStep >= m_numberOfSteps)
		m_currentStep = 0;

	m_timeSinceStepChange = 0;

	m_sprite->SetSize(m_imageSize);
	m_sprite->SetTextureRect(Nz::Rectui{ (unsigned int)(m_currentStep * m_imageSize.x), (unsigned int)(m_animationLine * m_imageSize.y), (unsigned int)(m_imageSize.x), (unsigned int)(m_imageSize.y) });
}

Nz::SpriteRef & AnimationComponent::getSprite()
{
	return m_sprite;
}
