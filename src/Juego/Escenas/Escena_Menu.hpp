#pragma once
#include "../Figuras/Figuras.hpp"
#include "../Objetos/Pais.hpp"
#include "../Objetos/Periodos.hpp"
#include "../../Motor/Primitivos/Escena.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../Objetos/Quests.hpp"

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

			void tutorial(float dt);
			void game(float dt);
		private:
			bool inicializar{true};
			std::vector<std::shared_ptr<Pais>> paises;
			bool mouse,mousePressed,mousePrev = false,mouseHover = false,keyPressed = false,keyPrev = false;

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
			int cant_paises = 0, pais_hover = 0;

			float tiempo{};
			float max_tiempo{};
			float ec{};

			std::shared_ptr<IVJ::Rectangulo> tuto_1;
			std::shared_ptr<IVJ::Rectangulo> tuto_2;
			std::shared_ptr<IVJ::Rectangulo> hattie;
			std::shared_ptr<CE::ITexto> texto_tutorial;
			std::vector<CE::Vector2D> pos_tutorial_1;
			std::vector<CE::Vector2D> pos_tutorial_2;
			bool algo = false;
			bool tutoQuest = false;
			bool tutoEnd = false;
			int parrafo = 1;
			int cant_parrafos{23};

			CE::Vector2D mousePos;
	};
}
