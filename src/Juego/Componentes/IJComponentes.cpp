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

	float getVel(const nlohmann::json& j, const std::string& prefijo)
	{
		float vel = 0.0f;

		for(const auto& item: j["maxFrames"])
		{
			std::string nombre = item["name"];
			if(nombre.rfind(prefijo,0)==0){
				vel = item["vel"];
				break;
			}
		}

		return vel;
	}

	std::string getUbicacion(const nlohmann::json& j, const std::string& prefijo)
	{
		return j[prefijo];
	}

	bool enteDescubierto(const nlohmann::json& j, const std::string& prefijo)
	{
		return j[prefijo];
	}

	void enteVisto(const std::string& prefijo)
	{
		json descubiertos;

		std::ifstream in(ASSETS "/Descubiertos.json");
		in >> descubiertos;

		if(!descubiertos[prefijo])
		{
			descubiertos[prefijo] = true;
			
			std::ofstream out(ASSETS "/Descubiertos.json");
			out << descubiertos;
		}
	}

	std::wstring getInfo(const std::string& ubicacion)
	{
		setlocale(LC_ALL, "");

		std::wifstream input1(ASSETS + ubicacion, std::ios::binary);
		std::wstring content((std::istreambuf_iterator<wchar_t>(input1)),
		    {});

		return content;
	}

	void actualizarQuests()
	{
		std::ifstream in(ASSETS "/Quests.json");
		json quests;

		in >> quests;

		for(auto& item :quests["Quests"])
		{
			if(item["estado"] == IVJ::States::DESCUBIERTO || item["estado"] == IVJ::States::EN_PROCESO)
			{
				item["estado"] = IVJ::States::EN_PROCESO;

				IVJ::Quests::Get().addQuest(item["name"],IVJ::States::EN_PROCESO,item["texto"]);
			}
		}

		std::ofstream out(ASSETS "/Quests.json");
		out << quests;
	}

	void actualizarQuests(std::string quest, IVJ::States estado)
	{
		std::ifstream in(ASSETS "/Quests.json");
		json quests;

		in >> quests;

		for(auto& item :quests["Quests"])
		{
			if(item["name"] == quest)
			{
				item["estado"] = estado;

			}
		}

		std::ofstream out(ASSETS "/Quests.json");
		out << quests;
	}

	std::string getTutorial(const std::string& ubicacion, int parrafo)
	{
		setlocale(LC_ALL, "");

		std::ifstream input1(ASSETS + ubicacion, std::ios::binary);

    	std::string linea;
    	std::string parrafoActual;
    	int num = 0;
    	bool esParrafo = false;

    	while (std::getline(input1, linea)) {
    	    if (linea.find('-') != std::string::npos) {
    	        if (esParrafo) {
    	            num++;
    	            if (num == parrafo) {
    	                return parrafoActual;
    	            }
    	            parrafoActual.clear();
    	            esParrafo = false;
    	        }
    	    } else {
    	        if (!esParrafo) {
    	            esParrafo = true;
    	        }
    	        parrafoActual += linea + "\n";
    	    }
    	}

    	if (esParrafo && num + 1 == parrafo) {
    	    return parrafoActual;
    	}

    	return "";
	}
}
