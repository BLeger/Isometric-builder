#include "../../includes/World/WorldMap.hpp"

WorldMap::WorldMap(int size_x, int size_y) : m_size_x(size_x), m_size_y(size_y) {

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			m_tiles.push_back(Tile{TileType::Tile_1x1});
		}
	}
}

Tile& WorldMap::getTile(int x, int y) {
	return m_tiles.at(m_size_x * y + x);
}

void WorldMap::display(Ndk::World& world)
{
	for (int y = 0; y < m_size_y; y++) {
		for (int x = 0; x < m_size_x; x++) {
			Nz::MaterialRef mat = Nz::Material::New();
			mat->LoadFromFile("tiles/tile.png");
			mat->EnableBlending(true);
			mat->SetDstBlend(Nz::BlendFunc_InvSrcAlpha);
			mat->SetSrcBlend(Nz::BlendFunc_SrcAlpha);
			mat->EnableDepthWrite(false);

			Nz::SpriteRef spr = Nz::Sprite::New(mat);

			Ndk::EntityHandle test = world.CreateEntity();
			Ndk::NodeComponent &nodeComp = test->AddComponent<Ndk::NodeComponent>();
			Ndk::GraphicsComponent &GraphicsComp = test->AddComponent<Ndk::GraphicsComponent>();
			GraphicsComp.Attach(spr);

			float scale = 0.5f;
			float tile_width = 128.f;
			float tile_height = 64.f;

			nodeComp.SetScale(scale, scale);
			float height = y / 2.f * scale * tile_height;
			std::cout << "x = " << x << " y = " << y << "   " << height << std::endl;
			if (y % 2 == 0) {
				// Ligne paire
				nodeComp.SetPosition(x * scale * tile_width, height);
			}
			else {
				nodeComp.SetPosition(x * scale * tile_width + (0.5 * scale*tile_width), height);
			}
			
		}
	}
}
