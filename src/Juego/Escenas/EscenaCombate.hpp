#pragma once
#include "../../Motor/Primitivos/Escena.hpp"
#include "../Objetos/Entidad.hpp"
#include "../Figuras/Figuras.hpp"
#include "../Objetos/TileMap.hpp"
#include "../Habilidades/Habilidad.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"
#include "../Objetos/Jugador.hpp"
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
        private:
            bool mouse = false,mousePressed = false,mousePrev = false, botonMouseAnterior = false;

            bool inicializar{true};
            sf::ConvexShape selector;
            bool mostrarSelector = false;
            sf::RectangleShape rectanguloDino;
            float ancho,alto;
            std::shared_ptr<IVJ::Entidad> actual;
            TileMap bg[4];
	        sf::RectangleShape fondo;
            std::vector<std::shared_ptr<Rectangulo>> vector_botones;
            std::vector<std::shared_ptr<CE::ITexto>> textos;
            std::shared_ptr<CE::ITexto> dinoPuntos;

            std::shared_ptr<IVJ::Rectangulo> log;
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
        private:
            void cambiarTurno();
            void posicionarEntes();
    };
}
