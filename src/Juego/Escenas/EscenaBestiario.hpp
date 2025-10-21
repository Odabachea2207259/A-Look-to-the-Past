#pragma once
#include "../Figuras/Figuras.hpp"
#include "../../Motor/Primitivos/Escena.hpp"

namespace IVJ
{
	class EscenaBestiario : public CE::Escena
	{
		public:
			EscenaBestiario():CE::Escena{}{};
			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
		private:
			bool inicializar{true};
            bool mouse,mousePressed,mousePrev = false;

            std::shared_ptr<Entidad> fondo;
            std::shared_ptr<Rectangulo> izq;
            std::shared_ptr<Rectangulo> der;

            bool salir = false,salida = false;
	};
}
