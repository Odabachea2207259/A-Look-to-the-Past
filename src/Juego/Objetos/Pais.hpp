#pragma once
#include "../Figuras/Figuras.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"

namespace IVJ
{
    class Pais : public IVJ::Rectangulo
    {
        public:
            explicit Pais(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno,bool desbloqueado, int precio);
            bool desbloqueado;
            int precio;
            std::vector<std::shared_ptr<Dinosaurio>> dinosaurios;
        
        public:
            Dinosaurio getDinosaurio();
            bool mostrarPrecio = false;
            int cantClics = 0;

        public:
            void dinosCan();
            void dinosUsa();
            void dinosMex();
            void dinosArg();
    };
}
