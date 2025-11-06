#include "Habilidad.hpp"
#include "../Objetos/Log.hpp"

namespace IVJ
{
/*----------------------------------------------------ACCION DE MOVIMIENTO DE CADA TIPO DE HABILIDAD------------------------------------------*/
    bool Ataque::accion(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt)
    {
        auto c_principal = principal->getComponente<CE::IControl>();
        auto c_target = target->getComponente<CE::IControl>();

        auto trans_principal = principal->getTransformada();
        auto trans_target = target->getTransformada();

        float velocidadDefault = 800.f;
        if(c_principal->accion){        

            auto direccion = trans_target->posicion - trans_principal->posicion;
            if(trans_target->posicion.x > trans_principal->posicion.x)
                c_principal->der = true;
            else
                c_principal->izq = true;

            float magnitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

            if(magnitud != 0.f)
            {
                direccion.x /= magnitud;
                direccion.y /= magnitud;
            }

            CE::Vector2D velocidad(direccion.x*velocidadDefault,direccion.y*velocidadDefault);

            if(magnitud > 100.f)
            {
                auto cpy = velocidad;
                trans_principal->posicion.suma(cpy.escala(dt));
                return true;
            }
            
            c_principal->der = false;
            c_principal->izq = false;
            c_principal->acc = true;
            c_target->damage = true;
            realizarMov(principal,target);

            int damage = target->getStats()->hp_prev - target->getStats()->hp;
            *IVJ::Log::Get().texto = principal->getNombre()->nombre + "\nredujo " + std::to_string(damage) + " puntos de HP a \n" + target->getNombre()->nombre;
            IVJ::Log::Get().buff = false;

            target->getStats()->hp_prev = target->getStats()->hp;
            if(target->getComponente<CE::IPersonaje>()->especial) 
            {
                auto esp = target->getComponente<CE::IPersonaje>()->target;
                esp->getComponente<CE::IControl>()->ataque = "Mordisco";
                esp->getComponente<CE::IControl>()->acc = true;
                SistemaQuitarVida(principal,esp->getStats()->str);

                if(!principal->estaVivo()) return false;
            }
            c_principal->accion = false;
        }

        if(c_principal->acc)
            return true;

        auto pos_original = trans_principal->pos_original;

        auto direccion = pos_original - trans_principal->posicion;

        if(pos_original.x > trans_principal->posicion.x)
            c_principal->der = true;
        else
            c_principal->izq = true;

        float magnitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);

        if(magnitud != 0.f)
        {
            direccion.x /= magnitud;
            direccion.y /= magnitud;
        }
        CE::Vector2D velocidad(direccion.x*velocidadDefault,direccion.y*velocidadDefault);
        if(magnitud > 15.f)
        {
            auto cpy = velocidad;
            trans_principal->posicion.suma(cpy.escala(dt));
            return true;
        }

        auto c_sprite = principal->getComponente<CE::ISprite>();
        
        c_principal->der = false;
        c_principal->izq = false;

        return false;
    }

    bool Buff::accion(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt)
    {
        auto c_principal = principal->getComponente<CE::IControl>();

        if(c_principal->accion)
        {
            c_principal->sacc = true;
            c_principal->accion = false;
        }

        if(c_principal->sacc)
            return true;
        
        realizarMov(principal,target);
        *IVJ::Log::Get().texto = principal->getNombre()->nombre + "\nuso " + this->nombre->nombre + " en\n" + target->getNombre()->nombre;
        IVJ::Log::Get().buff = true;
        target->getStats()->hp_prev = target->getStats()->hp;

        return false;
    }

    bool Debuff::accion(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt)
    {
        auto c_principal = principal->getComponente<CE::IControl>();
        auto c_target = target->getComponente<CE::IControl>();

        if(c_principal->accion) 
        {
            c_principal->sacc = true;
            c_principal->accion = false;
        }

        if(c_principal->sacc)
        {
            c_target->damage = true;
            return true;
        }
        if(c_target->damage)
        return true;
        
        realizarMov(principal,target);
        *IVJ::Log::Get().texto = principal->getNombre()->nombre + "\nuso " + this->nombre->nombre + " en\n" + target->getNombre()->nombre;
        IVJ::Log::Get().buff = false;
        return false;
    }

/*-------------------------------------------------ATAQUES--------------------------------------------------------------------*/

    void Embestida::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {        
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        SistemaQuitarVida(target,damage+principal->getStats()->str);
        
    }

    void Mordisco::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {        
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        SistemaQuitarVida(target,damage+principal->getStats()->str);
        
    }

    void SuperMordisco::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        SistemaQuitarVida(target,damage+principal->getStats()->str);
    }

    void Cabezazo::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        SistemaQuitarVida(target,damage+principal->getStats()->str);

        auto estados = target->getComponente<CE::IEstados>();
        estados->estados.push_back(std::make_shared<Aturdido>());
        estados->cantidad++;
    }

    void SuperCabezazo::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->medidor = 0;
        SistemaQuitarVida(target,damage+principal->getStats()->str);
        auto aturdido = std::make_shared<Aturdido>();
        aturdido->turnos = 5;

        auto estados = target->getComponente<CE::IEstados>();
        estados->estados.push_back(aturdido);
        estados->cantidad++;
    }

    void Punzada::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        SistemaQuitarVida(target,damage+principal->getStats()->str);

        auto estados = target->getComponente<CE::IEstados>();
        estados->estados.push_back(std::make_shared<Sangrado>());
        estados->cantidad++;
    }

    void SuperPunzada::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->medidor = 0;
        SistemaQuitarVida(target,damage+principal->getStats()->str);

        auto estados = target->getComponente<CE::IEstados>();
        estados->estados.push_back(std::make_shared<Sangrado>());
        estados->cantidad++;
    }

/*-------------------------------------------------DEBUFFS--------------------------------------------------------------------*/
    void Rugido::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        target->getStats()->str -= 1.f;
        target->getStats()->def -= 1.f;
    }

    void Canto::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;

        auto estados = target->getComponente<CE::IEstados>();
        estados->estados.push_back(std::make_shared<Dormido>());
        estados->cantidad++;
    }
/*-------------------------------------------------BUFFS--------------------------------------------------------------------*/
    void Valor::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        target->getStats()->def += 1.f;
    }

    void Impulso::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        target->getStats()->agi += 1.f;
    }

    void Sanar::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        SistemaAgregarVida(target,10.f);
    }

    void Curar::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;

        auto estados = target->getComponente<CE::IEstados>();
        
        estados->estados.erase(
            std::remove_if(estados->estados.begin(), estados->estados.end(),
            [](const std::shared_ptr<Estado>& estado) {
                return estado->curable;
            }),
		    estados->estados.end());
        
        estados->cantidad = (int)(estados->estados.size());
        }

    void Renacer::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->medidor = 0;
        target->getStats()->hp = target->getStats()->hp_max;
        target->getComponente<CE::IJugador>()->dinoPuntos = 15;

        auto estados = target->getComponente<CE::IEstados>();

        estados->estados.erase(
		    std::remove_if(estados->estados.begin(), estados->estados.end(),
		        [](const std::shared_ptr<Estado>& estado) {
		            return estado->curable;
		        }),
		    estados->estados.end());
        estados->cantidad = (int)(estados->estados.size());
    }

    void Adrenalina::realizarMov(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target)
    {
        if(principal->tieneComponente<CE::IJugador>()) principal->getComponente<CE::IJugador>()->dinoPuntos -= this->dinoPuntos;
        target->getStats()->str += 1.f;
        target->getStats()->def += 1.f;
        target->getStats()->agi += 1.f;
    }
}