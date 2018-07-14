#include "../includes/CityState.h"

CityState::CityState(Ndk::World& world, Nz::RenderWindow& window) :
	State(),
	m_windowSize(window.GetSize())
{

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