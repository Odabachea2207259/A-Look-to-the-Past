#include "GestorEscenas.hpp"

namespace CE
{
	GestorEscenas& GestorEscenas::Get()
	{
		if(!instancia)
			instancia = new GestorEscenas();
		return *instancia;
	}

	void GestorEscenas::registrarEscena(const std::string& key, const std::shared_ptr<Escena>& escena)
	{
		if(escenas.empty())
			escena_actual = key;
		escenas[key]=escena;
		escena->nombre = key;
	}

	void GestorEscenas::cambiarEscena(const std::string& key)
	{
		if(escenas.find(key) == escenas.end() || escenas.empty()) return;

		escenas[escena_actual]->onFinal();
		escena_actual = key;
		escenas[escena_actual]->onInit();
	}

	Escena& GestorEscenas::getEscenaActual()
	{
		return *escenas[escena_actual];
	}
}
