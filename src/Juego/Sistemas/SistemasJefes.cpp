#include "SistemasJefes.hpp"

namespace IVJ
{
	bool SistemaAtaque(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt,bool salto)
	{
        auto c_principal = principal->getComponente<CE::IControl>();
		auto c_target = target->getComponente<CE::IControl>();
		auto trans_principal = principal->getTransformada();
		auto trans_target = target->getTransformada();
		//float velocidadDefault = 800.f;
		float velocidadDefault = (salto) ? 400.f : 800.f;

		if(c_principal->accion && !salto && !principal->getComponente<CE::IControl>()->salto)
			return SistemaMover_Target(principal,target,dt,c_principal,c_target,trans_principal,trans_target,velocidadDefault);
		else if(c_principal->accion && salto)// && principal->getComponente<CE::IControl>()->salto)
			return SistemaSaltar_Target(principal,target,dt,c_principal,c_target,trans_principal,trans_target,velocidadDefault);

        if(c_principal->acc)
		{
            return true;
		}
		else if(target->getComponente<CE::IPersonaje>()->especial){
			SistemaElegirAtaque(principal,target,c_principal->mov);
			target->getComponente<CE::IPersonaje>()->especial = false;
		}

		return SistemaMover_Original(principal,target,dt,c_principal,c_target,trans_principal,trans_target,velocidadDefault);
	}

	bool SistemaSaltar(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt)
	{
        auto c_principal = principal->getComponente<CE::IControl>();
		auto c_target = target->getComponente<CE::IControl>();
		auto trans_principal = principal->getTransformada();
		auto trans_target = target->getTransformada();
		float velocidadDefault = 800.f;

		if(c_principal->accion)
			return SistemaSaltar_Target(principal,target,dt,c_principal,c_target,trans_principal,trans_target,velocidadDefault);

		return false;
	}

	void SistemaElegirAtaque(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target, std::string ataque)
	{
		if(ataque == "Mordisco" || ataque == "Torpedo")
		{
			float damage = (ataque == "Mordisco") ? 20.f : 50.f;
			SistemaQuitarVida(target,damage);
		}
		else if(ataque == "Rasguño" || ataque == "SuperRasguño")
		{
			float damage = (ataque == "Rasguño") ? 10.f : 30.f;
        	SistemaQuitarVida(target,damage);

			auto sangrado = std::make_shared<IVJ::Sangrado>();
			sangrado->curable = false;
			target->getComponente<CE::IEstados>()->estados.push_back(sangrado);
			target->getComponente<CE::IEstados>()->cantidad++;
		}
	}

	bool SistemaMover_Target(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt, CE::IControl *c_principal,CE::IControl *c_target,std::shared_ptr<CE::ITransform> trans_principal,std::shared_ptr<CE::ITransform> trans_target, float velocidadDefault)
	{
		if(target->getComponente<CE::IPersonaje>()->especial || principal->getComponente<CE::IPersonaje>()->especial) return true;

		auto direccion = trans_target->posicion - trans_principal->posicion;
        if(trans_target->posicion.x > trans_principal->posicion.x)
            c_principal->izq = true;
        else
            c_principal->der = true;

        float magnitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

        if(magnitud != 0.f)
        {
            direccion.x /= magnitud;
            direccion.y /= magnitud;
        }

        CE::Vector2D velocidad(direccion.x*velocidadDefault,direccion.y*velocidadDefault);

        if(magnitud > 100.f)
        {
            auto cpy = velocidad;
            trans_principal->posicion.suma(cpy.escala(dt));
            return true;
        }
            
        c_principal->der = false;
        c_principal->izq = false;
        c_target->damage = true;

		SistemaElegirAtaque(principal,target,c_principal->ataque);
		
        c_principal->accion = false;
		
        c_principal->acc = true;
		return true;
	}


	bool SistemaSaltar_Target(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt, CE::IControl *c_principal,CE::IControl *c_target,std::shared_ptr<CE::ITransform> trans_principal,std::shared_ptr<CE::ITransform> trans_target, float velocidadDefault)
	{
        auto direccion = trans_target->posicion - trans_principal->posicion;

		if(!target->tieneComponente<CE::IJugador>())
		{
			direccion.y -= 150.f;
			direccion.x -= 150.f;
		}

        if(trans_target->posicion.x > trans_principal->posicion.x)
            c_principal->izq = true;
        else
            c_principal->der = true;

        float magnitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

        if(magnitud != 0.f)
        {
            direccion.x /= magnitud;
            direccion.y /= magnitud;
        }

        CE::Vector2D velocidad(direccion.x*velocidadDefault,direccion.y*velocidadDefault);

        if(magnitud > 100.f)
        {
            auto cpy = velocidad;
            trans_principal->posicion.suma(cpy.escala(dt));
            return true;
        }
            
        c_principal->der = false;
        c_principal->izq = false;
		c_principal->saltando = false;
		c_principal->salto = false;
		
        c_principal->accion = false;
		target->getComponente<CE::IPersonaje>()->especial = true;	
		//principal->getComponente<CE::IPersonaje>()->especial = false;	
		
		return true;
	}

	bool SistemaMover_Original(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt, CE::IControl *c_principal,CE::IControl *c_target,std::shared_ptr<CE::ITransform> trans_principal,std::shared_ptr<CE::ITransform> trans_target, float velocidadDefault)
	{
        auto pos_original = trans_principal->pos_original;

        auto direccion = pos_original - trans_principal->posicion;

        if(pos_original.x > trans_principal->posicion.x)
            c_principal->izq = true;
        else
            c_principal->der = true;

        float magnitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

        if(magnitud != 0.f)
        {
            direccion.x /= magnitud;
            direccion.y /= magnitud;
        }
        CE::Vector2D velocidad(direccion.x*velocidadDefault,direccion.y*velocidadDefault);
        if(magnitud > 15.f)
        {
            auto cpy = velocidad;
            trans_principal->posicion.suma(cpy.escala(dt));
            return true;
        }

        auto c_sprite = principal->getComponente<CE::ISprite>();
        
        c_principal->der = false;
        c_principal->izq = false;

        return false;
	}

	bool SistemaIAJefes(std::shared_ptr<Entidad> actual, std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt)
	{
		bool mov = false;
		switch(Jugador::Get().GetPeriodo())
		{
			case 3:
				mov = SistemaIAJefes_P(actual,player,enemigos,dt);
				break;
		}

		return mov;
	}

	bool SistemaIAJefes_P(std::shared_ptr<Entidad> actual, std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt)
	{
		if(actual->getNombre()->nombre == "Coty")
		{
			actual->getComponente<CE::IPersonaje>()->target = enemigos.at(0);
			return false;
		} 

		auto vida = enemigos.at(1)->getStats()->hp;
		auto vida_max = enemigos.at(1)->getStats()->hp_max;

		auto personaje = actual->getComponente<CE::IPersonaje>();

		if(enemigos.at(1)->getComponente<CE::IPersonaje>()->especial && !personaje->turno){
			personaje->turno = true;
			personaje->especial = false;

			do
			{
				personaje->numDino = rand() % player.size();
				if(player.at(personaje->numDino)->estaVivo()) break;
			} while (true);

			std::string mov;
			switch(rand() % 2){
				case 0:
				{
					mov = "SuperRasguño";
					break;
				}
				case 1:
				{
					mov = "Torpedo";
					break;
				}
			}

			actual->getComponente<CE::IControl>()->mov = mov;
			actual->getComponente<CE::IControl>()->salto = true;
			personaje->target = player.at(personaje->numDino);
			personaje->target->getComponente<CE::IPersonaje>()->especial = true;
			enemigos.at(1)->getComponente<CE::IPersonaje>()->especial = false;
		}

		if(!personaje->turno)
		{
			int prob = 1;
			personaje->turno = true;

			//if(vida <= vida_max/2 && enemigos.at(1)->estaVivo()) prob = 4;
			if(vida <= vida_max && enemigos.at(1)->estaVivo()) prob = 4;

			switch(rand() % prob)
			{
				case 0:
				{
					do
					{
						personaje->numDino = rand() % player.size();
						if(player.at(personaje->numDino)->estaVivo()) break;
					} while (true);
				
					std::string ataque;
					switch(rand() % 2){
						case 0:
						{
							ataque = "Rasguño";
							break;
						}
						case 1:
						{
							ataque = "Mordisco";
							break;
						}
						default:
						{
							ataque = "Rasguño";
							break;
						}
					}
				
					actual->getComponente<CE::IControl>()->ataque = ataque;
					personaje->target = player.at(personaje->numDino);
					break;
				}
				case 1:
				case 2:
				case 3:
				{
					enemigos.at(0)->getComponente<CE::IPersonaje>()->especial = true;
					actual->getComponente<CE::IPersonaje>()->especial = true;
					personaje->target = enemigos.at(1);

					actual->getComponente<CE::IControl>()->mov = "Salto";
					actual->getComponente<CE::IControl>()->salto = true;

					break;
				}
			}
		}

		if(actual->getComponente<CE::IPersonaje>()->especial) return SistemaSaltar(actual,personaje->target,dt);
		else return SistemaAtaque(actual,personaje->target,dt,personaje->target->getComponente<CE::IPersonaje>()->especial);
	}  

}