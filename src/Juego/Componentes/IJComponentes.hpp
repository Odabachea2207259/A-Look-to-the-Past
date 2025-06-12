#pragma once
#include "../Maquinas/FSM.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include <nlohmann/json.hpp>

namespace IVJ
{
	class FSM;
	class IMaquinaEstado : public CE::IComponentes
	{
		public:
			explicit IMaquinaEstado();
			~IMaquinaEstado() override{};
		public:
			std::shared_ptr<FSM> fsm;
	};

	std::vector<CE::Vector2D> cargarSprites(const nlohmann::json& j, const std::string& prefijo);
}
