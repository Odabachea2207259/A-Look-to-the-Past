#include "Sistemas.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../../Motor/Render/Render.hpp"
#include <cmath>

namespace IVJ
{
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
}
