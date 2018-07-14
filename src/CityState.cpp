#include "../includes/CityState.h"

CityState::CityState(Ndk::World& world, Nz::RenderWindow& window) :
	State(),
	m_windowSize(window.GetSize()),
	m_worldMap(WorldMap{10, 10})
{
	// Creating a world
	//m_worldMap = WorldMap{20, 20};
	m_worldMap.display(world);
}

void CityState::Enter(Ndk::StateMachine& fsm)
{
}

void CityState::Leave(Ndk::StateMachine& fsm)
{
}

bool CityState::Update(Ndk::StateMachine& fsm, float elapsedTime)
{
	
	return true;
}