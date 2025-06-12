#pragma once
#include <SFML/Graphics.hpp>
#include "../../Motor/Utils/Utils.hpp"
#include "../../Motor/Utils/Vector2D.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"

#include<memory>
namespace IVJ
{
    class Jugador
    {
        public:
            static Jugador& Get(void);
            static void Terminar(void);
            int& GetDinero(void);
            int& GetNivel(void);
            std::vector<std::shared_ptr<Dinosaurio>>& GetDinosaurios();
        private:
            Jugador();
            static inline Jugador* instancia =nullptr;
            std::unique_ptr<int> dinero;
            std::unique_ptr<int> nivel;
            std::unique_ptr<std::vector<std::shared_ptr<Dinosaurio>>> dinosaurios;
    };
}
