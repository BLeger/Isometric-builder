#include "../../includes/Components/WalkerComponent.hpp"

Ndk::ComponentIndex WalkerComponent::componentIndex;

WalkerComponent::WalkerComponent(Nz::Vector2ui position) : m_tilePosition(position)
{
	m_pixelPosition = Nz::Vector2ui(200, 100);
	//m_relativePosition = Nz::Vector2f{ 0.5f, 0.5f };
}
