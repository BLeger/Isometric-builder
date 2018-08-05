#include "..\..\includes\Systems\WallSystem.hpp"

Ndk::SystemIndex WallSystem::systemIndex;

WallSystem::WallSystem(WorldMap& map, SpriteLibrary& spriteLib) : m_worldMap(map), m_spriteLib(spriteLib)
{
	Requires<WallComponent, Ndk::GraphicsComponent, Ndk::NodeComponent>();
	SetUpdateOrder(5);
	SetMaximumUpdateRate(10.f);
	//SetUpdateRate(10.f);
}

void WallSystem::OnUpdate(float elapsed)
{
	for (auto& entity : GetEntities()) {
		WallComponent &wall = entity->GetComponent<WallComponent>();
		Ndk::GraphicsComponent &gc = entity->GetComponent<Ndk::GraphicsComponent>();
		gc.Clear();
		
		Nz::Vector2ui position = wall.m_position;

		int numberOfSurrondingWall = 0;
		std::vector<std::string> spriteExtensions;

		Nz::Vector2ui topLeft = Isometric::topLeftCell(position);
		Nz::Vector2ui topRight = Isometric::topRightCell(position);
		Nz::Vector2ui bottomLeft = Isometric::bottomLeftCell(position);
		Nz::Vector2ui bottomRight = Isometric::bottomRightCell(position);

		if (m_worldMap.isWall(topLeft)) {
			numberOfSurrondingWall++;
			spriteExtensions.push_back("_no");
		}

		if (m_worldMap.isWall(topRight)) {
			numberOfSurrondingWall++;
			spriteExtensions.push_back("_ne");
		}

		if (m_worldMap.isWall(bottomLeft)) {
			numberOfSurrondingWall++;
			spriteExtensions.push_back("_so");
		}

		if (m_worldMap.isWall(bottomRight)) {
			numberOfSurrondingWall++;
			spriteExtensions.push_back("_se");
		}

		if (numberOfSurrondingWall == 0) {
			gc.Attach(m_spriteLib.getSprite("wall"), position.y);
		}
		else if (numberOfSurrondingWall == 4) {

		}
		else {
			std::string spriteName = "wall";
			for (std::string s : spriteExtensions) {
				spriteName += s;
			}

			gc.Attach(m_spriteLib.getSprite(spriteName), position.y);
		}
	}
}
