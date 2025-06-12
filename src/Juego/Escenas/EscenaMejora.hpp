#pragma once
#include "../Figuras/Figuras.hpp"
#include "../../Motor/Primitivos/Escena.hpp"
#include <cstdlib>
#include <ctime>

namespace IVJ
{
	class EscenaMejora : public CE::Escena
	{
		public:
			EscenaMejora():CE::Escena{}{};
			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
		private:
			bool inicializar{true};
            bool mouse = false,mousePressed = false,mousePrev = false;

            int precioMejora = 10;

			std::shared_ptr<CE::ISprite> fondo;

            sf::ConvexShape selector;
            float ancho,alto;
            int dinosSeleccionados;
            bool mostrarSelector = false;

            sf::RectangleShape rectanguloDino;

            std::shared_ptr<Dinosaurio> dinoSelecc;
            std::shared_ptr<IVJ::Rectangulo> boton;

			std::vector<std::shared_ptr<CE::ITexto>> niveles;

		private:
			void actualizarNiveles();
	};
}
