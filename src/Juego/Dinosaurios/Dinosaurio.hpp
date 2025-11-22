#pragma once
#include "../Objetos/Entidad.hpp"
#include "../Habilidades/Habilidad.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../Componentes/IJComponentes.hpp"
#include "../Maquinas/IdleFSM.hpp"
#include "../Sistemas/Sistemas.hpp"

#include <vector>
#include <memory>

namespace IVJ
{
    class Habilidad;

    class Dinosaurio : public Entidad
    {
        public:
            Dinosaurio(/*int*/float nivel){
                esDino = true;
                this->addComponente(std::make_shared<CE::ISelectores>());
                this->addComponente(std::make_shared<CE::IPersonaje>());
                this->getComponente<CE::ISelectores>()->vida_max.setSize(sf::Vector2f(100.f, 10.f));  // Tamaño total de la barra
                this->getComponente<CE::ISelectores>()->vida_max.setFillColor(sf::Color(0,0,0,100));
                
                this->getComponente<CE::ISelectores>()->vida.setSize(sf::Vector2f(100.f, 10.f));      // Al inicio, vida completa
                this->getComponente<CE::ISelectores>()->vida.setFillColor(sf::Color::Green);

                this->getComponente<CE::IPersonaje>()->nivel = nivel;
            }
        
        public:
            void acomodarBoton(std::shared_ptr<Habilidad> mov, int i);
            void acomodarHabilidadEspecial(std::shared_ptr<Habilidad> mov);

            void agregarComponentes(const std::string& nombre, int w, int h, float escala)
            {
		        this->addComponente(std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura(nombre),w,h,escala));
                this->addComponente(std::make_shared<CE::IControl>());
                this->addComponente(std::make_shared<IVJ::IMaquinaEstado>());
                this->addComponente(std::make_shared<CE::IEstados>());
                this->addComponente(std::make_shared<CE::IHabilidades>());
                this->addComponente(std::make_shared<CE::ISonido>());

                auto sonidos = this->getComponente<CE::ISonido>();
                sonidos->muerte = "sonido_muerte";
                sonidos->ataque = nombre + "_ataque";

		        auto &fsm_init = this->getComponente<IMaquinaEstado>()->fsm;
		        fsm_init = std::make_shared<IdleFSM>();
		        fsm_init->onEntrar(*this);
            }

            virtual void agregarHabilidades(){};
    };

    class Pachycephalosaurus : public Dinosaurio
    {
        public:
            Pachycephalosaurus(/*int*/float nivel):Dinosaurio(nivel)
            {
                auto nombre = this->getNombre();
		        nombre->nombre = "Pachycephalosaurus";
                agregarComponentes("pachy",315,296,0.8f);
                agregarHabilidades();

                getComponente<CE::IPersonaje>()->tieneAtaquesGratis = false;
                getComponente<CE::IPersonaje>()->tipo = TipoEnte::Atacante;

                IVJ::SistemaConfigurarStats(this,100.f,15.f,15.f,4.f);
            }

            void agregarHabilidades();
    };

    class Parasaurolophus : public Dinosaurio
    {
        public:
            Parasaurolophus(/*int*/float nivel):Dinosaurio(nivel)
            {
		        auto nombre = this->getNombre();
		        nombre->nombre = "Parasaurolophus";
                agregarComponentes("parasaurolophus",303,263,0.8f);
                agregarHabilidades();

                getComponente<CE::IPersonaje>()->tipo = TipoEnte::Healer;

                IVJ::SistemaConfigurarStats(this,150.f,10.f,10.f,1.f);
            }

            void agregarHabilidades();
    };

    class Centrosaurus : public Dinosaurio
    {
        public:
            Centrosaurus(/*int*/float nivel):Dinosaurio(nivel)
            {
		        auto nombre = this->getNombre();
		        nombre->nombre = "Centrosaurus";
                agregarComponentes("centrosaurus",303,226,0.8f);
                agregarHabilidades();

                getComponente<CE::IPersonaje>()->tipo = TipoEnte::Atacante;

                IVJ::SistemaConfigurarStats(this,200.f,20.f,5.f,5.f);
            }

            void agregarHabilidades();
    };

    class Carnotauro : public Dinosaurio
    {
        public:
            Carnotauro(/*int*/float nivel):Dinosaurio(nivel)
            {
		        auto nombre = this->getNombre();
		        nombre->nombre = "Carnotauro";
                agregarComponentes("carnotauro",297,251,0.8f);
                agregarHabilidades();

                getComponente<CE::IPersonaje>()->tipo = TipoEnte::Atacante;

                IVJ::SistemaConfigurarStats(this,100.f,15.f,20.f,2.f);
            }

            void agregarHabilidades();
    };
}