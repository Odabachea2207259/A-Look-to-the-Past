#pragma once

#include "../../Motor/Primitivos/Escena.hpp"

namespace IVJ
{
	class Escena_Zombie : public CE::Escena
	{
		public:
			//Escena_Zombie():CE::Escena{}{};

			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
            
        private:
            int inicializar{1};
	};
}
