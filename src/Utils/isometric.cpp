#include "../../includes/Utils/isometric.hpp"

Nz::Vector2<int> Isometric::topLeftCell(int x, int y)
{
	if (y % 2 == 0) {
		return Nz::Vector2<int>(x - 1, y - 1);
	}
	return Nz::Vector2<int>(x, y - 1);
}

Nz::Vector2<int> Isometric::topRightCell(int x, int y)
{
	if (y % 2 == 0) {
		return Nz::Vector2<int>(x, y - 1);
	}
	return Nz::Vector2<int>(x + 1, y - 1);
}

Nz::Vector2<int> Isometric::bottomLeftCell(int x, int y)
{
	if (y % 2 == 0) {
		return Nz::Vector2<int>(x - 1, y + 1);
	}
	return Nz::Vector2<int>(x, y + 1);
}

Nz::Vector2<int> Isometric::bottomRightCell(int x, int y)
{
	if (y % 2 == 0) {
		return Nz::Vector2<int>(x, y + 1);
	}
	return Nz::Vector2<int>(x + 1, y + 1);
}

std::vector<Nz::Vector2<int>> Isometric::square(int x, int y, int width, int height)
{
	std::vector<Nz::Vector2<int>> cells{};

	for (int i = 0; i < width; i++) {
		cells.push_back(Nz::Vector2<int>(x, y));

		int xLineStart = x;
		int yLineStart = y;

		for (int j = 0; j < height - 1; j++) {
			Nz::Vector2<int> botRight = bottomRightCell(x, y);
			cells.push_back(botRight);
			x = botRight.x;
			y = botRight.y;
		}

		Nz::Vector2<int> topRight = topRightCell(xLineStart, yLineStart);
		x = topRight.x;
		y = topRight.y;
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

float Isometric::distanceToCenter(int tileX, int tileY, float mouseX, float mouseY, float tileWidth, float tileHeight)
{
	Nz::Vector2f center = cellCenter(tileX, tileY, tileWidth, tileHeight);
	return pow(center.x - mouseX, 2) + pow(center.y - mouseY, 2);
}

Nz::Vector2f Isometric::cellCenter(int x, int y, float tileWidth, float tileHeight)
{
	float xPos = x * tileWidth + (tileWidth / 2);
	if (y % 2 != 0)
		xPos += tileWidth / 2;

	float yPos = y / 2.f * tileHeight + (tileHeight / 2);
	return Nz::Vector2f(xPos, yPos);
}

bool Isometric::isInside(int tileX, int tileY, float mouseX, float mouseY, float larg_tile, float heut_tile)
{
	Nz::Vector2f center = cellCenter(tileX, tileY, larg_tile, heut_tile);

	float dx = abs(mouseX - center.x);
	float dy = abs(mouseY - center.y);

	return (dx / (larg_tile * 0.5) + dy / (heut_tile * 0.5) <= 1);
}
