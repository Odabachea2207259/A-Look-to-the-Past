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

	int getMaxFrames(const nlohmann::json& j, const std::string& prefijo)
	{
		int max = 0;

		for(const auto& item: j["maxFrames"])
		{
			std::string nombre = item["name"];
			if(nombre.rfind(prefijo,0)==0){
				max = item["max"];
				break;
			}
		}

		return max;
	}

	std::string getUbicacion(const nlohmann::json& j, const std::string& prefijo)
	{
		return j[prefijo];
	}
}
