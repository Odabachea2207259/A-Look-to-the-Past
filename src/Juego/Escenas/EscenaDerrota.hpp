#pragma once
#include "../Figuras/Figuras.hpp"
#include "../../Motor/Primitivos/Escena.hpp"

namespace IVJ
{
	class EscenaDerrota : public CE::Escena
	{
		public:
			EscenaDerrota():CE::Escena{}{};
			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
		private:
			bool inicializar{true};

            std::shared_ptr<Rectangulo> boton;

			std::shared_ptr<CE::ITexto> dinero;
            std::shared_ptr<CE::ISprite> fondo;
	};
}
