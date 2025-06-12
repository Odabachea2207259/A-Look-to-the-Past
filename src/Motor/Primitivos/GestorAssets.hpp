#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "../Utils/Vector2D.hpp"
#include <map>
#include <memory>
#include <string>

namespace CE
{
	class GestorAssets
	{
		public:
			static GestorAssets& Get();
			void agregarFont(const std::string& key, const std::string& filepath);
			sf::Font& getFont(const std::string& key)
			{
				return *hashFonts[key];
			}
			void agregarTextura(const std::string& key, const std::string& filepath,const CE::Vector2D& pos_init, const CE::Vector2D& dim);
			sf::Texture& getTextura(const std::string& key)
			{
				return *hashTexturas[key];
			}
		private:
			std::map<std::string, std::shared_ptr<sf::Font>> hashFonts;
			std::map<std::string, std::shared_ptr<sf::Texture>> hashTexturas;
			static inline GestorAssets* instancia = nullptr;
	};
}
