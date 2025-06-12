#include "Entidad.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../../Motor/Primitivos/Objetos.hpp"
namespace IVJ
{
	void Entidad::onUpdate(float dt)
	{
		if(tieneComponente<CE::ISprite>())
		{
			auto sprite = getComponente<CE::ISprite>();
			auto pos = getTransformada()->posicion;
			sprite->m_sprite.setPosition({pos.x,pos.y});
		}

		if(tieneComponente<CE::ISprite>() && tieneComponente<CE::IBoundingBox>())
		{
			auto sprite = getComponente<CE::ISprite>();
			auto bound = getComponente<CE::IBoundingBox>();
			sprite->m_sprite.setOrigin({bound->mitad.x,bound->mitad.y});
		}

		if(tieneComponente<IVJ::IMaquinaEstado>())
		{
			auto mq = getComponente<IVJ::IMaquinaEstado>();
			if(mq->fsm)
				mq->fsm->onUpdate(*this,dt);
			inputFSM();
		}

		transform->pos_prev = transform->posicion;
	}

	void Entidad::draw(sf::RenderTarget &target, sf::RenderStates state) const
	{
		state.transform *= getTransform();
#if DEBUG
		if(tieneComponente<CE::IBoundingBox>())
		{
			auto bound = getComponente<CE::IBoundingBox>();
			sf::RectangleShape box{{bound->tam.x,bound->tam.y}};
			box.setFillColor(sf::Color::Transparent);
			box.setOutlineColor(sf::Color::Red);
			box.setOutlineThickness(2.f);
			box.setOrigin({bound->mitad.x,bound->mitad.y});
			auto pos = transform->posicion;
			box.setPosition({pos.x,pos.y});
			target.draw(box);
		}
#endif
		if(tieneComponente<CE::ISprite>())
		{
			auto sprite = getComponente<CE::ISprite>();
			if(tieneComponente<CE::IShader>())
			{
				target.draw(sprite->m_sprite,&getComponente<CE::IShader>()->m_shader);
			}
			else
				target.draw(sprite->m_sprite);
		}
	}

	void Entidad::inputFSM()
	{
		if(!getComponente<IMaquinaEstado>() || !getComponente<CE::IControl>() || !getComponente<IMaquinaEstado>()->fsm)
			return;

		auto mq = getComponente<IMaquinaEstado>();
		auto control = *getComponente<CE::IControl>();
		auto n_estado = mq->fsm->onInputs(control);
		std::shared_ptr<FSM> estado(n_estado);
		if(estado)
			setFSM(estado);
	}

	void Entidad::setFSM(const std::shared_ptr<FSM>& mq)
	{
		auto &estado_actual = getComponente<IMaquinaEstado>()->fsm;
		estado_actual->onSalir(*this);
		estado_actual = mq;
		estado_actual->onEntrar(*this);
	}
}
