#ifndef SPRITE_LIBRARY_H
#define SPRITE_LIBRARY_H

#include <NDK/Application.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>

#include <string>
#include <iostream>
#include <map>

class SpriteLibrary {

public:
	SpriteLibrary();

	bool spriteExists(std::string name);

	void createSprite(std::string name, float heightOffset);
	Nz::SpriteRef& getSprite(std::string name);

private:
	std::map<std::string, Nz::SpriteRef> m_sprites;
};

#endif