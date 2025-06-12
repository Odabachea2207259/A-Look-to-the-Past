#pragma once
#include "../Figuras/Figuras.hpp"
#include "../Dinosaurios/Dinosaurio.hpp"
#include "../Estados/Estados.hpp"
#include "../../Motor/Primitivos/Objetos.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"

#include <ctime>

namespace IVJ
{
    enum TipoHabilidad
    {
        Attack,
        Debuffeo,
        Buffeo,
        EspecialAtaque,
        EspecialBuff
    };

    class Dinosaurio;
    class Habilidad : public Rectangulo
    {
        public:
            explicit Habilidad(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Rectangulo{ancho, largo,relleno,contorno}{}
            float curacion = 0;
            float damage = 0;
            int dinoPuntos = 0;
            int medidor = 0;
            TipoHabilidad tipo;

            bool seleccionado = false;
        
        public:
            virtual bool accion(std::shared_ptr<IVJ::Dinosaurio> principal, std::shared_ptr<IVJ::Dinosaurio> target,float dt)=0;
            virtual void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)=0;
    };

/*---------------------------------------------------ATAQUES---------------------------------------------------*/

    class Ataque : public Habilidad
    {
        public:
            explicit Ataque(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Habilidad{ancho, largo,relleno,contorno}{
                tipo = Attack;
            }
        
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)=0;
            bool accion(std::shared_ptr<IVJ::Dinosaurio> principal, std::shared_ptr<IVJ::Dinosaurio> target,float dt);  
    };

    class Embestida : public Ataque
    {
        public:
            explicit Embestida(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Ataque{ancho,largo,relleno,contorno}{
                damage = 15.f;
                dinoPuntos = 1;

                auto nombre = getNombre();
                nombre->nombre = "Embestida";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //Mordisco
    class Mordisco : public Ataque
    {
        public:
            explicit Mordisco(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Ataque{ancho,largo,relleno,contorno}{
                damage = 10.f;
                dinoPuntos = 0;

                auto nombre = getNombre();
                nombre->nombre = "Mordisco";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //SuperMordisco - Habilidad especial de Carnotauro
    class SuperMordisco : public Ataque
    {
        public:
            explicit SuperMordisco(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Ataque{ancho,largo,relleno,contorno}{
                damage = 200.f;
                medidor = 200;
                tipo = EspecialAtaque;

                auto nombre = getNombre();
                nombre->nombre = "SuperMordisco";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //Cabezazo
    class Cabezazo : public Ataque
    {
        public:
            explicit Cabezazo(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Ataque{ancho,largo,relleno,contorno}{
                damage = 20.f;
                dinoPuntos = 3;

                auto nombre = getNombre();
                nombre->nombre = "Cabezazo";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //SuperCabezazo - HABILIDAD ESPECIAL DE PACHY
    class SuperCabezazo : public Ataque
    {
        public:
            explicit SuperCabezazo(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Ataque{ancho,largo,relleno,contorno}{
                damage = 50.f;
                medidor = 100;
                tipo = EspecialAtaque;

                auto nombre = getNombre();
                nombre->nombre = "SuperCabezazo";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);   
    };

    //Punzada
    class Punzada : public Ataque
    {
        public:
            explicit Punzada(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Ataque{ancho,largo,relleno,contorno}{
                damage = 40.f;
                dinoPuntos = 5;

                auto nombre = getNombre();
                nombre->nombre = "Punzada";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //SuperPunzada - Habilidad Especial de Centrosaurus
    class SuperPunzada : public Ataque
    {
        public:
            explicit SuperPunzada(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Ataque{ancho,largo,relleno,contorno}{
                damage = 100.f;
                medidor = 150;
                tipo = EspecialAtaque;

                auto nombre = getNombre();
                nombre->nombre = "SuperPunzada";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

/*------------------------------------------------------DEBUFFS-----------------------------------------------------------*/

    class Debuff : public Habilidad
    {
        public:
            explicit Debuff(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Habilidad{ancho, largo,relleno,contorno}{
                tipo = Debuffeo;
            }
        
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)=0;
            bool accion(std::shared_ptr<IVJ::Dinosaurio> principal, std::shared_ptr<IVJ::Dinosaurio> target,float dt);   
    };

    //Rugido
    class Rugido : public Debuff
    {
        public:
            explicit Rugido(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Debuff{ancho,largo,relleno,contorno}{
                dinoPuntos = 2;

                auto nombre = getNombre();
                nombre->nombre = "Rugido";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //Canto
    class Canto : public Debuff
    {
        public:
            explicit Canto(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Debuff{ancho,largo,relleno,contorno}{
                dinoPuntos = 3;

                auto nombre = getNombre();
                nombre->nombre = "Canto";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

/*---------------------------------------------------BUFFS---------------------------------------------------------------*/

    class Buff : public Habilidad
    {
        public:
            explicit Buff(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Habilidad{ancho, largo,relleno,contorno}{
                tipo = Buffeo;
            }
        
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)=0;
            bool accion(std::shared_ptr<IVJ::Dinosaurio> principal, std::shared_ptr<IVJ::Dinosaurio> target,float dt);   
    };

    class Valor : public Buff
    {
        public:
            explicit Valor(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Buff{ancho,largo,relleno,contorno}{
                dinoPuntos = 1;

                auto nombre = getNombre();
                nombre->nombre = "Valor";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //Impulso
    class Impulso : public Buff
    {
        public:
            explicit Impulso(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Buff{ancho,largo,relleno,contorno}{
                dinoPuntos = 1;

                auto nombre = getNombre();
                nombre->nombre = "Impulso";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //Sanar
    class Sanar : public Buff
    {
        public:
            explicit Sanar(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Buff{ancho,largo,relleno,contorno}{
                dinoPuntos = 1;

                auto nombre = getNombre();
                nombre->nombre = "Sanar";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //Curar
    class Curar : public Buff
    {
        public:
            explicit Curar(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Buff{ancho,largo,relleno,contorno}{
                dinoPuntos = 2;

                auto nombre = getNombre();
                nombre->nombre = "Curar";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //Renacer - Habilidad especial de Parasaurolophus
    class Renacer : public Buff
    {
        public:
            explicit Renacer(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Buff{ancho,largo,relleno,contorno}{
                medidor = 100;
                tipo = EspecialBuff;

                auto nombre = getNombre();
                nombre->nombre = "Renacer";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

    //Adrenalina
    class Adrenalina : public Buff
    {
        public:
            explicit Adrenalina(float ancho, float largo,const sf::Color& relleno,const  sf::Color& contorno)
            :Buff{ancho,largo,relleno,contorno}{
                dinoPuntos = 3;

                auto nombre = getNombre();
                nombre->nombre = "Adrenalina";
            }
        public:
            void realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target);
    };

}