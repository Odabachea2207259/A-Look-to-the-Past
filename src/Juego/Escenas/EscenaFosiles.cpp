#include "EscenaFosiles.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Objetos/Jugador.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "../../Motor/Utils/Lerp.hpp"
#include <fstream>

namespace IVJ
{
	void EscenaFosiles::onInit()
	{
		if(!inicializar)
        {
            mostrarDinos();
            return;
        }

        CE::GestorCamaras::Get().setCamaraActiva(0);

 		registrarBotones(sf::Keyboard::Scancode::Escape,"menu");

        //Recorrer el .txt

        fondo = sf::RectangleShape({static_cast<float>(CE::Render::Get().GetVentana().getSize().x),static_cast<float>(CE::Render::Get().GetVentana().getSize().y)});
        fondo.setFillColor(sf::Color(164,89,69));

        std::ifstream archivo{ASSETS "/sprites_dinos/Dinosaurios.txt"};
        std::string nombre;

        if(!archivo.is_open())
            std::cerr << "No se pudo abrir el txt\n";

        int i = 0;
        int y = 1;

        while(std::getline(archivo,nombre))
        {
            CE::GestorAssets::Get().agregarTextura("fondo_"+nombre,ASSETS "/sprites_dinos/"+nombre+"/Fondo.png",CE::Vector2D{0,0},CE::Vector2D{250.f,250.f});
            CE::GestorAssets::Get().agregarTextura("skull_"+nombre,ASSETS "/sprites_dinos/"+nombre+"/Skull.png",CE::Vector2D{0,0},CE::Vector2D{250.f,250.f});

            auto fosil = std::make_shared<IVJ::Rectangulo>(250.f,250.f,sf::Color::Transparent,sf::Color::Transparent);
            fosil->addComponente(std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("fondo_"+nombre),250.f,250.f,1.f));
            fosil->getComponente<CE::ISprite>()->m_sprite.setPosition({(260.f*i)+125.f,10.f+125.f});
            auto nombre_fosil = fosil->getNombre();
            nombre_fosil->nombre = nombre;
            fosiles.push_back(fosil);

            i += 1;
            if(i%4==0)
                y++;
        }

        archivo.close();

        mostrarDinos();

		inicializar = false;
	}
	void EscenaFosiles::onFinal(){}
	void EscenaFosiles::onUpdate(float dt)
	{

	}

	void EscenaFosiles::onInputs(const CE::Botones& accion)
	{

		if(accion.getTipo() == CE::Botones::TipoAccion::OnPress)
		{
            if(accion.getNombre() == "menu")
				CE::GestorEscenas::Get().cambiarEscena("Menu");
		}
	}

	void EscenaFosiles::onRender()
	{
        CE::Render::Get().AddToDraw(fondo);

		for(auto &f : fosiles)
			CE::Render::Get().AddToDraw(f->getComponente<CE::ISprite>()->m_sprite);

		for(auto &s : skulls)
			CE::Render::Get().AddToDraw(s->getComponente<CE::ISprite>()->m_sprite);
	}

    void EscenaFosiles::mostrarDinos()
    {
        auto dinos = Jugador::Get().GetDinosaurios();
        for(auto & dino : dinos)
        {
            int i = 0, y = 1;
            for(auto & fosil : fosiles)
            {
                auto nombre = dino->getNombre()->nombre;
                auto nombre_fosil = fosil->getNombre()->nombre;
                if(nombre == nombre_fosil)
                {
                    auto skull = std::make_shared<IVJ::Rectangulo>(250.f,250.f,sf::Color::Transparent,sf::Color::Transparent);
                    skull->addComponente(std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("skull_"+nombre),250.f,250.f,1.f));
                    skull->getComponente<CE::ISprite>()->m_sprite.setPosition({(260.f*i)+125.f,(10.f*y)+125.f});
                    skulls.push_back(skull);
                    break;
                }
                i += 1;
                if(i%4==0)
                    y++;
            }
        }
    }
}