#include <NDK/Application.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>
#include <NDK/StateMachine.hpp>
#include <NDK/Canvas.hpp>
#include <NDK/Widgets/CheckboxWidget.hpp>
#include <NDK/Widgets/ButtonWidget.hpp>

#include "includes/CityState.h"
#include "includes/Components/EnvironmentTileComponent.hpp"
#include "includes/Components/WallComponent.hpp"
#include "includes/Components/AnimationComponent.hpp"
#include "includes/Components/WalkerComponent.hpp"
#include "includes/Components/BuildingComponent.hpp"
#include "includes/Systems/WallSystem.hpp"
#include "includes/Systems/AnimationSystem.hpp"
#include "includes/Systems/WalkerSystem.hpp"
#include "includes/Systems/BuildingSystem.hpp"

#include <iostream>

int main()
{
	Ndk::InitializeComponent<EnvironmentTileComponent>("EnvTile");
	Ndk::InitializeComponent<WallComponent>("Wall");
	Ndk::InitializeComponent<WalkerComponent>("Walker");
	Ndk::InitializeComponent<AnimationComponent>("Anima");
	Ndk::InitializeComponent<BuildingComponent>("Build");

	Ndk::InitializeSystem<WallSystem>();
	Ndk::InitializeSystem<WalkerSystem>();
	Ndk::InitializeSystem<AnimationSystem>();
	Ndk::InitializeSystem<BuildingSystem>();

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

	/*Ndk::Canvas canvas{ world.CreateHandle(), mainWindow.GetEventHandler(), mainWindow.GetCursorController().CreateHandle() };

	Ndk::ButtonWidget* b = canvas.Add<Ndk::ButtonWidget>();
	b->Move(500.f, 500.f);*/

	// We add our state machine with the newly created GameState
	Ndk::StateMachine fsm(std::make_shared<CityState>(world, mainWindow));

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

/*Nz::MaterialRef tree = Nz::Material::New();
tree->LoadFromFile("tiles/tree.png");
tree->EnableBlending(true);
tree->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
tree->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
tree->EnableDepthWrite(false);

Nz::SpriteRef spr;
spr = Nz::Sprite::New(tree);
spr->SetOrigin(Nz::Vector3f(0.f, 0.f, 0.f));

for (int i = 0; i < 10000; i++) {
Ndk::EntityHandle tree_entity = world.CreateEntity();
Ndk::NodeComponent &tNode = tree_entity->AddComponent<Ndk::NodeComponent>();
Ndk::GraphicsComponent &tGraphics = tree_entity->AddComponent<Ndk::GraphicsComponent>();
tNode.SetPosition(Nz::Vector3f(i * 2.f, i * 2.f, 0.f));
tGraphics.Attach(spr);
}*/