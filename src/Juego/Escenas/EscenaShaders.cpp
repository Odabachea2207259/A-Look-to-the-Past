#include "EscenaShaders.hpp"
#include "../Figuras/Figuras.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Utils/Vector2D.hpp"
#include "../../Motor/Utils/Lerp.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "../Componentes/IJComponentes.hpp"
#include "../Maquinas/IdleFSM.hpp"
#include "../../Motor/GUI/GLogger.hpp"
#include "../Objetos/Equipos.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

namespace IVJ
{
	void EscenaShaders::onInit()
	{
		objetos.getPool().clear();
		cantDinos = 0;
		dinoTurno = 0;
		if(inicializar) {
			registrarBotones(sf::Keyboard::Scancode::Escape,"menu");
			CE::GestorAssets::Get().agregarTextura("nubes",ASSETS "/textura/cloud.png",CE::Vector2D{0,0},CE::Vector2D{400,400});
			CE::GestorAssets::Get().agregarTextura("noise",ASSETS "/textura/noise_texture.png",CE::Vector2D{0,0},CE::Vector2D{256,256});

			auto tam = CE::Render::Get().GetVentana().getSize();

			medidor = std::make_shared<Rectangulo>(tam.x-6.f,10.f,sf::Color::Blue,sf::Color::Black);
			medidor->setPosicion(3.f,3.f);

			log = std::make_shared<Rectangulo>(500.f,100.f,sf::Color::Green,sf::Color::Black);
			log->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman")," "));
			log->setPosicion((tam.x/2.f)-250.f,40.f);
			auto textLog = log->getComponente<CE::ITexto>();
			textLog->m_texto.setPosition({(tam.x/2.f)-250.f,45.f});
			textLog->m_texto.setCharacterSize(10);

			nivelActual = std::make_shared<Rectangulo>(100.f,100.f,sf::Color::Transparent,sf::Color::Transparent);
			nivelActual->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"), " "));
			auto textoNivel = nivelActual->getComponente<CE::ITexto>();
			textoNivel->m_texto.setCharacterSize(20);
			textoNivel->m_texto.setPosition({5.f,40.f});
			textoNivel->m_texto.setFillColor(sf::Color::Black);

			dinoPuntos = std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman")," ");
			dinoPuntos->m_texto.setCharacterSize(10);
			dinoPuntos->m_texto.setFillColor(sf::Color::Black);
			dinoPuntos->m_texto.setPosition({850.f,650.f});

			rectanguloDino.setFillColor(sf::Color::Transparent);
			rectanguloDino.setOutlineColor(sf::Color::White);
			rectanguloDino.setOutlineThickness(5.f);

			selector.setPointCount(3);

			ancho = 30.f;
			alto = 25.f;
			selector.setPoint(0,sf::Vector2f(ancho / 2.f,0));
			selector.setPoint(1,sf::Vector2f(0,alto));
			selector.setPoint(2,sf::Vector2f(ancho,alto));

			selector.setFillColor(sf::Color::White);
			selector.setRotation(sf::degrees(180));

			fondo.setSize(sf::Vector2f(static_cast<float>(tam.x),150.f));
			fondo.setPosition({2,tam.y-150.f});
			fondo.setFillColor(sf::Color(100,100,100,100));
			fondo.setOutlineColor(sf::Color::Black);
			fondo.setOutlineThickness(2.f);

			if(!bg[0].loadTileMap(ASSETS "/mapas/mapaPelea1_layer1.txt")) exit(EXIT_FAILURE);
			if(!bg[1].loadTileMap(ASSETS "/mapas/mapaPelea1_layer2.txt")) exit(EXIT_FAILURE);
			if(!bg[2].loadTileMap(ASSETS "/mapas/mapaPelea1_layer3.txt")) exit(EXIT_FAILURE);
			if(!bg[3].loadTileMap(ASSETS "/mapas/mapaPelea1_layer4.txt")) exit(EXIT_FAILURE);
			inicializar = false;
		}

		auto textNivelActual = nivelActual->getComponente<CE::ITexto>();
		textNivelActual->m_texto.setString(sf::String(std::to_string(Jugador::Get().GetNivel())));
		eSelecc = false;
		pSelecc = false;
		habilidadActiva = false;
		enemSelecc = nullptr;
		playerSelecc = nullptr;
		habilidadSelecc = nullptr;
		turnos.clear();

		Equipos::Get().crearEnemigos();

		posicionarEnemy();
		posicionarPlayer();

		ordenarTurnos();
		actual = turnos.at(dinoTurno);
		setBotonesFalso();

		/*
		argentino = std::make_shared<IVJ::Entidad>();

		argentino->addComponente(std::make_shared<CE::ISprite>(
			CE::GestorAssets::Get().getTextura("argentino"),
			916,510,
			2.f
		));

		argentino->addComponente(std::make_shared<CE::IControl>());
		argentino->addComponente(std::make_shared<IVJ::IMaquinaEstado>());
		auto &fsm_init = argentino->getComponente<IMaquinaEstado>()->fsm;
		fsm_init = std::make_shared<IdleFSM>();
		fsm_init->onEntrar(*argentino);

		objetos.agregarPool(argentino);
		*/

		//CE::Vector2D{540,360},CE::Vector2D{1090.f,720.f}
		CE::GestorCamaras::Get().agregarCamara(std::make_shared<CE::CamaraCuadro>(
			CE::Vector2D{540,360},CE::Vector2D{100.f,50.f}
		));

		inicializar = false;
	}

    void EscenaShaders::posicionarPlayer()
	{
		int dinoPlayer = 0;
		for(auto & player : Equipos::Get().GetPlayer())
		{
			cantDinos++;
			if(dinoPlayer == 0)
				player->setPosicion(300.f,270.f);
			else if(dinoPlayer == 1)
				player->setPosicion(200.f,380.f);
			else if(dinoPlayer == 2)
				player->setPosicion(300.f,460.f);
			player->setPosOriginal();

			dinoPlayer++;
			objetos.agregarPool(player);
		}
	}

    void EscenaShaders::posicionarEnemy()
	{
		int dinoEnemy = 0;
		for(auto & enemy : Equipos::Get().GetEnemigos())
		{
			cantDinos++;
			if(dinoEnemy == 0)
				enemy->setPosicion(800.f,270.f);
			else if(dinoEnemy == 1)
				enemy->setPosicion(700.f,380.f);
			else if(dinoEnemy == 2)
				enemy->setPosicion(800.f,460.f);
			enemy->setPosOriginal();

			auto sprite = enemy->getComponente<CE::ISprite>();
			sprite->m_sprite.setScale({-sprite->escala,sprite->escala});
			objetos.agregarPool(enemy);

			dinoEnemy++;
		}
	}

	void EscenaShaders::actualizarMedidor()
	{
		auto dinoLider = Equipos::Get().GetDinoLider();
		float porcentaje = dinoLider->getComponente<CE::IJugador>()->medidor / dinoLider->habilidadEspecial->medidor;
		porcentaje = std::min(porcentaje,1.f);
		medidor->setTam(medidor->getWidth() * porcentaje,medidor->getHeight());
	}
	void EscenaShaders::onFinal(){}
	void EscenaShaders::onUpdate(float dt)
	{
		actualizarMedidor();
		if(!actual->estaVivo())
			cambiarTurno();

		CE::GLogger::Get().agregarLog(actual->getNombre()->nombre + ":("+std::to_string(actual->getPosicion().x)+", "+std::to_string(actual->getPosicion().y) + ")",CE::GLogger::Niveles::LOG);
		CE::GLogger::Get().agregarLog("HP->"+std::to_string(actual->getStats()->hp),CE::GLogger::Niveles::LOG);
		CE::GLogger::Get().agregarLog("Str->"+std::to_string(actual->getStats()->str),CE::GLogger::Niveles::LOG);
		CE::GLogger::Get().agregarLog("Agi->"+std::to_string(actual->getStats()->agi),CE::GLogger::Niveles::LOG);
		CE::GLogger::Get().agregarLog("Def->"+std::to_string(actual->getStats()->def),CE::GLogger::Niveles::LOG);
		
		mouse = false;
		auto c = actual->getComponente<CE::IControl>();

		for(auto &f: objetos.getPool())
		{
			f->onUpdate(dt);
		}

		for(auto & enemy : Equipos::Get().GetEnemigos())
		{
			enemy->mostrarEstados();
			enemy->actualizarVida();
		}

		for(auto & player : Equipos::Get().GetPlayer())
		{
			player->mostrarEstados();
			player->actualizarVida();
		}

		CE::Vector2D mousePos = CE::Render::Get().getMousePos();

		//if(actual->jugador && actual->estaVivo())
		if(actual->tieneComponente<CE::IJugador>() && actual->estaVivo())
		{
			auto info = actual->getComponente<CE::IJugador>();
			if(!habilidadActiva)
			{
				for(auto &boton:actual->movimientos)
				{
					if(boton->tipo == EspecialAtaque || boton->tipo == EspecialBuff)
						if(actual != Equipos::Get().GetDinoLider())
							continue;
						else if(info->medidor < boton->medidor)
						{
							boton->setColor(sf::Color::Cyan);
							continue;
						}
					if(boton->dinoPuntos <= info->dinoPuntos && boton->rect_bounding.contains(sf::Vector2i(mousePos.x,mousePos.y)) || boton->seleccionado)
					{
						boton->setColor(sf::Color::Black);
						auto texto = boton->getComponente<CE::ITexto>();
						texto->m_texto.setFillColor(sf::Color::White);
						if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
						{
							habilidadSelecc = boton;
							setBotonesFalso();
							boton->seleccionado = true;
							
							switch(boton->tipo){
								case Attack:
								case Debuffeo:
								case EspecialAtaque:
									eSelecc = true;
									pSelecc = false;
									break;
								case Buffeo:
								case EspecialBuff:
									eSelecc = false;
									pSelecc = true;
									break;
							}
						}
					}
					else
					{
						if((boton->tipo == EspecialAtaque || boton->tipo == EspecialBuff) && Equipos::Get().GetDinoLider()->getComponente<CE::IJugador>()->medidor < boton->medidor) boton->setColor(sf::Color::White);
						else boton->setColor(sf::Color::Cyan);

						if(boton->dinoPuntos > info->dinoPuntos) boton->setColor(sf::Color::White);
						else{
							switch(boton->tipo)
							{
								case Attack:
									boton->setColor(sf::Color::Red);
									break;
								case Buffeo:
									boton->setColor(sf::Color::Blue);
									break;
								case Debuffeo:
									boton->setColor(sf::Color::Magenta);
									break;
								case EspecialAtaque:
								case EspecialBuff:
									boton->setColor(sf::Color::Cyan);
									break;
							}
						}
						auto texto = boton->getComponente<CE::ITexto>();
						texto->m_texto.setFillColor(sf::Color::Black);		
					}
				
					if(eSelecc && habilidadSelecc)
					{
						for(auto& enem : Equipos::Get().GetEnemigos())
						{
							//auto box = enem->getComponente<CE::IBoundingBox>();
							auto box = enem->getComponente<CE::ISprite>();
							auto pos = enem->getPosicion();
						
							auto width = box->width*box->escala;
							auto height = box->height*box->escala;
							sf::IntRect rect({static_cast<int>(pos.x-width/2),static_cast<int>(pos.y-height/2)},{static_cast<int>(width),static_cast<int>(height)});
							
							if(rect.contains(sf::Vector2i(mousePos.x,mousePos.y)) && enem->estaVivo())
							{
								mouse = true;
								mostrarSelector = true;
								rectanguloDino.setSize(sf::Vector2f{width,height});
								rectanguloDino.setPosition(sf::Vector2f{pos.x-width/2,pos.y-height/2});
							
								selector.setPosition({(pos.x-width/2) + (height - ancho) / 2.f,
													(pos.y-width/2) - alto - 2});
								
								bool botonMouseActual = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
								
								if(botonMouseActual && !botonMouseAnterior)
								{
									enemSelecc = enem;
									habilidadActiva = true;
									c->accion = true;
									break;
								}
								
								botonMouseAnterior = botonMouseActual;
							
								break;
							}
							else{
								mouse = false;
							}
						}
					}
					if(pSelecc && habilidadSelecc)
					{
						for(auto& player : Equipos::Get().GetPlayer())
						{
							//auto box = enem->getComponente<CE::IBoundingBox>();
							auto box = player->getComponente<CE::ISprite>();
							auto pos = player->getPosicion();
						
							auto width = box->width*box->escala;
							auto height = box->height*box->escala;
							sf::IntRect rect({static_cast<int>(pos.x-width/2),static_cast<int>(pos.y-height/2)},{static_cast<int>(width),static_cast<int>(height)});
							
							if(rect.contains(sf::Vector2i(mousePos.x,mousePos.y)) && player->estaVivo())
							{
								mouse = true;
								mostrarSelector = true;
								rectanguloDino.setSize(sf::Vector2f{width,height});
								rectanguloDino.setPosition(sf::Vector2f{pos.x-width/2,pos.y-height/2});
							
								selector.setPosition({(pos.x-width/2) + (height - ancho) / 2.f,
													(pos.y-width/2) - alto - 2});
								
								bool botonMouseActual = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
								
								if(botonMouseActual && !botonMouseAnterior)
								{
									playerSelecc = player;
									habilidadActiva = true;
									c->accion = true;
									break;
								}
								
								botonMouseAnterior = botonMouseActual;
							
								break;
							}
							else{
								mouse = false;
							}
						}
					}
				}
			}
		}
		else
		{
			if(!actual->estaVivo()) return;
			if(!habilidadActiva)
			{
				habilidadActiva = true;
				c->accion = true;
			}
			
			habilidadActiva = actual->turnoEnemigo(actual,Equipos::Get().GetPlayer(),Equipos::Get().GetEnemigos(),dt);

			if(!habilidadActiva)
			{
				auto logText = log->getComponente<CE::ITexto>();
				auto nombreDino = actual->getNombre()->nombre;
				sf::String n(nombreDino + "\na realizado su\nmovimiento");
				logText->m_texto.setString(n);

				logText->m_texto.setFillColor(sf::Color::Red);

				pSelecc = false;
				eSelecc = false;
				enemSelecc = nullptr;
				playerSelecc = nullptr;
				habilidadSelecc = nullptr;
				setBotonesFalso();
				cambiarTurno();
			}
		}

		//if(actual->jugador && actual->estaVivo() && enemSelecc)
		if(actual->tieneComponente<CE::IJugador>() && actual->estaVivo() && enemSelecc)
		{
			habilidadActiva = habilidadSelecc->accion(actual,enemSelecc,dt);
			
			if(!habilidadActiva)
			{
				auto logText = log->getComponente<CE::ITexto>();
				auto nombreDino = actual->getNombre()->nombre;
				auto nombreHabilidad = habilidadSelecc->getNombre()->nombre;
				auto nombreEnem = enemSelecc->getNombre()->nombre;
				sf::String n(nombreDino + "\na realizado\n" + nombreHabilidad + "\nen " + nombreEnem);
				logText->m_texto.setString(n);
				//if(actual->jugador)
				if(actual->tieneComponente<CE::IJugador>())
					logText->m_texto.setFillColor(sf::Color::Blue);

				pSelecc = false;
				eSelecc = false;
				enemSelecc = nullptr;
				playerSelecc = nullptr;
				habilidadSelecc = nullptr;
				setBotonesFalso();
				cambiarTurno();
			}
		}
		//if(actual->jugador && actual->estaVivo() && playerSelecc)
		if(actual->tieneComponente<CE::IJugador>() && actual->estaVivo() && playerSelecc)
		{
			habilidadActiva = habilidadSelecc->accion(actual,playerSelecc,dt);
			
			if(!habilidadActiva)
			{
				auto logText = log->getComponente<CE::ITexto>();
				auto nombreDino = actual->getNombre()->nombre;
				auto nombreHabilidad = habilidadSelecc->getNombre()->nombre;
				auto nombrePlayer = playerSelecc->getNombre()->nombre;
				sf::String n(nombreDino + "\na realizado\n" + nombreHabilidad + "\nen " + nombrePlayer);
				logText->m_texto.setString(n);
				//if(actual->jugador)
				if(actual->tieneComponente<CE::IJugador>())
					logText->m_texto.setFillColor(sf::Color::Blue);
				
				pSelecc = false;
				eSelecc = false;
				enemSelecc = nullptr;
				playerSelecc = nullptr;
				habilidadSelecc = nullptr;
				setBotonesFalso();
				cambiarTurno();
			}
		}
		if(!mouse)
		{
			mousePressed = false;
			mousePrev = false;
		}

		objetos.borrarPool();
	}

	void EscenaShaders::setBotonesFalso()
	{
		for(auto& boton:actual->movimientos)
			boton->seleccionado = false;
		actual->habilidadEspecial->seleccionado = false;
		eSelecc = false;
		pSelecc = false;
		mostrarSelector = false;
	}

	void EscenaShaders::cambiarTurno()
	{
		actual->habilidadSelecc = nullptr;
		habilidadSelecc = nullptr;
		switch(revisarGanador()){
			case -1:
				CE::GestorEscenas::Get().cambiarEscena("Derrota");
				return;
			case 1:
				CE::GestorEscenas::Get().cambiarEscena("Victoria");
				return;
		}

		auto c = actual->getComponente<CE::IControl>();
		c->der = false;
		c->izq = false;
		c->abj = false;
		c->arr = false;

		actual->turno = false;
		//actual->dormido = false;
		//actual->aturdido = false;

		auto estado_dino = actual->getComponente<CE::IEstados>();
		estado_dino->dormido = false;
		estado_dino->aturdido = false;
		dinoTurno++;
		if(dinoTurno >= cantDinos)
			dinoTurno = 0;
		
		actual = turnos.at(dinoTurno);
		if(actual->estaVivo()){
			//if(actual->jugador && actual == Equipos::Get().GetDinoLider()) Equipos::Get().GetDinoLider()->medidor += 10;
			//if(actual->tieneComponente<CE::IJugador>() && actual == Equipos::Get().GetDinoLider()) Equipos::Get().GetDinoLider()->getComponente<CE::IJugador>()->medidor += 10;
			//dinoPuntos->m_texto.setString(sf::String("DinoPuntos:\n"+std::to_string(actual->getComponente<CE::IJugador>()->dinoPuntos)));

			if(actual->tieneComponente<CE::IJugador>())
			{
				if(actual == Equipos::Get().GetDinoLider())Equipos::Get().GetDinoLider()->getComponente<CE::IJugador>()->medidor += 10;
				dinoPuntos->m_texto.setString(sf::String("DinoPuntos:\n"+std::to_string(actual->getComponente<CE::IJugador>()->dinoPuntos)));
			}
			actual->habilidadSelecc = nullptr;
			aplicarEstados();
			c = actual->getComponente<CE::IControl>();
			c->der = false;
			c->izq = false;
			if(actual->tieneComponente<CE::IJugador>() && actual->getComponente<CE::IJugador>()->dinoPuntos <= 0 && !actual->tieneAtaquesGratis) cambiarTurno();
			if(actual->getComponente<CE::IEstados>()->dormido || actual->getComponente<CE::IEstados>()->aturdido) cambiarTurno();		}
		else
			cambiarTurno();
	}

	void EscenaShaders::ordenarTurnos()
	{
		for(auto & dino : Equipos::Get().GetPlayer())
			turnos.push_back(dino);
		
		for(auto & dino : Equipos::Get().GetEnemigos())
			turnos.push_back(dino);

		std::sort(turnos.begin(),turnos.end(),[](const std::shared_ptr<Dinosaurio>& a, const std::shared_ptr<Dinosaurio>& b){
			return a->getStats()->agi > b->getStats()->agi;
		});
	}

	int EscenaShaders::revisarGanador()
	{
		int player = 0;
		for(auto & dino : Equipos::Get().GetPlayer())
			if(dino->estaVivo()) player++;

		if(player <= 0)
			return -1;
			//CE::GestorEscenas::Get().cambiarEscena("Derrota");
		
		int enemy = 0;
		for(auto & dino : Equipos::Get().GetEnemigos())
			if(dino->estaVivo()) enemy++;

		if(enemy <= 0)
			return 1;
			//CE::GestorEscenas::Get().cambiarEscena("Victoria");
		
			return 0;
	}

	bool EscenaShaders::aplicarEstados()
	{
		auto estados = actual->getComponente<CE::IEstados>();
		if(estados->estados.empty()) return true;

		for(auto & estado : estados->estados)
		{
			estado->aplicarEstado(actual);
			if(!estado->permanente) estado->turnos -= 1;
		}

		estados->estados.erase(
		    std::remove_if(estados->estados.begin(), estados->estados.end(),
		        [](const std::shared_ptr<Estado>& estado) {
		            return estado->turnos <= 0;
		        }),
		    estados->estados.end());

		return true;
	}

	void EscenaShaders::onInputs(const CE::Botones& accion){
		if(accion.getTipo() == CE::Botones::TipoAccion::OnPress)
		{
            if(accion.getNombre() == "menu")
				CE::GestorEscenas::Get().cambiarEscena("Menu");
		}
	}

	void EscenaShaders::onRender()
	{
		for(auto &b :bg)
			CE::Render::Get().AddToDraw(b);

		for(auto &f:objetos.getPool())
			CE::Render::Get().AddToDraw(*f);

		CE::Render::Get().AddToDraw(fondo);

		for(auto & npc:Equipos::Get().GetEnemigos())
		{
			if(npc->estaVivo())
			{
				for(auto & estado: npc->getComponente<CE::IEstados>()->estados)
					CE::Render::Get().AddToDraw(*estado);
				CE::Render::Get().AddToDraw(npc->vida_max);
				CE::Render::Get().AddToDraw(npc->vida);
			}
		}

		for(auto & player:Equipos::Get().GetPlayer())
		{
			if(player->estaVivo())
			{
				for(auto & estado: player->getComponente<CE::IEstados>()->estados)
					CE::Render::Get().AddToDraw(*estado);
				CE::Render::Get().AddToDraw(player->vida_max);
				CE::Render::Get().AddToDraw(player->vida);
			}
		}

		if(mostrarSelector)
		{
			CE::Render::Get().AddToDraw(selector);
			CE::Render::Get().AddToDraw(rectanguloDino);
		}

		//if(actual->jugador)
		if(actual->tieneComponente<CE::IJugador>())
		{
			for(int i = 0; i < 4; i++)
			{
				CE::Render::Get().AddToDraw(*actual->movimientos.at(i));
				CE::Render::Get().AddToDraw(actual->movimientos.at(i)->getComponente<CE::ITexto>()->m_texto);
			}

			if(actual == Equipos::Get().GetDinoLider())
			{
				CE::Render::Get().AddToDraw(*actual->habilidadEspecial);
				CE::Render::Get().AddToDraw(actual->habilidadEspecial->getComponente<CE::ITexto>()->m_texto);
			}

			CE::Render::Get().AddToDraw(dinoPuntos->m_texto);
		}

		CE::Render::Get().AddToDraw(*medidor);
		CE::Render::Get().AddToDraw(*log);
		CE::Render::Get().AddToDraw(log->getComponente<CE::ITexto>()->m_texto);

		CE::Render::Get().AddToDraw(nivelActual->getComponente<CE::ITexto>()->m_texto);
	}
}
