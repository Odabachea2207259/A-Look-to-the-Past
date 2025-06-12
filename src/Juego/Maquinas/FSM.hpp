#pragma once
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../Objetos/Entidad.hpp"
#include <SFML/Graphics.hpp>

namespace IVJ
{
	class Entidad;
	class FSM
	{
		public:
			virtual ~FSM()=default;
			virtual FSM* onInputs(const CE::IControl& control)=0;
			virtual void onEntrar(const Entidad& obj)=0;
			virtual void onSalir(const Entidad& obj)=0;
			virtual void onUpdate(const Entidad& obj,float dt)=0;
		protected:
			std::string nombre;
	};
}
