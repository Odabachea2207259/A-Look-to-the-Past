#include "Objetos.hpp"
#include <iostream>
namespace CE
{
	int Objeto::num_objetos = 0;

	Objeto::Objeto()
	{
		nombre = std::make_shared<INombre>("Objeto "+std::to_string(Objeto::num_objetos+1));
		transform = std::make_shared<ITransform>();
		stats = std::make_shared<IStats>();
		Objeto::num_objetos++;
	}

	void Objeto::setPosicion(float x, float y)
	{
		transform->pos_prev = transform->posicion;
		transform->posicion.x = x;
		transform->posicion.y = y;
	}
	CE::Vector2D Objeto::getPosicion()
	{
		return transform->posicion;
	}
	void Objeto::setVelocidad(float x, float y)
	{
		transform->velocidad.x = x;
		transform->velocidad.y = y;
	}


	Objeto& Objeto::addComponente(const std::shared_ptr<IComponentes>& componente)
	{
		componentes.push_back(componente);
		return *this;
	}

	void Objeto::draw(sf::RenderTarget& target, sf::RenderStates state) const
	{
		std::cout<<"Objeto::Draw()\n";
	}
}
