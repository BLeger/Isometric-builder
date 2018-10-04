#include "../includes/CityState.hpp"

CityState::CityState(Ndk::World& world, Nz::RenderWindow& window, Ndk::EntityHandle& camera) :
	m_world(world),
	State(),
	m_windowSize(window.GetSize()),
	m_worldMap(WorldMap{ Nz::Vector2ui{70, 140}, world }),
	m_city(City{m_worldMap}),
	m_userTool(UserTools::PLACE_BUILDING),
	m_camera(camera)
{
	m_worldMap.generateTerrain(m_spriteLib);

	// Activate systems
	m_world.AddSystem<WallSystem>(m_worldMap);
	m_world.AddSystem<WalkerSystem>(m_worldMap);
	m_world.AddSystem<AnimationSystem>();
	m_world.AddSystem<BuildingSystem>(m_worldMap);
	m_world.AddSystem<ResidentialBuildingSystem>(m_city, m_spriteLib);

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

	switch (m_userTool)
	{
	case PLACE_BUILDING:
		m_worldMap.addBuilding(tilePosition, m_currentTile);
		//m_worldMap.addEnvironmentTile(tilePosition, m_currentTile);
		break;
	case DESTROY:
		m_worldMap.removeBuilding(tilePosition);
		//m_worldMap.removeEnvironmentTile(tilePosition);
		break;
	case PLACE_WALL:
		m_worldMap.addWall(tilePosition);
		break;
	case PLACE_ROAD:
		m_selectionEnabled = true;
		m_selectionStart = tilePosition;
		break;
	default:
		break;
	}
}

void CityState::mouseLeftReleased(Nz::Vector2ui mousePosition)
{
	if (m_userTool == UserTools::PLACE_ROAD) {
		m_selectionEnabled = false;

		Nz::Vector2ui tilePosition = Isometric::pixelToCell(mousePosition, m_worldMap.getScale(), -m_worldMap.getCameraOffset());
		tilePosition = m_worldMap.getHoveredCell(tilePosition);

		std::vector<Nz::Vector2ui> cells = getSelectedTiles(tilePosition);
		// Every tile must be available in order to build the road
		for (auto pos : cells) {
			if (!m_worldMap.isPositionAvailable(pos) && !m_worldMap.isRoad(pos))
				return;
		}

		for (auto pos : cells) {
			m_worldMap.addRoad(pos);
		}
	}

	m_worldMap.resetPreview();
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

	// Get the tile hovered by the mouse
	Nz::Vector2ui tilePosition = Isometric::pixelToCell(mousePosition, m_worldMap.getScale(), -m_worldMap.getCameraOffset());
	tilePosition = m_worldMap.getHoveredCell(tilePosition);

	if (!m_worldMap.isPositionCorrect(tilePosition)) 
		return; // The cursor is off the map

	if (m_selectionEnabled) {
		// Display road placement preview
		if (m_lastMouseTilePosition == tilePosition)
			return;

		m_lastMouseTilePosition = tilePosition;
		m_worldMap.resetPreview();

		std::vector<Nz::Vector2ui> cells = getSelectedTiles(tilePosition);
		
		for (auto pos : cells) {
			if (!m_worldMap.isPositionAvailable(pos) && !m_worldMap.isRoad(pos)) {
				m_worldMap.resetPreview();
				return;
			}

			switch (m_userTool)
			{
			case PLACE_WALL:
				m_worldMap.previewEntity(pos, WALL);
				break;
			case PLACE_ROAD:
				m_worldMap.previewEntity(pos, ROAD);
				break;
			default:
				return;
				break;
			}
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
		SelectionModes selectionMode = SelectionModes::CURSOR;
		switch (k.code)
		{
		case 26:
			m_userTool = UserTools::PLACE_BUILDING;
			std::cout << "Place building tool" << std::endl;
			actionPreview = true;
			m_currentTile = HOUSE;
			break;
		case 27:
			m_userTool = UserTools::DESTROY;
			std::cout << "Destroy tool" << std::endl;
			break;
		case 28:
			m_userTool = UserTools::PLACE_WALL;
			std::cout << "Place wall tool" << std::endl;
			actionPreview = true;
			m_currentTile = WALL;
			break;
		case 29:
			m_userTool = UserTools::PLACE_ROAD;
			std::cout << "Place road tool" << std::endl;
			selectionMode = SelectionModes::PATH;
			actionPreview = true;
			m_currentTile = ROAD;
			break;
		/*case 30:
			m_userTool = UserTools::SELECT_AREA;
			std::cout << "Select area" << std::endl;
			actionPreview = true;
			m_currentTile = ROAD;
			break;*/
		default:
			m_userTool = UserTools::PLACE_BUILDING;
			std::cout << "Place building tool" << std::endl;
			actionPreview = true;
			m_currentTile = HOUSE;
			break;
		}

		m_actionPreview = actionPreview;
		m_selectionMode = selectionMode;
		mouseMoved(m_lastMousePosition);

		m_selectionEnabled = false;
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

std::vector<Nz::Vector2ui> CityState::getSelectedTiles(Nz::Vector2ui tilePosition)
{
	std::vector<Nz::Vector2ui> cells;
	if (m_selectionMode == SelectionModes::PATH) {
		cells = Isometric::perpendicularPath(m_selectionStart, tilePosition);
	}
	else if (m_selectionMode == SelectionModes::AREA) {
		cells = Isometric::area(m_selectionStart, tilePosition);
	}
	else {
		cells.push_back(tilePosition);
	}

	return cells;
}
