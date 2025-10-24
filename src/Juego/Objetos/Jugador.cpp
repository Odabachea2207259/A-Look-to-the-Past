#include "Jugador.hpp"
#include <iostream>

namespace IVJ
{
    Jugador& Jugador::Get()
    {
        if(!instancia)
        {
            instancia = new Jugador();
        }
        return *instancia;
    }

    Jugador::Jugador()
    {
        dinero = std::make_unique<int>(0);
        nivel = std::make_unique<int>(0);
        periodo = std::make_unique<int>(1);
        checkpoint = std::make_unique<int>(1);
        dinosaurios = std::make_unique<std::vector<std::shared_ptr<Dinosaurio>>>();
    }

    void Jugador::Terminar()
    {
        delete instancia;
        //instancia = nullptr;
    }

    int& Jugador::GetDinero(void)
    {
        return *dinero;
    }

    int& Jugador::GetNivel(void)
    {
        return *nivel;
    }

    int& Jugador::GetPeriodo(void)
    {
        return *periodo;
    }

    int& Jugador::GetCheckpoint(void)
    {
        return *checkpoint;
    }

    std::vector<std::shared_ptr<Dinosaurio>>& Jugador::GetDinosaurios() 
    {
        return *dinosaurios;
    }
}
