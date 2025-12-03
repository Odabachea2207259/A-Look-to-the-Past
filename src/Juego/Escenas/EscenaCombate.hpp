#pragma once
#include "../../Motor/Primitivos/Escena.hpp"
#include "../Objetos/Entidad.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Objetos/TileMap.hpp"
#include "../Habilidades/Habilidad.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"
#include "../Objetos/Jugador.hpp"
#include "../Objetos/Log.hpp"
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Window/Export.hpp>
#include <vector>
namespace IVJ
{
    class EscenaCombate :public CE::Escena
    {
        public:
            EscenaCombate():CE::Escena{}{};
            void onInit();
            void onFinal();
            void onUpdate(float dt);
            void onInputs(const CE::Botones& accion);
            void onRender();

            void game(float dt);
            void tutorial(float dt);
        private:
            bool mouse = false,mousePressed = false,mousePrev = false, botonMouseAnterior = false;

            bool inicializar{true};
            
            bool mostrarSelector = false;
            std::shared_ptr<CE::ISprite> dinoSelector;
            sf::ConvexShape selector;
            sf::RectangleShape rectanguloDino;
            float ancho,alto;

            std::shared_ptr<IVJ::Entidad> actual;

            TileMap bg[4];
	        sf::RectangleShape fondo;
            sf::RectangleShape fondoQueue;
            std::shared_ptr<IVJ::Rectangulo> fondoDP;
            std::shared_ptr<CE::ITexto> stats;
            std::shared_ptr<IVJ::Rectangulo> tooltip;

            std::shared_ptr<IVJ::Rectangulo> nivelActual;
            std::shared_ptr<IVJ::Rectangulo> medidor;

            std::shared_ptr<IVJ::Entidad> enemSelecc = nullptr;
            std::shared_ptr<IVJ::Entidad> playerSelecc = nullptr;
            std::shared_ptr<Habilidad> habilidadSelecc = nullptr;
            bool habilidadActiva = false;

            bool eSelecc;
            bool pSelecc;

            int cantDinos = 0;
            int dinoTurno = 0;

            std::vector<std::shared_ptr<Entidad>> turnos;
            std::vector<std::shared_ptr<CE::ISprite>> queue;
            std::shared_ptr<CE::ISprite> enteActual;

			std::shared_ptr<IVJ::Rectangulo> tuto_1;
			std::shared_ptr<IVJ::Rectangulo> tuto_2;
			std::shared_ptr<IVJ::Rectangulo> hattie;
			std::shared_ptr<CE::ITexto> texto_tutorial;
            std::vector<CE::Vector2D> pos_tutorial_1;
			bool algo = false;
			int parrafo = 1;
			int cant_parrafos{37};
            float ec{};
        private:
            void cambiarTurno();
            void posicionarEntes();
            void posicionarQueue();
    };
}