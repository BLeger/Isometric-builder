#include "..\..\includes\Systems\WalkerSystem.hpp"

Ndk::SystemIndex WalkerSystem::systemIndex;

WalkerSystem::WalkerSystem(WorldMap& map) : m_worldMap(map)
{
	Requires<WalkerComponent, Ndk::GraphicsComponent, Ndk::NodeComponent>();
	SetUpdateOrder(5);
	SetMaximumUpdateRate(10.f);
	//SetUpdateRate(10.f);
}

void WalkerSystem::OnUpdate(float elapsed)
{
	float mapScale = m_worldMap.getScale();
	Nz::Vector2f cameraOffset = m_worldMap.getCameraOffset();

	for (auto& entity : GetEntities()) {
 		WalkerComponent &walker = entity->GetComponent<WalkerComponent>();
		Ndk::NodeComponent &nc = entity->GetComponent<Ndk::NodeComponent>();

		bool animation = false;

		if (!walker.m_path.empty()) {
			Nz::Vector2ui currentTile = walker.m_tilePosition;
			Nz::Vector2ui nextTileInPath = walker.m_path.front();

			Direction direction;
			try {
				direction = Isometric::getDirection(currentTile, nextTileInPath);

				switch (direction)
				{
				case NORTH_EST:
					walker.m_pixelPosition.x += walker.m_speed * 2;
					walker.m_pixelPosition.y -= walker.m_speed;
					break;
				case NORTH_WEST:
					walker.m_pixelPosition.x -= walker.m_speed * 2;
					walker.m_pixelPosition.y -= walker.m_speed;
					break;
				case SOUTH_EST:
					walker.m_pixelPosition.x += walker.m_speed * 2;
					walker.m_pixelPosition.y += walker.m_speed;
					break;
				case SOUTH_WEST:
					walker.m_pixelPosition.x -= walker.m_speed * 2;
					walker.m_pixelPosition.y += walker.m_speed;
					break;
				default:
					break;
				}

				animation = true;
			}
			catch (std::exception e) {
				// IF the two cells are not next to each other
				// Need to get another path
			}

			// Display the walker at it's new position
			nc.SetScale(mapScale);
			nc.SetPosition(Nz::Vector2f{ (float)walker.m_pixelPosition.x * mapScale + cameraOffset.x, (float)walker.m_pixelPosition.y * mapScale + cameraOffset.y });

			// Update the tile position
			walker.m_tilePosition = Isometric::pixelToCell(walker.m_pixelPosition, mapScale, cameraOffset);

			if (entity->HasComponent<AnimationComponent>()) {
				// Enable or disable the walker animation component
				entity->GetComponent<AnimationComponent>().enable(animation);
			}
		}
	}
}
