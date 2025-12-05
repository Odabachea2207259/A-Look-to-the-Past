#include "Quests.hpp"
#include "Jugador.hpp"
#include "../../Motor/Utils/Ventana.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"

namespace IVJ
{
    Quests& Quests::Get()
    {
        if(!instancia)
        {
            instancia = new Quests();
        }
        return *instancia;
    }

    Quests::Quests()
    {
        cant = 0;
        cambios = std::make_unique<bool>(true);
        abierto = std::make_unique<bool>(false);
        
        rect_1 = std::make_shared<IVJ::Rectangulo>(
            50.f,50.f,
            sf::Color(0,0,0,200),
            sf::Color::Black
        );

        rect_1->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("tablet"),
            0.08f
        ));

        auto sprite = rect_1->getComponente<CE::ISprite>();
        sprite->m_sprite.setPosition({CE::WIDTH-25.f,60.f + 25});

        rect_2 = std::make_shared<IVJ::Rectangulo>(
            500.f,100.f,
            sf::Color(0,0,0,200),
            sf::Color::Black
        );

        rect_1->setPosicion(CE::WIDTH - 50.f,60.f);
        rect_2->setPosicion(CE::WIDTH,60.f);
    }

    bool& Quests::GetAbierto(void)
    {
        return *abierto;
    }

    bool& Quests::GetCambios(void)
    {
        return *cambios;
    }

    std::map<std::string,std::pair<std::shared_ptr<CE::ITexto>,States>>& Quests::GetQuests(void)
    {
        return quests;
    }

    void Quests::ordenarTexto()
    {
        int i = 0;
        for(auto & [key,quest] : this->quests)
        {
            quest.first->m_texto.setPosition({CE::WIDTH - 490.f, 50.f + (30 * i)});
            i++;

            std::string text(quest.first->m_texto.getString());
            if(text.find('\n')  != std::string::npos) i++;

            if(quest.second == IVJ::States::COMPLETADO)
            {
                quest.first->m_texto.setStyle(sf::Text::StrikeThrough);
                quest.first->m_texto.setFillColor(sf::Color::Green);
            }
        }
    }

    void Quests::addQuest(std::string name, IVJ::States estado, std::string texto)
    {
        auto textoQ = std::make_shared<CE::ITexto>(
            CE::GestorAssets::Get().getFont("Byte"),
            texto
        );

        textoQ->m_texto.setPosition({CE::WIDTH - 490.f, 50.f + (30 * cant)});
        textoQ->m_texto.setCharacterSize(30.f);
        textoQ->m_texto.setFillColor(sf::Color::White);
        textoQ->m_texto.setLineSpacing(0.5f);

        quests[name] = std::make_pair(textoQ,estado);

        if(texto.find('\n')  != std::string::npos) cant++;
        cant++;

        //ordenarTexto();

        if(cant >= 3){
            rect_2->setTam(500.f,cant * 40.f);
        }
    }

    void Quests::terminarQuest(std::string quest)
    {
        if(!(quests.count(quest) > 0)) return;
        IVJ::actualizarQuests(quest,IVJ::States::COMPLETADO);
        quests[quest].second = IVJ::States::COMPLETADO;
        //quests.erase(quest);
        IVJ::Jugador::Get().GetDinero() += 100;
        ordenarTexto();
    }
}