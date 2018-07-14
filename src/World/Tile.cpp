#include "../../includes/World/Tile.hpp"

Tile::Tile(TileType type) : m_type(type)
{

}

Nz::MaterialRef Tile::getMaterial()
{
	Nz::MaterialRef material = Nz::Material::New();
	material->LoadFromFile("tiles/tile.png");
	material->EnableBlending(true);
	material->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
	material->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
	material->EnableDepthWrite(false);

	return material;
}
