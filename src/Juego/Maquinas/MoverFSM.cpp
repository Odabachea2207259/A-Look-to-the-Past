#include "IdleFSM.hpp"
#include "MoverFSM.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace IVJ
{
	MoverFSM::MoverFSM(bool flip_sprite)
	:FSM(),flip{flip_sprite}
	{
		nombre="MoverFSM";
	}
	FSM* MoverFSM::onInputs(const CE::IControl& control)
	{
		if(!control.arr && !control.abj && !control.der && !control.izq)
			return new IdleFSM();
		if(control.der)
			flip = false;
		else if(control.izq)
			flip = true;

		return nullptr;
	}
	void MoverFSM::onEntrar(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		sprite = &c_sprite->m_sprite;
		s_w = c_sprite->width;
		s_h = c_sprite->height;

		escala_or = c_sprite->m_sprite.getScale();

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

		auto vectores = cargarSprites(j,"Movimiento");

		for(size_t i = 0; i < vectores.size() && i < 9; i++)
			ani_frames[i] = vectores[i];

		max_tiempo = 0.05f;
		tiempo = max_tiempo;
		id_actual = 0;
	}

	void MoverFSM::flipSprite(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		if(flip)
			c_sprite->m_sprite.setScale({-c_sprite->escala,c_sprite->escala});
		else
			c_sprite->m_sprite.setScale({c_sprite->escala,c_sprite->escala});
	}

	void MoverFSM::onSalir(const Entidad& obj){
		auto c_sprite = obj.getComponente<CE::ISprite>();
		c_sprite->m_sprite.setScale(escala_or);
	}

	void MoverFSM::onUpdate(const Entidad& obj,float dt)
	{
		tiempo = tiempo - 1*dt;
		
		flipSprite(obj);
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
		}
	}
}
