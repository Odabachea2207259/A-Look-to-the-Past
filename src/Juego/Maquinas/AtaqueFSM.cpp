#include "IdleFSM.hpp"
#include "AtaqueFSM.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace IVJ
{
	AtaqueFSM::AtaqueFSM()
	:FSM()
	{
		nombre="AtaqueFSM";
		termino = false;
		frame = 0;
	}
	FSM* AtaqueFSM::onInputs(const CE::IControl& control)
	{
		if(termino)
			return new IdleFSM();
		return nullptr;
	}
	void AtaqueFSM::onEntrar(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		sprite = &c_sprite->m_sprite;
		s_w = c_sprite->width;
		s_h = c_sprite->height;

		json j;
		json ub;

		auto nombre = obj.toString();

		std::ifstream ubicaciones(ASSETS "/Ubicaciones.json");
		ubicaciones >> ub;

		std::string ubicacion = (obj.esDino) ? "/sprites_dinos/"+nombre+"/"+nombre+"_tex.json" : getUbicacion(ub,nombre);

		std::ifstream file(ASSETS + ubicacion);

		if(!file)
			std::cout << "Error\nNo se pudo abrir el archivo\n";

		file >> j;

		auto vectores = cargarSprites(j,"Ataque");

		for(size_t i = 0; i < vectores.size() && i < 9; i++)
			ani_frames[i] = vectores[i];

		if(nombre=="Pachycephalosaurus")
			max_tiempo = 0.15f;
		else
			max_tiempo = 0.1f;
		tiempo = max_tiempo;
		id_actual = 0;
	}

	void AtaqueFSM::flipSprite(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		if(flip)
			sprite->setScale({-c_sprite->escala,c_sprite->escala});
		else
			sprite->setScale({c_sprite->escala,c_sprite->escala});
	}

	void AtaqueFSM::onSalir(const Entidad& obj){
		
		auto c = obj.getComponente<CE::IControl>();

		c->acc = false;
	}

	void AtaqueFSM::onUpdate(const Entidad& obj,float dt)
	{
		tiempo = tiempo - 1*dt;

		if(tiempo <= 0)
		{
			//std::cout << "{" << (int)ani_frames[id_actual%3].x << ", " <<(int)ani_frames[id_actual%3].y << "}\n";
			sprite->setTextureRect(
			sf::IntRect{
				{//posicion
					(int)ani_frames[id_actual%9].x,
					(int)ani_frames[id_actual%9].y
				},
				{//tamaño
					s_w,
					s_h
				}});
			tiempo = max_tiempo;
			id_actual++;
			frame++;

			if(id_actual%9 == 9 || frame == 9)
			{
				termino = true;
			}
		}
	}
}
