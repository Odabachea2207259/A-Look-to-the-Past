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
        player = std::make_unique<std::vector<std::shared_ptr<Dinosaurio>>>();
        enemigos = std::make_unique<std::vector<std::shared_ptr<Dinosaurio>>>();
        habilidadEspecial = nullptr;
        dinoLider = nullptr;
    }

    void Equipos::Terminar()
    {
        delete instancia;
        //instancia = nullptr;
    }

    std::vector<std::shared_ptr<Dinosaurio>>& Equipos::GetPlayer() 
    {
        return *player;
    }

    std::vector<std::shared_ptr<Dinosaurio>>& Equipos::GetEnemigos() 
    {
        return *enemigos;
    }

    std::shared_ptr<Habilidad> Equipos::GetHabilidadEsp()
    {
        return habilidadEspecial;
    }

    std::shared_ptr<Dinosaurio>& Equipos::GetDinoLider()
    {
        return dinoLider;
    }

    void Equipos::crearEnemigos()
    {
        enemigos->clear();
		float nivelJugador = static_cast<int>(Jugador::Get().GetNivel() / 2);
        if(nivelJugador < 1) nivelJugador = 1;

		int prob = rand() % 4;
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
					enemigos->push_back(std::make_shared<Centrosaurus>( nivelJugador));
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
}
