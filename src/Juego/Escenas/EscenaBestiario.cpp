#include "EscenaBestiario.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Objetos/Jugador.hpp"
#include "../Maquinas/AbrirFSM.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../../Motor/Render/Render.hpp"

namespace IVJ
{
	void EscenaBestiario::onInit()
	{
		std::ifstream des(ASSETS"/Descubiertos.json");
		des >> descubiertos;
		mov = true;
		
		if(!inicializar)
        {
            fondo->getComponente<CE::IControl>()->abrir = true;
            return;
        }

		std::ifstream in(ASSETS "/Info.json");
		in >> info;
		
        CE::GestorCamaras::Get().setCamaraActiva(0);

 		registrarBotones(sf::Keyboard::Scancode::Escape,"menu");

        fondo = std::make_shared<Entidad>();

        fondo->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("Bestiario"),
            1080,720,
            1.0f
        ));
        fondo->setPosicion(1080/2,720/2);

		auto nombre = fondo->getNombre();
		nombre->nombre = "Bestiario";

        fondo->addComponente(std::make_shared<CE::IControl>());
        fondo->addComponente(std::make_shared<IVJ::IMaquinaEstado>());
		auto &fsm_init = fondo->getComponente<IMaquinaEstado>()->fsm;
		fsm_init = std::make_shared<AbrirFSM>();
		fsm_init->onEntrar(*fondo);

        izq = std::make_shared<Rectangulo>(470,520,sf::Color::Transparent,sf::Color::White);
        izq->setPosicion(111.f,123.f);

        der = std::make_shared<Rectangulo>(470,520,sf::Color::Transparent,sf::Color::White);
        der->setPosicion(577.f,137.f);

		textoPrueba = std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Shadows"),
			""
		);

		textoPrueba->m_texto.setCharacterSize(30.f);
		textoPrueba->m_texto.setFillColor(sf::Color::Black);
		textoPrueba->m_texto.setPosition({300.f,300.f});

		noDescubierto = std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Shadows"),
			"?\t\t?"
		);

		noDescubierto->m_texto.setCharacterSize(100.f);
		noDescubierto->m_texto.setFillColor(sf::Color::Black);
		noDescubierto->m_texto.setPosition({300.f,300.f});

		periodo = std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Shadows"),
			"Periodo: "
		);

		periodo->m_texto.setCharacterSize(40.f);
		periodo->m_texto.setFillColor(sf::Color::Black);
		periodo->m_texto.setPosition({140.f,600.f});

		nombreEnte = std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Shadows"),
			"Nombre: "
		);

		nombreEnte->m_texto.setCharacterSize(40.f);
		nombreEnte->m_texto.setFillColor(sf::Color::Black);
		nombreEnte->m_texto.setPosition({130.f,500.f});

        objetos.agregarPool(fondo);
        //fondo->getComponente<CE::IControl>()->abrir = true;

        inicializar = false;
	}
	void EscenaBestiario::onFinal(){
        salir = false;
        fondo->getComponente<CE::IControl>()->cambiar = false;
        fondo->getComponente<CE::IControl>()->cerrar = false;
    }
	void EscenaBestiario::onUpdate(float dt)
	{
		auto control = fondo->getComponente<CE::IControl>();

		if(numPagina >= 0 && numPagina < MAX_ENTES){
			if(enteDescubierto(descubiertos,entes[numPagina]))
			{
				textoPrueba->m_texto.setString(entes[numPagina] + "DESCUBIERTOOO");
				nombreEnte->m_texto.setString("Nombre: " + entes[numPagina]);
				std::string p = info[entes[numPagina]]["periodo"];
				periodo->m_texto.setString("Periodo: " + p);
				descubierto = true;
			}
			else
				descubierto = false;
		}
        if(salir)
        {
            auto cerrar = control->cerrar;
            auto cambiar = control->cambiar;

            if(cambiar)
            {
                CE::GestorEscenas::Get().cambiarEscena("Menu");
                return;
            }
            
            if(!cerrar)
                fondo->getComponente<CE::IControl>()->cerrar = true;
        }

        mouse = false;
		auto mousePos = CE::Render::Get().getMousePos();

        for(auto obj : objetos.getPool())
            obj->onUpdate(dt);

		if(izq->rect_bounding.contains(sf::Vector2i{static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}))
		{
		    mouse = true;

			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				mousePressed = true;
			}

			if(mousePressed)
			{
				if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					mousePressed = false;
					mousePrev = true;
				}
			}

			if(mousePrev)
			{
				numPagina--;
                fondo->getComponente<CE::IControl>()->prevPage = true;
				mousePrev = false;
			}
		}

		if(der->rect_bounding.contains(sf::Vector2i{static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}))
		{
		    mouse = true;

			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				mousePressed = true;
			}

			if(mousePressed)
			{
				if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					mousePressed = false;
					mousePrev = true;
				}
			}

			if(mousePrev)
			{
				numPagina++;
                fondo->getComponente<CE::IControl>()->nextPage = true;
				mousePrev = false;
			}
		}

		if(!mouse)
		{
			mousePrev = false;
			mousePressed = false;
		}

		if(numPagina < 0) numPagina = MAX_ENTES-1;
		else if(numPagina >= MAX_ENTES) numPagina = 0;

		if(control->nextPage || control->prevPage || control->abrir || control->cerrar || control->cambiar) mov = true;
		else mov = false;
	}

	void EscenaBestiario::onInputs(const CE::Botones& accion)
	{

		if(accion.getTipo() == CE::Botones::TipoAccion::OnPress)
		{
            if(accion.getNombre() == "menu")
				//CE::GestorEscenas::Get().cambiarEscena("Menu");
                salir = true;
		}
	}

	void EscenaBestiario::onRender()
	{
        CE::Render::Get().AddToDraw(fondo->getComponente<CE::ISprite>()->m_sprite);
		
		if(!mov) 
		{
			if(descubierto){
				CE::Render::Get().AddToDraw(textoPrueba->m_texto);
				CE::Render::Get().AddToDraw(periodo->m_texto);
				CE::Render::Get().AddToDraw(nombreEnte->m_texto);
			}	
			else CE::Render::Get().AddToDraw(noDescubierto->m_texto);
		}
	}
}