#include "CamarasGestor.hpp"

namespace CE
{
	GestorCamaras& GestorCamaras::Get()
	{
		if(!instancia)
			instancia = new GestorCamaras();
		return *instancia;
	}
	void GestorCamaras::agregarCamara(const std::shared_ptr<Camara>& nueva)
	{
		m_listaCamaras.push_back(nueva);
	}
	void GestorCamaras::setCamaraActiva(int id)
	{
		if(id>m_listaCamaras.size()-1 || id<0) return ;
		if(m_camaraActiva.lock())
			m_camaraActiva.lock()->esta_activo=false;
		m_camaraActiva = m_listaCamaras[id];
		m_camaraActiva.lock()->esta_activo=true;
	}

	void GestorCamaras::onUpdateCamara(float dt)
	{
		if(m_camaraActiva.lock())
			m_camaraActiva.lock()->onUpdate(dt);
	}

	void GestorCamaras::onRenderCamara(sf::RenderTexture &tex)
	{
		tex.setView(m_camaraActiva.lock()->getView());
	}
}
