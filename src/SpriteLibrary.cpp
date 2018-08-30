#include "..\includes\SpriteLibrary.hpp"

SpriteLibrary::SpriteLibrary()
{
	createSprite("house_0", 90.f);

	createSprite("character_animations", 64.f);
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
	assert(spriteExists(name));
	return m_sprites.at(name);
}
