#include "Juego.hpp"
#include<iostream>
#include"../Motor/Render/Render.hpp"
#include"../Motor/Utils/Vector2D.hpp"
#include "Figuras/Figuras.hpp"
#include "Sistemas/Sistemas.hpp"
#include "../Motor/Utils/Lista.hpp"
#include "../Motor/GUI/GLogger.hpp"
#include "../Motor/Camaras/CamarasGestor.hpp"
#include "Escenas/EscenaCuadro.hpp"
#include "Escenas/EscenaCirculos.hpp"
#include "Escenas/EscenaFigura.hpp"
#include "../Motor/Primitivos/GestorEscenas.hpp"

#include<SFML/Graphics.hpp>
#include <fstream>
#include <string>

namespace IVJ
{

    Juego::Juego()
        :CE::GameLayer{}
    {
        termino=false;
    }
    void Juego::OnInit(void)
    {
        std::cout<<"Inicializando Juego\n";

	CE::GestorEscenas::Get().registrarEscena("Cuadros",std::make_shared<IVJ::EscenaCuadros>());
	CE::GestorEscenas::Get().registrarEscena("Circulos",std::make_shared<IVJ::EscenaCirculos>());
	CE::GestorEscenas::Get().registrarEscena("Figuras",std::make_shared<IVJ::EscenaFiguras>());
	CE::GestorEscenas::Get().cambiarEscena("Figuras");
	escena_actual = &CE::GestorEscenas::Get().getEscenaActual();

    }
    void Juego::OnInputs(float dt ,std::optional<sf::Event>& eventos)
    {
        if(eventos->getIf<sf::Event::Closed>())
            termino =true;

	    //INPUTS
	    CE::Botones::TipoAccion tipo_accion = CE::Botones::TipoAccion::None;
	    std::string strAccion = "None";
	    sf::Keyboard::Scancode scan = sf::Keyboard::Scancode::Comma;

	    if(eventos->is<sf::Event::KeyPressed>())
	    {
	    	const auto e = eventos->getIf<sf::Event::KeyPressed>();
		tipo_accion = CE::Botones::TipoAccion::OnPress;

		if(e)
		{
			scan = e->scancode;
			if(escena_actual->getBotones().find(scan) == escena_actual->getBotones().end()) return;
			strAccion = escena_actual->getBotones().at(scan);
		}
	    }
	    else
	    {
	    	const auto e = eventos->getIf<sf::Event::KeyReleased>();
		tipo_accion = CE::Botones::TipoAccion::OnRelease;
		
		if(e)
		{
			scan = e->scancode;
			if(escena_actual->getBotones().find(scan) == escena_actual->getBotones().end()) return;
			strAccion = escena_actual->getBotones().at(scan);
		}
	     }
	     escena_actual->onInputs(CE::Botones(strAccion,tipo_accion,scan));
    }

    void Juego::OnUpdate(float dt)
    {
    	escena_actual = &CE::GestorEscenas::Get().getEscenaActual();
	escena_actual->onUpdate(dt);
    }

    void Juego::OnRender(float dt)
    {
    	escena_actual->onRender();
    }

}
