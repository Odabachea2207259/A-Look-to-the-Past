#include "Dinosaurio.hpp"
#include "../../Motor/Render/Render.hpp"

namespace IVJ
{
	void Dinosaurio::acomodarBoton(std::shared_ptr<Habilidad> mov, int i)
	{
			mov->setPosicion(50.f + (200.f*i),650.f);
			mov->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),mov->getNombre()->nombre + "\n" + std::to_string(mov->dinoPuntos)));
			auto texto = mov->getComponente<CE::ITexto>();
			texto->m_texto.setCharacterSize(10);
			texto->m_texto.setFillColor(sf::Color::Black);
			texto->m_texto.setPosition({mov->getPosicion().x,mov->getPosicion().y+2.f});
			
			//this->movimientos.push_back(mov);

			this->getComponente<CE::IHabilidades>()->movimientos.push_back(mov);
	}

	void Dinosaurio::acomodarHabilidadEspecial(std::shared_ptr<Habilidad> mov)
	{
		mov->setPosicion(50.f,580.f);
		mov->addComponente(std::make_shared<CE::ITexto>(CE::GestorAssets::Get().getFont("Caveman"),mov->getNombre()->nombre));
		auto texto = mov->getComponente<CE::ITexto>();
		texto->m_texto.setCharacterSize(10);
		texto->m_texto.setFillColor(sf::Color::Black);
		texto->m_texto.setPosition({mov->getPosicion().x,mov->getPosicion().y+2.f});
		
		//this->habilidadEspecial = mov;
		//this->movimientos.push_back(mov);

		auto habilidades = this->getComponente<CE::IHabilidades>();
		habilidades->habilidadEspecial = mov;
		habilidades->movimientos.push_back(mov);
	}
	/*----------------------------HABILIDADDES------------------------------------------------------*/
	
    void Pachycephalosaurus::agregarHabilidades()
    {
		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Cabezazo>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Embestida>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Valor>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Impulso>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}

		auto habEspecial = std::make_shared<SuperCabezazo>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

    void Parasaurolophus::agregarHabilidades()
    {
		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Mordisco>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Sanar>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Curar>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Canto>(185.f,50.f,sf::Color::Magenta,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}
		auto habEspecial = std::make_shared<Renacer>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

    void Centrosaurus::agregarHabilidades()
    {
		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Embestida>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Punzada>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Mordisco>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Adrenalina>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}
		auto habEspecial = std::make_shared<SuperPunzada>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

    void Carnotauro::agregarHabilidades()
    {
		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Embestida>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Mordisco>(185.f,50.f,sf::Color::Red,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Rugido>(185.f,50.f,sf::Color::Magenta,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Impulso>(185.f,50.f,sf::Color::Blue,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}
		auto habEspecial = std::make_shared<SuperMordisco>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }
}