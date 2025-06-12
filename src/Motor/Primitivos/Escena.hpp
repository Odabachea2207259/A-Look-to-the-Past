#pragma once
#include "../Inputs/Botones.hpp"
#include "CEPool.hpp"
#include <SFML/Graphics.hpp>
#include <map>

namespace CE
{
	class Escena
	{
		typedef std::map<sf::Keyboard::Scancode,std::string> HashBotones;
	public:
		virtual ~Escena(){};

		virtual void onInit()=0;
		virtual void onFinal()=0;
		virtual void onUpdate(float dt)=0;
		virtual void onInputs(const CE::Botones& accion)=0;
		virtual void onRender()=0;
		
		void registrarBotones(sf::Keyboard::Scancode boton, const std::string &accion)
		{
			botones[boton]=accion;
		}

		HashBotones &getBotones()
		{
			return botones;
		}
		Pool& getPool()
		{
			return objetos;
		}
            std::vector<sf::Keyboard::Scancode> 
            getBotonesRegistrados()
            {
                std::vector<sf::Keyboard::Scancode> b;
                b.reserve(botones.size());
                for(auto k = botones.begin();k!=botones.end();k++)
                {
                    b.emplace_back(k->first);
                }
                return b;
            }
	public:
		HashBotones botones;
		HashBotones gui;
		std::string nombre;
	protected:
		Pool objetos{100};
	};
}
