#ifndef CITY_STATE_H
#define CITY_STATE_H

#include <iostream>

#include <NDK/Application.hpp>
#include <NDK/Entity.hpp>
#include <NDK/State.hpp>
#include <NDK/StateMachine.hpp>
#include <NDK/World.hpp>
#include <NDK/Components.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>

#include "Config\TilesConfig.hpp"
#include "World/WorldMap.hpp"
#include "UserTools.hpp"
#include "SpriteLibrary.hpp"
#include "Utils\PathFinder.hpp"
#include "City\City.hpp"

#include "Systems\WallSystem.hpp"
#include "Systems\WalkerSystem.hpp"
#include "Systems\AnimationSystem.hpp"
#include "Systems\BuildingSystem.hpp"
#include "Systems\ResidentialBuildingSystem.hpp"

class CityState : public Ndk::State {

public:
	CityState(Ndk::World& world, Nz::RenderWindow& window, Ndk::EntityHandle& camera);
	void Enter(Ndk::StateMachine& fsm) override;
	void Leave(Ndk::StateMachine& fsm) override;
	bool Update(Ndk::StateMachine& fsm, float elapsedTime) override;

	void mouseLeftPressed(Nz::Vector2ui mousePosition);
	void mouseLeftReleased(Nz::Vector2ui mousePosition);
	void mouseRightPressed(Nz::Vector2ui mousePosition);
	void mouseWheelMoved(float delta);
	void mouseMoved(Nz::Vector2ui mousePosition);
	void keyPressed(const Nz::WindowEvent::KeyEvent& k);

private:
	std::vector<Nz::Vector2ui> getSelectedTiles(Nz::Vector2ui tilePosition);

	Ndk::World& m_world;
	const Nz::Vector2f m_windowSize;
	Ndk::EntityHandle& m_camera;

	WorldMap m_worldMap;
	City m_city;
	
	// User tool & selection
	UserTools m_userTool;
	SelectionModes m_selectionMode;
	bool m_selectionEnabled = false;
	Nz::Vector2ui m_selectionStart;

	Nz::Vector2ui m_lastMousePosition{ 0u, 0u };
	Nz::Vector2ui m_lastMouseTilePosition{ 0u, 0u };
	bool m_actionPreview = false;

	SpriteLibrary m_spriteLib;

	TileDef m_currentTile = ROCK;
};

#endif // !CITY_STATE_H
