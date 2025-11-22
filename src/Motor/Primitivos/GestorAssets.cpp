#include "GestorAssets.hpp"
#include <iostream>

namespace CE
{
	
	GestorAssets& GestorAssets::Get()
	{
		if(!instancia)
			instancia = new GestorAssets();
		return *instancia;
	}
		
	void GestorAssets::agregarFont(const std::string& key, const std::string& filepath)
	{
		auto font = std::make_shared<sf::Font>();
		if(!font->openFromFile(filepath))
		{
			std::cerr<<"no se pudo abrir el archivo\n";
			exit(EXIT_FAILURE);
		}

		hashFonts[key] = font;
	}

	void GestorAssets::agregarTextura(const std::string& key, const std::string& filepath, const CE::Vector2D& pos_init, const CE::Vector2D& dim)
	{
		auto textura = std::make_shared<sf::Texture>();
		//if(!textura->loadFromFile(filepath,false,sf::IntRect({10,10},{1300,200})))
		if(!textura->loadFromFile(filepath, false, sf::IntRect({(int)pos_init.x,(int)pos_init.y},{(int)dim.x,(int)dim.y})))
		{
			std::cerr<<"no se pudo abrir el archivo\n";
			exit(EXIT_FAILURE);
		}

		textura->setSmooth(true);
		hashTexturas[key] = textura;
	}

    void GestorAssets::agregarSonido(const std::string& key, const std::string& filepath)
    {   
		auto buffer = std::make_shared<sf::SoundBuffer>();
        if(!buffer->loadFromFile(filepath))
            std::cerr<<"No se pudo cargar la Sonido "<<filepath<<"\n";

		hashSoundBuffers[key] = buffer;

		auto sound = std::make_shared<sf::Sound>(*buffer);
		
        hashSonidos[key] = sound;
    }

    void GestorAssets::agregarMusica(const std::string& key, const std::string& filepath)
    {   
        auto musica = std::make_shared<sf::Music>();
        if(!musica->openFromFile(filepath))
            std::cerr<<"No se pudo cargar la Música "<<filepath<<"\n";
        hashMusica[key] = musica;
    }
}
