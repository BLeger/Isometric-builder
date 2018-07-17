#include "../includes/CityState.h"

CityState::CityState(Ndk::World& world, Nz::RenderWindow& window) :
	State(),
	m_windowSize(window.GetSize()),
	m_worldMap(WorldMap{10, 10})
{
	// Creating a world
	//m_worldMap = WorldMap{20, 20};
	
	TileData grass{ TileType::Tile_1x1, "grass", 0.f, 1, 1 };
	TileData tree{ TileType::Tile_1x1, "tree", -72.f, 1, 1 };
	TileData batiment{ TileType::Object_NxN_Attach, "batiment", -185.f, 2, 2 };

	m_worldMap.generateMap(grass);
	m_worldMap.changeTile(2, 2, tree);

	Building b{ batiment };
	m_worldMap.addBuilding(b, 3, 5);

	m_worldMap.display(world);
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