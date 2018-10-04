#include <NDK/Application.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>
#include <NDK/StateMachine.hpp>
#include <NDK/Canvas.hpp>
#include <NDK/Widgets/CheckboxWidget.hpp>
#include <NDK/Widgets/ButtonWidget.hpp>

#include "includes/CityState.hpp"
#include "includes/Components/EnvironmentTileComponent.hpp"
#include "includes/Components/WallComponent.hpp"
#include "includes/Components/AnimationComponent.hpp"
#include "includes/Components/WalkerComponent.hpp"
#include "includes/Components/BuildingComponent.hpp"
#include "includes/Components/ResidentialBuildingComponent.hpp"

#include "includes/Systems/WallSystem.hpp"
#include "includes/Systems/AnimationSystem.hpp"
#include "includes/Systems/WalkerSystem.hpp"
#include "includes/Systems/BuildingSystem.hpp"
#include "includes/Systems/ResidentialBuildingSystem.hpp"

#include <iostream>

int main()
{
	Ndk::InitializeComponent<EnvironmentTileComponent>("EnvTile");
	Ndk::InitializeComponent<WallComponent>("Wall");
	Ndk::InitializeComponent<WalkerComponent>("Walker");
	Ndk::InitializeComponent<AnimationComponent>("Anima");
	Ndk::InitializeComponent<BuildingComponent>("Build");
	Ndk::InitializeComponent<ResidentialBuildingComponent>("ResBuild");

	Ndk::InitializeSystem<WallSystem>();
	Ndk::InitializeSystem<WalkerSystem>();
	Ndk::InitializeSystem<AnimationSystem>();
	Ndk::InitializeSystem<BuildingSystem>();
	Ndk::InitializeSystem<ResidentialBuildingSystem>();

	Ndk::Application application;

	Nz::RenderWindow& mainWindow = application.AddWindow<Nz::RenderWindow>();
	mainWindow.Create(Nz::VideoMode(900, 600, 32), "Test");
	mainWindow.EnableVerticalSync(true);

	// World
	Ndk::World& world = application.AddWorld();
	world.GetSystem<Ndk::RenderSystem>().SetGlobalUp(Nz::Vector3f::Down());

	// Camera
	Ndk::EntityHandle viewEntity = world.CreateEntity();
	viewEntity->AddComponent<Ndk::NodeComponent>();
	Ndk::CameraComponent& viewer = viewEntity->AddComponent<Ndk::CameraComponent>();
	viewer.SetTarget(&mainWindow);
	viewer.SetProjectionType(Nz::ProjectionType_Orthogonal);

	// We add our state machine with the newly created GameState
	Ndk::StateMachine fsm(std::make_shared<CityState>(world, mainWindow, viewEntity));

	application.EnableFPSCounter(true);

	// We make it run
	while (application.Run())
	{
		// We update the state machine which will ensure that our states are updated
		if (!fsm.Update(application.GetUpdateTime()))
		{
			NazaraError("Failed to update state machine.");
			return EXIT_FAILURE;
		}

		mainWindow.Display();
	}
	
	return EXIT_SUCCESS;
}