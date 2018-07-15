#ifndef ISOMETRIC_H
#define ISOMETRIC_H

#include <Nazara\Math\Vector2.hpp>

class Isometric {
public:
	static Nz::Vector2<int> topLeftCell(int x, int y);
	static Nz::Vector2<int> topRightCell(int x, int y);
	static Nz::Vector2<int> bottomLeftCell(int x, int y);
	static Nz::Vector2<int> bottomRightCell(int x, int y);

	static std::vector<Nz::Vector2<int>> square(int x, int y, int width, int height);
};

#endif // !ISOMETRIC_H
