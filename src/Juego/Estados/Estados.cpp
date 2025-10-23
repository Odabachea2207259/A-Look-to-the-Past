#include "Estados.hpp"

namespace IVJ
{
    void Sangrado::aplicarEstado(std::shared_ptr<Dinosaurio> principal)
    {
        //principal->quitarVida(principal->getStats()->hp * 0.2);
        principal->getStats()->hp -= principal->getStats()->hp * 0.2;
    }

    void Dormido::aplicarEstado(std::shared_ptr<Dinosaurio> principal)
    {
        int prob = rand() % 100 + 1;
        if(prob >= 50)
            principal->getComponente<CE::IEstados>()->dormido = true;
        
    }

    void Aturdido::aplicarEstado(std::shared_ptr<Dinosaurio> principal)
    {
        principal->getComponente<CE::IEstados>()->aturdido = true;
    }
}