#pragma once
#include"../Motor/App/ALayer.hpp"
#include <vector>
#include "Figuras/Figuras.hpp"
#include <memory>
#include "../Motor/Primitivos/Escena.hpp"

namespace IVJ
{
    class Juego: public CE::GameLayer
    {
        public:
            explicit Juego();
            void OnInit(void);
            void OnInputs(float dt ,std::optional<sf::Event>& eventos);
            void OnInputs(float dt);
            void OnUpdate(float dt);
            void OnRender(float dt);
        private:
	    CE::Escena* escena_actual;
    };

}

