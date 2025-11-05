#include "IdleFSM.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MoverFSM.hpp"
#include "AtaqueFSM.hpp"
#include "BuffFSM.hpp"
#include "DamageFSM.hpp"
#include "MuerteFSM.hpp"
#include "CambiarPaginaFSM.hpp"
#include "CerrarFSM.hpp"
#include "AbrirFSM.hpp"
#include "SaltoFSM.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;


namespace IVJ
{
	IdleFSM::IdleFSM()
	:FSM()
	{
		nombre="IdleFSM";
	}
	FSM* IdleFSM::onInputs(const CE::IControl& control)
	{
		if(control.arr)
			return new MoverFSM(false);
		else if(control.abj)
			return new MoverFSM(true);
		else if(control.salto)
			return new SaltoFSM(true);
		else if(control.der)
			return new MoverFSM(false);
		else if(control.izq)
			return new MoverFSM(true);
		else if(control.acc)
			return new AtaqueFSM(control.ataque);
		else if(control.sacc)
			return new BuffFSM();
		else if(control.damage)
			return new DamageFSM();
		else if(control.muerte)
			return new MuerteFSM();
		else if(control.nextPage)
			return new CambiarPaginaFSM(true);
		else if(control.prevPage)
			return new CambiarPaginaFSM(false);
		else if(control.cerrar)
			return new CerrarFSM();
		else if(control.abrir)
			return new AbrirFSM();

		return nullptr;
	}
	void IdleFSM::onEntrar(const Entidad& obj)
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

		auto vectores = cargarSprites(j,"Idle");
		max_frames = getMaxFrames(j,"Idle");
		max_tiempo = getVel(j,"Idle");

		for(size_t i = 0; i < vectores.size() && i < max_frames; i++)
			ani_frames[i] = vectores[i];

		//max_tiempo = 0.15f;
		tiempo = max_tiempo;
		id_actual = 0;
	}

	void IdleFSM::onSalir(const Entidad& obj){}

	void IdleFSM::onUpdate(const Entidad& obj,float dt)
	{
		tiempo = tiempo - 1*dt;

		if(tiempo <= 0)
		{
			sprite->setTextureRect(
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
		}
	}
}
