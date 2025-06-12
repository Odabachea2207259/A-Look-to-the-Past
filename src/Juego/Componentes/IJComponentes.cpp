#include "IJComponentes.hpp"

namespace IVJ
{
	IMaquinaEstado::IMaquinaEstado()
	{
		fsm = nullptr;
	}

	std::vector<CE::Vector2D> cargarSprites(const nlohmann::json& j, const std::string& prefijo)
	{
		std::vector<CE::Vector2D> resultado;

		for(const auto& item :j["SubTexture"])
		{
			std::string nombre = item["name"];
			if(nombre.rfind(prefijo, 0) == 0)
			{
				float x = item["x"];
				float y = item["y"];
				resultado.emplace_back(x,y);
			}
		}

		return resultado;
	}
}
