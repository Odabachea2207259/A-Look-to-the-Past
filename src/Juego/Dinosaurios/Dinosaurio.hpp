#pragma once
#include "../Objetos/Entidad.hpp"
#include "../Habilidades/Habilidad.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
//#include "../../Motor/Primitivos/Objetos.hpp"
#include "../Componentes/IJComponentes.hpp"
#include "../Maquinas/IdleFSM.hpp"

#include <vector>
#include <memory>

namespace IVJ
{
    class Habilidad;
    //class Estado;
    class Dinosaurio : public Entidad
    {
        public:
            Dinosaurio(/*int*/float nivel) : nivel{nivel}{
                esDino = true;
                vida_max.setSize(sf::Vector2f(100.f, 10.f));  // Tamaño total de la barra
                //vida_max.setFillColor(sf::Color::Red);
                vida_max.setFillColor(sf::Color(0,0,0,100));
                
                vida.setSize(sf::Vector2f(100.f, 10.f));      // Al inicio, vida completa
                vida.setFillColor(sf::Color::Green);
            }
            //float medidor = 0; // -> Componente
            /*int*/float nivel;
            //bool jugador = false; // -> Componente
            bool accion = false;
            bool turno = false;
            //bool dormido = false; // -> Componente
            //bool aturdido = false; // -> Componente
            bool tieneAtaquesGratis = true;
            int numDino;
            //int dinoPuntos = 15; // -> Componente
            std::shared_ptr<Habilidad> habilidadSelecc;
            std::shared_ptr<Habilidad> habilidadEspecial;
                        
            std::vector<std::shared_ptr<IVJ::Habilidad>> movimientos;
            //std::vector<std::shared_ptr<Estado>> estados;
            sf::RectangleShape vida;
            sf::RectangleShape vida_max;

            sf::RectangleShape seleccion;
        
        public:
            void mostrarEstados();
            void acomodarBoton(std::shared_ptr<Habilidad> mov, int i);
            void acomodarHabilidadEspecial(std::shared_ptr<Habilidad> mov);
            void subirNivel()
            {
                this->getStats()->hp_max += this->getStats()->hp_max * 0.2;
                this->getStats()->agi_max += 2.f;
                this->getStats()->str_max += 2.f;
                this->getStats()->def_max += 2.f;    
                
                this->nivel++;
                reiniciarStats();
            }
            void reiniciarStats()
            {
                this->getStats()->hp = this->getStats()->hp_max;
                this->getStats()->agi = this->getStats()->agi_max;
                this->getStats()->str = this->getStats()->str_max;
                this->getStats()->def = this->getStats()->def_max;
            }
            void reiniciarDino()
            {
                //medidor = 0;
                //jugador = false;
                //accion = false;
                this->eliminarComponente<CE::IJugador>();
                turno = false;
                //dormido = false;
                //aturdido = false;

                reiniciarStats();
                //estados.clear();

                auto estados = this->getComponente<CE::IEstados>();
                estados->aturdido = false;
                estados->dormido = false;
                estados->estados.clear();

                auto c = this->getComponente<CE::IControl>();
                c->abj = false;
                c->der = false;
                c->arr = false;
                c->izq = false;
                c->acc = false;
                c->sacc = false;
                c->damage = false;
                c->muerte = false;
                c->muerto = false;
                c->accion = false;

		        auto &fsm_init = this->getComponente<IMaquinaEstado>()->fsm;
		        fsm_init = std::make_shared<IdleFSM>();
		        fsm_init->onEntrar(*this);
            }
            void cambiarNivel(int nivel);
            void actualizarVida()
            {   
                float porcentaje = this->getStats()->hp/this->getStats()->hp_max;
                porcentaje = std::max(0.f,porcentaje);
                vida.setSize(sf::Vector2f(vida_max.getSize().x * porcentaje, 10.f));
            }
            void quitarVida(float damage) //-> Sistema
            {
                float realDamage = damage * std::pow(0.9,this->getStats()->def);
                this->getStats()->hp -= realDamage;
            }
            void agregarVida(float vida) // -> Sistema
            {
                if(this->getStats()->hp + vida >= this->getStats()->hp_max)
                    this->getStats()->hp = this->getStats()->hp_max;
                else   
                    this->getStats()->hp += vida;
            }
            void setPosOriginal()
            {
                getTransformada()->pos_original = getTransformada()->posicion;
                auto sprite = this->getComponente<CE::ISprite>();
                auto width = sprite->width;
                auto height = sprite->height;
                vida.setPosition({getTransformada()->pos_original.x - (width/8),getTransformada()->pos_original.y-(height/4)});
                vida_max.setPosition({getTransformada()->pos_original.x - (width/8),getTransformada()->pos_original.y-(height/4)});
            }

            void configurarVida(float vida)
            {
                this->getStats()->hp = vida * nivel;
                this->getStats()->hp_max = vida * nivel;
            }
            void configurarStr(float str)
            {
                this->getStats()->str = str * nivel;
                this->getStats()->str_max = str * nivel;
            }
            void configurarAgi(float agi)
            {
                this->getStats()->agi = agi * nivel;
                this->getStats()->agi_max = agi * nivel;
            }
            void configurarDef(float def)
            {
                this->getStats()->def = def * nivel;
                this->getStats()->def_max = def * nivel;
            }

            void agregarComponentes(const std::string& nombre, int w, int h, float escala)
            {
		        this->addComponente(std::make_shared<CE::ISprite>(CE::GestorAssets::Get().getTextura(nombre),w,h,escala));
                this->addComponente(std::make_shared<CE::IControl>());
                this->addComponente(std::make_shared<IVJ::IMaquinaEstado>());
                this->addComponente(std::make_shared<CE::IEstados>());
                //this->addComponente(std::make_shared<CE::IJugador>()); 
		        auto &fsm_init = this->getComponente<IMaquinaEstado>()->fsm;
		        fsm_init = std::make_shared<IdleFSM>();
		        fsm_init->onEntrar(*this);
            }

            bool aplicarEstados();
            virtual void agregarHabilidades(){};
            virtual bool turnoEnemigo(std::shared_ptr<Dinosaurio> actual,std::vector<std::shared_ptr<Dinosaurio>> player, std::vector<std::shared_ptr<Dinosaurio>> enemigos, float dt){return true;};
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

                tieneAtaquesGratis = false;
                
                configurarVida(100.f);
                configurarStr(15.f);
                configurarAgi(15.f);
                configurarDef(4.f);
            }

            void agregarHabilidades();
            bool turnoEnemigo(std::shared_ptr<Dinosaurio> actual,std::vector<std::shared_ptr<Dinosaurio>> player, std::vector<std::shared_ptr<Dinosaurio>> enemigos, float dt);
    };

    class Parasaurolophus : public Dinosaurio
    {
        public:
            Parasaurolophus(/*int*/float nivel):Dinosaurio(nivel)
            {
                configurarVida(100.f);
		        auto nombre = this->getNombre();
		        nombre->nombre = "Parasaurolophus";
                agregarComponentes("parasaurolophus",303,263,0.8f);
                agregarHabilidades();

                configurarVida(150.f);
                configurarStr(10.f);
                configurarAgi(10.f);
                configurarDef(1.f);
            }

            void agregarHabilidades();
            bool turnoEnemigo(std::shared_ptr<Dinosaurio> actual,std::vector<std::shared_ptr<Dinosaurio>> player, std::vector<std::shared_ptr<Dinosaurio>> enemigos, float dt);
    };

    class Centrosaurus : public Dinosaurio
    {
        public:
            Centrosaurus(/*int*/float nivel):Dinosaurio(nivel)
            {
                configurarVida(100.f);
		        auto nombre = this->getNombre();
		        nombre->nombre = "Centrosaurus";
                agregarComponentes("centrosaurus",303,226,0.8f);
                agregarHabilidades();

                configurarVida(200.f);
                configurarStr(20.f);
                configurarAgi(5.f);
                configurarDef(5.f);
            }

            void agregarHabilidades();
            bool turnoEnemigo(std::shared_ptr<Dinosaurio> actual,std::vector<std::shared_ptr<Dinosaurio>> player, std::vector<std::shared_ptr<Dinosaurio>> enemigos, float dt);
    };

    class Carnotauro : public Dinosaurio
    {
        public:
            Carnotauro(/*int*/float nivel):Dinosaurio(nivel)
            {
                configurarVida(100.f);
		        auto nombre = this->getNombre();
		        nombre->nombre = "Carnotauro";
                agregarComponentes("carnotauro",297,251,0.8f);
                agregarHabilidades();

                configurarVida(100.f);
                configurarStr(15.f);
                configurarAgi(20.f);
                configurarDef(2.f);
            }

            void agregarHabilidades();
            bool turnoEnemigo(std::shared_ptr<Dinosaurio> actual,std::vector<std::shared_ptr<Dinosaurio>> player, std::vector<std::shared_ptr<Dinosaurio>> enemigos, float dt);
    };
}