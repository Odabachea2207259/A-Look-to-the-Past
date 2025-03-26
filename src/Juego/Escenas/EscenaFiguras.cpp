#include "EscenaFigura.hpp"
#include "../Figuras/Figuras.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../../Motor/Primitivos/GestorEscenas.hpp"
#include "../../Motor/Render/Render.hpp"
#include "../Sistemas/Sistemas.hpp"

namespace IVJ
{
	void EscenaFiguras::onInit()
	{
		if(!inicializar) return;

		int n = 50;
		
		registrarBotones(sf::Keyboard::Scancode::W,"arriba");
		registrarBotones(sf::Keyboard::Scancode::Up,"arriba");
		registrarBotones(sf::Keyboard::Scancode::S,"abajo");
		registrarBotones(sf::Keyboard::Scancode::Down,"abajo");
		registrarBotones(sf::Keyboard::Scancode::A,"izquierda");
		registrarBotones(sf::Keyboard::Scancode::Left,"izquierda");
		registrarBotones(sf::Keyboard::Scancode::D,"derecha");
		registrarBotones(sf::Keyboard::Scancode::Right,"derecha");
		registrarBotones(sf::Keyboard::Scancode::Escape,"circulos");


		for(int i = 0; i < n; i++)
		{
			int opcion = rand() % 3;

			switch(opcion)
			{
				case 0:
				{
					auto fig = std::make_shared<Rectangulo>(
					rand() % 301, rand() % 301,
					sf::Color(rand() % 256,rand() % 256, rand() % 256, 255),
					sf::Color(rand() % 256,rand() % 256, rand() % 256, 255));
					fig->setPosicion(rand() % 501, rand() % 501);
					fig->getStats()->hp = rand() % 10001;
					objetos.agregarPool(fig);
					break;
				}
				case 1:
				{
					auto fig = std::make_shared<Triangulo>(
					rand() % 301,
					sf::Color(rand() % 256,rand() % 256, rand() % 256, 255),
					sf::Color(rand() % 256,rand() % 256, rand() % 256, 255));
					fig->setPosicion(rand() % 501, rand() % 501);
					fig->getStats()->hp = rand() % 10001;
					objetos.agregarPool(fig);
					break;
				}
				case 2:
				{
					auto fig = std::make_shared<Circulo>(
					rand() % 301,
					sf::Color(rand() % 256,rand() % 256, rand() % 256, 255),
					sf::Color(rand() % 256,rand() % 256, rand() % 256, 255));
					fig->setPosicion(rand() % 501, rand() % 501);
					fig->getStats()->hp = rand() % 10001;
					objetos.agregarPool(fig);
					break;
				}
			}
		}

		CE::GestorCamaras::Get().agregarCamara(std::make_shared<CE::CamaraCuadro>(
		CE::Vector2D{540,360},CE::Vector2D{1080.f,720.f}));
		CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(objetos[1]);
		inicializar = false;
	}
	void EscenaFiguras::onFinal(){}
	void EscenaFiguras::onUpdate(float dt)
	{
		SistemaMovimientoEntes(objetos.getPool(),dt);
		for(auto &f : objetos.getPool())
		{
			//auto stats = f->getStats();
			f->getStats()->hp--;
			f->onUpdate(dt);
		}
		objetos.borrarPool();
		
		if(objetos.getPool().size() == 0)
			CE::GestorEscenas::Get().cambiarEscena("Circulos");
	}

	void EscenaFiguras::onInputs(const CE::Botones& accion)
	{
		auto p = objetos[1]->getTransformada();

		if(accion.getTipo() == CE::Botones::TipoAccion::OnPress)
		{
			if(accion.getNombre() == "arriba")
				p->velocidad.y = -800;
			else if(accion.getNombre() == "derecha")
				p->velocidad.x = 800;
			else if(accion.getNombre() == "abajo")
				p->velocidad.y = +800;
			else if(accion.getNombre() == "izquierda")
				p->velocidad.x = -800;
			else if(accion.getNombre() == "circulos")
				CE::GestorEscenas::Get().cambiarEscena("Circulos");
		}
		else if(accion.getTipo() == CE::Botones::TipoAccion::OnRelease)
		{
			if(accion.getNombre() == "arriba")
				p->velocidad.y = 0;
			else if(accion.getNombre() == "derecha")
				p->velocidad.x = 0;
			else if(accion.getNombre() == "abajo")
				p->velocidad.y = 0;
			else if(accion.getNombre() == "izquierda")
				p->velocidad.x = 0;
		}
	}

	void EscenaFiguras::onRender()
	{
		for(auto &f : objetos.getPool())
			CE::Render::Get().AddToDraw(*f);
	}
}
