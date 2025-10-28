#include "Equipos.hpp"
#include <iostream>

namespace IVJ
{
    Equipos& Equipos::Get()
    {
        if(!instancia)
        {
            instancia = new Equipos();
        }
        return *instancia;
    }

    Equipos::Equipos()
    {
        player = std::make_unique<std::vector<std::shared_ptr<IVJ::Entidad>>>();
        enemigos = std::make_unique<std::vector<std::shared_ptr<IVJ::Entidad>>>();
        habilidadEspecial = nullptr;
        dinoLider = nullptr;
    }

    void Equipos::Terminar()
    {
        delete instancia;
        //instancia = nullptr;
    }

    std::vector<std::shared_ptr<IVJ::Entidad>>& Equipos::GetPlayer() 
    {
        return *player;
    }

    std::vector<std::shared_ptr<IVJ::Entidad>>& Equipos::GetEnemigos() 
    {
        return *enemigos;
    }

    std::shared_ptr<Habilidad> Equipos::GetHabilidadEsp()
    {
        return habilidadEspecial;
    }

    std::shared_ptr<IVJ::Entidad>& Equipos::GetDinoLider()
    {
        return dinoLider;
    }

    void Equipos::crearEnemigos()
    {
        enemigos->clear();
		float nivelJugador = static_cast<int>(Jugador::Get().GetNivel() / 2);
        if(nivelJugador < 1) nivelJugador = 1;

		int prob = rand() % 5;
		//int prob = 1;
		int cant = rand() % player->size() + 1;

        nivelJugador = 0.5;

		switch(prob)
		{
			case 0:
				for(int i = 0; i < cant;i++)
					enemigos->push_back(std::make_shared<Pachycephalosaurus>(nivelJugador));
				break;
			case 1:
				for(int i = 0; i < cant;i++)
					enemigos->push_back(std::make_shared<Parasaurolophus>(nivelJugador));
				break;
			case 2:
				for(int i = 0; i < cant;i++)
					enemigos->push_back(std::make_shared<Centrosaurus>(nivelJugador));
				break;
			case 3:
				for(int i = 0; i < cant;i++)
					enemigos->push_back(std::make_shared<Carnotauro>(nivelJugador));
				break;
			case 4:
                enemigos->push_back(std::make_shared<Carnotauro>(nivelJugador));
                enemigos->push_back(std::make_shared<Pachycephalosaurus>(nivelJugador));
				enemigos->push_back(std::make_shared<Carnotauro>(nivelJugador));
				break;
			default:
				break;
		}
    }


    /*<-----------------------Crear una función intermedia para saber en que ronda nos encontramos----------------->*/
    /*<-----------------------y mandar a la clase que creara los jefes necesarios.                ----------------->*/
    /*<-----------------------Esta función intermedia se usará en todas las escenas y detectará si----------------->*/
    /*<-----------------------mandar a la función de crear enemigos random o a los jefes.         ----------------->*/


    //void Equipos::crearJefesP()
    //void Equipos::crearJefesM()
    //void Equipos::crearJefesC()
}
