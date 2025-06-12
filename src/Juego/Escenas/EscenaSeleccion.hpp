#pragma once
#include "../Figuras/Figuras.hpp"
#include "../../Motor/Primitivos/Escena.hpp"
#include <cstdlib>
#include <ctime>

namespace IVJ
{
	class EscenaSeleccion : public CE::Escena
	{
		public:
			EscenaSeleccion():CE::Escena{}{};
			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
		private:
			bool inicializar{true};
            bool mouse = false,mousePressed = false,mousePrev = false;

            sf::ConvexShape selector;
            float ancho,alto;
            int dinosSeleccionados;
            bool mostrarSelector = false;

            sf::RectangleShape rectanguloDino;

            sf::RectangleShape fondo;

            std::shared_ptr<IVJ::Rectangulo> boton;
	};
}
