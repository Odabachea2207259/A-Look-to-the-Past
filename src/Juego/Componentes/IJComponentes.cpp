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
		std::cout << prefijo << std::endl;
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

	std::string getTutorial(const std::string& ubicacion, int parrafo)
	{
		setlocale(LC_ALL, "");

		std::ifstream input1(ASSETS + ubicacion, std::ios::binary);

    	std::string line;
    	std::string currentParagraph;
    	int currentParagraphCount = 0;
    	bool inParagraph = false;

    	while (std::getline(input1, line)) {
    	    if (line.find('-') != std::string::npos) {
    	        if (inParagraph) {
    	            currentParagraphCount++;
    	            if (currentParagraphCount == parrafo) {
    	                return currentParagraph;
    	            }
    	            currentParagraph.clear();
    	            inParagraph = false;
    	        }
    	    } else {
    	        if (!inParagraph) {
    	            inParagraph = true;
    	        }
    	        currentParagraph += line + "\n";
    	    }
    	}

    	if (inParagraph && currentParagraphCount + 1 == parrafo) {
    	    return currentParagraph;
    	}

    	return "";
	}
}
