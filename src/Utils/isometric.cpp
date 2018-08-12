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

Nz::Vector2ui Isometric::getCell(Nz::Vector2ui position, Direction direction)
{
	switch (direction)
	{
	case NORTH_EST:
		return topRightCell(position);
		break;
	case NORTH_WEST:
		return topLeftCell(position);
		break;
	case SOUTH_EST:
		return bottomRightCell(position);
		break;
	case SOUTH_WEST:
		return bottomLeftCell(position);
		break;
	default:
		return position;
		break;
	}
}

Direction Isometric::getDirection(Nz::Vector2ui start, Nz::Vector2ui destination)
{
	if (destination == topLeftCell(start)) {
		return Direction::NORTH_WEST;
	}
	else if (destination == topRightCell(start)) {
		return Direction::NORTH_EST;
	}
	else if (destination == bottomLeftCell(start)) {
		return Direction::SOUTH_WEST;
	}
	else if (destination == bottomRightCell(start)) {
		return Direction::SOUTH_EST;
	}

	throw std::exception{"Theses tiles are not next to each other"};
}

std::vector<Nz::Vector2ui> Isometric::square(Nz::Vector2ui tilePosition, Nz::Vector2ui size)
{
	std::vector<Nz::Vector2ui> cells{};

	for (int i = 0; i < size.x; i++) {
		cells.push_back(Nz::Vector2ui(tilePosition.x, tilePosition.y));

		Nz::Vector2ui lineStart = tilePosition;

		for (int j = 0; j < size.y - 1; j++) {
			Nz::Vector2ui botRight = bottomRightCell(tilePosition);
			cells.push_back(botRight);
			tilePosition = botRight;
		}

		Nz::Vector2ui topRight = topRightCell(lineStart);
		tilePosition = topRight;
	}

	return cells;
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

/*float Isometric::distanceToCenter(Nz::Vector2i tilePosition, Nz::Vector2i mousePosition, float tileWidth, float tileHeight)
{
	Nz::Vector2f center = cellCenter(tilePosition, tileWidth, tileHeight);
	return pow(center.x - mousePosition.x, 2) + pow(center.y - mousePosition.y, 2);
}*/

Nz::Vector2ui Isometric::getCellClicked(Nz::Vector2ui mousePosition, float mapScale, Nz::Vector2f cameraOffset)
{
	mousePosition.x /= mapScale;
	mousePosition.y /= mapScale;

	mousePosition.x -= cameraOffset.x;
	mousePosition.y -= cameraOffset.y;

	float halfH = (float)mainTileSize.y / 2.f;
	float ratio = (float)mainTileSize.y / (float)mainTileSize.x;
	int referenceX = mousePosition.x / mainTileSize.x;
	int referenceY = (mousePosition.y / mainTileSize.y);
	int relativeX = mousePosition.x - referenceX * mainTileSize.x;
	int relativeY = mousePosition.y - referenceY * mainTileSize.y;

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

Nz::Vector2ui Isometric::getCellPixelCoordinates(Nz::Vector2ui cellPosition, float scale, Nz::Vector2f cameraOffset)
{
	float xPos = cellPosition.x * mainTileSize.x;
	float yPos = cellPosition.y / 2.f * mainTileSize.y;

	if (cellPosition.y % 2 != 0) {
		// Odd line are shifted
		xPos += 0.5f * mainTileSize.x;
	}

	xPos *= scale;
	yPos *= scale;

	xPos += cameraOffset.x;
	yPos += cameraOffset.y;

	return Nz::Vector2ui {(unsigned int) xPos, (unsigned int) yPos };
}

Nz::Vector2ui Isometric::cellPixelCenter(Nz::Vector2ui cellPosition, float scale, Nz::Vector2f cameraOffset)
{
	Nz::Vector2ui cellPixel = getCellPixelCoordinates(cellPosition, scale, cameraOffset);

	cellPixel.x += mainTileSize.x / 2;
	cellPixel.y += mainTileSize.y / 2;

	return cellPixel;
}
