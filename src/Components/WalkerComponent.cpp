#include "../../includes/Components/WalkerComponent.hpp"

Ndk::ComponentIndex WalkerComponent::componentIndex;

WalkerComponent::WalkerComponent(Nz::Vector2ui position) : m_tilePosition(position)
{
	m_pixelPosition = Isometric::cellPixelCenter(position);
	//m_relativePosition = Nz::Vector2f{ 0.5f, 0.5f };
	m_speed = 2;

	m_path.push(Nz::Vector2ui{ 0, 1 });
}
