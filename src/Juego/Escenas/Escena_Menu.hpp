#pragma once
#include "../Figuras/Figuras.hpp"
#include "../Objetos/Pais.hpp"
#include "../Objetos/Periodos.hpp"
#include "../../Motor/Primitivos/Escena.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"

namespace IVJ
{
	class Escena_Menu : public CE::Escena
	{
		public:
			Escena_Menu():CE::Escena{}{};
			void onInit();
			void onFinal();
			void onUpdate(float dt);
			void onInputs(const CE::Botones& accion);
			void onRender();
		private:
			bool inicializar{true};
			std::vector<std::shared_ptr<Pais>> paises;
			bool mouse,mousePressed,mousePrev = false;

			std::shared_ptr<Rectangulo> tooltip;
			std::shared_ptr<Rectangulo> iconoDinero;
			std::shared_ptr<Rectangulo> progreso;
			std::shared_ptr<Rectangulo> fosiles;
			std::shared_ptr<Rectangulo> lab;
			std::shared_ptr<Rectangulo> bestiario;
			std::shared_ptr<Rectangulo> periodo;

			std::vector<std::shared_ptr<CE::ISprite>> cuello;
			std::shared_ptr<CE::ISprite> craneo;

			std::shared_ptr<CE::ISprite> fondo_1;
			bool uno = true;
			std::shared_ptr<CE::ISprite> fondo_2;
			bool dos = false;
			std::shared_ptr<CE::ISprite> fondo_3;
			bool tres = false;

			int periodo_prev = 1;

			float tiempo{};
			float max_tiempo{};
	};
}
