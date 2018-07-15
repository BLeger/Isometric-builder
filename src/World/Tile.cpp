#include "../../includes/World/Tile.hpp"

Tile::Tile(TileType type, std::string material) : m_type(type), m_materialName(material)
{

}

void Tile::setType(TileType type) {
	m_type = type;
}

TileType Tile::getType() {
	return m_type;
}

void Tile::setMaterialName(std::string material) {
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
