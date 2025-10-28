#include "Sistemas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../../Motor/Utils/Vector2D.hpp"
#include "../../Motor/Utils/Lerp.hpp"
#include "../Objetos/Entidad.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Estados/Estados.hpp"
#include <cmath>

namespace IVJ
{
	void SistemaMover(const std::vector<std::shared_ptr<CE::Objeto>>& entes, float dt)
	{
		for(auto& ente : entes)
		{
			if(!ente->tieneComponente<CE::ITimer>())
			{
				auto trans = ente->getTransformada();
				auto cpy = trans->velocidad;
				trans->posicion.suma(cpy.escala(dt));
			}
		}
	}

	void SistemaMovimientoRebote(std::vector<std::shared_ptr<CE::Objeto>> entes, float dt)
	{
		for(auto & e: entes)
		{
			if(e->tieneComponente<CE::ITimer>())
			{
				auto& timer = *e->getComponente<CE::ITimer>();
				auto trans = e->getTransformada();
				auto& ventana = CE::Render::Get().GetVentana();
				int x = ventana.getSize().x;
				int y = ventana.getSize().y;
				//trans.posicion.x += 25*dt;
				//trans.posicion.y += 5*dt;

				if(trans->posicion.y + 10 > y || trans->posicion.y - 10 < 0)
					trans->dirY *= -1;

				if(trans->posicion.x + 10 > x || trans->posicion.x - 10 < 0)
					trans->dirX *= -1;

				//trans.posicion.suma(CE::Vector2D{trans.velocidad.x + 100 * trans.dirX * dt,100 * trans.dirY * dt});
				trans->posicion.suma(CE::Vector2D{trans->velocidad.x * trans->dirX * dt, trans->velocidad.y * trans->dirY * dt});
				//trans->posicion.suma(trans->velocidad);

				timer.frame_actual++;
			}
		}
	}

	void SistemaMovimientoEntes(std::vector<std::shared_ptr<CE::Objeto>> entes, float dt)
	{
		for(auto & e: entes)
		{
			if(e->tieneComponente<CE::ITimer>())
			{
				auto& timer = *e->getComponente<CE::ITimer>();
				auto& trans = *e->getTransformada();
				auto& nombre = *e->getNombre();
				auto& ventana = CE::Render::Get().GetVentana();
				int x = ventana.getSize().x;
				int y = ventana.getSize().y;
				//trans.posicion.x += 25*dt;
				//trans.posicion.y += 5*dt;

				if(trans.posicion.y > y || trans.posicion.y < 0)
					trans.dirY *= -1;

				if(trans.posicion.x > x || trans.posicion.x < 0)
					trans.dirX *= -1;

				if(nombre.nombre == "Rectangulo")
				{
					trans.posicion.y += 25*dt*trans.dirY;
				}
				else if(nombre.nombre == "Triangulo")
				{
					trans.posicion.x += dt*30*trans.dirX;
					trans.posicion.y += sin(trans.posicion.x * 0.3);
				}
				else if(nombre.nombre == "Circulo")
				{
					trans.posicion.x += cos(M_PI/16);
					trans.posicion.y += sin(M_PI/16);
				}
				timer.frame_actual++;
			}
		}
	}

	CE::Vector2D SistemaPosMouse()
	{
#if DEBUG
		return CE::Render::Get().getMousePos();
#else
		auto& ventana = CE::Render::Get().GetVentana();
		CE::Vector2D mousePos(sf::Mouse::getPosition(ventana).x,sf::Mouse::getPosition(ventana).y);

		return mousePos;
#endif
	}
	
	void SistemaContains(const std::vector<std::shared_ptr<IVJ::Rectangulo>>& entes, CE::Vector2D mousePos)
	{
		float suma;
		for(auto & ente : entes)
		{
			suma = 0;
			auto& trans = *ente->getTransformada();

			//RECTANGULOS SIN ANGULO
			//if(mousePos.x >= trans.posicion.x
			//&& mousePos.x <= trans.posicion.x + ente->getWidth()
			//&& mousePos.y >= trans.posicion.y
			//&& mousePos.y <= trans.posicion.y + ente->getHeight())
			//	ente->mouse = 1;
			//else
			//	ente->mouse = 0;

			//RECTANGULOS CON ANGULO Y SIN ANGULO
			CE::Vector2D a(trans.posicion.x - ente->getWidth() / 2,trans.posicion.y - ente->getHeight()/2);
			CE::Vector2D b(trans.posicion.x + ente->getWidth() - ente->getWidth()/2,trans.posicion.y-ente->getHeight()/2);
			CE::Vector2D c(trans.posicion.x + ente->getWidth()-ente->getWidth()/2, trans.posicion.y + ente->getHeight()-ente->getHeight()/2);
			CE::Vector2D d(trans.posicion.x-ente->getWidth()/2, trans.posicion.y + ente->getHeight()-ente->getHeight()/2);
			
			//ABC
			//suma += abs((b.x * a.y - a.x * b.y) + (c.x * b.y - b.x * c.y) + (a.x * c.y - c.x * a.y))/2;

			float mouseX = mousePos.x;// - (ente->getWidth() / 2);
			float mouseY = mousePos.y;// - (ente->getHeight() / 2);

			//APD
			suma += abs((mouseX * a.y - a.x * mouseY) + (d.x * mouseY - mouseX * d.y) + (a.x * d.y - d.x * a.y))/2;
			//DPC
			suma += abs((mouseX * d.y - d.x * mouseY) + (c.x * mouseY - mouseX * c.y) + (d.x * c.y - c.x * d.y))/2;
			//CPB
			suma += abs((mouseX * c.y - c.x * mouseY) + (b.x * mouseY - mouseX * b.y) + (c.x * b.y - b.x * c.y))/2;
			//PBA
			suma += abs((b.x * mouseY - mouseX * b.y) + (a.x * b.y - b.x * a.y) + (mouseX * a.y - a.x * mouseY))/2;

			if(suma > ente->getArea())
				ente->mouse = 0;
			else
				ente->mouse = 1;
		}
	}

	bool SistemaColAABB(CE::Objeto& A, CE::Objeto& B, bool resolucion)
	{
		if(!A.tieneComponente<CE::IBoundingBox>() || !B.tieneComponente<CE::IBoundingBox>())
			return false;

		auto bA = A.getComponente<CE::IBoundingBox>()->tam;
		auto mA = A.getComponente<CE::IBoundingBox>()->mitad;
		auto *pa = &A.getTransformada()->posicion;
		auto prevA = A.getTransformada()->pos_prev;
		
		auto bB = B.getComponente<CE::IBoundingBox>()->tam;
		auto mB = B.getComponente<CE::IBoundingBox>()->mitad;
		auto pb = B.getTransformada()->posicion;

		bool H = pa->y-mA.y < pb.y+bB.y - mB.y && pb.y-mB.y < pa->y+bA.y - mA.y;
		bool V = pa->x-mA.x < pb.x+bB.x - mB.x && pb.x-mB.x < pa->x+bA.x - mA.x;
		bool hay_colision = H && V;
		if(hay_colision && resolucion)
		{
			auto c = B.getComponente<CE::IControl>();
			c->muerte = true;
			*pa = prevA;
		}
		return hay_colision;
	}

	bool SistemaColAABBMid(CE::Objeto&A, CE::Objeto& B, bool resolucion)
	{
		if(!A.tieneComponente<CE::IBoundingBox>() || !B.tieneComponente<CE::IBoundingBox>())
			return false;
		auto midA = A.getComponente<CE::IBoundingBox>()->mitad;
		auto *pa = &A.getTransformada()->posicion;
		auto prevA = A.getTransformada()->pos_prev;
		auto midB = B.getComponente<CE::IBoundingBox>()->mitad;
		auto *pb = &B.getTransformada()->posicion;

		float dX = std::abs(pb->x - pa->x);
		float dY = std::abs(pb->y - pa->y);
		float sumMidX = midA.x + midB.x;
		float sumMidY = midA.y + midB.y;
		bool V = sumMidX - dX > 0;
		bool H = sumMidY - dY > 0;
		bool hay_colision = V && H;

		if(hay_colision && resolucion)
			*pa = prevA;
		return hay_colision;
	}

	
	void SistemaSpawn(std::vector<std::shared_ptr<CE::Objeto>>& spawns)
	{
		for(auto &s : spawns)
		{
			auto respawnData = s->getComponente<CE::IRespawn>();

			if(!respawnData)
				continue;

			if(respawnData->num_objetos >= respawnData->max_objetos)
				continue;

			if(respawnData->timer_actual >= respawnData->timer_maximo)
			{
				//Crear objeto
				auto malillo = std::make_shared<Entidad>();

            	malillo->addComponente(std::make_shared<CE::ISprite>(
            	    CE::GestorAssets::Get().getTextura("hoja_yellow"),
            	    68,85,
            	    1.0f
            	));

				auto comp = respawnData->prefab->getComponente<CE::ISprite>();

				malillo->copyComponente<CE::ISprite>(comp);

				//malillo->copyComponente<CE::IPaths>(respawnData->prefab->getComponente<CE::IPaths>());
				
				malillo->getStats()->hp = 100;
				
				int size_x = respawnData->width;
				int size_y = respawnData->height;
				float x0 = s->getTransformada()->posicion.x - size_x/2.f;
				float y0 = s->getTransformada()->posicion.y - size_y/2.f;
				float x = x0+rand()%size_x;
				float y = y0+rand()%size_y;
				
				malillo->addComponente(std::make_shared<CE::IPaths>(200));
        		auto path_enemies = malillo->getComponente<CE::IPaths>();
        		path_enemies->addCurva(CE::Vector2D{x,y},CE::Vector2D{x-100.f,y-100.f},CE::Vector2D{x-300,y-300});
				path_enemies->addCurva(CE::Vector2D{700.f,200.f},CE::Vector2D{600.f,500.f},CE::Vector2D{500.f,200.f});


				malillo->setPosicion(x,y);
				//spawns.push_back(malillo);
				spawns.emplace_back(malillo);
				
				respawnData->timer_actual=0;
				respawnData->num_objetos++;
			}

			respawnData->timer_actual++;
		}
	}
	
	void SistemaPaths(const std::vector<std::shared_ptr<CE::Objeto>>& obj)
	{
		for(auto & o : obj)
		{
			std::cout << o->tieneComponente<CE::IPaths>() << std::endl;
			if(o->tieneComponente<CE::IPaths>())
			{
				auto *path = o->getComponente<CE::IPaths>();
				int num_curvas = path->puntos.size()/3;
				
				std::cout << o << std::endl;
				if(path->puntos.size() == 0) continue;
				if(path->id_curva >= num_curvas) continue;
				
				//std::cout << path->puntos.size() <<"  " << path->id_curva << "   " << num_curvas << std::endl;
					
				float t = path->frame_actual_curva/(float)path->frame_total_curva;

				CE::Vector2D P0 = path->puntos[0+path->id_curva*(path->offset)];
				CE::Vector2D P1 = path->puntos[1+path->id_curva*(path->offset)];
				CE::Vector2D P2 = path->puntos[2+path->id_curva*(path->offset)];

				auto posiciones_actual = CE::lerp2(P0,P1,P2,t);
				path->frame_actual_curva++;

				o->setPosicion(posiciones_actual.x,posiciones_actual.y);
				//std::cout << posiciones_actual.x << " " << posiciones_actual.y << std::endl;
				
				if(t==1)
				{
					path->id_curva++;
					path->frame_actual_curva=0;
				}
			}
		}
	}

	void SistemaQuitarVida(std::shared_ptr<IVJ::Entidad> target, float damage)
	{
		float realDamage = damage * std::pow(0.9,target->getStats()->def);
        target->getStats()->hp -= realDamage;
	}

	void SistemaAgregarVida(std::shared_ptr<IVJ::Entidad> target, float vida)
	{
        if(target->getStats()->hp + vida >= target->getStats()->hp_max)
            target->getStats()->hp = target->getStats()->hp_max;
        else   
            target->getStats()->hp += vida;
	}

	void SistemaAplicarEstados(std::shared_ptr<IVJ::Entidad> target)
	{
		auto estados = target->getComponente<CE::IEstados>();
		if(estados->estados.empty()) return;

		for(auto & estado : estados->estados)
		{
			estado->aplicarEstado(target);
			if(!estado->permanente) estado->turnos -= 1;
		}

		estados->estados.erase(
		    std::remove_if(estados->estados.begin(), estados->estados.end(),
		        [](const std::shared_ptr<Estado>& estado) {
		            return estado->turnos <= 0;
		        }),
		    estados->estados.end());

		return;
	}

	std::vector<std::shared_ptr<IVJ::Entidad>> SistemaOrdenarTurnos(std::vector<std::shared_ptr<IVJ::Entidad>> jugador,std::vector<std::shared_ptr<IVJ::Entidad>> enemigos)
	{	
		std::vector<std::shared_ptr<IVJ::Entidad>> turnos;

		for(auto & dino : jugador)
			turnos.push_back(dino);
		
		for(auto & dino : enemigos)
			turnos.push_back(dino);

		std::sort(turnos.begin(),turnos.end(),[](const std::shared_ptr<Entidad>& a, const std::shared_ptr<Entidad>& b){
			return a->getStats()->agi >= b->getStats()->agi;
		});

		for(auto& turno : turnos) std::cout << turno->getNombre()->nombre <<std::endl;
		std::cout << std::endl;

		return turnos;
	}

	void SistemaMostrarEstados(std::shared_ptr<IVJ::Entidad> target)
	{
		auto estados = target->getComponente<CE::IEstados>();
        if(target->getComponente<CE::IEstados>()->cantidad > 0)
        {
            int i = 0;
            
            for(auto & estado : estados->estados)
            {
                estado->setPosicion(target->getComponente<CE::ISelectores>()->vida_max.getPosition().x + (14*i),target->getComponente<CE::ISelectores>()->vida_max.getPosition().y + 15.f);
                i++;
                if(i >= 5) return;
            }
        }
	}

	void SistemaSetPosOriginal(std::shared_ptr<IVJ::Entidad> target)
	{
	    target->getTransformada()->pos_original = target->getTransformada()->posicion;
        auto sprite = target->getComponente<CE::ISprite>();
        auto width = sprite->width;
        auto height = sprite->height;
        target->getComponente<CE::ISelectores>()->vida.setPosition({target->getTransformada()->pos_original.x - (width/8),target->getTransformada()->pos_original.y-(height/4)});
        target->getComponente<CE::ISelectores>()->vida_max.setPosition({target->getTransformada()->pos_original.x - (width/8),target->getTransformada()->pos_original.y-(height/4)});
	}

	void SistemaActualizarVida(std::shared_ptr<IVJ::Entidad> target)
	{
        float porcentaje = target->getStats()->hp/target->getStats()->hp_max;
        porcentaje = std::max(0.f,porcentaje);
        target->getComponente<CE::ISelectores>()->vida.setSize(sf::Vector2f(target->getComponente<CE::ISelectores>()->vida_max.getSize().x * porcentaje, 10.f));
	}

	void SistemaReiniciarStats(std::shared_ptr<IVJ::Entidad> target)
	{
        target->getStats()->hp = target->getStats()->hp_max;
        target->getStats()->agi =target->getStats()->agi_max;
        target->getStats()->str =target->getStats()->str_max;
        target->getStats()->def =target->getStats()->def_max;
	}

	void SistemaReiniciarDino(std::shared_ptr<IVJ::Entidad> target)
	{
		target->eliminarComponente<CE::IJugador>();
        target->getComponente<CE::IPersonaje>()->turno = false;

		SistemaReiniciarStats(target);

        auto estados = target->getComponente<CE::IEstados>();
        estados->aturdido = false;
        estados->dormido = false;
        estados->estados.clear();

    	auto c = target->getComponente<CE::IControl>();
    	c->abj = false;
    	c->der = false;
    	c->arr = false;
    	c->izq = false;
    	c->acc = false;
    	c->sacc = false;
    	c->damage = false;
    	c->muerte = false;
    	c->muerto = false;
    	c->accion = false;

		auto &fsm_init = target->getComponente<IMaquinaEstado>()->fsm;
		fsm_init = std::make_shared<IdleFSM>();
		fsm_init->onEntrar(*target);
	}

	void SistemaSubirNivel(std::shared_ptr<IVJ::Entidad> target)
	{
        target->getStats()->hp_max += target->getStats()->hp_max * 0.2;
        target->getStats()->agi_max += 2.f;
        target->getStats()->str_max += 2.f;
        target->getStats()->def_max += 2.f;    
        
        target->getComponente<CE::IPersonaje>()->nivel++;
		SistemaReiniciarStats(target);
	}

	void SistemaConfigurarStats(IVJ::Dinosaurio * const &target,float hp, float str, float agi, float def)
	{
		auto nivel = target->getComponente<CE::IPersonaje>()->nivel;
		target->getStats()->hp = hp * nivel;
		target->getStats()->hp_max = hp * nivel;

		target->getStats()->str = str * nivel;
		target->getStats()->str_max = str * nivel;

		target->getStats()->agi = agi * nivel;
		target->getStats()->agi_max = agi * nivel;

		target->getStats()->def = def * nivel;
		target->getStats()->def_max = def * nivel;
	}

	bool SistemaIA(std::shared_ptr<Entidad> actual,std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt)
	{
		bool mov = false;
		switch(actual->getComponente<CE::IPersonaje>()->tipo)
		{
			case IVJ::TipoEnte::Atacante:
				mov = SistemaIA_Attack(actual,enemigos,player,dt);
				break;
			case IVJ::TipoEnte::Healer:
				mov = SistemaIA_Heal(actual,enemigos,player,dt);
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
					personaje->numDino = rand() % player.size();
					if(player.at(personaje->numDino)->estaVivo()) break;
				}
				else
				{
					personaje->numDino = rand() % enemigos.size();
					if(enemigos.at(personaje->numDino)->estaVivo()) break;
				}
			} while(true);			
		}

		if(actualHabilidades->habilidadSelecc->tipo == IVJ::TipoHabilidad::Buffeo)
			return actualHabilidades->habilidadSelecc->accion(actual,player.at(personaje->numDino),dt);
		
		return actualHabilidades->habilidadSelecc->accion(actual,enemigos.at(personaje->numDino),dt);
	}

	bool SistemaIA_Heal(std::shared_ptr<Entidad> actual,std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt)
	{
		auto actualHabilidades = actual->getComponente<CE::IHabilidades>();

		auto personaje = actual->getComponente<CE::IPersonaje>();

		if(!personaje->turno)
		{
			int x = 50, y = 50, z = 50;
			personaje->turno = true;

			float menorVida = 1000.f;
			personaje->numDino = -1;

			for(auto & a: enemigos)
			{
				if(a->getStats()->hp < menorVida && a->estaVivo())
				{
					menorVida = a->getStats()->hp;
				}
				personaje->numDino++;
			}

			if(menorVida < enemigos.at(personaje->numDino)->getStats()->hp_max * 0.5f && menorVida > 0.f)
			{
				x = 50/3;
				y = 50 + x;
				z = y + 50/3;
			}
		
			int prob = (rand() % 100) + 1;

			if(prob >= 1 && prob <= x)
			{
				actualHabilidades->habilidadSelecc = actualHabilidades->movimientos.at(0);
			}
			else if(prob > x && prob <= y)
			{
				actualHabilidades->habilidadSelecc = actualHabilidades->movimientos.at(1);
			}
			else if(prob > y && prob <= z)
			{
				actualHabilidades->habilidadSelecc = actualHabilidades->movimientos.at(2);
			}
			else if(prob > z && prob <= 100)
			{
				actualHabilidades->habilidadSelecc = actualHabilidades->movimientos.at(3);
			}

			do{
				if(actualHabilidades->habilidadSelecc->tipo == Buffeo)
				{
					personaje->numDino = rand() % player.size();
					if(player.at(personaje->numDino)->estaVivo()) break;
				}
				else
				{
					if(menorVida < 40.f && menorVida > 0.f) break;
					personaje->numDino = rand() % enemigos.size();
	
					if(enemigos.at(personaje->numDino)->estaVivo()) break;
				}
			} while(true);			
		}

		if(actualHabilidades->habilidadSelecc->tipo == Buffeo)
			return actualHabilidades->habilidadSelecc->accion(actual,player.at(personaje->numDino),dt);
		
		return actualHabilidades->habilidadSelecc->accion(actual,enemigos.at(personaje->numDino),dt);
	}

	void SistemaActualizarMedidor(std::shared_ptr<IVJ::Entidad> dinoLider,std::shared_ptr<IVJ::Rectangulo> medidor)
	{
		float porcentaje = dinoLider->getComponente<CE::IJugador>()->medidor / dinoLider->getComponente<CE::IHabilidades>()->habilidadEspecial->medidor;
		porcentaje = std::min(porcentaje,1.f);
		medidor->setTam(medidor->getWidth() * porcentaje,medidor->getHeight());
	}

	void SistemaApagarBotones(std::shared_ptr<IVJ::Entidad> actual, bool* eSelecc, bool* pSelecc, bool* mostrarSelector)
	{
		for(auto& boton:actual->getComponente<CE::IHabilidades>()->movimientos)
			boton->seleccionado = false;
		actual->getComponente<CE::IHabilidades>()->habilidadEspecial->seleccionado = false;
		*eSelecc = false;
		*pSelecc = false;
		*mostrarSelector = false;
	}

	int SistemaRevisarGanador(std::vector<std::shared_ptr<IVJ::Entidad>> turnos)
	{
		int player = 0, enemy = 0;

		for(auto & ente : turnos){
			if(ente->tieneComponente<CE::IJugador>() && ente->estaVivo()) player++;
			else if(ente->estaVivo()) enemy++;
		}

		if(player <= 0) return -1;
		if(enemy <= 0) return 1;

		return 0;
	}
}
