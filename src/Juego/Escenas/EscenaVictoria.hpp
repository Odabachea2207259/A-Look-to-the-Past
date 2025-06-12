#pragma once
#include "../Figuras/Figuras.hpp"
#include "../../Motor/Primitivos/Escena.hpp"
#include "../Objetos/Recompensas.hpp"

namespace IVJ
{
	class EscenaVictoria : public CE::Escena
	{
		public:
			EscenaVictoria():CE::Escena{}{};
			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
		private:
			bool inicializar{true};

			bool mousePressed = false, mousePrev = false;

            std::shared_ptr<Rectangulo> boton;
			std::shared_ptr<CE::ISprite> fondo;

			std::shared_ptr<CE::ITexto> dinero;
			std::shared_ptr<CE::ITexto> recompensa;

			std::vector<std::shared_ptr<Rectangulo>> areas;
			std::vector<Recompensas::Rewards> recompensas;

			bool recompensaSelecc = false;
			int recompensaPos = 0;

			int ganancias = 0;
		private:
			void setRecompensas();
			void getRecompensa();
	};
}
