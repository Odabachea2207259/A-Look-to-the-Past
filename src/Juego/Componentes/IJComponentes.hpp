#pragma once
#include "../Maquinas/FSM.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <locale.h>

using json = nlohmann::json;

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
	int getMaxFrames(const nlohmann::json& j, const std::string& prefijo);
	std::string getUbicacion(const nlohmann::json& j, const std::string& prefijo);
	float getVel(const nlohmann::json& j, const std::string& prefijo);

	bool enteDescubierto(const nlohmann::json& j, const std::string& prefijo);
	void enteVisto(const std::string& prefijo);

	std::wstring getInfo(const std::string& ubicacion);
}
