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
		if(!inicializar)
        {
            fondo->getComponente<CE::IControl>()->abrir = true;
            return;
        }

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
        if(salir)
        {
            auto cerrar = fondo->getComponente<CE::IControl>()->cerrar;
            auto cambiar = fondo->getComponente<CE::IControl>()->cambiar;

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
                fondo->getComponente<CE::IControl>()->nextPage = true;
				mousePrev = false;
			}
		}

		if(!mouse)
		{
			mousePrev = false;
			mousePressed = false;
		}
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
	}
}