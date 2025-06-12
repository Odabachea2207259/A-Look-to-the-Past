#include "Sistemas.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../../Motor/Render/Render.hpp"
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
}
