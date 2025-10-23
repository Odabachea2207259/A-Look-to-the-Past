#include "EscenaMejora.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/GUI/GLogger.hpp"
#include "../Objetos/Jugador.hpp"
#include "../Objetos/Equipos.hpp"
#include "../../Motor/Render/Render.hpp"
#include <fstream>

namespace IVJ
{
	void EscenaMejora::onInit()
	{
		objetos.getPool().clear();
		niveles.clear();
		dinoSelecc = nullptr;
		if(!inicializar)
        {
            int i = 1,y=1;

            dinosSeleccionados = 0;
            mostrarSelector = false;
            for(auto & dino : Jugador::Get().GetDinosaurios())
            {
				auto nivelDino = std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),"");
				nivelDino->m_texto.setCharacterSize(10);
				nivelDino->m_texto.setFillColor(sf::Color::Black);
				nivelDino->m_texto.setPosition({360.f*i,150.f*y});
				niveles.push_back(nivelDino);

                //dino->jugador = false;
				dino->eliminarComponente<CE::IJugador>();
                dino->seleccion.setFillColor(sf::Color::Transparent);
                dino->seleccion.setOutlineThickness(5.f);
                dino->setPosicion(360.f*i,200.f*y);
                dino->setPosOriginal();
                i++;
                if(i%3==0)
                {
                    i = 1;
                    y++;
                }
                objetos.agregarPool(dino);
            }
            return;
        }

		srand(static_cast<unsigned>(time(nullptr)));

        CE::GestorCamaras::Get().setCamaraActiva(0);

		CE::GestorAssets::Get().agregarTextura("Mejora",ASSETS "/pantallas/Mejora.png",CE::Vector2D{0,0},CE::Vector2D{1080,720});

		fondo = std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("Mejora"),1080,720,1.f);
		fondo->m_sprite.setPosition({1080.f/2.f,720.f/2.f});

 		registrarBotones(sf::Keyboard::Scancode::Escape,"menu");

		boton = std::make_shared<IVJ::Rectangulo>(185.f,50.f,sf::Color::Red,sf::Color::Black);
		boton->setPosicion(450.f,470.f);
		boton->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),"Mejorar"));
		auto texto = boton->getComponente<CE::ITexto>();
		texto->m_texto.setCharacterSize(10);
		texto->m_texto.setPosition(boton->getPosicion());
		texto->m_texto.setFillColor(sf::Color::Black);

        dinosSeleccionados = 0;

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

        int i = 1,y=1, cant = 0;

        for(auto & dino : Jugador::Get().GetDinosaurios())
        {
			auto nivelDino = std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),"");
			nivelDino->m_texto.setCharacterSize(10);
			nivelDino->m_texto.setFillColor(sf::Color::Black);
			nivelDino->m_texto.setPosition({360.f*i,150.f*y});

			niveles.push_back(nivelDino);

            //dino->jugador = false;
			dino->eliminarComponente<CE::IJugador>();
            dino->seleccion.setFillColor(sf::Color::Transparent);
            dino->seleccion.setOutlineThickness(5.f);
            dino->setPosicion(360.f*i,200.f*y);
            dino->setPosOriginal();
            i++;
            if(i%3==0)
            {
                i = 1;
                y++;
            }

            objetos.agregarPool(dino);
        }

		inicializar = false;
	}

	void EscenaMejora::actualizarNiveles()
	{
		int i = 0;
		for(auto & dino : Jugador::Get().GetDinosaurios())
		{
			niveles.at(i)->m_texto.setString("Nivel " + std::to_string(dino->nivel));
			i++;
		}
	}

	void EscenaMejora::onFinal(){
	}
	void EscenaMejora::onUpdate(float dt)
	{
		actualizarNiveles();
        mouse = false;

		for(auto &f: objetos.getPool())
			f->onUpdate(dt);

		CE::Vector2D mousePos = CE::Render::Get().getMousePos();

        auto texto = boton->getComponente<CE::ITexto>();
		if(dinosSeleccionados <= 0 || Jugador::Get().GetDinero() < dinoSelecc->nivel*precioMejora)
        {
            texto->m_texto.setString("Mejora");
			boton->setColor(sf::Color(255,0,0,100));
        }
		else
        {
            sf::String mensaje(std::to_string(dinoSelecc->nivel*precioMejora));
            texto->m_texto.setString(mensaje);
			boton->setColor(sf::Color(255,0,0,255));
        }

		if(boton->rect_bounding.contains({static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}) && dinosSeleccionados > 0 && Jugador::Get().GetDinero() >= dinoSelecc->nivel*precioMejora)
		{
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
                Jugador::Get().GetDinero() -= (dinoSelecc->nivel*precioMejora);
                dinoSelecc->subirNivel();
				mousePrev = false;
				return;
            }
			return;
		}
        if(dinoSelecc)
        {
            auto c_dino = dinoSelecc->getComponente<CE::IControl>();
            auto box = dinoSelecc->getComponente<CE::ISprite>();
			auto pos = dinoSelecc->getPosicion();
            
			auto width = box->width*box->escala;
			auto height = box->height*box->escala;
            dinoSelecc->seleccion.setOutlineColor(sf::Color::Red);
			dinoSelecc->seleccion.setSize(sf::Vector2f{width,height});
			dinoSelecc->seleccion.setPosition(sf::Vector2f{pos.x-width/2,pos.y-height/2});
        }
		for(auto & dino : Jugador::Get().GetDinosaurios())
		{
            auto c_dino = dino->getComponente<CE::IControl>();
            auto box = dino->getComponente<CE::ISprite>();
			auto pos = dino->getPosicion();
            
			auto width = box->width*box->escala;
			auto height = box->height*box->escala;

			sf::IntRect rect({static_cast<int>(pos.x-width/2),static_cast<int>(pos.y-height/2)},{static_cast<int>(width),static_cast<int>(height)});
			
			if(rect.contains(sf::Vector2i(mousePos.x,mousePos.y)))
			{
				mouse = true;
				mostrarSelector = true;
				rectanguloDino.setSize(sf::Vector2f{width,height});
				rectanguloDino.setPosition(sf::Vector2f{pos.x-width/2,pos.y-height/2});
			
				selector.setPosition({(pos.x-width/2) + (height - ancho),
									(pos.y-width/6)});
                
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
                    if(dino == dinoSelecc)
                    {
                        dinoSelecc = nullptr;
                        dinosSeleccionados--;  
                    }
                    else if(dino != dinoSelecc && dinosSeleccionados < 1)
                    {
                        c_dino->sacc = true;
                        dinoSelecc = dino;
                        dinosSeleccionados++;
                    }
                    mousePrev = false;
                    break;
			    }
                break;
			}
			else{
				mouse = false;
                mostrarSelector = false;
			}
		}
		if(!mouse)
		{
			mousePressed = false;
			mousePrev = false;
		}

		objetos.borrarPool();   
	}

	void EscenaMejora::onInputs(const CE::Botones& accion)
	{
		if(accion.getTipo() == CE::Botones::TipoAccion::OnPress)
		{
            if(accion.getNombre() == "menu")
				CE::GestorEscenas::Get().cambiarEscena("Menu");
		}
	}

	void EscenaMejora::onRender()
	{
		CE::Render::Get().AddToDraw(fondo->m_sprite);
		if(mostrarSelector)
		{
			CE::Render::Get().AddToDraw(selector);
			//CE::Render::Get().AddToDraw(rectanguloDino);
		}
		for(auto & nivel : niveles)
			CE::Render::Get().AddToDraw(nivel->m_texto);

        for(auto & dino : Jugador::Get().GetDinosaurios())
        {
            CE::Render::Get().AddToDraw(dino->getComponente<CE::ISprite>()->m_sprite);
        }

        if(dinoSelecc)
            CE::Render::Get().AddToDraw(dinoSelecc->seleccion);

		CE::Render::Get().AddToDraw(*boton);
		CE::Render::Get().AddToDraw(boton->getComponente<CE::ITexto>()->m_texto);
	}
}