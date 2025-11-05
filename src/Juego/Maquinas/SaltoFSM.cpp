#include "IdleFSM.hpp"
#include "SaltoFSM.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace IVJ
{
	SaltoFSM::SaltoFSM(bool flip_sprite)
	:FSM(),flip{flip_sprite}
	{
		nombre="SaltoFSM";
		termino = false;
		frame = 0;
	}
	FSM* SaltoFSM::onInputs(const CE::IControl& control)
	{
		if((!control.saltando && !control.salto) || termino)
			return new IdleFSM();
		if(control.der)
			flip = false;
		else if(control.izq)
			flip = true;

		return nullptr;
	}
	void SaltoFSM::onEntrar(const Entidad& obj)
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

		auto vectores = cargarSprites(j,obj.getComponente<CE::IControl>()->mov);
		max_frames = getMaxFrames(j,obj.getComponente<CE::IControl>()->mov);
		max_tiempo = getVel(j,obj.getComponente<CE::IControl>()->mov);

		for(size_t i = 0; i < vectores.size() && i < max_frames; i++)
			ani_frames[i] = vectores[i];

		//max_tiempo = 0.05f;
		tiempo = max_tiempo;
		id_actual = 0;
	}

	void SaltoFSM::flipSprite(const Entidad& obj)
	{
		auto c_sprite = obj.getComponente<CE::ISprite>();
		if(flip)
			c_sprite->m_sprite.setScale({-c_sprite->escala,c_sprite->escala});
		else
			c_sprite->m_sprite.setScale({c_sprite->escala,c_sprite->escala});
	}

	void SaltoFSM::onSalir(const Entidad& obj){
		auto c_sprite = obj.getComponente<CE::ISprite>();
		c_sprite->m_sprite.setScale(escala_or);

        auto c = obj.getComponente<CE::IControl>();
        c->saltando = false;
        c->salto = false;
	}

	void SaltoFSM::onUpdate(const Entidad& obj,float dt)
	{
		//std::cout << "SaltoUpdate\n";
        auto c = obj.getComponente<CE::IControl>();
		tiempo = tiempo - 1*dt;
		
		flipSprite(obj);

        if(c->saltando){
            sprite->setTextureRect(
                sf::IntRect{
                    {
                        (int)ani_frames[max_frames/2].x,
                        (int)ani_frames[max_frames/2].y
                    },
                    {
                        s_w,
                        s_h
                    }
                }
            );

			return;
        }
		else id_actual++;

		if(tiempo <= 0)
		{
			//std::cout << "{" << (int)ani_frames[id_actual%3].x << ", " <<(int)ani_frames[id_actual%3].y << "}\n";
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
			frame++;
		}

        if((id_actual%max_frames) == (max_frames / 2)) c->saltando=true;
		else if(id_actual%max_frames == max_frames || frame == max_frames)
		{
			termino = true;
		}
	}
}
