#include "../includes/CityState.h"

CityState::CityState(Ndk::World& world, Nz::RenderWindow& window) :
	m_world(world),
	State(),
	m_windowSize(window.GetSize()),
	m_worldMap(WorldMap{ Nz::Vector2ui{10, 10}, world })
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

	Nz::Vector2ui tilePosition = Isometric::getCellClicked(mousePosition);

	Nz::MaterialRef tree = Nz::Material::New();
	tree->LoadFromFile("tiles/tree.png");
	tree->EnableBlending(true);
	tree->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	tree->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	tree->EnableDepthWrite(false);

	Nz::SpriteRef spr;
	spr = Nz::Sprite::New(tree);
	spr->SetOrigin(Nz::Vector3f(0.f, 32.f, 0.f));

	m_worldMap.addEnvironmentTile(tilePosition, spr);
	m_worldMap.update();

	//TileData tree{ TileType::Tile_1x1, "tree", -72.f, 1, 1 };
	//m_worldMap.changeTile(tilePosition.x, tilePosition.y, tree);
	//m_worldMap.display(m_world);
}

void CityState::mouseRightPressed(Nz::Vector2ui mousePosition)
{
	Nz::Vector2ui tilePosition = Isometric::getCellClicked(mousePosition);
	m_worldMap.removeEnvironmentTile(tilePosition);
	m_worldMap.update();
}

void CityState::mouseWheelMoved(float delta)
{
	m_worldMap.zoom(delta);
	//m_worldMap.display(m_world);
}
