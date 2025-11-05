#include "Log.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../../Motor/Render/Render.hpp"
#include <iostream>

namespace IVJ
{
    Log& Log::Get()
    {
        if(!instancia)
        {
            instancia = new Log();
        }
        return *instancia;
    }

    Log::Log()
    {
        //log = std::make_unique<IVJ::Rectangulo>();
        texto = std::make_unique<std::string>();

        //textos = std::make_unique<std::vector<CE::ITexto>>(CE::GestorAssets::Get().getFont("Caveman"),"");

        log = std::make_unique<Rectangulo>(500.f,100.f,sf::Color::Green,sf::Color::Black);
        auto tam = CE::Render::Get().GetVentana().getSize();
        log->setPosicion((tam.x/2.f)-250.f,40.f);
    }

    void Log::Terminar()
    {
        delete instancia;
        //instancia = nullptr;
    }
}
