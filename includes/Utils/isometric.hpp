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
#include <Nazara\Math\Vector2.hpp>

class Isometric {
public:
	static Nz::Vector2<int> topLeftCell(int x, int y);
	static Nz::Vector2<int> topRightCell(int x, int y);
	static Nz::Vector2<int> bottomLeftCell(int x, int y);
	static Nz::Vector2<int> bottomRightCell(int x, int y);

	static std::vector<Nz::Vector2<int>> square(int x, int y, int width, int height);

	static Nz::MaterialRef createMaterial(std::string materialName);

	static float distanceToCenter(int tileX, int tileY, float mouseX, float mouseY, float tileWidth, float tileHeight);
	static Nz::Vector2f cellCenter(int x, int y, float tileWidth, float tileHeight);
	static bool isInside(int tileX, int tileY, float mouseX, float mouseY, float larg_tile, float heut_tile);
};

#endif // !ISOMETRIC_H
