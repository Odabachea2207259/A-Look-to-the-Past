#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

namespace IVJ
{
	class TileMap : public sf::Transformable, public sf::Drawable
	{
		public:
			explicit TileMap() = default;
		public:
			bool loadTileMap(const std::string& atlas_path);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
		private:
			int atlas_w{};
			int atlas_h{};
			int tile_w{};
			int tile_h{};
			int map_r{};
			int map_c{};
			std::string atlas_p{};
			sf::VertexArray tiles_vertex;
			sf::Texture atlas_texture;
	};
}
