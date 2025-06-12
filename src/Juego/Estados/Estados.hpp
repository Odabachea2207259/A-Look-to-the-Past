#pragma once
#include "../Figuras/Figuras.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"

namespace IVJ
{
    class Dinosaurio;
    class Estado : public Rectangulo
    {
        public:
            explicit Estado(const sf::Color& relleno,const  sf::Color& contorno)
            :Rectangulo{6.f,6.f,relleno,contorno}{}

            int turnos = 0;
            bool permanente = false;

        public:
            virtual void aplicarEstado(std::shared_ptr<IVJ::Dinosaurio> principal)=0;
    };

    class Sangrado : public Estado
    {
        public:
            explicit Sangrado()
            :Estado{sf::Color::Red,sf::Color::Red}
            {
                turnos = 1;
                permanente = true;
            }

            void aplicarEstado(std::shared_ptr<IVJ::Dinosaurio> principal);
    };

    class Dormido : public Estado
    {
        public:
            explicit Dormido()
            :Estado{sf::Color::Magenta,sf::Color::Magenta}
            {
                turnos = 1;
                permanente = true;
            }

            void aplicarEstado(std::shared_ptr<IVJ::Dinosaurio> principal);
    };

    class Aturdido : public Estado
    {
        public:
            explicit Aturdido()
            :Estado{sf::Color::Yellow,sf::Color::Yellow}
            {
                turnos = 2;
            }

            void aplicarEstado(std::shared_ptr<IVJ::Dinosaurio> principal);
    };
}