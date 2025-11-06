#pragma once
#include "../Figuras/Figuras.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
//#include "../../Motor/Componentes/IComponentes.hpp"

namespace IVJ
{
    class Dinosaurio;
    class Estado : public Rectangulo
    {
        public:
            explicit Estado(const sf::Color& relleno,const  sf::Color& contorno)
            :Rectangulo{15.f,15.f,relleno,contorno}{} //Revisar tamaño

            int turnos = 0;
            bool permanente = false;
            bool curable = true;

        public:
            //virtual void aplicarEstado(std::shared_ptr<IVJ::Dinosaurio> principal)=0;
            virtual void aplicarEstado(std::shared_ptr<IVJ::Entidad> principal)=0;
    };

    class Sangrado : public Estado
    {
        public:
            explicit Sangrado()
            :Estado{sf::Color::Red,sf::Color::Red}
            {
                turnos = 1;
                permanente = true;

                this->addComponente(std::make_shared<CE::ISprite>(
                    CE::GestorAssets::Get().getTextura("sangrado"),
                    100.f,100.f,
                    0.25f
                ));
            }

            //void aplicarEstado(std::shared_ptr<IVJ::Dinosaurio> principal);
            void aplicarEstado(std::shared_ptr<IVJ::Entidad> principal);
    };

    class Dormido : public Estado
    {
        public:
            explicit Dormido()
            :Estado{sf::Color::Magenta,sf::Color::Magenta}
            {
                turnos = 1;
                permanente = true;

                this->addComponente(std::make_shared<CE::ISprite>(
                    CE::GestorAssets::Get().getTextura("dormido"),
                    100.f,100.f,
                    0.25f
                ));
            }

            //void aplicarEstado(std::shared_ptr<IVJ::Dinosaurio> principal);
            void aplicarEstado(std::shared_ptr<IVJ::Entidad> principal);
    };

    class Aturdido : public Estado
    {
        public:
            explicit Aturdido()
            :Estado{sf::Color::Yellow,sf::Color::Yellow}
            {
                turnos = 2;

                this->addComponente(std::make_shared<CE::ISprite>(
                    CE::GestorAssets::Get().getTextura("aturdido"),
                    100.f,100.f,
                    0.25f
                ));
            }

            //void aplicarEstado(std::shared_ptr<IVJ::Dinosaurio> principal);
            void aplicarEstado(std::shared_ptr<IVJ::Entidad> principal);
    };
}