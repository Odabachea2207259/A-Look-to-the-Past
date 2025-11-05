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

        textos = std::make_unique<std::vector<std::shared_ptr<CE::ITexto>>>();

        log = std::make_unique<Rectangulo>(500.f,100.f,sf::Color::Black,sf::Color::Black);
        auto tam = CE::Render::Get().GetVentana().getSize();
        log->setPosicion((tam.x/2.f)-250.f,40.f);
    }

    void Log::Terminar()
    {
        delete instancia;
        //instancia = nullptr;
    }

    std::vector<std::shared_ptr<CE::ITexto>>& Log::GetTextos() 
    {
        return *textos;
    }

    void Log::acomodarTextos()
    {
        textos->clear();

        std::string linea;
        for(int i = 0; i < texto->length()+1;i++){
            if(*(texto->begin()+i) == '\n' || i == texto->length())// || *(texto->begin()+i) == ' ')
            {
                textos->push_back(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),linea));
                linea.clear();
            }
            else linea.push_back(*(texto->begin()+i));
        }

        linea.clear();
        int lineas = 0;
        for(auto & texto : *textos)
        {
			//texto->m_texto.setPosition({(tam.x/2.f)-250.f,45.f});
			//texto->m_texto.setPosition({log->getPosicion().x,log->getPosicion().y + (30*lineas)});
			texto->m_texto.setCharacterSize(10);
            lineas++;
            
            sf::FloatRect bounds = texto->m_texto.getLocalBounds();
            texto->m_texto.setOrigin({bounds.position.x + bounds.size.x/2, 0.f});

            texto->m_texto.setPosition({ log->getRectangle().getPosition().x + log->getWidth()/2, log->getRectangle().getPosition().y + (texto->m_texto.getCharacterSize() * lineas * 2.f)});
        }
    }
}
