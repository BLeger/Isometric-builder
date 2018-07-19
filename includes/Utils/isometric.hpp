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
	static Nz::Vector2i topLeftCell(Nz::Vector2i position);
	static Nz::Vector2i topRightCell(Nz::Vector2i position);
	static Nz::Vector2i bottomLeftCell(Nz::Vector2i position);
	static Nz::Vector2i bottomRightCell(Nz::Vector2i position);

	static std::vector<Nz::Vector2<int>> square(Nz::Vector2i tilePosition, int width, int height);

	static Nz::MaterialRef createMaterial(std::string materialName);

	static std::vector<Nz::Vector2i> getSurroundingTiles(Nz::Vector2i position);
	static float distanceToCenter(Nz::Vector2i tilePosition, Nz::Vector2i mousePosition, float tileWidth, float tileHeight);
	static Nz::Vector2f cellCenter(Nz::Vector2i tilePosition, float tileWidth, float tileHeight);

	static Nz::Vector2i getCellClicked(Nz::Vector2i mousePosition);
};

#endif // !ISOMETRIC_H
