#include "IdleFSM.hpp"
#include "CambiarPaginaFSM.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace IVJ
{
	CambiarPaginaFSM::CambiarPaginaFSM(bool der)
	:FSM(),der{der}
	{
		nombre="CambiarPaginaFSM";
        termino = false;
        frame = 0;
	}
	FSM* CambiarPaginaFSM::onInputs(const CE::IControl& control)
	{
		if(termino)
			return new IdleFSM();

		return nullptr;
	}
	void CambiarPaginaFSM::onEntrar(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		sprite = &c_sprite->m_sprite;
		s_w = c_sprite->width;
		s_h = c_sprite->height;

		json j;

		auto nombre = obj.toString();

		std::ifstream file(ASSETS "/bestiario/Bestiario.json");

		if(!file)
		{
			std::cerr << "No se pudo abrir el JSON\n";
		}

		file >> j;

        std::vector<CE::Vector2D> vectores;

        if(der)
		    vectores = cargarSprites(j,"Der");
        else
            vectores = cargarSprites(j,"Izq");

		for(size_t i = 0; i < vectores.size() && i < 11; i++)
			ani_frames[i] = vectores[i];

		max_tiempo = 0.05f;
		tiempo = max_tiempo;
		id_actual = 0;
	}

	void CambiarPaginaFSM::onSalir(const Entidad& obj){
        auto c = obj.getComponente<CE::IControl>();

		if(der)
		    c->nextPage = false;
        else
            c->prevPage = false;
	}  

	void CambiarPaginaFSM::onUpdate(const Entidad& obj,float dt)
	{
		tiempo = tiempo - 1*dt;
		
		if(tiempo <= 0)
		{
			//std::cout << "{" << (int)ani_frames[id_actual%3].x << ", " <<(int)ani_frames[id_actual%3].y << "}\n";
			sprite->setTextureRect(
			sf::IntRect{
				{//posicion
					(int)ani_frames[id_actual%11].x,
					(int)ani_frames[id_actual%11].y
				},
				{//tamaño
					s_w,
					s_h
				}});
			tiempo = max_tiempo;
			id_actual++;
			frame++;

			if(id_actual%11 == 11 || frame == 11)
			{
				termino = true;
			}
		}
	}
}
