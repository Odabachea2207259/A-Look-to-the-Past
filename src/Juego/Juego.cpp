#include "Juego.hpp"
#include<iostream>
#include"../Motor/Render/Render.hpp"
#include"../Motor/Utils/Vector2D.hpp"
#include "Figuras/Figuras.hpp"
#include "Sistemas/Sistemas.hpp"
#include "../Motor/Utils/Lista.hpp"
#include "../Motor/GUI/GLogger.hpp"
#include "../Motor/Camaras/CamarasGestor.hpp"
#include "Escenas/Escena_Menu.hpp"
#include "Escenas/EscenaCombate.hpp"
#include "Escenas/EscenaJefe.hpp"
#include "Escenas/EscenaFosiles.hpp"
#include "Escenas/EscenaSeleccion.hpp"
#include "Escenas/EscenaVictoria.hpp"
#include "Escenas/EscenaDerrota.hpp"
#include "Escenas/EscenaMejora.hpp"
#include "Escenas/Escena_Zombie.hpp"
#include "Escenas/EscenaBestiario.hpp"
#include "Objetos/Jugador.hpp"
#include "Objetos/Recompensas.hpp"
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
        Jugador::Get().GetDinero() = 100;
        Jugador::Get().GetNivel() = 1;
        Recompensas::Get().GetRecompensa() = Recompensas::Rewards::NADA;


        //DESCOMENTAR
        
	    CE::GestorEscenas::Get().registrarEscena("Menu",std::make_shared<IVJ::Escena_Menu>());
	    CE::GestorEscenas::Get().registrarEscena("Combate",std::make_shared<EscenaCombate>());
        CE::GestorEscenas::Get().registrarEscena("Jefe",std::make_shared<IVJ::EscenaJefe>());
        CE::GestorEscenas::Get().registrarEscena("Fosiles",std::make_shared<IVJ::EscenaFosiles>());
        CE::GestorEscenas::Get().registrarEscena("Seleccion",std::make_shared<IVJ::EscenaSeleccion>());
        CE::GestorEscenas::Get().registrarEscena("Victoria",std::make_shared<IVJ::EscenaVictoria>());
        CE::GestorEscenas::Get().registrarEscena("Derrota",std::make_shared<IVJ::EscenaDerrota>());
        CE::GestorEscenas::Get().registrarEscena("Mejora",std::make_shared<IVJ::EscenaMejora>());
        CE::GestorEscenas::Get().registrarEscena("Bestiario",std::make_shared<IVJ::EscenaBestiario>());
        
	    CE::GestorEscenas::Get().cambiarEscena("Menu");
        

        //--------------------Escenas de clase-------------------------------------------->
        //CE::GestorEscenas::Get().registrarEscena("Zombie",std::make_shared<IVJ::Escena_Zombie>());
	    //CE::GestorEscenas::Get().cambiarEscena("Zombie");
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

	    if(eventos->is<sf::Event::KeyPressed>() || eventos->is<sf::Event::MouseButtonPressed>())
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

    void Juego::OnInputs(float dt)
    {
        auto br = escena_actual->getBotonesRegistrados();

        CE::Botones::TipoAccion tipo_accion = CE::Botones::TipoAccion::OnRelease;
        std::string strAccion ="None";
        sf::Keyboard::Scancode scan = sf::Keyboard::Scancode::Comma;

        for(auto &sk : br)
        {
            if(sf::Keyboard::isKeyPressed(sk))
            {
                tipo_accion = CE::Botones::TipoAccion::OnPress;
                scan = sk;
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
