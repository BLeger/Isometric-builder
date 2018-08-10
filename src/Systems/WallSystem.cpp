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
		if (wall.m_needsUpdate) {
			wall.m_needsUpdate = false;
			
			Ndk::GraphicsComponent &gc = entity->GetComponent<Ndk::GraphicsComponent>();
			gc.Clear();

			Nz::Vector2ui position = wall.m_position;

			int numberOfSurrondingWall = 0;
			std::vector<std::string> spriteExtensions;

			std::vector<std::pair<std::string, Nz::Vector2ui>> surrongingCells{};
			surrongingCells.push_back(std::make_pair("_no", Isometric::topLeftCell(position)));
			surrongingCells.push_back(std::make_pair("_ne", Isometric::topRightCell(position)));
			surrongingCells.push_back(std::make_pair("_so", Isometric::bottomLeftCell(position)));
			surrongingCells.push_back(std::make_pair("_se", Isometric::bottomRightCell(position)));

			for (auto surronding : surrongingCells) { 
				if (m_worldMap.isWall(surronding.second)) {
					numberOfSurrondingWall++;
					spriteExtensions.push_back(surronding.first);
				}
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
}
