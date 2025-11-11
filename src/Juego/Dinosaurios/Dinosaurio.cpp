#include "Dinosaurio.hpp"
#include "../../Motor/Render/Render.hpp"

namespace IVJ
{
	void Dinosaurio::acomodarBoton(std::shared_ptr<Habilidad> mov, int i)
	{
			//mov->setPosicion(50.f + (200.f*i),650.f);
			mov->setPosicion(30.f + (250.f*i),630.f);
			
			if(mov->tieneComponente<CE::ISprite>())
			{
				auto sprite = mov->getComponente<CE::ISprite>();
				auto escala = sprite->escala;
				auto w = sprite->width;
				auto h = sprite->height;
				sprite->m_sprite.setPosition({(20.f + (250.f*i) + (w*escala)/2),(625.f+(h*escala)/2)});
				//sprite->m_sprite.setPosition({((200.f*i) + (w*escala)/2),(650.f+(h*escala)/2)});
			}

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
		//float w = 185.f;
		float w = 600.f * .35f;

		//float h = 50.f;
		float h = 200.f * .35f;

		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Cabezazo>(w,h,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Embestida>(w,h,sf::Color::Red,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Valor>(w,h,sf::Color::Blue,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Impulso>(w,h,sf::Color::Blue,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}

		auto habEspecial = std::make_shared<SuperCabezazo>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

    void Parasaurolophus::agregarHabilidades()
    {
		//float w = 185.f;
		float w = 600.f * .35f;

		//float h = 50.f;
		float h = 200.f * .35f;

		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Mordisco>(w,h,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Sanar>(w,h,sf::Color::Blue,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Curar>(w,h,sf::Color::Blue,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Canto>(w,h,sf::Color::Magenta,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}
		auto habEspecial = std::make_shared<Renacer>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

    void Centrosaurus::agregarHabilidades()
    {
		//float w = 185.f;
		float w = 600.f * .35f;

		//float h = 50.f;
		float h = 200.f * .35f;

		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Embestida>(w,h,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Punzada>(w,h,sf::Color::Red,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Mordisco>(w,h,sf::Color::Red,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Adrenalina>(w,h,sf::Color::Blue,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}
		auto habEspecial = std::make_shared<SuperPunzada>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }

    void Carnotauro::agregarHabilidades()
    {
		//float w = 185.f;
		float w = 600.f * .35f;

		//float h = 50.f;
		float h = 200.f * .35f;

		for(int i = 0; i < 4; i++)
		{
			std::shared_ptr<Habilidad> mov;
			switch(i)
			{
				case 0:
					mov = std::make_shared<IVJ::Embestida>(w,h,sf::Color::Red,sf::Color::Black);
					break;
				case 1:
					mov = std::make_shared<IVJ::Mordisco>(w,h,sf::Color::Red,sf::Color::Black);
					break;
				case 2:
					mov = std::make_shared<IVJ::Rugido>(w,h,sf::Color::Magenta,sf::Color::Black);
					break;
				case 3:
					mov = std::make_shared<IVJ::Impulso>(w,h,sf::Color::Blue,sf::Color::Black);
					break;				
			}
			acomodarBoton(mov,i);
		}
		auto habEspecial = std::make_shared<SuperMordisco>(835.f,50.f,sf::Color::Cyan,sf::Color::Black);
		acomodarHabilidadEspecial(habEspecial);
    }
}