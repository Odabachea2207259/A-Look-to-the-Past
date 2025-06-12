#include "IdleFSM.hpp"
#include "DamageFSM.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace IVJ
{
	DamageFSM::DamageFSM()
	:FSM()
	{
		nombre="DamageFSM";
		termino = false;
		frame = 0;
	}
	FSM* DamageFSM::onInputs(const CE::IControl& control)
	{
		if(termino)
			return new IdleFSM();
		return nullptr;
	}
	void DamageFSM::onEntrar(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		sprite = &c_sprite->m_sprite;
		s_w = c_sprite->width;
		s_h = c_sprite->height;

		json j;

		auto nombre = obj.toString();

		std::ifstream file(ASSETS "/sprites_dinos/"+nombre+"/"+nombre+"_tex.json");

		if(!file)
		{
			std::cerr << "No se pudo abrir el JSON\n";
		}

		file >> j;

		auto vectores = cargarSprites(j,"Daño");

		for(size_t i = 0; i < vectores.size() && i < 9; i++)
			ani_frames[i] = vectores[i];

		max_tiempo = 0.08f;
		tiempo = max_tiempo;
		id_actual = 0;
	}

	void DamageFSM::flipSprite(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		if(flip)
			sprite->setScale({-c_sprite->escala,c_sprite->escala});
		else
			sprite->setScale({c_sprite->escala,c_sprite->escala});
	}

	void DamageFSM::onSalir(const Entidad& obj){
		
		auto c = obj.getComponente<CE::IControl>();

		c->damage = false;
	}

	void DamageFSM::onUpdate(const Entidad& obj,float dt)
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
