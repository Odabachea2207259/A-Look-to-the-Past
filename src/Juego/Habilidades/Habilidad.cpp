#include "Habilidad.hpp"
namespace IVJ
{
/*----------------------------------------------------ACCION DE MOVIMIENTO DE CADA TIPO DE HABILIDAD------------------------------------------*/
    bool Ataque::accion(std::shared_ptr<IVJ::Dinosaurio> principal, std::shared_ptr<IVJ::Dinosaurio> target, float dt)
    {
        auto c_principal = principal->getComponente<CE::IControl>();
        auto c_target = target->getComponente<CE::IControl>();

        auto trans_principal = principal->getTransformada();
        auto trans_target = target->getTransformada();

        float velocidadDefault = 800.f;
        if(principal->accion){        

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
            principal->accion = false;
        }

        if(c_principal->acc)
            return true;

        auto pos_original = principal->pos_original;

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

    bool Buff::accion(std::shared_ptr<IVJ::Dinosaurio> principal, std::shared_ptr<IVJ::Dinosaurio> target, float dt)
    {
        auto c_principal = principal->getComponente<CE::IControl>();

        if(principal->accion)
        {
            c_principal->sacc = true;
            principal->accion = false;
        }

        if(c_principal->sacc)
            return true;
        realizarMov(principal,target);

        return false;
    }

    bool Debuff::accion(std::shared_ptr<IVJ::Dinosaurio> principal, std::shared_ptr<IVJ::Dinosaurio> target, float dt)
    {
        auto c_principal = principal->getComponente<CE::IControl>();
        auto c_target = target->getComponente<CE::IControl>();

        if(principal->accion) 
        {
            c_principal->sacc = true;
            principal->accion = false;
        }

        if(c_principal->sacc)
        {
            c_target->damage = true;
            return true;
        }
        if(c_target->damage)
        return true;
        
        realizarMov(principal,target);
        return false;
    }

/*-------------------------------------------------ATAQUES--------------------------------------------------------------------*/

    void Embestida::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        target->quitarVida(damage+principal->getStats()->str);
    }

    void Mordisco::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        target->quitarVida(damage+principal->getStats()->str);
    }

    void SuperMordisco::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->medidor = 0;
        target->quitarVida(damage+principal->getStats()->str);
    }

    void Cabezazo::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        target->quitarVida(damage+principal->getStats()->str);
        //Aqui se haria algo como ponerle el estado de Aturdido
        target->estados.push_back(std::make_shared<Aturdido>());
    }

    void SuperCabezazo::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->medidor = 0;
        target->quitarVida(damage+principal->getStats()->str);
        //Aqui se haria algo como ponerle el estado de Aturdido
        auto aturdido = std::make_shared<Aturdido>();
        aturdido->turnos = 5;
        target->estados.push_back(aturdido);
    }

    void Punzada::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        target->quitarVida(damage+principal->getStats()->str);
        //Aqui se haria algo como ponerle el estado de Sangrado
        target->estados.push_back(std::make_shared<Sangrado>());
    }

    void SuperPunzada::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->medidor = 0;
        target->quitarVida(damage+principal->getStats()->str);
        //Aqui se haria algo como ponerle el estado de Sangrado
        target->estados.push_back(std::make_shared<Sangrado>());
    }

/*-------------------------------------------------DEBUFFS--------------------------------------------------------------------*/
    void Rugido::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        target->getStats()->str -= 1.f;
        target->getStats()->def -= 1.f;
    }

    void Canto::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        //Ponde Dormido
        target->estados.push_back(std::make_shared<Dormido>());
    }
/*-------------------------------------------------BUFFS--------------------------------------------------------------------*/
    void Valor::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        target->getStats()->def += 1.f;
    }

    void Impulso::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        target->getStats()->agi += 1.f;
    }

    void Sanar::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        target->agregarVida(10.f);
    }

    void Curar::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        //Quita estados
        target->estados.clear();
    }

    void Renacer::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->medidor = 0;
        //Quita estados
        target->estados.clear();
        target->getStats()->hp = target->getStats()->hp_max;
        target->dinoPuntos = 15;
        //Poner estado de regenerar
    }

    void Adrenalina::realizarMov(std::shared_ptr<IVJ::Dinosaurio> principal,std::shared_ptr<IVJ::Dinosaurio> target)
    {
        if(principal->jugador) principal->dinoPuntos -= this->dinoPuntos;
        target->getStats()->str += 1.f;
        target->getStats()->def += 1.f;
        target->getStats()->agi += 1.f;
    }
}