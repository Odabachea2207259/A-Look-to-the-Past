#pragma once
#include "../Figuras/Figuras.hpp"
#include "../../Motor/Primitivos/Escena.hpp"

namespace IVJ
{
	class EscenaFosiles : public CE::Escena
	{
		public:
			EscenaFosiles():CE::Escena{}{};
			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
		private:
			bool inicializar{true};
			int figura = 1;

            std::vector<std::shared_ptr<IVJ::Rectangulo>> fosiles;
            std::vector<std::shared_ptr<IVJ::Rectangulo>> skulls;

            sf::RectangleShape fondo;

			void mostrarDinos();
	};
}
