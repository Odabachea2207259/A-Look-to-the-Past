#include "Escena_Menu.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Objetos/Jugador.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../../Motor/GUI/GLogger.hpp"
#include "../Objetos/Texto.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace IVJ
{
	void Escena_Menu::onInit()
	{
		CE::GestorCamaras::Get().setCamaraActiva(0);

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

		CE::GestorAssets::Get().agregarTextura("hoja_yellow",ASSETS "/sprites_aliens/alienYellow.png",CE::Vector2D{0,0},CE::Vector2D{256,512});
		CE::GestorAssets::Get().agregarTextura("hoja_pink",ASSETS "/sprites_aliens/alienPink.png",CE::Vector2D{0,0},CE::Vector2D{256,512});

		CE::GestorAssets::Get().agregarTextura("parasaurolophus",ASSETS "/sprites_dinos/Parasaurolophus/Parasaurolophus_tex.png",CE::Vector2D{0,0},CE::Vector2D{1221,3976});
		CE::GestorAssets::Get().agregarTextura("centrosaurus",ASSETS "/sprites_dinos/Centrosaurus/Centrosaurus_tex.png",CE::Vector2D{0,0},CE::Vector2D{1221,3877});
		CE::GestorAssets::Get().agregarTextura("pachy",ASSETS "/sprites_dinos/Pachycephalosaurus/Pachycephalosaurus_tex.png",CE::Vector2D{0,0},CE::Vector2D{1586,3875});
		CE::GestorAssets::Get().agregarTextura("carnotauro",ASSETS "/sprites_dinos/Carnotauro/Carnotauro_tex.png",CE::Vector2D{0,0},CE::Vector2D{1197,4049});
		
		CE::GestorAssets::Get().agregarTextura("argentino",ASSETS "/enemigos/jefes/Argentinosaurus/Armature_tex.png",CE::Vector2D{0,0},CE::Vector2D{1837,3073});
		CE::GestorAssets::Get().agregarTextura("anteosaurus",ASSETS "/enemigos/jefes/Anteosaurus/Anteosaurus_tex.png",CE::Vector2D{0,0},CE::Vector2D{1760,3960});
		CE::GestorAssets::Get().agregarTextura("coty",ASSETS "/enemigos/jefes/Coty/Coty_tex.png",CE::Vector2D{0,0},CE::Vector2D{1020,1722});

		CE::GestorAssets::Get().agregarFont("Byte",ASSETS "/fonts/Bytesized-Regular.ttf");
		CE::GestorAssets::Get().agregarFont("Caveman",ASSETS "/fonts/Prehistoric Caveman.ttf");

		CE::GestorAssets::Get().agregarTextura("dinero", ASSETS "/iconos/dinero.PNG",CE::Vector2D{0,0},CE::Vector2D{132,74});
		CE::GestorAssets::Get().agregarTextura("progreso", ASSETS "/iconos/progreso.png", CE::Vector2D{0,0},CE::Vector2D{1300,200});
		CE::GestorAssets::Get().agregarTextura("fosiles",ASSETS "/iconos/Fosiles.png",CE::Vector2D{0,0},CE::Vector2D{273,112});
		CE::GestorAssets::Get().agregarTextura("lab",ASSETS "/iconos/Lab.png",CE::Vector2D{0,0},CE::Vector2D{234,104});
		CE::GestorAssets::Get().agregarTextura("craneo",ASSETS "/iconos/Craneo.png",CE::Vector2D{0,0},CE::Vector2D{167,109});
		CE::GestorAssets::Get().agregarTextura("cuello",ASSETS "/iconos/Cuello.png",CE::Vector2D{0,0},CE::Vector2D{91,90});

		CE::GestorAssets::Get().agregarTextura("sangrado",ASSETS "/estados/Sangrado.PNG",CE::Vector2D{0,0},CE::Vector2D{100,100});
		CE::GestorAssets::Get().agregarTextura("dormido",ASSETS "/estados/Dormido.PNG",CE::Vector2D{0,0},CE::Vector2D{100,100});
		CE::GestorAssets::Get().agregarTextura("aturdido",ASSETS "/estados/Aturdido.png",CE::Vector2D{0,0},CE::Vector2D{100,100});

		CE::GestorAssets::Get().agregarTextura("Embestida",ASSETS "/habilidades/Embestida.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Mordisco",ASSETS "/habilidades/Mordisco.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Cabezazo",ASSETS "/habilidades/Cabezazo.png",CE::Vector2D{0,0},CE::Vector2D{600,200});
		CE::GestorAssets::Get().agregarTextura("Punzada",ASSETS "/habilidades/Punzada.png",CE::Vector2D{0,0},CE::Vector2D{600,200});

		CE::GestorAssets::Get().agregarTextura("Mapa_1", ASSETS "/fondo/MenuPrincipal-Mapa1.jpg",CE::Vector2D{0,0},CE::Vector2D{1600,1200});
		CE::GestorAssets::Get().agregarTextura("Mapa_2", ASSETS "/fondo/MenuPrincipal-Mapa2.jpg",CE::Vector2D{0,0},CE::Vector2D{1600,1200});
		CE::GestorAssets::Get().agregarTextura("Mapa_3", ASSETS "/fondo/MenuPrincipal-Mapa3.jpg",CE::Vector2D{0,0},CE::Vector2D{1600,1200});

		CE::GestorAssets::Get().agregarTextura("Bestiario",ASSETS "/bestiario/Bestiario.png",CE::Vector2D{0,0},CE::Vector2D{4320,4320});
		
		auto sizeVentana = CE::Render::Get().GetVentana().getSize();

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

		bestiario = std::make_shared<Rectangulo>(200,100,sf::Color::White,sf::Color::White);
		bestiario->setPosicion((sizeVentana.x - 900.f),(sizeVentana.y - 104.f));
		
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
	void Escena_Menu::onFinal(){}
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
		auto mousePos = CE::Render::Get().getMousePos();
		for(auto &f : objetos.getPool())
		{
			f->onUpdate(dt);
		}

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
					}
				}
			}
			else{
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

	void Escena_Menu::onInputs(const CE::Botones& accion)
	{

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
			
			CE::Render::Get().AddToDraw(bestiario->getRectangle());
			
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
	}
}
