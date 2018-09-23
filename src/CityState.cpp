#include "../includes/CityState.h"

CityState::CityState(Ndk::World& world, Nz::RenderWindow& window, Ndk::EntityHandle& camera) :
	m_world(world),
	State(),
	m_windowSize(window.GetSize()),
	m_worldMap(WorldMap{ Nz::Vector2ui{70, 140}, world }),
	m_currentTool(UserTools::PLACE_BUILDING),
	m_camera(camera)
{
	m_worldMap.generateTerrain(m_spriteLib);

	// Activate systems
	m_world.AddSystem<WallSystem>(m_worldMap);
	m_world.AddSystem<WalkerSystem>(m_worldMap);
	m_world.AddSystem<AnimationSystem>();
	m_world.AddSystem<BuildingSystem>(m_worldMap);

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

	eventHandler.OnMouseButtonReleased.Connect([this](const Nz::EventHandler*, const Nz::WindowEvent::MouseButtonEvent& m)
	{
		Nz::Vector2ui mousePosition{ m.x, m.y };
		if (m.button == 0) // Left click
			mouseLeftReleased(mousePosition);

	});
	
	eventHandler.OnMouseWheelMoved.Connect([this](const Nz::EventHandler*, const Nz::WindowEvent::MouseWheelEvent& m)
	{
		mouseWheelMoved(m.delta);
	});

	eventHandler.OnKeyPressed.Connect([this](const Nz::EventHandler*, const Nz::WindowEvent::KeyEvent& k)
	{
		keyPressed(k);
	}); 

	eventHandler.OnMouseMoved.Connect([this](const Nz::EventHandler*, const Nz::WindowEvent::MouseMoveEvent& m)
	{
		mouseMoved(Nz::Vector2ui{ m.x, m.y });
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
	return true;
}

void CityState::mouseLeftPressed(Nz::Vector2ui mousePosition)
{
	Nz::Vector2ui tilePosition = Isometric::pixelToCell(mousePosition, m_worldMap.getScale(), -m_worldMap.getCameraOffset());
	tilePosition = m_worldMap.getHoveredCell(tilePosition);

	if (!m_worldMap.isPositionCorrect(tilePosition))
		return;

	switch (m_currentTool)
	{
	case PLACE_BUILDING:
		m_worldMap.addBuilding(tilePosition, m_currentTile);
		//m_worldMap.addEnvironmentTile(tilePosition, m_currentTile);
		break;
	case REMOVE_BUILDING:
		m_worldMap.removeBuilding(tilePosition);
		//m_worldMap.removeEnvironmentTile(tilePosition);
		break;
	case PLACE_WALL:
		m_worldMap.addWall(tilePosition);
		break;
	case PLACE_ROAD:
		m_placingRoad = true;
		m_roadPlacementStart = tilePosition;
		break;
	default:
		break;
	}
}

void CityState::mouseLeftReleased(Nz::Vector2ui mousePosition)
{
	if (m_currentTool == UserTools::PLACE_ROAD) {
		m_placingRoad = false;

		Nz::Vector2ui tilePosition = Isometric::pixelToCell(mousePosition, m_worldMap.getScale(), -m_worldMap.getCameraOffset());
		tilePosition = m_worldMap.getHoveredCell(tilePosition);
		PathFinder p{ m_worldMap };

		std::deque<Nz::Vector2ui> path = p.findPath(m_roadPlacementStart, tilePosition);
		while(!path.empty()){
			Nz::Vector2ui pos = path.front();
			path.pop_front();
			m_worldMap.addRoad(pos);
		}
	}
}

void CityState::mouseRightPressed(Nz::Vector2ui mousePosition)
{
	
}

void CityState::mouseWheelMoved(float delta)
{
	m_worldMap.zoom(delta);
}

void CityState::mouseMoved(Nz::Vector2ui mousePosition)
{	
	m_lastMousePosition = mousePosition;

	if (!m_actionPreview) {
		m_worldMap.resetPreview();
		return;
	}

	Nz::Vector2ui tilePosition = Isometric::pixelToCell(mousePosition, m_worldMap.getScale(), -m_worldMap.getCameraOffset());
	tilePosition = m_worldMap.getHoveredCell(tilePosition);

	if (m_currentTool == UserTools::PLACE_ROAD && m_placingRoad) {
		if (m_lastMouseTilePosition == tilePosition)
			return;

		m_lastMouseTilePosition = tilePosition;

		PathFinder p{ m_worldMap };

		m_worldMap.resetPreview();

		std::deque<Nz::Vector2ui> path = p.findPath(m_roadPlacementStart, tilePosition);
		while (!path.empty()) {
			Nz::Vector2ui pos = path.front();
			path.pop_front();
			m_worldMap.previewEntity(pos, ROAD);
		}
	}
	else if (m_worldMap.isPositionCorrect(tilePosition)) {
		// Preview a single entity / tile
		m_worldMap.resetPreview();
		m_worldMap.previewEntity(tilePosition, m_currentTile);
	}
}

void CityState::keyPressed(const Nz::WindowEvent::KeyEvent& k)
{
	//std::cout << k.code << std::endl;
	if (k.code >= 26 && k.code <= 36) {
		// F1 <-> F11
		bool actionPreview = false;
		switch (k.code)
		{
		case 26:
			m_currentTool = UserTools::PLACE_BUILDING;
			std::cout << "Place building tool" << std::endl;
			actionPreview = true;
			m_currentTile = HOUSE;
			break;
		case 27:
			m_currentTool = UserTools::REMOVE_BUILDING;
			std::cout << "Remove building tool" << std::endl;
			break;
		case 28:
			m_currentTool = UserTools::PLACE_WALL;
			std::cout << "Place wall tool" << std::endl;
			actionPreview = true;
			m_currentTile = WALL;
			break;
		case 29:
			m_currentTool = UserTools::PLACE_ROAD;
			std::cout << "Place road tool" << std::endl;
			actionPreview = true;
			m_currentTile = ROAD;
			break;
		default:
			break;
		}

		m_actionPreview = actionPreview;
		mouseMoved(m_lastMousePosition);
	}

	if (k.code >= 76 && k.code <= 85) {
		// 0 <-> 9 numbers
		switch (k.code)
		{
		case 77:
			m_currentTile = TREE;
			break;
		default:
			break;
		}

	}

	if (k.code >= 41 && k.code <= 44) {
		// Directions

		float movingStep = 20.f;

		Ndk::NodeComponent &nc = m_camera->GetComponent<Ndk::NodeComponent>();

		Nz::Vector3f position = nc.GetPosition();
		Nz::Vector2f newCameraOffset{ position.x, position.y };
		switch (k.code)
		{
		case 41:
			newCameraOffset.y += movingStep;
			break;
		case 42:
			newCameraOffset.x -= movingStep;
			break;
		case 43:
			newCameraOffset.x += movingStep;
			break;
		case 44:
			newCameraOffset.y -= movingStep;
			break;
		default:
			break;
		}
		nc.SetPosition(newCameraOffset);
		m_worldMap.setCameraOffset(newCameraOffset);
	}
}
