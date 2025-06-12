#pragma once
#include <SFML/Graphics.hpp>
#include "../../Motor/Utils/Utils.hpp"
#include "../../Motor/Utils/Vector2D.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"

#include <algorithm>
#include <random>
#include <ctime>
#include<memory>

namespace IVJ
{
    class Recompensas
    {
        public:

            enum Rewards
            {
                DINERO,
                REGENERAR,
                AUMENTAR,
                NADA,
                CANTIDAD
            };
            static Recompensas& Get(void);
            static void Terminar(void);
            Recompensas::Rewards& GetRecompensa(void);
            static std::vector<Rewards> GetTodasLasRecompensas() {
                return { DINERO, REGENERAR, AUMENTAR, NADA };
            }

            std::vector<IVJ::Recompensas::Rewards> ObtenerRecompensasUnicas(int cantidad)
            {
                auto todas = IVJ::Recompensas::GetTodasLasRecompensas();

                static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
                std::shuffle(todas.begin(), todas.end(), rng);

                if (cantidad > static_cast<int>(todas.size())) cantidad = todas.size();

                return std::vector<IVJ::Recompensas::Rewards>(todas.begin(), todas.begin() + cantidad);
            }
        private:
            Recompensas();
            static inline Recompensas* instancia =nullptr;
            std::unique_ptr<Recompensas::Rewards> recompensa;
    };
}
