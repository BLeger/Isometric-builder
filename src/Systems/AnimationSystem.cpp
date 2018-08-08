#include "..\..\includes\Systems\AnimationSystem.hpp"

Ndk::SystemIndex AnimationSystem::systemIndex;

AnimationSystem::AnimationSystem()
{
	Requires<AnimationComponent, Ndk::GraphicsComponent, Ndk::NodeComponent>();
	SetUpdateOrder(5);
	SetMaximumUpdateRate(10.f);
	//SetUpdateRate(10.f);
}

void AnimationSystem::OnUpdate(float elapsed)
{
	for (auto& entity : GetEntities()) {
		Ndk::GraphicsComponent &gc = entity->GetComponent<Ndk::GraphicsComponent>();
		AnimationComponent &ac = entity->GetComponent<AnimationComponent>();
	
		ac.addTime(elapsed);
		if (ac.timeToStep()) 
			ac.incrementStep();

		gc.Clear();
		gc.Attach(ac.getSprite());
	}
}
