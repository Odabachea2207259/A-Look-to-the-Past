#include "Escena_Menu.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Objetos/Jugador.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../../Motor/Utils/Ventana.hpp"
#include "../../Motor/GUI/GLogger.hpp"
#include "../Objetos/Texto.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace IVJ
{
	void Escena_Menu::onInit()
	{
		CE::GestorCamaras::Get().setCamaraActiva(0);

		if(tutoEnd) tutoQuest = true;

		if(IVJ::Quests::Get().GetCambios())
		{
			actualizarQuests();

			IVJ::Quests::Get().GetCambios() = false;
		}

		if((Jugador::Get().GetPeriodo() - periodo_prev) > 0){
			for(int i = 0; i < (Jugador::Get().GetPeriodo() - periodo_prev); i++){
				cuello.push_back(std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("cuello"),91,90,0.5f));
			}

			periodo_prev = Jugador::Get().GetPeriodo();
		}

		switch(Jugador::Get().GetPeriodo()){
			case MESOZOICO:
				Jugador::Get().GetCheckpoint() = Jugador::Get().GetPeriodo();
				break;
		}

		Jugador::Get().GetPeriodo() = Jugador::Get().GetCheckpoint(); 

		if(!inicializar) return;

		max_tiempo = 0.15f;
		tiempo = max_tiempo;
		ec = 0.f;

		registrarBotones(sf::Keyboard::Scancode::Tab,"quests");

		CE::GestorAssets::Get().agregarTextura("hattie", ASSETS "/Hatter.png", CE::Vector2D{0,0},CE::Vector2D{300,300});

		CE::GestorAssets::Get().agregarTextura("hoja_yellow",ASSETS "/sprites_aliens/alienYellow.png",CE::Vector2D{0,0},CE::Vector2D{256,512});
		CE::GestorAssets::Get().agregarTextura("hoja_pink",ASSETS "/sprites_aliens/alienPink.png",CE::Vector2D{0,0},CE::Vector2D{256,512});

		CE::GestorAssets::Get().agregarTextura("parasaurolophus",ASSETS "/sprites_dinos/Parasaurolophus/Parasaurolophus_tex.png",CE::Vector2D{0,0},CE::Vector2D{1221,3976});
		CE::GestorAssets::Get().agregarTextura("cabezaParasaurolophus",ASSETS "/sprites_dinos/Parasaurolophus/Cabeza.png",CE::Vector2D{0,0},CE::Vector2D{59,79});

		CE::GestorAssets::Get().agregarTextura("centrosaurus",ASSETS "/sprites_dinos/Centrosaurus/Centrosaurus_tex.png",CE::Vector2D{0,0},CE::Vector2D{1221,3877});
		CE::GestorAssets::Get().agregarTextura("cabezaCentrosaurus",ASSETS "/sprites_dinos/Centrosaurus/Cabeza.png",CE::Vector2D{0,0},CE::Vector2D{53,100});
		
		CE::GestorAssets::Get().agregarTextura("pachy",ASSETS "/sprites_dinos/Pachycephalosaurus/Pachycephalosaurus_tex.png",CE::Vector2D{0,0},CE::Vector2D{1586,3875});
		CE::GestorAssets::Get().agregarTextura("cabezaPachycephalosaurus",ASSETS "/sprites_dinos/Pachycephalosaurus/Cabeza.png",CE::Vector2D{0,0},CE::Vector2D{54,56});
		
		CE::GestorAssets::Get().agregarTextura("carnotauro",ASSETS "/sprites_dinos/Carnotauro/Carnotauro_tex.png",CE::Vector2D{0,0},CE::Vector2D{1197,4049});
		CE::GestorAssets::Get().agregarTextura("cabezaCarnotauro",ASSETS "/sprites_dinos/Carnotauro/Cabeza.png",CE::Vector2D{0,0},CE::Vector2D{62,45});
		
		CE::GestorAssets::Get().agregarTextura("argentino",ASSETS "/enemigos/jefes/Argentinosaurus/Armature_tex.png",CE::Vector2D{0,0},CE::Vector2D{1837,3073});
		CE::GestorAssets::Get().agregarTextura("anteosaurus",ASSETS "/enemigos/jefes/Anteosaurus/Anteosaurus_tex.png",CE::Vector2D{0,0},CE::Vector2D{1760,3960});
		CE::GestorAssets::Get().agregarTextura("cabezaAnteosaurus",ASSETS "/enemigos/jefes/Anteosaurus/Cabeza.png",CE::Vector2D{0,0},CE::Vector2D{82,71});
		
		CE::GestorAssets::Get().agregarTextura("coty",ASSETS "/enemigos/jefes/Coty/Coty_tex.png",CE::Vector2D{0,0},CE::Vector2D{1020,1722});
		CE::GestorAssets::Get().agregarTextura("cabezaCoty",ASSETS "/enemigos/jefes/Coty/Cabeza.png",CE::Vector2D{0,0},CE::Vector2D{50,43});

		CE::GestorAssets::Get().agregarFont("Caveman",ASSETS "/fonts/Prehistoric Caveman.ttf");
		CE::GestorAssets::Get().agregarFont("Shadows", ASSETS "/fonts/ShadowsIntoLight-Regular.ttf");
		CE::GestorAssets::Get().agregarFont("Science", ASSETS "/fonts/Science.ttf");

		CE::GestorAssets::Get().agregarTextura("dinero", ASSETS "/iconos/dinero.PNG",CE::Vector2D{0,0},CE::Vector2D{132,74});
		CE::GestorAssets::Get().agregarTextura("progreso", ASSETS "/iconos/progreso.png", CE::Vector2D{0,0},CE::Vector2D{1300,200});
		CE::GestorAssets::Get().agregarTextura("fosiles",ASSETS "/iconos/Fosiles.png",CE::Vector2D{0,0},CE::Vector2D{273,112});
		CE::GestorAssets::Get().agregarTextura("lab",ASSETS "/iconos/Lab.png",CE::Vector2D{0,0},CE::Vector2D{234,104});
		CE::GestorAssets::Get().agregarTextura("bestiarioBoton",ASSETS "/iconos/BestiarioCerr.png",CE::Vector2D{0,0},CE::Vector2D{113,136});
		
		CE::GestorAssets::Get().agregarTextura("craneo",ASSETS "/iconos/Craneo.png",CE::Vector2D{0,0},CE::Vector2D{167,109});
		CE::GestorAssets::Get().agregarTextura("cuello",ASSETS "/iconos/Cuello.png",CE::Vector2D{0,0},CE::Vector2D{91,90});
		CE::GestorAssets::Get().agregarTextura("selector",ASSETS "/iconos/selector.png",CE::Vector2D{0,0},CE::Vector2D{594,420});

		CE::GestorAssets::Get().agregarTextura("sangrado",ASSETS "/estados/Sangrado.PNG",CE::Vector2D{0,0},CE::Vector2D{100,100});
		CE::GestorAssets::Get().agregarTextura("dormido",ASSETS "/estados/Dormido.PNG",CE::Vector2D{0,0},CE::Vector2D{100,100});
		CE::GestorAssets::Get().agregarTextura("aturdido",ASSETS "/estados/Aturdido.png",CE::Vector2D{0,0},CE::Vector2D{100,100});

		CE::GestorAssets::Get().agregarTextura("Embestida",ASSETS "/habilidades/Embestida.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Mordisco",ASSETS "/habilidades/Mordisco.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Cabezazo",ASSETS "/habilidades/Cabezazo.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Punzada",ASSETS "/habilidades/Punzada.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		
		CE::GestorAssets::Get().agregarTextura("Rugido",ASSETS "/habilidades/Rugido.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Canto",ASSETS "/habilidades/Canto.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		
		CE::GestorAssets::Get().agregarTextura("Sanar",ASSETS "/habilidades/Sanar.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Curar",ASSETS "/habilidades/Curar.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Valor",ASSETS "/habilidades/Valor.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Impulso",ASSETS "/habilidades/Impulso.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Adrenalina",ASSETS "/habilidades/Adrenalina.png",CE::Vector2D{0,0},CE::Vector2D{600,200});

		CE::GestorAssets::Get().agregarTextura("Mapa_1", ASSETS "/fondo/MenuPrincipal-Mapa1.jpg",CE::Vector2D{0,0},CE::Vector2D{1600,1200});
		CE::GestorAssets::Get().agregarTextura("Mapa_2", ASSETS "/fondo/MenuPrincipal-Mapa2.jpg",CE::Vector2D{0,0},CE::Vector2D{1600,1200});
		CE::GestorAssets::Get().agregarTextura("Mapa_3", ASSETS "/fondo/MenuPrincipal-Mapa3.jpg",CE::Vector2D{0,0},CE::Vector2D{1600,1200});

		CE::GestorAssets::Get().agregarTextura("Bestiario",ASSETS "/bestiario/Bestiario.png",CE::Vector2D{0,0},CE::Vector2D{4320,4320});

		CE::GestorAssets::Get().agregarSonido("CerrarLibro", ASSETS "/bestiario/close_book.wav");
		CE::GestorAssets::Get().agregarSonido("AbrirLibro", ASSETS "/bestiario/open_book.mp3");

		CE::GestorAssets::Get().agregarSonido("mouse_hover", ASSETS "/mouse_hover.wav");
		
		auto sizeVentana = CE::Render::Get().GetVentana().getSize();

		pos_tutorial_1 = {
			{0.f,0.f},
			{450.f,0.f},
			{110.f,0.f},
			{0.f,-160.f},
			{0.f,150.f}
		};

		pos_tutorial_2 = {
			{-1080.f,0.f},
			{-910.f,0.f},
		};

		tuto_1 = std::make_shared<Rectangulo>(CE::WIDTH,CE::HEIGHT,sf::Color(0,0,0,200),sf::Color::Transparent);
		tuto_2 = std::make_shared<Rectangulo>(CE::WIDTH,CE::HEIGHT,sf::Color(0,0,0,200),sf::Color::Transparent);

		hattie = std::make_shared<Rectangulo>(300.f,300.f,sf::Color::Transparent,sf::Color::Transparent);

		hattie->addComponente(std::make_shared<CE::ISprite>(
			CE::GestorAssets::Get().getTextura("hattie"),
			300,300,
			1.f
		)
		);

		hattie->setPosicion(300.f,300.f);
		hattie->getComponente<CE::ISprite>()->m_sprite.setPosition({CE::WIDTH/2 - 150.f,CE::HEIGHT/2 - 100.f});

		texto_tutorial = std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Science"),
			"Prueba"
		);

		texto_tutorial->m_texto.setCharacterSize(30.f);
		texto_tutorial->m_texto.setFillColor(sf::Color::White);
		texto_tutorial->m_texto.setPosition({CE::WIDTH/2 - 300.f,CE::HEIGHT/2});

		progreso = std::make_shared<Rectangulo>((1300.f*0.6)-30,10+(200.f*0.5),sf::Color::Transparent,sf::Color::White);
		progreso->setPosicion(160.f, 20.f); //200.f,20.f
		progreso->addComponente(std::make_shared<CE::ISprite>(
			CE::GestorAssets::Get().getTextura("progreso"),1300.f,200.f,0.7f)
		);

		auto spriteProgreso = progreso->getComponente<CE::ISprite>();
		spriteProgreso->m_sprite.setPosition({70.f+(1300.f*0.7f)/2.f,(200.f*0.7f)/2.f});

		fosiles = std::make_shared<Rectangulo>(273,112,sf::Color::Transparent,sf::Color::White);
		fosiles->setPosicion((sizeVentana.x - 273.f),(sizeVentana.y - 112.f));
		fosiles->addComponente(std::make_shared<CE::ISprite>(
			CE::GestorAssets::Get().getTextura("fosiles"),273.f,112.f,1.f)
		);

		auto spriteFosiles = fosiles->getComponente<CE::ISprite>();
		spriteFosiles->m_sprite.setPosition({(sizeVentana.x - 273.f) + ((273.f * 1.f)/2.f),(sizeVentana.y - 112.f)+((112.f * 1.f)/2.f)});

		lab = std::make_shared<Rectangulo>(234,104,sf::Color::Transparent,sf::Color::White);
		lab->setPosicion((sizeVentana.x - 515.f),(sizeVentana.y - 104.f));
		lab->addComponente(std::make_shared<CE::ISprite>(
			CE::GestorAssets::Get().getTextura("lab"),234.f,104.f,1.f)
		);

		auto spriteLab = lab->getComponente<CE::ISprite>();
		spriteLab->m_sprite.setPosition({(sizeVentana.x - 515.f) + ((234.f * 1.f)/2.f),(sizeVentana.y - 104.f)+((104.f * 1.f)/2.f)});

		bestiario = std::make_shared<Rectangulo>(113,136,sf::Color::Transparent,sf::Color::Transparent);
		bestiario->setPosicion(50.f,(sizeVentana.y - 150.f));

		bestiario->addComponente(std::make_shared<CE::ISprite>(
			CE::GestorAssets::Get().getTextura("bestiarioBoton"),
			113,136,
			1.0f
		));

		auto spriteBestiario = bestiario->getComponente<CE::ISprite>();
		spriteBestiario->m_sprite.setPosition({50.f + (113/2),(sizeVentana.y - 150.f) + (136/2)});
		
		iconoDinero = std::make_shared<Rectangulo>(0,0,sf::Color::Transparent,sf::Color::Transparent);
		iconoDinero->addComponente(std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Caveman"),
			std::to_string(Jugador::Get().GetDinero())
		));

		iconoDinero->addComponente(std::make_shared<CE::ISprite>(
			CE::GestorAssets::Get().getTextura("dinero"),132.f,74.f,0.5f
		));

		auto spriteDinero = iconoDinero->getComponente<CE::ISprite>();
		spriteDinero->m_sprite.setPosition({35.f,120.f});

		auto textoDinero = iconoDinero->getComponente<CE::ITexto>();
		textoDinero->m_texto.setPosition(sf::Vector2f({73.f,122.f}));
		textoDinero->m_texto.setCharacterSize(6);
		textoDinero->m_texto.setFillColor(sf::Color::Black);

		periodo = std::make_shared<Rectangulo>(0,0,sf::Color::Transparent,sf::Color::Transparent);
		periodo->addComponente(std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Caveman"),
			std::to_string(Jugador::Get().GetPeriodo())
		));

		auto textoPeriodo = periodo->getComponente<CE::ITexto>();
		textoPeriodo->m_texto.setPosition(sf::Vector2f({73.f,100.f}));
		textoPeriodo->m_texto.setCharacterSize(6);
		textoPeriodo->m_texto.setFillColor(sf::Color::Black);

		tooltip = std::make_shared<Rectangulo>(0,0,sf::Color(245,240,230),sf::Color(0,0,0,0));
		tooltip->addComponente(std::make_shared<CE::ITexto>(
			CE::GestorAssets::Get().getFont("Caveman"),
			"Prueba"
		));

		auto textoTooltip = tooltip->getComponente<CE::ITexto>();
		textoTooltip->m_texto.setFont(CE::GestorAssets::Get().getFont("Caveman"));
		textoTooltip->m_texto.setCharacterSize(5);
		textoTooltip->m_texto.setFillColor(sf::Color::Black);

		auto mexico = std::make_shared<IVJ::Pais>(100.f,50.f,sf::Color::Transparent,sf::Color::Transparent,false,10);
		mexico->setPosicion(227.f,305.f);
		auto nombre_mex = mexico->getNombre();
		nombre_mex->nombre = "Mexico";
		mexico->dinosMex();

		paises.push_back(mexico);

		auto usa = std::make_shared<IVJ::Pais>(175.f,60.f,sf::Color::Transparent,sf::Color::Transparent,false,10);
		usa->setPosicion(213.f,236.f);
		auto nombre_usa = usa->getNombre();
		nombre_usa->nombre = "USA";
		usa->dinosUsa();

		paises.push_back(usa);

		auto canada = std::make_shared<IVJ::Pais>(175.f,75.f,sf::Color::Transparent,sf::Color::Transparent,false,10);
		canada->setPosicion(243.f,157.f);
		auto nombre_canada = canada->getNombre();
		nombre_canada->nombre = "Canada";
		canada->dinosCan();

		paises.push_back(canada);

		auto argentina = std::make_shared<IVJ::Pais>(30.f,100.f,sf::Color::Transparent,sf::Color::Transparent,false,20);
		argentina->setPosicion(361.f,520.f);
		auto nombre_arg = argentina->getNombre();
		nombre_arg->nombre = "Argentina";
		argentina->dinosArg();

		paises.push_back(argentina);

		cant_paises = 4;

		auto tam = CE::Render::Get().GetVentana().getSize();

		fondo_1 = std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("Mapa_1"),1600,1200,0.7f);
		fondo_1->m_sprite.setPosition(sf::Vector2f{(fondo_1->width*0.7f)/2,(fondo_1->height*0.7f)/2});

		fondo_2 = std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("Mapa_2"),1600,1200,0.7f);
		fondo_2->m_sprite.setPosition(sf::Vector2f{(fondo_2->width*0.7f)/2,(fondo_2->height*0.7f)/2});

		fondo_3 = std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("Mapa_3"),1600,1200,0.7f);
		fondo_3->m_sprite.setPosition(sf::Vector2f{(fondo_3->width*0.7f)/2,(fondo_3->height*0.7f)/2});

		//cuello = std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("cuello"),91,90,1.f);
		craneo = std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("craneo"),167,109,0.4f);
		craneo->m_sprite.setPosition(sf::Vector2f{200.f,100.f});

		//CE::GestorCamaras::Get().agregarCamara(std::make_shared<CE::CamaraLERP>(
		//	CE::Vector2D{540,360},CE::Vector2D{300.f,150.f}
		//));
		//CE::GestorCamaras::Get().setCamaraActiva(1);
		
		inicializar = false;
	}
	void Escena_Menu::onFinal(){
		//CE::GestorAssets::Get().getMusica("menu").pause();
	}

	void Escena_Menu::onUpdate(float dt)
	{
		auto textoDinero = iconoDinero->getComponente<CE::ITexto>();
		textoDinero->m_texto.setString(std::to_string(Jugador::Get().GetDinero()));

		auto textoPeriodo = periodo->getComponente<CE::ITexto>();
		textoPeriodo->m_texto.setString(std::to_string(periodo_prev));

		craneo->m_sprite.setPosition(sf::Vector2f{200.f + ((periodo_prev - 1) * 70.f),100.f});

		int cant = 0;
		for(auto &vertebra : cuello){
			vertebra->m_sprite.setPosition(sf::Vector2f{200.f + (cant * 70.f),100.f});
			cant++;
		}

		mouse = false;
		mousePos = CE::Render::Get().getMousePos();

		for(auto &f : objetos.getPool())
		{
			f->onUpdate(dt);
		}
		if(Jugador::Get().GetTutorial() && parrafo < cant_parrafos)
		{
			tutorial(dt);
			return;
		} else if(tutoQuest)
		{
			tutorial(dt);
			return;
		}
		
		game(dt);
	}

	void Escena_Menu::game(float dt)
	{
		if(Jugador::Get().GetDinosaurios().empty())
		{
			auto sprite = progreso->getComponente<CE::ISprite>();
			auto color = sprite->m_sprite.getColor();
			sprite->m_sprite.setColor(sf::Color(color.r,color.g,color.b,100));
		}
		else
		{
			auto sprite = progreso->getComponente<CE::ISprite>();
			auto color = sprite->m_sprite.getColor();
			sprite->m_sprite.setColor(sf::Color(color.r,color.g,color.g,255));	
		}

		if(progreso->rect_bounding.contains(sf::Vector2i{static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}) && !Jugador::Get().GetDinosaurios().empty())
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				CE::GestorEscenas::Get().cambiarEscena("Seleccion"); 
		}
	
		if(fosiles->rect_bounding.contains(sf::Vector2i{static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}))
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				CE::GestorEscenas::Get().cambiarEscena("Fosiles"); 
		}

		if(lab->rect_bounding.contains(sf::Vector2i{static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}))
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				CE::GestorEscenas::Get().cambiarEscena("Mejora"); 
		}

		if(bestiario->rect_bounding.contains(sf::Vector2i{static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}))
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				CE::GestorEscenas::Get().cambiarEscena("Bestiario"); 
		}

		for(auto &pais : paises)
		{
			if(pais->rect_bounding.contains(sf::Vector2i{static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}))
			{
				if(!pais->mouseHover) CE::GestorAssets::Get().getSonido("mouse_hover").play();
				pais->mouseHover = true;

				if(!pais->desbloqueado)
					tooltip->setColor(sf::Color(255,255,255,100));
				else
					tooltip->setColor(sf::Color(245,240,230));
				
				auto tooltipText = tooltip->getComponente<CE::ITexto>();
				auto nombre_pais = pais->getNombre();
				tooltipText->m_texto.setString(nombre_pais->nombre);
            	sf::FloatRect textBounds = tooltipText->m_texto.getLocalBounds();

				float padding = 6.0f;
				float tooltipW = textBounds.size.x + padding * 2;
				float tooltipH = textBounds.size.y + padding * 2;
				
				tooltipText->m_texto.setPosition(sf::Vector2f{mousePos.x - textBounds.size.x / 2, mousePos.y - tooltipH - 5 + padding});

            	tooltip->setTam(tooltipW,tooltipH);
            	tooltip->setPosicion(mousePos.x - tooltipW / 2, mousePos.y - tooltipH - 5);
				
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
					if(pais->cantClics == 0)
						pais->cantClics = 1;
					else if(pais->cantClics == 1)
						pais->cantClics = 2;
					mousePrev = false;
				}
				if(pais->cantClics == 1 && !pais->desbloqueado)
				{
					tooltipText->m_texto.setString(std::to_string(pais->precio));
					sf::FloatRect textBounds = tooltipText->m_texto.getLocalBounds();
					float padding = 6.0f;
					float tooltipW = textBounds.size.x + padding * 2;
					float tooltipH = textBounds.size.y + padding * 2;
					
					tooltipText->m_texto.setPosition(sf::Vector2f{mousePos.x - textBounds.size.x / 2, mousePos.y - tooltipH - 5 + padding});
					tooltip->setTam(tooltipW,tooltipH);
					tooltip->setPosicion(mousePos.x - tooltipW / 2, mousePos.y - tooltipH - 5);
					pais->mostrarPrecio = true;
				}
				if(pais->cantClics == 2){
					if(Jugador::Get().GetDinero() >= pais->precio && !pais->dinosaurios.empty()){
						Jugador::Get().GetDinero() -= pais->precio;
						pais->desbloqueado = true;
						Jugador::Get().GetDinosaurios().push_back(pais->dinosaurios.back());
						pais->dinosaurios.pop_back();
						if(Jugador::Get().GetDinosaurios().size() >= 4) IVJ::Quests::Get().terminarQuest("ConseguirDinos");
					}
				}
			}
			else{
				pais->mouseHover = false;
				pais->cantClics = 0;
				pais->mostrarPrecio = false;
			}
		}

		if(!mouse)
		{
			mousePrev = false;
			mousePressed = false;
		}

		tiempo = tiempo - 1*dt;

		if(tiempo <= 0)
		{
			if(uno)
			{
				uno = false;
				dos = true;
			}
			else if(dos)
			{
				dos = false;
				tres = true;
			}
			else if(tres)
			{
				tres = false;
				uno = true;
			}
			tiempo = max_tiempo;
		}
			
		//objetos.borrarPool();
	}

	void Escena_Menu::tutorial(float dt)
	{
		ec += dt*2;
		SistemaFlotar(hattie,ec);

		if(!algo)
		{
			if(!tutoQuest)
				texto_tutorial->m_texto.setString(IVJ::getTutorial("/Tutorial.txt",parrafo));
			else
				texto_tutorial->m_texto.setString(IVJ::getTutorial("/TutorialQuest.txt",parrafo-22));
			algo = true;
		}

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
			parrafo++;
			algo = false;
			mousePrev = false;

			if(tutoQuest)
			{
				switch (parrafo - 22)
				{
					case 3:
						texto_tutorial->m_texto.setCharacterSize(10.f);
						break;
					case 4:
						texto_tutorial->m_texto.setCharacterSize(30.f);
						break;
					case 6:
						texto_tutorial->m_texto.setCharacterSize(50.f);
						break;
					case 7:
						texto_tutorial->m_texto.setCharacterSize(30.f);
						break;
					case 10:
						tuto_1->setPosicion({-60.f,0.f});
						tuto_2->setPosicion({-1080.f,0.f});
						break;
					case 12:
						tuto_1->setPosicion({-560.f,0.f});
						tuto_2->setPosicion({-1080.f,0.f});

						texto_tutorial->m_texto.setPosition({10.f,CE::HEIGHT/2});
						break;
					case 14:
						texto_tutorial->m_texto.setFillColor(sf::Color::Green);
						texto_tutorial->m_texto.setStyle(sf::Text::StrikeThrough);
						break;
					case 15:
						texto_tutorial->m_texto.setFillColor(sf::Color::White);
						texto_tutorial->m_texto.setStyle(sf::Text::Regular);
						break;					
					case 20:
						tutoQuest = false;
						tutoEnd = false;
						Jugador::Get().GetTutorial() = false;
						break;
				}
			}

			switch(parrafo){
				case 5:
					tuto_1->setPosicion(pos_tutorial_1[1]);
					tuto_2->setPosicion(pos_tutorial_2[1]);
					hattie->getComponente<CE::ISprite>()->m_sprite.setPosition({CE::WIDTH/2 + 300.f,CE::HEIGHT/2 - 100.f});
					texto_tutorial->m_texto.setPosition({CE::WIDTH/2,CE::HEIGHT/2});
					break;
				case 8:
					tuto_1->setPosicion(pos_tutorial_1[2]);
					tuto_2->setPosicion(pos_tutorial_2[0]);
					hattie->getComponente<CE::ISprite>()->m_sprite.setPosition({CE::WIDTH/2 - 150.f,CE::HEIGHT/2 - 100.f});
					texto_tutorial->m_texto.setPosition({CE::WIDTH/2 - 300.f,CE::HEIGHT/2});
					break;
				case 10:
					tuto_1->setPosicion(pos_tutorial_1[3]);
					tuto_2->setPosicion(pos_tutorial_2[0]);
					break;
				case 18:
					tuto_1->setPosicion(pos_tutorial_1[4]);
					tuto_2->setPosicion(pos_tutorial_2[0]);
					break;	
				case 21:
					tuto_1->setPosicion({0.f,0.f});
					tuto_2->setPosicion({0.f,0.f});
					break;
				case 23:
					tutoEnd = true;
					break;
			}
		}
	}

	void Escena_Menu::onInputs(const CE::Botones& accion)
	{
		if(accion.getTipo() == CE::Botones::TipoAccion::OnPress)
		{
			if(accion.getNombre() == "quests") keyPrev = true;
		}

		if(accion.getTipo() == CE::Botones::TipoAccion::OnRelease)
		{
			if(accion.getNombre() == "quests" && keyPrev)
			{
				keyPressed = true;
				keyPrev = false;
			}
		}

        if(keyPressed)
		{
			if(!IVJ::Quests::Get().GetAbierto())
			{
				IVJ::Quests::Get().rect_1->setPosicion(CE::WIDTH - 550.f,60.f);
				IVJ::Quests::Get().rect_2->setPosicion(CE::WIDTH - 500.f,60.f);

				IVJ::Quests::Get().rect_1->getComponente<CE::ISprite>()->m_sprite.setPosition({CE::WIDTH - 525.f,60+25.f});

				IVJ::Quests::Get().GetAbierto() = true;
			}
			else
			{
				IVJ::Quests::Get().rect_1->setPosicion(CE::WIDTH - 50.f,60.f);
				IVJ::Quests::Get().rect_2->setPosicion(CE::WIDTH,60.f);

				IVJ::Quests::Get().rect_1->getComponente<CE::ISprite>()->m_sprite.setPosition({CE::WIDTH - 25.f,60+25.f});

				IVJ::Quests::Get().GetAbierto() = false;
			}
			keyPressed = false;
			return;
		}
	}

	void Escena_Menu::onRender()
	{
		if(uno)
			CE::Render::Get().AddToDraw(fondo_1->m_sprite);
		else if(dos)
			CE::Render::Get().AddToDraw(fondo_2->m_sprite);
		else if(tres)
			CE::Render::Get().AddToDraw(fondo_3->m_sprite);
		
			
			//for(auto &f : objetos.getPool())
			//	CE::Render::Get().AddToDraw(*f);
			
			CE::Render::Get().AddToDraw(progreso->getComponente<CE::ISprite>()->m_sprite);
			
			CE::Render::Get().AddToDraw(fosiles->getComponente<CE::ISprite>()->m_sprite);
			CE::Render::Get().AddToDraw(lab->getComponente<CE::ISprite>()->m_sprite);
			
			CE::Render::Get().AddToDraw(bestiario->getComponente<CE::ISprite>()->m_sprite);
			
			CE::Render::Get().AddToDraw(iconoDinero->getComponente<CE::ISprite>()->m_sprite);
			CE::Render::Get().AddToDraw(iconoDinero->getComponente<CE::ITexto>()->m_texto);
			
			CE::Render::Get().AddToDraw(periodo->getComponente<CE::ITexto>()->m_texto);
			
			CE::Render::Get().AddToDraw(craneo->m_sprite);

		for(auto &vertebra : cuello)
			CE::Render::Get().AddToDraw(vertebra->m_sprite);

		for(auto &pais : paises)
			CE::Render::Get().AddToDraw(*pais);
		
		if(mouse)
		{
			CE::Render::Get().AddToDraw(*tooltip);
			CE::Render::Get().AddToDraw(tooltip->getComponente<CE::ITexto>()->m_texto);
		}

		if(parrafo >= cant_parrafos + 2 || !Jugador::Get().GetTutorial())
		{
			CE::Render::Get().AddToDraw(*IVJ::Quests::Get().rect_1);
			CE::Render::Get().AddToDraw(IVJ::Quests::Get().rect_1->getComponente<CE::ISprite>()->m_sprite);
			CE::Render::Get().AddToDraw(*IVJ::Quests::Get().rect_2);

			if(IVJ::Quests::Get().GetAbierto()){
				for(const auto & [key,quest] : IVJ::Quests::Get().GetQuests())
					CE::Render::Get().AddToDraw(quest.first->m_texto);
			}
		}

		if(Jugador::Get().GetTutorial() && parrafo < cant_parrafos || tutoQuest){
			CE::Render::Get().AddToDraw(*tuto_1);
			CE::Render::Get().AddToDraw(*tuto_2);
			CE::Render::Get().AddToDraw(hattie->getComponente<CE::ISprite>()->m_sprite);
			CE::Render::Get().AddToDraw(texto_tutorial->m_texto);
		}
	}
}
