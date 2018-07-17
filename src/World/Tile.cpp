#include "../../includes/World/Tile.hpp"

Tile::Tile(TileType type, std::string material, float heightOffset) : m_type(type), m_materialName(material), m_heightOffset(heightOffset)
{

}

Tile::Tile(TileData& datas) : m_type(datas.type), m_materialName(datas.materialName), m_heightOffset(datas.heightOffset) {

}

void Tile::setTileDatas(TileData& datas)
{
	m_type = datas.type;
	m_materialName = datas.materialName;
	m_heightOffset = datas.heightOffset;
}

void Tile::setType(TileType type) {
	m_type = type;
}

TileType Tile::getType() {
	return m_type;
}

float Tile::getHeightOffset()
{
	return m_heightOffset;
}

void Tile::setMaterialName(std::string material) {
	std::cout << material << std::endl;
	m_materialName = material;
}

Nz::MaterialRef Tile::getMaterial()
{
	Nz::MaterialRef material = Nz::Material::New();
	material->LoadFromFile("tiles/" + m_materialName + ".png");
	material->EnableBlending(true);
	material->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	material->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	material->EnableDepthWrite(false);

	return material;
}
