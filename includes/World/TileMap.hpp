// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Nazara Engine - Graphics module"

// This file is originaly part of Nazara Engine
// It has been modified to suit my needs
// https://github.com/DigitalPulseSoftware/NazaraEngine/

#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <Nazara/Prerequisites.hpp>
#include <Nazara/Graphics/InstancedRenderable.hpp>
#include <Nazara/Graphics/Material.hpp>
#include <Nazara/Graphics/TileMap.hpp>
#include <Nazara/Graphics/AbstractRenderQueue.hpp>
#include <Nazara/Math/Rect.hpp>
#include <Nazara/Utility/VertexStruct.hpp>
#include <Nazara/Graphics/Debug.hpp>

#include "../Utils/TextureManager.hpp"

#include <set>
#include <map>

class TileMap;

using TileMapRef = Nz::ObjectRef<TileMap>;

class TileMap : public Nz::InstancedRenderable {

public:
	TileMap(const Nz::Vector2ui& mapSize, const Nz::Vector2f& tileSize, std::size_t materialCount = 1);

	static TileMapRef New(const Nz::Vector2ui& mapSize, const Nz::Vector2f& tileSize, std::size_t materialCount = 1);
	std::unique_ptr<InstancedRenderable> Clone() const override;

	void AddToRenderQueue(Nz::AbstractRenderQueue* renderQueue, const InstanceData& instanceData, const Nz::Recti& scissorRect) const override;

	void DisableTile(const Nz::Vector2ui& tilePos);
	void DisableTiles();

	void EnableTile(const Nz::Vector2ui& tilePos, const Nz::Rectf& coords, const TileSize& tileSize, const Nz::Color& color = Nz::Color::White, std::size_t materialIndex = 0U);
	void EnableTile(const Nz::Vector2ui& tilePos, const Nz::Rectui& texture, const TileSize& tileSize, const Nz::Color& color = Nz::Color::White, std::size_t materialIndex = 0U);

	using InstancedRenderable::SetMaterial;

private:
	void MakeBoundingVolume() const override;
	void UpdateData(InstanceData* instanceData) const override;

	Nz::Vector2f GetSize() const;

	struct Tile
	{
		std::size_t layerIndex = 0U;
		Nz::Color color = Nz::Color::White;
		Nz::Rectf textureCoords = Nz::Rectf::Zero();
		TileSize tileSize;
		bool enabled = false;
	};

	struct Layer
	{
		std::set<std::size_t> tiles;
	};

	std::vector<Tile> m_tiles;
	std::vector<Layer> m_layers;
	Nz::Vector2ui m_mapSize;
	Nz::Vector2f m_tileSize;
};

#endif