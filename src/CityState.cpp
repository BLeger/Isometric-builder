#include "../includes/CityState.h"

CityState::CityState(Ndk::World& world, Nz::RenderWindow& window) :
	m_world(world),
	State(),
	m_windowSize(window.GetSize()),
	m_worldMap(WorldMap{10, 10})
{
	// Creating a world
	//m_worldMap = WorldMap{20, 20};
	
	TileData grass{ TileType::Tile_1x1, "grass", 0.f, 1, 1 };
	TileData tree{ TileType::Tile_1x1, "tree", -72.f, 1, 1 };
	TileData batiment{ TileType::Object_NxN_Attach, "batiment", -185.f, 2, 2 };

	m_worldMap.generateMap(world, grass);
	m_worldMap.changeTile(2, 2, tree);

	Building b{ batiment, world, 500 };
	m_worldMap.addBuilding(b, 4, 6);
	//m_worldMap.addBuilding(b, 3, 5);
	//m_worldMap.addBuilding(b, 5, 7);

	

	m_worldMap.display(world);

	Nz::EventHandler& eventHandler = window.GetEventHandler();

	eventHandler.OnMouseButtonPressed.Connect([this](const Nz::EventHandler*, const Nz::WindowEvent::MouseButtonEvent& m)
	{
		if (m.button == 0) {
			// Left click
			mousePressed(Nz::Vector2i(m.x, m.y));
		}
		
	});

	eventHandler.OnMouseWheelMoved.Connect([this](const Nz::EventHandler*, const Nz::WindowEvent::MouseWheelEvent& m)
	{
		mouseWheelMoved(m.delta);
	});
}

void CityState::Enter(Ndk::StateMachine& fsm)
{
}

void CityState::Leave(Ndk::StateMachine& fsm)
{
}

bool CityState::Update(Ndk::StateMachine& fsm, float elapsedTime)
{
	//std::cout << "update" << std::endl;
	//m_worldMap.display(m_world);
	return true;
}

void CityState::mousePressed(Nz::Vector2i position)
{
	float larg_tile = 133.f * 0.5f;
	float heut_tile = 80.f * 0.5f;

	Nz::Vector2f testCenter = Isometric::cellCenter(0, 1, larg_tile, heut_tile);
	std::cout << testCenter.x << " / " << testCenter.y << std::endl;

	std::cout << "CART x: " << position.x << " y: " << position.y << std::endl;

	int tileX = position.x / larg_tile; // Colonne sur ligne paire
	int tileY = (position.y / heut_tile);

	Nz::Vector2f center = Isometric::cellCenter(tileX, tileY, larg_tile, heut_tile);
	

	float tileY_offset = (position.y - (tileY * heut_tile)) / heut_tile;
	float tileX_offset = (position.x - (tileX * larg_tile)) / larg_tile; // In percent

	tileY *= 2;

	std::cout << "tileX : " << tileX << " tileY : " << tileY << std::endl;
	std::cout << "X offset " << tileX_offset << " Y offset " << tileY_offset << std::endl;

	Nz::Vector2i other;
	/*if (tileX_offset > 0.5f) {
		if (tileY_offset > 0.5f) {
			other = Isometric::bottomRightCell(tileX, tileY);
		}
		else {
			other = Isometric::topRightCell(tileX, tileY);
		}
	}
	else {
		if (tileY_offset > 0.5f) {
			other = Isometric::bottomLeftCell(tileX, tileY);
		}
		else {
			other = Isometric::topLeftCell(tileX, tileY);
		}
	}*/

	std::vector<Nz::Vector2i> others{ Isometric::bottomLeftCell(tileX, tileY), Isometric::topLeftCell(tileX, tileY),
									  Isometric::bottomRightCell(tileX, tileY), Isometric::topRightCell(tileX, tileY) };

	Nz::Vector2i bestPos{ tileX, tileY };
	float bestDist = Isometric::distanceToCenter(tileX, tileY, position.x, position.y, larg_tile, heut_tile);
	
	for (Nz::Vector2i other : others) {
		float d2 = Isometric::distanceToCenter(other.x, other.y, position.x, position.y, larg_tile, heut_tile);
		std::cout << "Other : " << other.x << " - " << other.y << " Dist : " << d2 << std::endl;
		if (d2 < bestDist) {
			bestDist = d2;
			bestPos = other;
		}
	}

	std::cout << "RESULT : " << bestPos.x << " - " << bestPos.y << std::endl;
	TileData tree{ TileType::Tile_1x1, "tree", -72.f, 1, 1 };
	m_worldMap.changeTile(bestPos.x, bestPos.y, tree);
	m_worldMap.display(m_world);

	/*std::cout << "other tileX : " << other.x << " tileY : " << other.y << std::endl;

	float d1 = Isometric::distanceToCenter(tileX, tileY, position.x, position.y, larg_tile, heut_tile);
	float d2 = Isometric::distanceToCenter(other.x, other.y, position.x, position.y, larg_tile, heut_tile);
	std::cout << "d1 : " << d1 << " d2 " << d2 << std::endl;

	if (d1 < d2) {
		std::cout << "RESULT : " << tileX << " - " << tileY << std::endl;
	}
	else {
		std::cout << "RESULT : " << other.x << " - " << other.y << std::endl;
	}*/

	std::cout << "\n\n" << std::endl;
	
	/*Ndk::EntityHandle viewEntity = m_world.CreateEntity();
	Ndk::NodeComponent& node = viewEntity->AddComponent<Ndk::NodeComponent>();

	Nz::TextSpriteRef textSprite = Nz::TextSprite::New();
	textSprite->Update(Nz::SimpleTextDrawer::Draw("Hello world !", 15));
	node.SetPosition(Nz::Vector3f(position.x, position.y, 0));

	Ndk::GraphicsComponent& graphicsComponent = viewEntity->AddComponent<Ndk::GraphicsComponent>();
	graphicsComponent.Attach(textSprite);*/

}

void CityState::mouseWheelMoved(float delta)
{
	m_worldMap.zoom(delta);
	m_worldMap.display(m_world);
}
