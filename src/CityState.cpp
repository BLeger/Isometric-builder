#include "../includes/CityState.h"

CityState::CityState(Ndk::World& world, Nz::RenderWindow& window) :
	m_world(world),
	State(),
	m_windowSize(window.GetSize()),
	m_worldMap(WorldMap{ Nz::Vector2ui{10, 10}, world }),
	m_currentTool(UserTools::PLACE_BUILDING)
{
	// Activate systems
	m_world.AddSystem<WallSystem>(m_worldMap, m_spriteLib);
	m_world.AddSystem<WalkerSystem>(m_worldMap);
	m_world.AddSystem<AnimationSystem>();


	m_worldMap.addWalker(Nz::Vector2ui{ 4, 4 }, m_spriteLib.getSprite("character_animations"));

	// Events
	Nz::EventHandler& eventHandler = window.GetEventHandler();

	eventHandler.OnMouseButtonPressed.Connect([this](const Nz::EventHandler*, const Nz::WindowEvent::MouseButtonEvent& m)
	{
		Nz::Vector2ui mousePosition {m.x, m.y};
		if (m.button == 0) // Left click
			mouseLeftPressed(mousePosition);
		else if (m.button == 2) // Right click
			mouseRightPressed(mousePosition);
		
	});
	
	eventHandler.OnMouseWheelMoved.Connect([this](const Nz::EventHandler*, const Nz::WindowEvent::MouseWheelEvent& m)
	{
		mouseWheelMoved(m.delta);
	});

	eventHandler.OnKeyPressed.Connect([this](const Nz::EventHandler*, const Nz::WindowEvent::KeyEvent& k)
	{
		keyPressed(k);
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
	m_worldMap.update();
	return true;
}

void CityState::mouseLeftPressed(Nz::Vector2ui mousePosition)
{

	Nz::Vector2ui tilePosition = Isometric::getCellClicked(mousePosition, m_worldMap.getScale(), m_worldMap.getCameraOffset());

	if (!m_worldMap.isPositionCorrect(tilePosition))
		return;

	switch (m_currentTool)
	{
	case PLACE_BUILDING:
		m_worldMap.addEnvironmentTile(tilePosition, m_spriteLib.getSprite(m_currentSpriteName));
		break;
	case REMOVE_BUILDING:
		m_worldMap.removeEnvironmentTile(tilePosition);
		break;
	case PLACE_WALL:
		m_worldMap.addWall(tilePosition);
		break;
	default:
		break;
	}
	
	m_worldMap.update();
}

void CityState::mouseRightPressed(Nz::Vector2ui mousePosition)
{
	
}

void CityState::mouseWheelMoved(float delta)
{
	m_worldMap.zoom(delta);
	//m_worldMap.display(m_world);
}

void CityState::keyPressed(const Nz::WindowEvent::KeyEvent& k)
{
	std::cout << k.code << std::endl;
	if (k.code >= 26 && k.code <= 36) {
		// F1 <-> F11
		switch (k.code)
		{
		case 26:
			m_currentTool = UserTools::PLACE_BUILDING;
			std::cout << "Place building tool" << std::endl;
			break;
		case 27:
			m_currentTool = UserTools::REMOVE_BUILDING;
			std::cout << "Remove building tool" << std::endl;
			break;
		case 28:
			m_currentTool = UserTools::PLACE_WALL;
			std::cout << "Place wall tool" << std::endl;
			break;
		default:
			break;
		}
	}

	if (k.code >= 76 && k.code <= 85) {
		// 0 <-> 9 numbers
		switch (k.code)
		{
		case 77:
			m_currentSpriteName = "tree";
			break;
		default:
			break;
		}

		std::cout << m_currentSpriteName << std::endl;
	}

	if (k.code >= 41 && k.code <= 44) {
		// Directions
		switch (k.code)
		{
		case 41:
			m_worldMap.moveCamera(Nz::Vector2f{ 0.f, -10.f });
			break;
		case 42:
			m_worldMap.moveCamera(Nz::Vector2f{ 10.f, 0.f });
			break;
		case 43:
			m_worldMap.moveCamera(Nz::Vector2f{ -10.f, 0.f });
			break;
		case 44:
			m_worldMap.moveCamera(Nz::Vector2f{ 0.f, 10.f });
			break;
		default:
			break;
		}
	}
}
