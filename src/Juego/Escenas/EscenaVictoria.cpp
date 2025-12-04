#include "EscenaVictoria.hpp"
#include "../Objetos/Equipos.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Objetos/Jugador.hpp"
#include "../Objetos/Periodos.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../../Motor/Utils/Ventana.hpp"
#include "../Sistemas/Sistemas.hpp"
#include <fstream>

#include <ctime>

namespace IVJ
{
	void EscenaVictoria::onInit()
	{
        if(inicializar) {
            //std::srand(static_cast<unsigned>(std::time(nullptr)));
            CE::GestorAssets::Get().agregarTextura("Victoria",ASSETS "/pantallas/Victoria.png",CE::Vector2D{0,0},CE::Vector2D{1080,720});
    
			tuto_1 = std::make_shared<Rectangulo>(CE::WIDTH,CE::HEIGHT,sf::Color(0,0,0,200),sf::Color::Transparent);
			tuto_2 = std::make_shared<Rectangulo>(CE::WIDTH,CE::HEIGHT,sf::Color(0,0,0,200),sf::Color::Transparent);

			pos_tutorial_1 = {
				{0.f,0.f},
				{-650.f,0.f},
				{-845.f,0.f}
			};

            pos_tutorial_2 = {
                {0.f,0.f},
                {610.f,0.f},
                {540.f,0.f}
            };

			hattie = std::make_shared<Rectangulo>(300.f,300.f,sf::Color::Transparent,sf::Color::Transparent);

			hattie->addComponente(std::make_shared<CE::ISprite>(
				CE::GestorAssets::Get().getTextura("hattie"),
				300,300,
				1.f
			)
			);

			hattie->setPosicion(300.f,300.f);
			hattie->getComponente<CE::ISprite>()->m_sprite.setPosition({CE::WIDTH/2 - 150.f,CE::HEIGHT/2 - 150.f});

			texto_tutorial = std::make_shared<CE::ITexto>(
				CE::GestorAssets::Get().getFont("Science"),
				"Prueba"
			);

			texto_tutorial->m_texto.setCharacterSize(30.f);
			texto_tutorial->m_texto.setFillColor(sf::Color::White);
			texto_tutorial->m_texto.setPosition({CE::WIDTH/2 - 300.f,CE::HEIGHT/2});

            fondo = std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura("Victoria"),1080,720,1.f);
            fondo->m_sprite.setPosition({1080.f/2.f,720.f/2.f});
            //Agregar imagen al gestor de texturas
            boton = std::make_shared<Rectangulo>(200.f,20.f,sf::Color(224,201,166),sf::Color::Transparent);
            boton->addComponente(std::make_shared<CE::ITexto>(
                CE::GestorAssets::Get().getFont("Caveman"),"Continuar"
            ));

            //auto tam = CE::Render::Get().GetVentana().getSize();
           CE::Vector2D tam = {CE::WIDTH,CE::HEIGHT};

            dinero = std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),"Dino$");
            dinero->m_texto.setCharacterSize(10);
            dinero->m_texto.setFillColor(sf::Color(164,134,86));
            dinero->m_texto.setPosition({(tam.x/2)-300.f,tam.y-400.f});

            recompensa = std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),"Recompensa: ");
            recompensa->m_texto.setCharacterSize(10);
            recompensa->m_texto.setFillColor(sf::Color(164,134,86));
            recompensa->m_texto.setPosition({(tam.x/2)-300.f,tam.y-360.f});

            boton->setPosicion((tam.x/2)-100.f,tam.y-170.f);

            auto texto = boton->getComponente<CE::ITexto>();
            texto->m_texto.setCharacterSize(10);
            texto->m_texto.setPosition(boton->getPosicion());
            texto->m_texto.setFillColor(sf::Color::Black);

            for(int i = 0; i < 3; i++)
            {
                auto reward = std::make_shared<Rectangulo>(50.f,50.f,sf::Color::White,sf::Color::Black);
                reward->setOutThick(3.f);
                if(i != 1)
                    reward->setPosicion((tam.x/2)-100.f+(i*55.f),450.f);
                else
                    reward->setPosicion((tam.x/2)-100.f+(i*55.f),395.f);
                areas.push_back(reward);
            }
        }

        recompensaSelecc = false;

        recompensas = Recompensas::Get().ObtenerRecompensasUnicas(3);

        getRecompensa();
        setRecompensas();

        for(auto & dino : Equipos::Get().GetPlayer())
            if(dino->estaVivo())
                IVJ::SistemaAgregarVida(dino,dino->getStats()->hp_max * 0.2);

        
        ganancias += (Jugador::Get().GetNivel() * Equipos::Get().GetEnemigos().size()) * 5;
        dinero->m_texto.setString(sf::String("Dino$ " + std::to_string(ganancias)));
                
        Jugador::Get().GetDinero() += ganancias;
        
        
        if(Jugador::Get().GetPeriodo() < IVJ::MESOZOICO){
            if(Jugador::Get().GetNivel() % 3 == 0)
            {
                Jugador::Get().GetPeriodo() += 1;
                std::cout << "\nCambio de progreso\n";
            }
        } else if(Jugador::Get().GetPeriodo() < IVJ::CENOZOICO){
            if(Jugador::Get().GetPeriodo() % 4 == 0)
            Jugador::Get().GetNivel() += 1;
        }else{
            if(Jugador::Get().GetPeriodo() % 5 == 0)
            Jugador::Get().GetNivel() += 1;
        }
        
        Jugador::Get().GetNivel() += 1;
		inicializar = false;
	}

    void EscenaVictoria::getRecompensa()
    {
        switch(Recompensas::Get().GetRecompensa())
        {
            case Recompensas::AUMENTAR:
                recompensa->m_texto.setString("Recompensa: AUMENTAR STATS");
                for(auto & dino : Equipos::Get().GetPlayer())
                {
                    if(dino->estaVivo())
                    {
                        dino->getStats()->hp += 40;
                        dino->getStats()->agi += 5;
                        dino->getStats()->str += 5;
                        dino->getStats()->def += 5;
                    }
                }
                break;
            case Recompensas::DINERO:
                recompensa->m_texto.setString("Recompensa: MAS DINERO");
                ganancias += 30;
                break;
            case Recompensas::REGENERAR:
                recompensa->m_texto.setString("Recompensa: REGENERAR DINOS");
                for(auto & dino : Equipos::Get().GetPlayer())
                {
                    if(dino->estaVivo())
                    {
                        dino->getStats()->hp = dino->getStats()->hp_max;
                        dino->getComponente<CE::IJugador>()->dinoPuntos = 15;
                    }
                }
                break;
            default:
                recompensa->m_texto.setString("Recompensa: NADA");
                break;
        }
    }
    void EscenaVictoria::setRecompensas()
    {
        for(int i = 0; i < 3; i++)
        {
            sf::Color color;
            switch(recompensas.at(i))
            {
                case Recompensas::AUMENTAR:
                    color = sf::Color::Blue;
                    break;
                case Recompensas::DINERO:
                    color = sf::Color::Green;
                    break;
                case Recompensas::REGENERAR:
                    color = sf::Color::Magenta;
                    break;
                default:
                    color = sf::Color::White;
                    break;
            }
            areas.at(i)->setColor(color);
        }
    }
	void EscenaVictoria::onFinal(){
        if(recompensaSelecc)
            Recompensas::Get().GetRecompensa() = Recompensas::Rewards(recompensas.at(recompensaPos));
    }

    void EscenaVictoria::onUpdate(float dt)
    {
        mousePos = CE::Render::Get().getMousePos();

        static bool wasPressedLastFrame = false;
        bool isPressedNow = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        mousePrev = !isPressedNow && wasPressedLastFrame;
        wasPressedLastFrame = isPressedNow;

		if(Jugador::Get().GetTutorial() && parrafo < cant_parrafos && false)
		{
			tutorial(dt);
			return;
		}

        game(dt);
    }

	void EscenaVictoria::tutorial(float dt)
	{
		ec += dt*2;
		SistemaFlotar(hattie,ec);

		if(!algo)
		{
			texto_tutorial->m_texto.setString(IVJ::getTutorial("/TutorialVictoria.txt",parrafo));
			algo = true;
		}

		if(mousePrev)
		{
			parrafo++;
			algo = false;
			mousePrev = false;

			switch(parrafo)
			{
				case 3:
					texto_tutorial->m_texto.setCharacterSize(10);
					break;
				case 4:
					texto_tutorial->m_texto.setCharacterSize(40);
					break;
                case 5:
                    texto_tutorial->m_texto.setCharacterSize(30);
					tuto_1->setPosicion(pos_tutorial_1[1]);
					tuto_2->setPosicion(pos_tutorial_2[1]);

					hattie->getComponente<CE::ISprite>()->m_sprite.setPosition({CE::WIDTH/2 + 250.f,CE::HEIGHT/2 - 100.f});
					texto_tutorial->m_texto.setPosition({CE::WIDTH/2 + 90.f,CE::HEIGHT/2 + 50.f});

                    break;
                case 8:
                    texto_tutorial->m_texto.setFillColor(sf::Color::Green);
                    break;
                case 9:
                    texto_tutorial->m_texto.setFillColor(sf::Color::Blue);
                    break;
                case 10:
                    texto_tutorial->m_texto.setFillColor(sf::Color::Magenta);
                    break;
                case 11:
                    texto_tutorial->m_texto.setFillColor(sf::Color::White);
                    break;
                case 16:
					tuto_1->setPosicion(pos_tutorial_1[2]);
					tuto_2->setPosicion(pos_tutorial_2[2]);

					hattie->getComponente<CE::ISprite>()->m_sprite.setPosition({CE::WIDTH/2 + 150.f,CE::HEIGHT/2 - 100.f});
					texto_tutorial->m_texto.setPosition({CE::WIDTH/2 + 30.f,CE::HEIGHT/2 + 50.f});

                    break;
                case 17:
					tuto_1->setPosicion(pos_tutorial_1[0]);
					tuto_2->setPosicion(pos_tutorial_2[0]);

					hattie->getComponente<CE::ISprite>()->m_sprite.setPosition({CE::WIDTH/2 - 150.f,CE::HEIGHT/2 - 100.f});
					texto_tutorial->m_texto.setPosition({CE::WIDTH/2 - 300.f,CE::HEIGHT/2});
                    break;
			}
		}
	}

    void EscenaVictoria::game(float dt)
    {
        for (int i = 0; i < 3; i++)
        {
            if (areas.at(i)->rect_bounding.contains({static_cast<int>(mousePos.x), static_cast<int>(mousePos.y)}))
            {
                if (mousePrev)
                {
                    if (!recompensaSelecc)
                    {
                        recompensaSelecc = true;
                        recompensaPos = i;
                    }
                    else if (recompensaSelecc && i == recompensaPos)
                    {
                        recompensaSelecc = false;
                    }
                    else if(recompensaSelecc)
                        recompensaPos = i;
                }
            }
        }

        // Botón (fuera del loop de las áreas)
        if (boton->rect_bounding.contains({static_cast<int>(mousePos.x), static_cast<int>(mousePos.y)}))
        {
            boton->getComponente<CE::ITexto>()->m_texto.setFillColor(sf::Color(166, 134, 86));
            if (mousePrev)
            {
                switch(Jugador::Get().GetPeriodo())
                {
                    case (IVJ::MESOZOICO - 1):
                        CE::GestorEscenas::Get().cambiarEscena("Jefe");
                        break;
                    default:
                        CE::GestorEscenas::Get().cambiarEscena("Combate");
                        break;
                }
            }
        }
        else
        {
            boton->getComponente<CE::ITexto>()->m_texto.setFillColor(sf::Color::Black);
        }

        // Cambiar colores
        for (int i = 0; i < 3; i++)
        {
            if (recompensaSelecc && recompensaPos == i)
                areas.at(i)->setOutColor(sf::Color::Red);
            else
                areas.at(i)->setOutColor(sf::Color::Black);
        }
    }

	void EscenaVictoria::onInputs(const CE::Botones& accion)
	{

	}

	void EscenaVictoria::onRender()
	{
        CE::Render::Get().AddToDraw(fondo->m_sprite);

        CE::Render::Get().AddToDraw(dinero->m_texto);
        CE::Render::Get().AddToDraw(recompensa->m_texto);

        CE::Render::Get().AddToDraw(*boton);
        CE::Render::Get().AddToDraw(boton->getComponente<CE::ITexto>()->m_texto);

        for(auto & area : areas)
            CE::Render::Get().AddToDraw(*area);
        
        if(Jugador::Get().GetTutorial() && parrafo < cant_parrafos && false){
			CE::Render::Get().AddToDraw(*tuto_1);
			CE::Render::Get().AddToDraw(*tuto_2);
			CE::Render::Get().AddToDraw(hattie->getComponente<CE::ISprite>()->m_sprite);
			CE::Render::Get().AddToDraw(texto_tutorial->m_texto);
		}
	}
}