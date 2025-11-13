#pragma once
#include "../../Motor/Primitivos/Objetos.hpp"
#include "../Objetos/Entidad.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../Figuras/Figuras.hpp"
#include <SFML/Window/Mouse.hpp>

namespace IVJ
{
	[[maybe_unused]] bool SistemaIA(std::shared_ptr<Entidad> actual,std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt);
	[[maybe_unused]] bool SistemaIA_Attack(std::shared_ptr<Entidad> actual,std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt);
	[[maybe_unused]] bool SistemaIA_Heal(std::shared_ptr<Entidad> actual,std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt);
}
