#include "../../includes/World/Building.hpp"

Building::Building(TileData& tile, Ndk::World& world, int drawingOrder) :
m_size_x(tile.width),
m_size_y(tile.height),
m_materialName(tile.materialName),
m_heightOffset(tile.heightOffset),
m_tileData(tile)
{
	Nz::SpriteRef spr;
	spr = Nz::Sprite::New(Isometric::createMaterial(m_materialName));
	spr->SetOrigin(Nz::Vector3f(0.f, tile.heightOffset, 0.f));

	m_entity = world.CreateEntity();
	Ndk::NodeComponent &nodeComp = m_entity->AddComponent<Ndk::NodeComponent>();
	Ndk::GraphicsComponent &GraphicsComp = m_entity->AddComponent<Ndk::GraphicsComponent>();
	GraphicsComp.Attach(spr, drawingOrder);
}

void Building::setScale(float scale)
{
	Ndk::NodeComponent& nodeComp = m_entity->GetComponent<Ndk::NodeComponent>();
	nodeComp.SetScale(scale, scale);
}

void Building::setPosition(Nz::Vector2f position)
{
	Ndk::NodeComponent& nodeComp = m_entity->GetComponent<Ndk::NodeComponent>();
	nodeComp.SetPosition(position.x, position.y);
}

TileData & Building::getTileData()
{
	return m_tileData;
}

std::string Building::getMaterialName()
{
	return m_materialName;
}

float Building::getHeightOffset()
{
	return m_heightOffset;
}

Nz::Vector2<int> Building::getSize()
{
	return Nz::Vector2<int>(m_size_x, m_size_y);
}
