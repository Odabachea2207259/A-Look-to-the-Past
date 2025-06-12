#pragma once
#include <SFML/Graphics.hpp>
#include "../../Motor/Utils/Utils.hpp"
#include "../../Motor/Utils/Vector2D.hpp"
#include "Jugador.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"

#include<memory>
namespace IVJ
{
    class Equipos
    {
        public:
            static Equipos& Get(void);
            static void Terminar(void);

            std::vector<std::shared_ptr<Dinosaurio>>& GetPlayer();
            std::vector<std::shared_ptr<Dinosaurio>>& GetEnemigos();
            std::shared_ptr<Habilidad> GetHabilidadEsp();
            std::shared_ptr<Dinosaurio>& GetDinoLider();
            
            void crearEnemigos();
        private:
            Equipos();
            static inline Equipos* instancia =nullptr;
            std::unique_ptr<std::vector<std::shared_ptr<Dinosaurio>>> player;
            std::unique_ptr<std::vector<std::shared_ptr<Dinosaurio>>> enemigos;
            std::shared_ptr<Habilidad> habilidadEspecial;
            std::shared_ptr<Dinosaurio> dinoLider;
    };
}
