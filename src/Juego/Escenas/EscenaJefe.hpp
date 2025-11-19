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
    class EscenaJefe :public CE::Escena
    {
        public:
            EscenaJefe():CE::Escena{}{};
            void onInit();
            void onFinal();
            void onUpdate(float dt);
            void onInputs(const CE::Botones& accion);
            void onRender();
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

            std::shared_ptr<CE::ITexto> turnosDisponibles;

            std::shared_ptr<IVJ::Rectangulo> nivelActual;
            std::shared_ptr<IVJ::Rectangulo> medidor;

            std::shared_ptr<IVJ::Entidad> enemSelecc = nullptr;
            std::shared_ptr<IVJ::Entidad> playerSelecc = nullptr;
            std::shared_ptr<Habilidad> habilidadSelecc = nullptr;
            bool habilidadActiva = false;

            bool cotyVivo = true;

            bool eSelecc;
            bool pSelecc;

            int cantDinos = 0;
            int dinoTurno = 0;
            int turnosTotales;
            std::vector<std::shared_ptr<IVJ::Entidad>> turnos;
            std::vector<std::shared_ptr<CE::ISprite>> queue;
            std::shared_ptr<CE::ISprite> enteActual;
        private:
            void cambiarTurno();
            void posicionarEntes();
            void posicionarQueue();
    };
}
