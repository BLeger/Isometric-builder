#include <NDK/Application.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>
#include <NDK/StateMachine.hpp>

#include "includes/CityState.h"


#include <iostream>

int main()
{
	Ndk::Application application;

	Nz::RenderWindow& mainWindow = application.AddWindow<Nz::RenderWindow>();
	mainWindow.Create(Nz::VideoMode(800, 600, 32), "Test");
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
	Ndk::StateMachine fsm(std::make_shared<CityState>(world, mainWindow));

	//application.EnableFPSCounter(true);

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