#include "..\includes\SpriteLibrary.hpp"

SpriteLibrary::SpriteLibrary()
{
	createSprite("tree", 32.f);
	createSprite("wall", 32.f);
	createSprite("wall_ne", 32.f);
	createSprite("wall_no", 32.f);
	createSprite("wall_se", 32.f);
	createSprite("wall_so", 32.f);
	createSprite("wall_no_se", 32.f);
	createSprite("wall_ne_so", 32.f);
	createSprite("wall_ne_se", 32.f);
}

bool SpriteLibrary::spriteExists(std::string name)
{
	return m_sprites.find(name) != m_sprites.end();
}

void SpriteLibrary::createSprite(std::string name, float heightOffset)
{
	Nz::MaterialRef material = Nz::Material::New();
	material->LoadFromFile("tiles/" + name + ".png");

	material->EnableBlending(true);
	material->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	material->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	material->EnableDepthWrite(false);

	Nz::SpriteRef sprite;
	sprite = Nz::Sprite::New(material);
	sprite->SetOrigin(Nz::Vector3f(0.f, heightOffset, 0.f));

	m_sprites.insert(std::make_pair(name, sprite));
}

Nz::SpriteRef & SpriteLibrary::getSprite(std::string name)
{
	return m_sprites.at(name);
}
