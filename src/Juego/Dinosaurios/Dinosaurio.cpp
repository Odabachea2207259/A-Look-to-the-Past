#include "Dinosaurio.hpp"
#include "../../Motor/Render/Render.hpp"

namespace IVJ
{
    void Dinosaurio::cambiarNivel(int nivel)
    {
        auto stats = this->getStats();
        stats->hp *= nivel;
        stats->hp_max *= nivel;
        stats->str *= nivel;
        stats->agi *= nivel;
        stats->def *= nivel;
    }

    void Dinosaurio::mostrarEstados()
    {
		auto estados = this->getComponente<CE::IEstados>();
        if(getComponente<CE::IEstados>()->cantidad > 0)
        {
            int i = 0;
            
            for(auto & estado : estados->estados)
            {
                estado->setPosicion(vida_max.getPosition().x + (14*i),vida_max.getPosition().y + 15.f);
                i++;
                if(i >= 5) return;
            }
        }
    }

	void Dinosaurio::acomodarBoton(std::shared_ptr<Habilidad> mov, int i)
	{
			mov->setPosicion(50.f + (200.f*i),650.f);
			mov->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),mov->getNombre()->nombre + "\n" + std::to_string(mov->dinoPuntos)));
			auto texto = mov->getComponente<CE::ITexto>();
			texto->m_texto.setCharacterSize(10);
			texto->m_texto.setFillColor(sf::Color::Black);
			texto->m_texto.setPosition({mov->getPosicion().x,mov->getPosicion().y+2.f});
			
			this->movimientos.push_back(mov);
	}

	void Dinosaurio::acomodarHabilidadEspecial(std::shared_ptr<Habilidad> mov)
	{
		mov->setPosicion(50.f,580.f);
		mov->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),mov->getNombre()->nombre));
		auto texto = mov->getComponente<CE::ITexto>();
		texto->m_texto.setCharacterSize(10);
		texto->m_texto.setFillColor(sf::Color::Black);
		texto->m_texto.setPosition({mov->getPosicion().x,mov->getPosicion().y+2.f});
		
		this->habilidadEspecial = mov;
		this->movimientos.push_back(mov);
	}
	/*----------------------------HABILIDADDES------------------------------------------------------*/
	
    void Pachycephalosaurus::agregarHabilidades()
    {
		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Cabezazo>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Embestida>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Valor>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Impulso>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}

		auto habEspecial = std::make_shared<SuperCabezazo>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

    void Parasaurolophus::agregarHabilidades()
    {
		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Mordisco>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Sanar>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Curar>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Canto>(185.f,50.f,sf::Color::Magenta,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}
		auto habEspecial = std::make_shared<Renacer>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

    void Centrosaurus::agregarHabilidades()
    {
		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Embestida>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Punzada>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Mordisco>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Adrenalina>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}
		auto habEspecial = std::make_shared<SuperPunzada>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

    void Carnotauro::agregarHabilidades()
    {
		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Embestida>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Mordisco>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Rugido>(185.f,50.f,sf::Color::Magenta,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Impulso>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}
		auto habEspecial = std::make_shared<SuperMordisco>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

	/*----------------------------------------------IA-------------------------------------*/

	bool Pachycephalosaurus::turnoEnemigo(std::shared_ptr<Dinosaurio> actual, std::vector<std::shared_ptr<Dinosaurio>> player,std::vector<std::shared_ptr<Dinosaurio>> enemigos,float dt)
	{
		if(!turno)
		{
			turno = true;
			int prob = (rand() % 100) + 1;

			if(prob >= 1 && prob <= 25)
			{
				habilidadSelecc = actual->movimientos.at(0);
			}
			else if(prob >= 26 && prob <= 50)
			{
				habilidadSelecc = actual->movimientos.at(1);
			}
			else if(prob >= 51 && prob <= 75)
			{
				habilidadSelecc = actual->movimientos.at(2);
			}
			else if(prob >= 76 && prob <= 100)
			{
				habilidadSelecc = actual->movimientos.at(3);
			}

			do{
				if(habilidadSelecc->tipo == Attack || habilidadSelecc->tipo == Debuffeo)
				{
					numDino = rand() % player.size();
					if(player.at(numDino)->estaVivo()) break;
				}
				else
				{
					numDino = rand() % enemigos.size();
					if(enemigos.at(numDino)->estaVivo()) break;
				}
			} while(true);
			
			std::cout << habilidadSelecc->getNombre()->nombre;
		}

		if(habilidadSelecc->tipo == Attack || habilidadSelecc->tipo == Debuffeo)
			return habilidadSelecc->accion(actual,player.at(numDino),dt);
		
		return habilidadSelecc->accion(actual,enemigos.at(numDino),dt);
	}

	bool Parasaurolophus::turnoEnemigo(std::shared_ptr<Dinosaurio> actual,std::vector<std::shared_ptr<Dinosaurio>> player,std::vector<std::shared_ptr<Dinosaurio>> enemigos, float dt)
	{
		if(!turno)
		{
			int x = 50, y = 50, z = 50;
			turno = true;

			float menorVida = 1000.f;
			numDino = -1;

			for(auto & a: enemigos)
			{
				if(a->getStats()->hp < menorVida && a->estaVivo())
				{
					menorVida = a->getStats()->hp;
				}
				numDino++;
			}

			if(menorVida < enemigos.at(numDino)->getStats()->hp_max * 0.5f && menorVida > 0.f)
			{
				x = 50/3;
				y = 50 + x;
				z = y + 50/3;
			}
		
			int prob = (rand() % 100) + 1;

			if(prob >= 1 && prob <= x)
			{
				habilidadSelecc = actual->movimientos.at(0);
			}
			else if(prob > x && prob <= y)
			{
				habilidadSelecc = actual->movimientos.at(1);
			}
			else if(prob > y && prob <= z)
			{
				habilidadSelecc = actual->movimientos.at(2);
			}
			else if(prob > z && prob <= 100)
			{
				habilidadSelecc = actual->movimientos.at(3);
			}

			do{
				if(habilidadSelecc->tipo == Attack || habilidadSelecc->tipo == Debuffeo)
				{
					numDino = rand() % player.size();
					if(player.at(numDino)->estaVivo()) break;
				}
				else
				{
					if(menorVida < 40.f && menorVida > 0.f) break;
					numDino = rand() % enemigos.size();
	
					if(enemigos.at(numDino)->estaVivo()) break;
				}
			} while(true);
			
			std::cout << habilidadSelecc->getNombre()->nombre;
		}

		if(habilidadSelecc->tipo == Attack || habilidadSelecc->tipo == Debuffeo)
			return habilidadSelecc->accion(actual,player.at(numDino),dt);
		
		return habilidadSelecc->accion(actual,enemigos.at(numDino),dt);
	}

	bool Centrosaurus::turnoEnemigo(std::shared_ptr<Dinosaurio> actual,std::vector<std::shared_ptr<Dinosaurio>> player,std::vector<std::shared_ptr<Dinosaurio>> enemigos, float dt)
	{
		if(!turno)
		{
			turno = true;
			int prob = (rand() % 100) + 1;

			if(prob >= 1 && prob <= 25)
			{
				habilidadSelecc = actual->movimientos.at(0);
			}
			else if(prob >= 26 && prob <= 50)
			{
				habilidadSelecc = actual->movimientos.at(1);
			}
			else if(prob >= 51 && prob <= 75)
			{
				habilidadSelecc = actual->movimientos.at(2);
			}
			else if(prob >= 76 && prob <= 100)
			{
				habilidadSelecc = actual->movimientos.at(3);
			}

			do{
				if(habilidadSelecc->tipo == Attack || habilidadSelecc->tipo == Debuffeo)
				{
					numDino = rand() % player.size();
					if(player.at(numDino)->estaVivo()) break;
				}
				else
				{
					numDino = rand() % enemigos.size();
					if(enemigos.at(numDino)->estaVivo()) break;
				}
			} while(true);
			
			std::cout << habilidadSelecc->getNombre()->nombre;
		}

		if(habilidadSelecc->tipo == Attack || habilidadSelecc->tipo == Debuffeo)
			return habilidadSelecc->accion(actual,player.at(numDino),dt);
		
		return habilidadSelecc->accion(actual,enemigos.at(numDino),dt);
	}

	bool Carnotauro::turnoEnemigo(std::shared_ptr<Dinosaurio> actual,std::vector<std::shared_ptr<Dinosaurio>> player,std::vector<std::shared_ptr<Dinosaurio>> enemigos, float dt)
	{
		if(!turno)
		{
			turno = true;
			int prob = (rand() % 100) + 1;

			if(prob >= 1 && prob <= 25)
			{
				habilidadSelecc = actual->movimientos.at(0);
			}
			else if(prob >= 26 && prob <= 50)
			{
				habilidadSelecc = actual->movimientos.at(1);
			}
			else if(prob >= 51 && prob <= 75)
			{
				habilidadSelecc = actual->movimientos.at(2);
			}
			else if(prob >= 76 && prob <= 100)
			{
				habilidadSelecc = actual->movimientos.at(3);
			}

			do{
				if(habilidadSelecc->tipo == Attack || habilidadSelecc->tipo == Debuffeo)
				{
					numDino = rand() % player.size();
					if(player.at(numDino)->estaVivo()) break;
				}
				else
				{
					numDino = rand() % enemigos.size();
					if(enemigos.at(numDino)->estaVivo()) break;
				}
			} while(true);
			
			std::cout << habilidadSelecc->getNombre()->nombre;
		}

		if(habilidadSelecc->tipo == Attack || habilidadSelecc->tipo == Debuffeo)
			return habilidadSelecc->accion(actual,player.at(numDino),dt);
		
		return habilidadSelecc->accion(actual,enemigos.at(numDino),dt);
	}
}