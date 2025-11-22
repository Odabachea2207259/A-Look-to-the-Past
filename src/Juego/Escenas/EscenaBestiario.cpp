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

		CE::GestorAssets::Get().agregarTextura("dibujoPara",ASSETS "/sprites_dinos/Parasaurolophus/Parasaurolophus.PNG",CE::Vector2D{0,0},CE::Vector2D{400,300});
		CE::GestorAssets::Get().agregarTextura("dibujoPachy",ASSETS "/sprites_dinos/Pachycephalosaurus/Pachycephalosaurus.PNG",CE::Vector2D{0,0},CE::Vector2D{400,300});
		CE::GestorAssets::Get().agregarTextura("dibujoCentro",ASSETS "/sprites_dinos/Centrosaurus/Centrosaurus.PNG",CE::Vector2D{0,0},CE::Vector2D{400,300});
		CE::GestorAssets::Get().agregarTextura("dibujoCarno",ASSETS "/sprites_dinos/Carnotauro/Carnotauro.PNG",CE::Vector2D{0,0},CE::Vector2D{400,300});
		
		CE::GestorAssets::Get().agregarTextura("dibujoAnte",ASSETS "/enemigos/jefes/Anteosaurus/Anteosaurus.PNG",CE::Vector2D{0,0},CE::Vector2D{400,300});
		CE::GestorAssets::Get().agregarTextura("dibujoCoty",ASSETS "/enemigos/jefes/Coty/Coty.PNG",CE::Vector2D{0,0},CE::Vector2D{400,300});

		CE::GestorAssets::Get().agregarSonido("derecha", ASSETS "/bestiario/page-right.mp3");
		CE::GestorAssets::Get().agregarSonido("izquierda", ASSETS "/bestiario/page-left.mp3");

		CE::GestorAssets::Get().getSonido("derecha").setPitch(2.f);

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

		infoEnte = std::make_shared<IVJ::Rectangulo>(
			380.f,450.f,
			sf::Color::Transparent,
			sf::Color::White
		);

		infoEnte->setPosicion(600.f,200.f);

		infoEnte->addComponente(std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Shadows"),
			""
		));

		auto textoInfo = infoEnte->getComponente<CE::ITexto>();
		textoInfo->m_texto.setCharacterSize(30);
		textoInfo->m_texto.setFillColor(sf::Color::Black);
		textoInfo->m_texto.setPosition({600.f,200.f});

		dibujoEnte = std::make_shared<IVJ::Rectangulo>(
			400.f,300.f,
			sf::Color::Transparent,
			sf::Color::White
		);

		dibujoEnte->setPosicion(150.f,200.f); // -->NO MOVER

		dibujoEnte->addComponente(std::make_shared<CE::ISprite>(
			CE::GestorAssets::Get().getTextura("dibujoAnte"),
			400,300,
			1.f
		));

		dibujoEnte->getComponente<CE::ISprite>()->m_sprite.setPosition({350.f,350.f});

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
		periodo->m_texto.setPosition({150.f,600.f});

		nombreEnte = std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Shadows"),
			"Nombre: "
		);

		nombreEnte->m_texto.setCharacterSize(40.f);
		nombreEnte->m_texto.setFillColor(sf::Color::Black);
		nombreEnte->m_texto.setPosition({140.f,500.f});

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
			cargarInfo();
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
				descubierto = false;
				CE::GestorAssets::Get().getSonido("izquierda").play();
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
				descubierto = false;
				CE::GestorAssets::Get().getSonido("derecha").play();
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
				CE::Render::Get().AddToDraw(periodo->m_texto);
				CE::Render::Get().AddToDraw(nombreEnte->m_texto);
				CE::Render::Get().AddToDraw(infoEnte->getComponente<CE::ITexto>()->m_texto);
				CE::Render::Get().AddToDraw(dibujoEnte->getComponente<CE::ISprite>()->m_sprite);
			}	
			else CE::Render::Get().AddToDraw(noDescubierto->m_texto);
		}
	}

	void EscenaBestiario::cargarInfo()
	{
		if(enteDescubierto(descubiertos,entes[numPagina]))
		{
			//textoPrueba->m_texto.setString(entes[numPagina] + "DESCUBIERTOOO");
			if(descubierto) return;
			nombreEnte->m_texto.setString("Nombre: " + entes[numPagina]);
			std::string p = info[entes[numPagina]]["periodo"];
			periodo->m_texto.setString("Periodo: " + p);
			
			std::string ubi = info[entes[numPagina]]["info"];

			//infoEnte->getComponente<CE::ITexto>()->m_texto.setString(std::wstring(texto.begin(),texto.end()));
			infoEnte->getComponente<CE::ITexto>()->m_texto.setString(IVJ::getInfo(ubi));

			std::string ubiDibujo = info[entes[numPagina]]["dibujo"];

			dibujoEnte->getComponente<CE::ISprite>()->m_sprite.setTexture(
				CE::GestorAssets::Get().getTextura(ubiDibujo)
			);

			descubierto = true;
		}
		else
			descubierto = false;
	}
}