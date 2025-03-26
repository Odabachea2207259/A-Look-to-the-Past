#pragma once
#include "../../Motor/Primitivos/Escena.hpp"

namespace IVJ
{
	class EscenaFiguras : public CE::Escena
	{
		public:
			EscenaFiguras():CE::Escena{}{};
			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
		private:
			bool inicializar{true};
	};
}
