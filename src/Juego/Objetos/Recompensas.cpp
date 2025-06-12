#include "Recompensas.hpp"
#include <iostream>

namespace IVJ
{
    Recompensas& Recompensas::Get()
    {
        if(!instancia)
        {
            instancia = new Recompensas();
        }
        return *instancia;
    }

    Recompensas::Recompensas()
    {
        recompensa = std::make_unique<Recompensas::Rewards>(NADA);
    }

    void Recompensas::Terminar()
    {
        delete instancia;
        //instancia = nullptr;
    }

    Recompensas::Rewards& Recompensas::GetRecompensa(void)
    {
        return *recompensa;
    }
}
