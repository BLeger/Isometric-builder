#include "../../includes/Utils/isometric.hpp"

Nz::Vector2i Isometric::staggeredToDiamound(Nz::Vector2ui position)
{
	int x{ (int)std::floor((int)position.y / 2) + (int)position.y % 2 + (int)position.x };
	int y{ (int)std::floor((int)position.y / 2) - (int)position.x };

	return Nz::Vector2i{ x, y };
}

std::vector<Nz::Vector2ui> Isometric::perpendicularPath(Nz::Vector2ui start, Nz::Vector2ui end)
{
	Nz::Vector2i diamStart = staggeredToDiamound(start);
	Nz::Vector2i diamEnd = staggeredToDiamound(end);

	int dX = diamEnd.x - diamStart.x;
	int dY = diamEnd.y - diamStart.y;

	std::vector<Nz::Vector2ui> path{start};
	
	for (int i = 0; i < std::abs(dX); i++) {
		if (dX > 0) {
			path.push_back(bottomRightCell(path[path.size() - 1]));
		}
		else {
			path.push_back(topLeftCell(path[path.size() - 1]));
		}
	}

	for (int j = 0; j < std::abs(dY); j++) {
		if (dY < 0) {
			path.push_back(topRightCell(path[path.size() - 1]));
		}
		else {
			path.push_back(bottomLeftCell(path[path.size() - 1]));
		}
	}

	return path;
}

int Isometric::manhattanStaggeredDistance(Nz::Vector2ui start, Nz::Vector2ui end)
{
	return manhattanDistance(staggeredToDiamound(start), staggeredToDiamound(end));
}

int Isometric::manhattanDistance(Nz::Vector2i start, Nz::Vector2i end)
{
	return std::abs(end.x - start.x) + std::abs(end.y - start.y);
}

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

	if (size.x == 0 || size.y == 0)
		return cells;
	
	for (int i = 0; i < size.x; i++) {
		cells.push_back(Nz::Vector2ui(tilePosition.x, tilePosition.y));

		Nz::Vector2ui lineStart = tilePosition;

		for (int j = 0; j < size.y - 1; j++) {
			Nz::Vector2ui botRight = bottomRightCell(tilePosition);
			cells.push_back(botRight);
			tilePosition = botRight;
		}

		tilePosition = topRightCell(lineStart);
	}

	return cells;
}

std::vector<Nz::Vector2ui> Isometric::area(Nz::Vector2ui start, Nz::Vector2ui end)
{
	/*if (end.x <= start.x || end.y <= end.y) {
		int tX, tY;
		tX = end.x; tY = end.y;
		end.x = start.x; end.y = start.y;
		start.x = tX; start.y = tY;
	}*/

	Nz::Vector2i diamStart = staggeredToDiamound(start);
	Nz::Vector2i diamEnd = staggeredToDiamound(end);

	unsigned int dX = std::abs(diamEnd.x - diamStart.x);
	unsigned int dY = std::abs(diamEnd.y - diamStart.y); 

	assert(dX >= 0 && dY >= 0);

	return square(start, Nz::Vector2ui{ dY + 1, dX + 1 });
}

std::vector<Nz::Vector2ui> Isometric::getSurroundingTiles(Nz::Vector2ui position)
{
	std::vector<Nz::Vector2ui> tiles{Isometric::bottomLeftCell(position) , Isometric::topLeftCell(position),
		Isometric::bottomRightCell(position), Isometric::topRightCell(position) };

	std::vector<Nz::Vector2ui> surroundingTiles {};

	for (Nz::Vector2ui pos : tiles) {
		if (pos.x >= 0 && pos.y >= 0 && pos.x < position.x + 2 && pos.y < position.y + 2) {
			surroundingTiles.push_back(pos);
		}
	}

	return surroundingTiles;
}

Nz::Vector2ui Isometric::pixelToCell(Nz::Vector2ui pixelPosition, float mapScale, Nz::Vector2f cameraOffset)
{
	pixelPosition.x /= mapScale;
	pixelPosition.y /= mapScale;

	pixelPosition.x -= cameraOffset.x;
	pixelPosition.y -= cameraOffset.y;

	float halfH = (float)mainTileSize.y / 2.f;
	float ratio = (float)mainTileSize.y / (float)mainTileSize.x;
	int referenceX = pixelPosition.x / mainTileSize.x;
	int referenceY = (pixelPosition.y / mainTileSize.y);
	int relativeX = pixelPosition.x - referenceX * mainTileSize.x;
	int relativeY = pixelPosition.y - referenceY * mainTileSize.y;

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

Nz::Vector2ui Isometric::cellToPixel(Nz::Vector2ui cellPosition, float scale, Nz::Vector2f cameraOffset)
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
	Nz::Vector2ui cellPixel = cellToPixel(cellPosition, scale, cameraOffset);

	cellPixel.x += mainTileSize.x / 2;
	cellPixel.y += mainTileSize.y / 2;

	return cellPixel;
}
