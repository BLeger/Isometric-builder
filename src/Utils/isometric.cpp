#include "../../includes/Utils/isometric.hpp"

Nz::Vector2i Isometric::topLeftCell(Nz::Vector2i position)
{
	if (position.y % 2 == 0) {
		return Nz::Vector2i(position.x - 1, position.y - 1);
	}
	return Nz::Vector2i(position.x, position.y - 1);
}

Nz::Vector2i Isometric::topRightCell(Nz::Vector2i position)
{
	if (position.y % 2 == 0) {
		return Nz::Vector2i(position.x, position.y - 1);
	}
	return Nz::Vector2i(position.x + 1, position.y - 1);
}

Nz::Vector2i Isometric::bottomLeftCell(Nz::Vector2i position)
{
	if (position.y % 2 == 0) {
		return Nz::Vector2i(position.x - 1, position.y + 1);
	}
	return Nz::Vector2i(position.x, position.y + 1);
}

Nz::Vector2i Isometric::bottomRightCell(Nz::Vector2i position)
{
	if (position.y % 2 == 0) {
		return Nz::Vector2i(position.x, position.y + 1);
	}
	return Nz::Vector2i(position.x + 1, position.y + 1);
}

std::vector<Nz::Vector2i> Isometric::square(Nz::Vector2i tilePosition, int width, int height)
{
	std::vector<Nz::Vector2i> cells{};

	for (int i = 0; i < width; i++) {
		cells.push_back(Nz::Vector2i(tilePosition.x, tilePosition.y));

		Nz::Vector2i lineStart = tilePosition;

		for (int j = 0; j < height - 1; j++) {
			Nz::Vector2i botRight = bottomRightCell(tilePosition);
			cells.push_back(botRight);
			tilePosition = botRight;
		}

		Nz::Vector2i topRight = topRightCell(lineStart);
		tilePosition = topRight;
	}

	return cells;
}

Nz::MaterialRef Isometric::createMaterial(std::string materialName)
{
	Nz::MaterialRef material = Nz::Material::New();
	material->LoadFromFile("tiles/" + materialName + ".png");
	material->EnableBlending(true);
	material->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	material->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	material->EnableDepthWrite(false);

	return material;
}

std::vector<Nz::Vector2i> Isometric::getSurroundingTiles(Nz::Vector2i position)
{
	std::vector<Nz::Vector2i> tiles{Isometric::bottomLeftCell(position) , Isometric::topLeftCell(position),
		Isometric::bottomRightCell(position), Isometric::topRightCell(position) };

	std::vector<Nz::Vector2i> surroundingTiles {};

	for (Nz::Vector2i position : tiles) {
		if (position.x >= 0 && position.y >= 0) {
			surroundingTiles.push_back(position);
		}
	}

	return surroundingTiles;
}

float Isometric::distanceToCenter(Nz::Vector2i tilePosition, Nz::Vector2i mousePosition, float tileWidth, float tileHeight)
{
	Nz::Vector2f center = cellCenter(tilePosition, tileWidth, tileHeight);
	return pow(center.x - mousePosition.x, 2) + pow(center.y - mousePosition.y, 2);
}

Nz::Vector2f Isometric::cellCenter(Nz::Vector2i tilePosition, float tileWidth, float tileHeight)
{
	float xPos = tilePosition.x * tileWidth + (tileWidth / 2);
	if (tilePosition.y % 2 != 0)
		xPos += tileWidth / 2;

	float yPos = tilePosition.y / 2.f * tileHeight + (tileHeight / 2);
	return Nz::Vector2f(xPos, yPos);
}

Nz::Vector2i Isometric::getCellClicked(Nz::Vector2i mousePosition)
{
	float larg_tile = 133.f * 0.5f;
	float heut_tile = 80.f * 0.5f;

	//std::cout << "CART x: " << position.x << " y: " << position.y << std::endl;

	// Estimated tile
	Nz::Vector2i tile{ (int)(mousePosition.x / larg_tile), (int)(mousePosition.y / heut_tile) };
	// Position of the center of this tile
	Nz::Vector2f center = Isometric::cellCenter(tile, larg_tile, heut_tile);

	tile.y *= 2;

	//std::cout << "tileX : " << tileX << " tileY : " << tileY << std::endl;
	//std::cout << "X offset " << tileX_offset << " Y offset " << tileY_offset << std::endl;

	std::vector<Nz::Vector2i> others = Isometric::getSurroundingTiles(tile);

	Nz::Vector2i bestPos = tile;
	float minDist = distanceToCenter(tile, mousePosition, larg_tile, heut_tile);

	for (Nz::Vector2i other : others) {
		float d2 = distanceToCenter(other, mousePosition, larg_tile, heut_tile);
		//std::cout << "Other : " << other.x << " - " << other.y << " Dist : " << d2 << std::endl;
		if (d2 < minDist) {
			minDist = d2;
			bestPos = other;
		}
	}

	//std::cout << "RESULT : " << bestPos.x << " - " << bestPos.y << std::endl;
	return bestPos;
}

