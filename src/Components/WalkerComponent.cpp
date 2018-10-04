#include "../../includes/Components/WalkerComponent.hpp"

Ndk::ComponentIndex WalkerComponent::componentIndex;

WalkerComponent::WalkerComponent(Nz::Vector2ui position) : m_tilePosition(position), m_destination(position)
{
	m_pixelPosition = Isometric::cellPixelCenter(position);
	//m_relativePosition = Nz::Vector2f{ 0.5f, 0.5f };
	m_speed = 2;
}

void WalkerComponent::setDestination(Nz::Vector2ui destination)
{
	m_destination = destination;
	m_isDestinationReachable = true;
}