#pragma once
#include "../../Motor/Primitivos/Objetos.hpp"
#include "../Objetos/Entidad.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../Figuras/Figuras.hpp"
#include <SFML/Window/Mouse.hpp>

namespace IVJ
{
	[[maybe_unused]] void SistemaMover(const std::vector<std::shared_ptr<CE::Objeto>>& entes, float dt);
	[[maybe_unused]] void SistemaMovimientoEntes(std::vector<std::shared_ptr<CE::Objeto>> entes, float dt);
	[[maybe_unused]] void SistemaMovimientoRebote(std::vector<std::shared_ptr<CE::Objeto>> entes, float dt);
	[[maybe_unused]] CE::Vector2D SistemaPosMouse();
	[[maybe_unused]] void SistemaContains(const std::vector<std::shared_ptr<IVJ::Rectangulo>>& entes, CE::Vector2D mousePos);
	[[maybe_unused]] bool SistemaColAABB(CE::Objeto& A, CE::Objeto& B, bool resolucion = false);
	[[maybe_unused]] bool SistemaColAABBMid(CE::Objeto& A, CE::Objeto& B, bool resolucion = false);


	[[maybe_unused]] void SistemaSpawn(std::vector<std::shared_ptr<CE::Objeto>>& spawns);
	[[maybe_unused]] void SistemaPaths(const std::vector<std::shared_ptr<CE::Objeto>>& obj);

	[[maybe_unused]] void SistemaQuitarVida(std::shared_ptr<IVJ::Entidad> target, float damage);
	[[maybe_unused]] void SistemaAgregarVida(std::shared_ptr<IVJ::Entidad> target, float vida);
}
