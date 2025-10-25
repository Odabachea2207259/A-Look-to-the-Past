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
                //estado->setPosicion(vida_max.getPosition().x + (14*i),vida_max.getPosition().y + 15.f);
                i++;
                if(i >= 5) return;
            }
        }
	}
}
