#include "../../includes/World/Tile.hpp"

/*Tile::Tile(TileType type, std::string material, float heightOffset) : m_type(type), m_materialName(material), m_heightOffset(heightOffset)
{

}*/

Tile::Tile(TileData& datas, Ndk::World& world, int drawingOrder, Nz::MaterialRef& m) : m_drawingOrder(drawingOrder), m_materialName(datas.materialName), m_heightOffset(datas.heightOffset) {
	Nz::SpriteRef spr;
	spr = Nz::Sprite::New(m);
	spr->SetOrigin(Nz::Vector3f(0.f, m_heightOffset, 0.f));
	
	m_entity = world.CreateEntity();
	Ndk::NodeComponent &nodeComp = m_entity->AddComponent<Ndk::NodeComponent>();
	Ndk::GraphicsComponent &GraphicsComp = m_entity->AddComponent<Ndk::GraphicsComponent>();
	GraphicsComp.Attach(spr, drawingOrder);
}

void Tile::setScale(float scale)
{
	Ndk::NodeComponent& nodeComp = m_entity->GetComponent<Ndk::NodeComponent>();
	nodeComp.SetScale(scale, scale);
}

void Tile::setPosition(Nz::Vector2f position)
{
	Ndk::NodeComponent& nodeComp = m_entity->GetComponent<Ndk::NodeComponent>();
	nodeComp.SetPosition(position.x, position.y);
}

void Tile::setTileDatas(TileData& datas)
{
	m_materialName = datas.materialName;
	m_heightOffset = datas.heightOffset;

	Nz::SpriteRef spr;
	spr = Nz::Sprite::New(Isometric::createMaterial(m_materialName));
	spr->SetOrigin(Nz::Vector3f(0.f, m_heightOffset, 0.f));

	Ndk::GraphicsComponent &GraphicsComp = m_entity->GetComponent<Ndk::GraphicsComponent>();
	GraphicsComp.Clear();
	GraphicsComp.Attach(spr, m_drawingOrder);
}

/*void Tile::setType(TileType type) {
	m_type = type;
}

TileType Tile::getType() {
	return m_type;
}*/

float Tile::getHeightOffset()
{
	return m_heightOffset;
}

std::string Tile::getMaterialName()
{
	return m_materialName;
}
