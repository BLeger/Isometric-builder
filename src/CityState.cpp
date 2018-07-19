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

void CityState::mousePressed(Nz::Vector2i mousePosition)
{
	Nz::Vector2i tilePosition = Isometric::getCellClicked(mousePosition);

	TileData tree{ TileType::Tile_1x1, "tree", -72.f, 1, 1 };
	m_worldMap.changeTile(tilePosition.x, tilePosition.y, tree);
	m_worldMap.display(m_world);
}

void CityState::mouseWheelMoved(float delta)
{
	m_worldMap.zoom(delta);
	m_worldMap.display(m_world);
}
