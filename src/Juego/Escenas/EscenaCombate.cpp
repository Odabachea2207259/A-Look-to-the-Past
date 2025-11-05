#include "EscenaCombate.hpp"
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
	void EscenaCombate::onInit()
	{
		objetos.getPool().clear();
		cantDinos = 0;
		dinoTurno = 0;
		if(inicializar) {
			registrarBotones(sf::Keyboard::Scancode::Escape,"menu");
			CE::GestorAssets::Get().agregarTextura("nubes",ASSETS "/textura/cloud.png",CE::Vector2D{0,0},CE::Vector2D{400,400});
			CE::GestorAssets::Get().agregarTextura("noise",ASSETS "/textura/noise_texture.png",CE::Vector2D{0,0},CE::Vector2D{256,256});

			auto tam = CE::Render::Get().GetVentana().getSize();

			//AGREGAMOS EL MEDIDOR DE LA SUPER HABILIDAD
			medidor = std::make_shared<Rectangulo>(tam.x-6.f,10.f,sf::Color::Blue,sf::Color::Black);
			medidor->setPosicion(3.f,3.f);

			//AGREGAMOS EL LOG DE LOS MOVIMIENTOS REALIZADOS
			log = std::make_shared<Rectangulo>(500.f,100.f,sf::Color::Green,sf::Color::Black);
			log->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman")," "));
			log->setPosicion((tam.x/2.f)-250.f,40.f);
			auto textLog = log->getComponente<CE::ITexto>();
			textLog->m_texto.setPosition({(tam.x/2.f)-250.f,45.f});
			textLog->m_texto.setCharacterSize(10);

			//AGREGAMOS EL CONTADOR QUE DICE EN QUE RONDA ESTAMOS
			nivelActual = std::make_shared<Rectangulo>(100.f,100.f,sf::Color::Transparent,sf::Color::Transparent);
			nivelActual->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"), " "));
			auto textoNivel = nivelActual->getComponente<CE::ITexto>();
			textoNivel->m_texto.setCharacterSize(20);
			textoNivel->m_texto.setPosition({5.f,40.f});
			textoNivel->m_texto.setFillColor(sf::Color::Black);

			//AGREGAMOS EL TEXTO DE LOS PUNTOS DE CADA DINO
			/*<------------------Puede que esto pueda tenerlo cada dino------------------------------>*/
			dinoPuntos = std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman")," ");
			dinoPuntos->m_texto.setCharacterSize(10);
			dinoPuntos->m_texto.setFillColor(sf::Color::Black);
			dinoPuntos->m_texto.setPosition({850.f,650.f});

			//CREAMOS EL CUADRO PARA VER QUE DINO SELECCIONAMOS O A CUAL ESTAMOS APUNTANDO
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

		//ordenarTurnos();
		turnos = IVJ::SistemaOrdenarTurnos(Equipos::Get().GetPlayer(),Equipos::Get().GetEnemigos());
		posicionarEntes();


		//turnos = IVJ::SistemaOrdenarTurnos(Equipos::Get().GetPlayer(),Equipos::Get().GetPlayer());
		actual = turnos.at(dinoTurno); //---->revisar
		//setBotonesFalso();
		IVJ::SistemaApagarBotones(actual,&eSelecc,&pSelecc,&mostrarSelector);

		CE::GestorCamaras::Get().agregarCamara(std::make_shared<CE::CamaraCuadro>(
			CE::Vector2D{540,360},CE::Vector2D{100.f,50.f}
		));

		inicializar = false;
	}

	void EscenaCombate::posicionarEntes()
	{
		int dinoPlayer = 0;
		int dinoEnemy = 0;

		float y[3] = {270.f, 380.f, 460.f};
		float x[3] = {300.f,200.f,300.f};

		for(auto & ente : turnos)
		{
			cantDinos++;
			if(ente->tieneComponente<CE::IJugador>()){
				ente->setPosicion(x[dinoPlayer],y[dinoPlayer]);
				dinoPlayer++;
			} else{
				ente->setPosicion(x[dinoEnemy] + 500.f,y[dinoEnemy]);
				dinoEnemy++;
				
				auto sprite = ente->getComponente<CE::ISprite>();
				sprite->m_sprite.setScale({-sprite->escala,sprite->escala});
			}

			IVJ::SistemaSetPosOriginal(ente);

			objetos.agregarPool(ente);
		}
	}

	void EscenaCombate::onFinal(){}
	void EscenaCombate::onUpdate(float dt)
	{
		IVJ::SistemaActualizarMedidor(Equipos::Get().GetDinoLider(),medidor);
		if(!actual->estaVivo()) cambiarTurno();

		mouse = false;
		auto c = actual->getComponente<CE::IControl>();

		CE::GLogger::Get().agregarLog(std::to_string(actual->getComponente<CE::IPersonaje>()->nivel),CE::GLogger::Niveles::LOG_DEBUG);
		CE::GLogger::Get().agregarLog(std::to_string(actual->getStats()->hp_max),CE::GLogger::Niveles::LOG_DEBUG);
		CE::GLogger::Get().agregarLog(std::to_string(actual->getStats()->str_max),CE::GLogger::Niveles::LOG_DEBUG);
		CE::GLogger::Get().agregarLog(std::to_string(actual->getStats()->def_max),CE::GLogger::Niveles::LOG_DEBUG);
		CE::GLogger::Get().agregarLog(std::to_string(actual->getStats()->agi_max),CE::GLogger::Niveles::LOG_DEBUG);

		for(auto &f: objetos.getPool())
		{
			f->onUpdate(dt);
		}

		for(auto & entidades : turnos){
			//entidades->mostrarEstados();
			IVJ::SistemaMostrarEstados(entidades);
			//entidades->actualizarVida();
			IVJ::SistemaActualizarVida(entidades);
		}

		CE::Vector2D mousePos = CE::Render::Get().getMousePos();

		//REVISAMOS SI EL ACTUAL ES UN DINO DEL JUGADOR
		if(actual->tieneComponente<CE::IJugador>())
		{
			auto info = actual->getComponente<CE::IJugador>();

			if(!habilidadActiva) //SI NO HAY HABILIDAD EN PROCESO
			{
				for(auto &boton:actual->getComponente<CE::IHabilidades>()->movimientos)
				{
					if(boton->tipo == EspecialAtaque || boton->tipo == EspecialBuff)
						if(actual != Equipos::Get().GetDinoLider())
							continue;
						else if(info->medidor < boton->medidor)
						{
							boton->setColor(sf::Color::Cyan);
							continue;
						}
					//SI LA HABILIDAD CUESTA MENOS QUE LA CANTIDAD DE PUNTOS DISPONIBLES Y ESTÁ DENTRO DE LOS LIMITES DEL MOUSE
					//O SI YA FUE SELECCIONADA
					if(boton->dinoPuntos <= info->dinoPuntos && boton->rect_bounding.contains(sf::Vector2i(mousePos.x,mousePos.y)) || boton->seleccionado)
					{
						boton->setColor(sf::Color::Black); //CAMBIAMOS DE COLOR A NEGRO
						auto texto = boton->getComponente<CE::ITexto>();
						texto->m_texto.setFillColor(sf::Color::White); //CAMBIAMOS DE TEXTO A BLANCO

						//PREGUNTAMOS SI EL MOUSE FUE PRESIONADO
						if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
						{
							habilidadSelecc = boton; //SE SELECCIONA LA HABILIDAD
							//setBotonesFalso(); //SE PONEN TODOS LOS DEMÁS BOTONES DESELECCIONADOS
							IVJ::SistemaApagarBotones(actual,&eSelecc,&pSelecc,&mostrarSelector);
							boton->seleccionado = true; //SE CAMBIA A QUE ESTE BOTÓN ESTÁ SELECCIONADO
							
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
					else //SI EL BOTÓN NO ESTA SELECCIONADO O EL MOUSE NO ESTÁ ENCIMA
					{
						if((boton->tipo == EspecialAtaque || boton->tipo == EspecialBuff) && Equipos::Get().GetDinoLider()->getComponente<CE::IJugador>()->medidor < boton->medidor) boton->setColor(sf::Color::White);
						else boton->setColor(sf::Color::Cyan);

						if(boton->dinoPuntos > info->dinoPuntos) boton->setColor(sf::Color::White); //SI AL JUGADOR YA NO LE ALCANZA, SE CAMBIA EL COLOR
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
					
					if(habilidadSelecc)
					{
						for(auto& entidad : turnos)
						{
							auto box = entidad->getComponente<CE::ISprite>();
							auto pos = entidad->getPosicion();

							auto width = box->width*box->escala;
							auto height = box->height*box->escala;

							sf::IntRect rect({static_cast<int>(pos.x-width/2),static_cast<int>(pos.y-height/2)},{static_cast<int>(width),static_cast<int>(height)});

							if(rect.contains(sf::Vector2i(mousePos.x,mousePos.y)) && entidad->estaVivo())
							{
								if(pSelecc && !entidad->tieneComponente<CE::IJugador>()) continue;
								if(eSelecc && entidad->tieneComponente<CE::IJugador>()) continue;

								mouse = true;
								mostrarSelector = true;
								rectanguloDino.setSize(sf::Vector2f{width,height});
								rectanguloDino.setPosition(sf::Vector2f{pos.x-width/2,pos.y-height/2});
							
								selector.setPosition({(pos.x-width/2) + (height - ancho) / 2.f,
													(pos.y-width/2) - alto - 2});
								
								bool botonMouseActual = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
								
								if(botonMouseActual && !botonMouseAnterior)
								{
									if(pSelecc) playerSelecc = entidad;
									else if(eSelecc) enemSelecc = entidad;
									habilidadActiva = true;
									c->accion = true;
									break;
								}
								
								botonMouseAnterior = botonMouseActual;
							
								break;
							} else mouse = false;
						}
					}
				}
			}
		}
		else
		{
			if(!habilidadActiva)
			{
				habilidadActiva = true;
				c->accion = true;
			}
			
			//habilidadActiva = std::static_pointer_cast<IVJ::Dinosaurio>(actual)->turnoEnemigo(actual,Equipos::Get().GetPlayer(),Equipos::Get().GetEnemigos(),dt);
			habilidadActiva = IVJ::SistemaIA(actual,Equipos::Get().GetPlayer(),Equipos::Get().GetEnemigos(),dt);

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
				//setBotonesFalso();
				IVJ::SistemaApagarBotones(actual,&eSelecc,&pSelecc,&mostrarSelector);
				cambiarTurno();
			}
		}

		if(actual->tieneComponente<CE::IJugador>() && actual->estaVivo() && (playerSelecc || enemSelecc))
		{
			habilidadActiva = (playerSelecc) ? habilidadSelecc->accion(actual,playerSelecc,dt) : habilidadSelecc->accion(actual,enemSelecc,dt);

			if(!habilidadActiva)
			{
				auto logText = log->getComponente<CE::ITexto>();
				auto nombreDino = actual->getNombre()->nombre;
				auto nombreHabilidad = habilidadSelecc->getNombre()->nombre;
				auto nombreTarget = (playerSelecc) ? playerSelecc->getNombre()->nombre : enemSelecc->getNombre()->nombre;
				sf::String n(nombreDino + "\na realizado\n" + nombreHabilidad + "\nen " + nombreTarget);
				logText->m_texto.setString(n);

				logText->m_texto.setFillColor(sf::Color::Blue);

				pSelecc = false;
				eSelecc = false;
				enemSelecc = nullptr;
				playerSelecc = nullptr;
				habilidadSelecc = nullptr;
				//setBotonesFalso();
				IVJ::SistemaApagarBotones(actual,&eSelecc,&pSelecc,&mostrarSelector);
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

	void EscenaCombate::cambiarTurno()
	{
		actual->getComponente<CE::IHabilidades>()->habilidadSelecc = nullptr;
		habilidadSelecc = nullptr;
		//switch(revisarGanador()){
		switch(IVJ::SistemaRevisarGanador(turnos)){
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

		actual->getComponente<CE::IPersonaje>()->turno = false;

		auto estado_dino = actual->getComponente<CE::IEstados>();
		estado_dino->dormido = false;
		estado_dino->aturdido = false;
		dinoTurno++;
		if(dinoTurno >= cantDinos)
			dinoTurno = 0;
		
		actual = turnos.at(dinoTurno);
		if(actual->estaVivo()){

			if(actual->tieneComponente<CE::IJugador>())
			{
				if(actual == Equipos::Get().GetDinoLider())Equipos::Get().GetDinoLider()->getComponente<CE::IJugador>()->medidor += 10;
				dinoPuntos->m_texto.setString(sf::String("DinoPuntos:\n"+std::to_string(actual->getComponente<CE::IJugador>()->dinoPuntos)));
			}

			IVJ::SistemaAplicarEstados(actual);

			if(actual->tieneComponente<CE::IJugador>() && actual->getComponente<CE::IJugador>()->dinoPuntos <= 0 && !actual->getComponente<CE::IPersonaje>()->tieneAtaquesGratis) cambiarTurno();
			if(actual->getComponente<CE::IEstados>()->dormido || actual->getComponente<CE::IEstados>()->aturdido) cambiarTurno();		}
		else
			cambiarTurno();
	}

	void EscenaCombate::onInputs(const CE::Botones& accion){
		if(accion.getTipo() == CE::Botones::TipoAccion::OnPress)
		{
            if(accion.getNombre() == "menu")
				CE::GestorEscenas::Get().cambiarEscena("Menu");
		}
	}

	void EscenaCombate::onRender()
	{
		for(auto &b :bg)
			CE::Render::Get().AddToDraw(b);

		for(auto &f:objetos.getPool())
			CE::Render::Get().AddToDraw(*f);

		CE::Render::Get().AddToDraw(fondo);

		for(auto & ente : turnos)
		{
			if(ente->estaVivo()){
				for(auto & estado : ente->getComponente<CE::IEstados>()->estados)
					CE::Render::Get().AddToDraw(*estado);
				CE::Render::Get().AddToDraw(ente->getComponente<CE::ISelectores>()->vida_max);
				CE::Render::Get().AddToDraw(ente->getComponente<CE::ISelectores>()->vida);
			}
		}

		if(mostrarSelector)
		{
			CE::Render::Get().AddToDraw(selector);
			CE::Render::Get().AddToDraw(rectanguloDino);
		}

		if(actual->tieneComponente<CE::IJugador>())
		{
			for(int i = 0; i < 4; i++)
			{
				CE::Render::Get().AddToDraw(*actual->getComponente<CE::IHabilidades>()->movimientos.at(i));
				CE::Render::Get().AddToDraw(actual->getComponente<CE::IHabilidades>()->movimientos.at(i)->getComponente<CE::ITexto>()->m_texto);
			}

			if(actual == Equipos::Get().GetDinoLider())
			{
				CE::Render::Get().AddToDraw(*actual->getComponente<CE::IHabilidades>()->habilidadEspecial);
				CE::Render::Get().AddToDraw(actual->getComponente<CE::IHabilidades>()->habilidadEspecial->getComponente<CE::ITexto>()->m_texto);
			}

			CE::Render::Get().AddToDraw(dinoPuntos->m_texto);
		}

		CE::Render::Get().AddToDraw(*medidor);

		
		//CE::Render::Get().AddToDraw(*log);
		//CE::Render::Get().AddToDraw(log->getComponente<CE::ITexto>()->m_texto);

		CE::Render::Get().AddToDraw(*Log::Get().log);

		CE::Render::Get().AddToDraw(nivelActual->getComponente<CE::ITexto>()->m_texto);
	}
}
