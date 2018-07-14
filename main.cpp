#include <NDK/Application.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <NDK/Application.hpp>
#include <NDK/Components.hpp>
#include <NDK/Systems.hpp>
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

	Nz::MaterialRef mat = Nz::Material::New();
	mat->LoadFromFile("tiles/tile.png");
	mat->EnableBlending(true);
	mat->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	mat->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	mat->EnableDepthWrite(false);

	Nz::SpriteRef spr = Nz::Sprite::New(mat);

	Ndk::EntityHandle sprEntity = world.CreateEntity();
	Ndk::NodeComponent &nodeComp = sprEntity->AddComponent<Ndk::NodeComponent>();
	Ndk::GraphicsComponent &GraphicsComp = sprEntity->AddComponent<Ndk::GraphicsComponent>();
	GraphicsComp.Attach(spr);

	nodeComp.SetScale(0.4f, 0.4f);
	//nodeComp.SetPosition(100.f, 80.f);

	
	

	while (application.Run())
	{
		mainWindow.Display();
	}

	return EXIT_SUCCESS;
}