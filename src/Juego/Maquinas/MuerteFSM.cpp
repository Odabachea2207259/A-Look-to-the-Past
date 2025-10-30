#include "IdleFSM.hpp"
#include "MuerteFSM.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace IVJ
{
	MuerteFSM::MuerteFSM()
	:FSM()
	{
		nombre="MuerteFSM";
		termino = false;
		frame = 0;
		disolving = 0;
	}
	FSM* MuerteFSM::onInputs(const CE::IControl& control)
	{
		if(termino)
			return new IdleFSM();
		return nullptr;
	}
	void MuerteFSM::onEntrar(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		auto c = obj.getComponente<CE::IControl>();
		c->muerte = false;
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

		auto vectores = cargarSprites(j,"Muerte");
		max_frames = getMaxFrames(j,"Muerte");

		for(size_t i = 0; i < vectores.size() && i < max_frames; i++)
			ani_frames[i] = vectores[i];

		if(nombre=="Pachycephalosaurus")
			max_tiempo = 0.15f;
		else
			max_tiempo = 0.1f;
		tiempo = max_tiempo;
		id_actual = 0;
	}

	void MuerteFSM::flipSprite(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		if(flip)
			c_sprite->m_sprite.setScale({-c_sprite->escala,c_sprite->escala});
		else
			c_sprite->m_sprite.setScale({c_sprite->escala,c_sprite->escala});
	}

	void MuerteFSM::onSalir(const Entidad& obj){
		
		auto c = obj.getComponente<CE::IControl>();

		c->muerte = false;
		c->muerto = true;
	}

	void MuerteFSM::onUpdate(const Entidad& obj,float dt)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		auto c_control = obj.getComponente<CE::IControl>();

		if(c_control->muerto)
		{
			c_sprite->m_sprite.setTextureRect(
			sf::IntRect{
				{//posicion
					(int)ani_frames[8].x,
					(int)ani_frames[8].y
				},
				{//tamaño
					s_w,
					s_h
				}});
			return;
		}

		tiempo = tiempo - 1*dt;

		if(tiempo <= 0)
		{
			c_sprite->m_sprite.setTextureRect(
			sf::IntRect{
				{//posicion
					(int)ani_frames[id_actual%max_frames].x,
					(int)ani_frames[id_actual%max_frames].y
				},
				{//tamaño
					s_w,
					s_h
				}});
			tiempo = max_tiempo;
			id_actual++;
			frame++;

			if(id_actual%max_frames == max_frames || frame == max_frames)
			{
				auto c = obj.getComponente<CE::IControl>();
				c->muerto = true;
			}
		}
	}
}
