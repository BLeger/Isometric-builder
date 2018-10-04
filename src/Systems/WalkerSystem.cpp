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

		// If the walker has a destination but not any path
		if (walker.m_path.empty() && walker.m_destination != walker.m_tilePosition && walker.m_isDestinationReachable) {
			PathFinder p{ m_worldMap };
			walker.m_path = p.findPath(walker.m_tilePosition, walker.m_destination);

			if (walker.m_path.empty()) {
				walker.m_isDestinationReachable = false;
				std::cout << "A walker cannot reach his destination" << std::endl;
			}
		}

		if (!walker.m_path.empty()) {
			Nz::Vector2ui currentTile = walker.m_tilePosition;
			Nz::Vector2ui nextTileInPath = walker.m_path.front();

			// Check if the walker is already on that tile
			if (currentTile.x == nextTileInPath.x && currentTile.y == nextTileInPath.y) {
				walker.m_path.pop_front();
				if (!walker.m_path.empty())
					nextTileInPath = walker.m_path.front();
			}
			
			// Get the direction the walker need to follow
			// And move it's position according to it
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
				std::cout << "[Walker system] path error" << std::endl;
			}

			// Display the walker at it's new position
			nc.SetScale(mapScale);
			nc.SetPosition(Nz::Vector2f{ (float)walker.m_pixelPosition.x * mapScale, (float)walker.m_pixelPosition.y * mapScale });

			// Update the tile position
			walker.m_tilePosition = Isometric::pixelToCell(walker.m_pixelPosition, mapScale, cameraOffset);

			if (entity->HasComponent<AnimationComponent>()) {
				// Enable or disable the walker animation component
				entity->GetComponent<AnimationComponent>().enable(animation);
			}
		}
	}
}
