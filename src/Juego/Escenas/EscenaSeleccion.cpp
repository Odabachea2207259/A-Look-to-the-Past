#include "EscenaSeleccion.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../Objetos/Jugador.hpp"
#include "../Objetos/Equipos.hpp"
#include "../../Motor/Render/Render.hpp"
#include <fstream>

namespace IVJ
{
	void EscenaSeleccion::onInit()
	{
		objetos.getPool().clear();
		Equipos::Get().GetPlayer().clear();
		if(!inicializar)
        {
            int i = 1,y=1;

            dinosSeleccionados = 0;
            mostrarSelector = false;
            for(auto & dino : Jugador::Get().GetDinosaurios())
            {
                //dino->jugador = false;
				dino->eliminarComponente<CE::IJugador>();
                dino->seleccion.setFillColor(sf::Color::Transparent);
                dino->seleccion.setOutlineThickness(5.f);
                dino->setPosicion(300.f*i,250.f*y);
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

 		registrarBotones(sf::Keyboard::Scancode::Escape,"menu");

		boton = std::make_shared<IVJ::Rectangulo>(185.f,50.f,sf::Color::Red,sf::Color::Black);
		boton->setPosicion(50.f,650.f);
		boton->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),"Continuar"));
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
            //dino->jugador = false;
			dino->eliminarComponente<CE::IJugador>();
            dino->seleccion.setFillColor(sf::Color::Transparent);
            dino->seleccion.setOutlineThickness(5.f);
            dino->setPosicion(300.f*i,250.f*y);
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
	void EscenaSeleccion::onFinal(){
		Equipos::Get().GetDinoLider() = Equipos::Get().GetPlayer().at(dinosSeleccionados-1);
		std::cout<<Equipos::Get().GetDinoLider()->getNombre()->nombre<<std::endl;
	}
	void EscenaSeleccion::onUpdate(float dt)
	{
        mouse = false;

		for(auto &f: objetos.getPool())
			f->onUpdate(dt);

		CE::Vector2D mousePos = CE::Render::Get().getMousePos();

		if(dinosSeleccionados <= 0)
			boton->setColor(sf::Color(255,0,0,100));
		else
			boton->setColor(sf::Color(255,0,0,255));

		if(boton->rect_bounding.contains({static_cast<int>(mousePos.x),static_cast<int>(mousePos.y)}) && dinosSeleccionados > 0)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
				CE::GestorEscenas::Get().cambiarEscena("Shaders");
			}
		}

		for(auto & dino : Jugador::Get().GetDinosaurios())
		{
            auto c_dino = dino->getComponente<CE::IControl>();
            auto box = dino->getComponente<CE::ISprite>();
			auto pos = dino->getPosicion();
            
			auto width = box->width*box->escala;
			auto height = box->height*box->escala;
            //if(dino->jugador)
			if(dino->tieneComponente<CE::IJugador>())
            {
                dino->seleccion.setOutlineColor(sf::Color::Red);
				dino->seleccion.setSize(sf::Vector2f{width,height});
				dino->seleccion.setPosition(sf::Vector2f{pos.x-width/2,pos.y-height/2});
            }
			sf::IntRect rect({static_cast<int>(pos.x-width/2),static_cast<int>(pos.y-height/2)},{static_cast<int>(width),static_cast<int>(height)});
			
			if(rect.contains(sf::Vector2i(mousePos.x,mousePos.y)))
			{
				mouse = true;
				mostrarSelector = true;
				rectanguloDino.setSize(sf::Vector2f{width,height});
				rectanguloDino.setPosition(sf::Vector2f{pos.x-width/2,pos.y-height/2});
			
				selector.setPosition({(pos.x-width/2) + (height - ancho) / 2.f,
									(pos.y-width/2) - alto - 2});
                
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
                    //if(dino->jugador)
					if(dino->tieneComponente<CE::IJugador>())
                    {
                        //dino->jugador = false;
						dino->eliminarComponente<CE::IJugador>();
                        dinosSeleccionados--;
                        dino->seleccion.setOutlineColor(sf::Color::Transparent);
                        int i = 0;
                        for(auto & equipo : Equipos::Get().GetPlayer())
						{
                            if(equipo == dino)
							{
                                Equipos::Get().GetPlayer().erase(Equipos::Get().GetPlayer().begin()+i);
								break;
							}
							i++;
						}
                    }
                    else if(!dino->tieneComponente<CE::IJugador>() && dinosSeleccionados < 3)
                    {
                        c_dino->sacc = true;
                        //dino->jugador = true;
						dino->addComponente(std::make_shared<CE::IJugador>());
                        dinosSeleccionados++;
                        Equipos::Get().GetPlayer().push_back(dino);
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

	void EscenaSeleccion::onInputs(const CE::Botones& accion)
	{
		if(accion.getTipo() == CE::Botones::TipoAccion::OnPress)
		{
            if(accion.getNombre() == "menu")
				CE::GestorEscenas::Get().cambiarEscena("Menu");
		}
	}

	void EscenaSeleccion::onRender()
	{
		if(mostrarSelector)
		{
			CE::Render::Get().AddToDraw(selector);
			CE::Render::Get().AddToDraw(rectanguloDino);
		}
        for(auto & dino : Jugador::Get().GetDinosaurios())
        {
            CE::Render::Get().AddToDraw(dino->getComponente<CE::ISprite>()->m_sprite);
            //if(dino->jugador)
			if(dino->tieneComponente<CE::IJugador>())
            {
                CE::Render::Get().AddToDraw(dino->seleccion);
            }
        }

		CE::Render::Get().AddToDraw(*boton);
		CE::Render::Get().AddToDraw(boton->getComponente<CE::ITexto>()->m_texto);
	}
}