#include "EscenaDerrota.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Objetos/Jugador.hpp"
#include "../Objetos/Equipos.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "../../Motor/Utils/Lerp.hpp"
#include "../../Motor/Utils/Ventana.hpp"
#include <fstream>

namespace IVJ
{
	void EscenaDerrota::onInit()
	{
		if(inicializar) {
            CE::GestorAssets::Get().agregarTextura("Derrota",ASSETS "/pantallas/Derrota.png",CE::Vector2D{0,0},CE::Vector2D{1080,720});
            fondo = std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("Derrota"),1080,720,1.f);
            fondo->m_sprite.setPosition({1080.f/2.f,720.f/2.f});
            //Agregar imagen al gestor de texturas
            boton = std::make_shared<Rectangulo>(200.f,20.f,sf::Color(224,201,166),sf::Color::Transparent);
            boton->addComponente(std::make_shared<CE::ITexto>(
                CE::GestorAssets::Get().getFont("Caveman"),"Regresar"
            ));

            dinero = std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),"Dino$");
            dinero->m_texto.setCharacterSize(10);
            dinero->m_texto.setFillColor(sf::Color(164,134,86));
            //auto tam = CE::Render::Get().GetVentana().getSize();
            CE::Vector2D tam = {CE::WIDTH,CE::HEIGHT};

            dinero->m_texto.setPosition({(tam.x/2)-100.f,tam.y-400.f});
            boton->setPosicion((tam.x/2)-100.f,tam.y-165.f);

            auto texto = boton->getComponente<CE::ITexto>();
            texto->m_texto.setCharacterSize(10);
            texto->m_texto.setPosition(boton->getPosicion());
            texto->m_texto.setFillColor(sf::Color::Black);
        }
        
        for(auto & dino : Equipos::Get().GetPlayer())
                IVJ::SistemaReiniciarDino(dino);

        int ganancias = Jugador::Get().GetNivel() * 5;

        dinero->m_texto.setString(sf::String("Dino$ " + std::to_string(ganancias)));
            
        Jugador::Get().GetDinero() += ganancias;
        
        Equipos::Get().GetPlayer().clear();

        Jugador::Get().GetNivel() = 1;

		inicializar = false;
	}
	void EscenaDerrota::onFinal(){
        CE::GestorAssets::Get().getMusica("combate").stop();

        CE::GestorAssets::Get().getMusica("menu").play();
        CE::GestorAssets::Get().getMusica("oceano").play();
    }
	void EscenaDerrota::onUpdate(float dt)
	{
        auto mousePos = CE::Render::Get().getMousePos();
        if(boton->rect_bounding.contains({static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}))
        {
            boton->getComponente<CE::ITexto>()->m_texto.setFillColor(sf::Color(166,134,86));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                CE::GestorEscenas::Get().cambiarEscena("Menu");
        }
        else
            boton->getComponente<CE::ITexto>()->m_texto.setFillColor(sf::Color::Black);   
	}

	void EscenaDerrota::onInputs(const CE::Botones& accion)
	{

	}

	void EscenaDerrota::onRender()
	{
        CE::Render::Get().AddToDraw(fondo->m_sprite);

        CE::Render::Get().AddToDraw(dinero->m_texto);

        CE::Render::Get().AddToDraw(*boton);
        CE::Render::Get().AddToDraw(boton->getComponente<CE::ITexto>()->m_texto);
	}
}