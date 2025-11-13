#include "SistemasIA.hpp"
#include "../Habilidades/Habilidad.hpp"

namespace IVJ
{
	bool SistemaIA(std::shared_ptr<Entidad> actual,std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt)
	{
		bool mov = false;
		switch(actual->getComponente<CE::IPersonaje>()->tipo)
		{
			case IVJ::TipoEnte::Atacante:
				mov = SistemaIA_Attack(actual,player,enemigos,dt);
				break;
			case IVJ::TipoEnte::Healer:
				mov = SistemaIA_Heal(actual,player,enemigos,dt);
				break;
		}

		return mov;
	}
	
	bool SistemaIA_Attack(std::shared_ptr<Entidad> actual,std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt)
	{
		auto actualHabilidades = actual->getComponente<CE::IHabilidades>();

		auto personaje = actual->getComponente<CE::IPersonaje>();

		if(!personaje->turno)
		{
			personaje->turno = true;
			int prob = (rand() % 100) + 1;
			int habilidad = 0;

			if(prob >= 76) habilidad = 3;
			else if(prob >= 51) habilidad = 2;
			else if(prob >= 26) habilidad = 1;
			else habilidad = 0;

			actualHabilidades->habilidadSelecc = actualHabilidades->movimientos.at(habilidad);

			do{
				if(actualHabilidades->habilidadSelecc->tipo == IVJ::TipoHabilidad::Buffeo)
				{
					personaje->numDino = rand() % enemigos.size();
					if(enemigos.at(personaje->numDino)->estaVivo()){
						personaje->target = enemigos.at(personaje->numDino);
						break;
					} 
				}
				else
				{
					personaje->numDino = rand() % player.size();
					if(player.at(personaje->numDino)->estaVivo())
					{
						personaje->target = player.at(personaje->numDino);
						break;
					}
				}
			} while(true);			
		}

		if(actualHabilidades->habilidadSelecc->tipo == IVJ::TipoHabilidad::Buffeo)
			return actualHabilidades->habilidadSelecc->accion(actual,personaje->target,dt);
		
		return actualHabilidades->habilidadSelecc->accion(actual,personaje->target,dt);
	}

	bool SistemaIA_Heal(std::shared_ptr<Entidad> actual,std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt)
	{
		auto actualHabilidades = actual->getComponente<CE::IHabilidades>();

		auto personaje = actual->getComponente<CE::IPersonaje>();

		if(!personaje->turno)
		{
			int x = 50, y = 50, z = 50;
			personaje->turno = true;

			//float menorVida = 1000.f;
			float menorVida = INT_MAX;

			for(int i = 0; i < enemigos.size(); i++)
			{
				auto e = enemigos.at(i);
				if(e->getStats()->hp < menorVida && e->estaVivo()){
					menorVida = e->getStats()->hp;
					personaje->numDino = i;
				}
			}

			personaje->target = enemigos.at(personaje->numDino);

			if(menorVida < enemigos.at(personaje->numDino)->getStats()->hp_max * 0.5f && menorVida > 0.f)
			{
				x = 50/3;
				y = 50 + x;
				z = y + 50/3;
			}
		
			int prob = (rand() % 100) + 1;
			int habilidad = 0;
			if(prob >= 1 && prob <= x) habilidad = 0;
			else if(prob > x && prob <= y) habilidad = 1;
			else if(prob > y && prob <= z) habilidad = 2;
			else if(prob > z && prob <= 100) habilidad = 3;

			actualHabilidades->habilidadSelecc = actualHabilidades->movimientos.at(habilidad);

			do{
				if(actualHabilidades->habilidadSelecc->tipo == Buffeo)
				{
					if(menorVida < 40.f && menorVida > 0.f) break;
					
					personaje->numDino = rand() % enemigos.size();
					if(enemigos.at(personaje->numDino)->estaVivo()) 
					{
						personaje->target = enemigos.at(personaje->numDino);
						break;
					}
				}
				else
				{
					personaje->numDino = rand() % player.size();
	
					if(player.at(personaje->numDino)->estaVivo()) 
					{
						personaje->target = player.at(personaje->numDino);
						break;
					}
				}
			} while(true);			
		}

		if(actualHabilidades->habilidadSelecc->tipo == Buffeo)
			return actualHabilidades->habilidadSelecc->accion(actual,personaje->target,dt);
		
		return actualHabilidades->habilidadSelecc->accion(actual,personaje->target,dt);
	}
}