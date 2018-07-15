#include "../../includes/World/Tile.hpp"

Tile::Tile(TileType type, std::string material) : m_type(type), m_material_name(material)
{

}

void Tile::setType(TileType type) {
	m_type = type;
}

TileType Tile::getType() {
	return m_type;
}

Nz::MaterialRef Tile::getMaterial()
{
	Nz::MaterialRef material = Nz::Material::New();
	material->LoadFromFile("tiles/" + m_material_name + ".png");
	material->EnableBlending(true);
	material->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	material->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	material->EnableDepthWrite(false);

	return material;
}
