#include "Equipos.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"

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
        switch(Jugador::Get().GetPeriodo()){
            case 1:
                crearJefesP();
                break;
            case 9:
            default:
                crearEnemigosDefault();
                break;
        }
    }

    void Equipos::crearEnemigosDefault()
    {
        enemigos->clear();
		float nivelJugador = static_cast<int>(Jugador::Get().GetNivel() / 2);
        if(nivelJugador < 1) nivelJugador = 1;

		int prob = rand() % 5;
		//int prob = 1;
		int cant = rand() % player->size() + 1;

        nivelJugador = 0.2;

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

    void Equipos::crearJefesP()
    {
        enemigos->clear();

        auto jefeA = std::make_shared<IVJ::Entidad>();
        jefeA->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("anteosaurus"),
            416,207,1.0f
        ));

        auto nombre = jefeA->getNombre();
        nombre->nombre = "Anteosaurus";

        jefeA->addComponente(std::make_shared<CE::IControl>());
        jefeA->addComponente(std::make_shared<IVJ::IMaquinaEstado>());
        jefeA->addComponente(std::make_shared<CE::IEstados>());
        jefeA->addComponente(std::make_shared<CE::ISelectores>());
        jefeA->addComponente(std::make_shared<CE::IPersonaje>());

        jefeA->getComponente<CE::IPersonaje>()->nivel = 10;

        auto &fsm_init = jefeA->getComponente<IVJ::IMaquinaEstado>()->fsm;
        fsm_init = std::make_shared<IVJ::IdleFSM>();
        fsm_init->onEntrar(*jefeA);

        IVJ::SistemaConfigurarStatsE(jefeA,1000,20,1,10);

        enemigos->push_back(jefeA);
        
    }
    //void Equipos::crearJefesM()
    //void Equipos::crearJefesC()
}
