#include "../../includes/Utils/isometric.hpp"

Nz::Vector2ui Isometric::topLeftCell(Nz::Vector2ui position)
{
	if (position.y % 2 == 0) {
		return Nz::Vector2ui(position.x - 1, position.y - 1);
	}
	return Nz::Vector2ui(position.x, position.y - 1);
}

Nz::Vector2ui Isometric::topRightCell(Nz::Vector2ui position)
{
	if (position.y % 2 == 0) {
		return Nz::Vector2ui(position.x, position.y - 1);
	}
	return Nz::Vector2ui(position.x + 1, position.y - 1);
}

Nz::Vector2ui Isometric::bottomLeftCell(Nz::Vector2ui position)
{
	if (position.y % 2 == 0) {
		return Nz::Vector2ui(position.x - 1, position.y + 1);
	}
	return Nz::Vector2ui(position.x, position.y + 1);
}

Nz::Vector2ui Isometric::bottomRightCell(Nz::Vector2ui position)
{
	if (position.y % 2 == 0) {
		return Nz::Vector2ui(position.x, position.y + 1);
	}
	return Nz::Vector2ui(position.x + 1, position.y + 1);
}

std::vector<Nz::Vector2ui> Isometric::square(Nz::Vector2ui tilePosition, int width, int height)
{
	std::vector<Nz::Vector2ui> cells{};

	for (int i = 0; i < width; i++) {
		cells.push_back(Nz::Vector2ui(tilePosition.x, tilePosition.y));

		Nz::Vector2ui lineStart = tilePosition;

		for (int j = 0; j < height - 1; j++) {
			Nz::Vector2ui botRight = bottomRightCell(tilePosition);
			cells.push_back(botRight);
			tilePosition = botRight;
		}

		Nz::Vector2ui topRight = topRightCell(lineStart);
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

std::vector<Nz::Vector2ui> Isometric::getSurroundingTiles(Nz::Vector2ui position)
{
	std::vector<Nz::Vector2ui> tiles{Isometric::bottomLeftCell(position) , Isometric::topLeftCell(position),
		Isometric::bottomRightCell(position), Isometric::topRightCell(position) };

	std::vector<Nz::Vector2ui> surroundingTiles {};

	for (Nz::Vector2ui position : tiles) {
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

Nz::Vector2ui Isometric::getCellClicked(Nz::Vector2ui mousePosition, float mapScale, Nz::Vector2f cameraOffset)
{
	mousePosition.x /= mapScale;
	mousePosition.y /= mapScale;

	mousePosition.x -= cameraOffset.x;
	mousePosition.y -= cameraOffset.y;

	float halfH = mainTileSize.y / 2;
	float ratio = (float)mainTileSize.y / (float)mainTileSize.x;
	int referenceX = mousePosition.x / mainTileSize.x;
	int referenceY = (mousePosition.y / mainTileSize.y);
	float relativeX = mousePosition.x - referenceX * mainTileSize.x;
	float relativeY = mousePosition.y - referenceY * mainTileSize.y;

	referenceY *= 2;

	Nz::Vector2ui cell;

	if (halfH - (relativeX * ratio) > relativeY) 
		cell = Isometric::topLeftCell(Nz::Vector2ui(referenceX, referenceY));
	else if (-halfH + (relativeX * ratio) > relativeY)
		cell = Isometric::topRightCell(Nz::Vector2ui(referenceX, referenceY));
	else if (halfH + (relativeX * ratio) < relativeY)
		cell = Isometric::bottomLeftCell(Nz::Vector2ui(referenceX, referenceY));
	else if (halfH * 3 - (relativeX * ratio) < relativeY)
		cell = Isometric::bottomRightCell(Nz::Vector2ui(referenceX, referenceY));
	else
		cell = Nz::Vector2ui(referenceX, referenceY);

	return cell;
}

Nz::Vector2i Isometric::getCellPixelCoordinates(Nz::Vector2ui cellPosition, float scale, Nz::Vector2f cameraOffset)
{
	float xPos = cellPosition.x * mainTileSize.x; // * scale ?
	float yPos = cellPosition.y / 2.f * mainTileSize.y;

	if (cellPosition.y % 2 != 0) {
		// Odd line are shifted
		xPos += 0.5 * mainTileSize.x;
	}

	xPos *= scale;
	yPos *= scale;

	xPos += cameraOffset.x;
	yPos += cameraOffset.y;

	return Nz::Vector2i {(int) xPos, (int) yPos };
}

