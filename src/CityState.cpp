#include "../includes/CityState.h"

CityState::CityState(Ndk::World& world, Nz::RenderWindow& window) :
	m_world(world),
	State(),
	m_windowSize(window.GetSize()),
	m_worldMap(WorldMap{ Nz::Vector2ui{10, 10}, world }),
	m_currentTool(UserTools::PLACE_BUILDING)
{

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

	Nz::MaterialRef tree = Nz::Material::New();
	tree->LoadFromFile("tiles/wall_open_ne.png");
	
	tree->EnableBlending(true);
	tree->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	tree->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	tree->EnableDepthWrite(false);

	Nz::SpriteRef spr;
	spr = Nz::Sprite::New(tree);
	//spr->SetOrigin(Nz::Vector3f(0.f, 32.f, 0.f));
	spr->SetOrigin(Nz::Vector3f(0.f, 32.f, 0.f));

	m_worldMap.addEnvironmentTile(tilePosition, spr);
	m_worldMap.update();
}

void CityState::mouseRightPressed(Nz::Vector2ui mousePosition)
{
	Nz::Vector2ui tilePosition = Isometric::getCellClicked(mousePosition, m_worldMap.getScale(), m_worldMap.getCameraOffset());

	if (!m_worldMap.isPositionCorrect(tilePosition))
		return;

	m_worldMap.removeEnvironmentTile(tilePosition);
	m_worldMap.update();
}

void CityState::mouseWheelMoved(float delta)
{
	m_worldMap.zoom(delta);
	//m_worldMap.display(m_world);
}

void CityState::keyPressed(const Nz::WindowEvent::KeyEvent& k)
{
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
		default:
			break;
		}
	}
}
