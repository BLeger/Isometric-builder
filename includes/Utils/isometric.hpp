#ifndef ISOMETRIC_H
#define ISOMETRIC_H

#include <string>
#include <cmath>

#include <NDK/Application.hpp>
#include <NDK/Entity.hpp>
#include <NDK/State.hpp>
#include <NDK/StateMachine.hpp>
#include <NDK/World.hpp>
#include <NDK/Components.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <Nazara/Math\Vector2.hpp>

#include "../Config/TilesConfig.hpp"
#include <iostream>

class Isometric {
public:
	static Nz::Vector2ui topLeftCell(Nz::Vector2ui position);
	static Nz::Vector2ui topRightCell(Nz::Vector2ui position);
	static Nz::Vector2ui bottomLeftCell(Nz::Vector2ui position);
	static Nz::Vector2ui bottomRightCell(Nz::Vector2ui position);

	static std::vector<Nz::Vector2ui> square(Nz::Vector2ui tilePosition, int width, int height);

	static Nz::MaterialRef createMaterial(std::string materialName);

	static std::vector<Nz::Vector2ui> getSurroundingTiles(Nz::Vector2ui position);
	static float distanceToCenter(Nz::Vector2i tilePosition, Nz::Vector2i mousePosition, float tileWidth, float tileHeight);
	static Nz::Vector2f cellCenter(Nz::Vector2i tilePosition, float tileWidth, float tileHeight);

	static Nz::Vector2ui getCellClicked(Nz::Vector2ui mousePosition, float mapScale = 1.f, Nz::Vector2f cameraOffset = Nz::Vector2f(0.f, 0.f));

	static Nz::Vector2i getCellPixelCoordinates(Nz::Vector2ui cellPosition, float scale = 1.f, Nz::Vector2f cameraOffset = Nz::Vector2f(0.f, 0.f));
};

#endif // !ISOMETRIC_H
