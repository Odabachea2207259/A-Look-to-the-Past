#pragma once
#include "../../Motor/Primitivos/Objetos.hpp"
#include "../Objetos/Entidad.hpp"
#include "../../Motor/Componentes/IComponentes.hpp"
#include "../../Motor/Primitivos/GestorAssets.hpp"
#include "../Figuras/Figuras.hpp"
#include <SFML/Window/Mouse.hpp>
#include <cmath>

namespace IVJ
{
	class Dinosaurio;
	
	[[maybe_unused]] void SistemaMover(const std::vector<std::shared_ptr<CE::Objeto>>& entes, float dt);
	[[maybe_unused]] void SistemaMovimientoEntes(std::vector<std::shared_ptr<CE::Objeto>> entes, float dt);
	[[maybe_unused]] void SistemaMovimientoRebote(std::vector<std::shared_ptr<CE::Objeto>> entes, float dt);
	[[maybe_unused]] CE::Vector2D SistemaPosMouse();
	[[maybe_unused]] void SistemaContains(const std::vector<std::shared_ptr<IVJ::Rectangulo>>& entes, CE::Vector2D mousePos);
	[[maybe_unused]] bool SistemaColAABB(CE::Objeto& A, CE::Objeto& B, bool resolucion = false);
	[[maybe_unused]] bool SistemaColAABBMid(CE::Objeto& A, CE::Objeto& B, bool resolucion = false);
	[[maybe_unused]] void SistemaFlotar(std::shared_ptr<CE::Objeto> obj,float dt);


	[[maybe_unused]] void SistemaSpawn(std::vector<std::shared_ptr<CE::Objeto>>& spawns);
	[[maybe_unused]] void SistemaPaths(const std::vector<std::shared_ptr<CE::Objeto>>& obj);


	/*<----- SISTEMAS DE ENTIDADES (DINOS, ENEMIGOS, JEFES)*/
	[[maybe_unused]] void SistemaQuitarVida(std::shared_ptr<IVJ::Entidad> target, float damage);
	[[maybe_unused]] void SistemaAgregarVida(std::shared_ptr<IVJ::Entidad> target, float vida);
	[[maybe_unused]] void SistemaAplicarEstados(std::shared_ptr<IVJ::Entidad> target);

	[[maybe_unused]] void SistemaMostrarEstados(std::shared_ptr<IVJ::Entidad> target);
	[[maybe_unused]] void SistemaSetPosOriginal(std::shared_ptr<IVJ::Entidad> target);
	[[maybe_unused]] void SistemaActualizarVida(std::shared_ptr<IVJ::Entidad> target);
	[[maybe_unused]] void SistemaReiniciarStats(std::shared_ptr<IVJ::Entidad> target);
	[[maybe_unused]] void SistemaReiniciarDino(std::shared_ptr<IVJ::Entidad> target);
	[[maybe_unused]] void SistemaSubirNivel(std::shared_ptr<IVJ::Entidad> target);
	[[maybe_unused]] void SistemaConfigurarStats(IVJ::Dinosaurio * const &target,float hp, float str, float agi, float def);
	[[maybe_unused]] void SistemaConfigurarStatsE(std::shared_ptr<IVJ::Entidad> target,float hp, float str, float agi, float def);

	/*<----- SISTEMAS DE ESCENAS ------>*/
	[[maybe_unused]] std::vector<std::shared_ptr<IVJ::Entidad>> SistemaOrdenarTurnos(std::vector<std::shared_ptr<IVJ::Entidad>> jugador,std::vector<std::shared_ptr<IVJ::Entidad>> enemigos);
	[[maybe_unused]] void SistemaActualizarMedidor(std::shared_ptr<IVJ::Entidad> dinoLider,std::shared_ptr<IVJ::Rectangulo> medidor);
	[[maybe_unused]] void SistemaApagarBotones(std::shared_ptr<IVJ::Entidad> actual, bool* eSelecc, bool* pSelecc, bool* mostrarSelector);
	[[maybe_unused]] int SistemaRevisarGanador(std::vector<std::shared_ptr<IVJ::Entidad>> turnos);
	[[maybe_unused]] std::vector<std::shared_ptr<CE::ISprite>> SistemaGetQueue(std::vector<std::shared_ptr<IVJ::Entidad>> turnos);
}
