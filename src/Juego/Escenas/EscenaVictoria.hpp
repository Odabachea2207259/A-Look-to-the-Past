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

			void game(float dt);
			void tutorial(float dt);
		private:
			bool inicializar{true};

			bool mousePressed = false, mousePrev = false;
			CE::Vector2D mousePos{};

            std::shared_ptr<Rectangulo> boton;
			std::shared_ptr<CE::ISprite> fondo;

			std::shared_ptr<CE::ITexto> dinero;
			std::shared_ptr<CE::ITexto> recompensa;

			std::vector<std::shared_ptr<Rectangulo>> areas;
			std::vector<Recompensas::Rewards> recompensas;

			bool recompensaSelecc = false;
			int recompensaPos = 0;

			int ganancias = 0;

			std::shared_ptr<IVJ::Rectangulo> tuto_1;
			std::shared_ptr<IVJ::Rectangulo> tuto_2;
			std::shared_ptr<IVJ::Rectangulo> hattie;
			std::shared_ptr<CE::ITexto> texto_tutorial;
            std::vector<CE::Vector2D> pos_tutorial_1;
            std::vector<CE::Vector2D> pos_tutorial_2;
			bool algo = false;
			int parrafo = 1;
			int cant_parrafos{20};
            float ec{};
		private:
			void setRecompensas();
			void getRecompensa();
	};
}
