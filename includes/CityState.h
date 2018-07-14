#ifndef CITY_STATE_H
#define CITY_STATE_H

#include <NDK/Entity.hpp>
#include <NDK/State.hpp>
#include <NDK/StateMachine.hpp>
#include <NDK/World.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>

class CityState : public Ndk::State {

public:
	CityState(Ndk::World& world, Nz::RenderWindow& window);
	void Enter(Ndk::StateMachine& fsm) override;
	void Leave(Ndk::StateMachine& fsm) override;
	bool Update(Ndk::StateMachine& fsm, float elapsedTime) override;

private:
	const Nz::Vector2f m_windowSize;
};

#endif // !CITY_STATE_H
