#pragma once
#include "../Objetos/Entidad.hpp"
#include "../Objetos/Jugador.hpp"
#include "../Objetos/Periodos.hpp"

namespace IVJ{
	[[maybe_unused]] bool SistemaAtaque(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt,bool salto);
	[[maybe_unused]] bool SistemaSaltar(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt);

	[[maybe_unused]] void SistemaElegirAtaque(std::shared_ptr<IVJ::Entidad> principal,std::shared_ptr<IVJ::Entidad> target, std::string ataque);

	[[maybe_unused]] bool SistemaMover_Target(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt, CE::IControl *c_principal,CE::IControl *c_target,std::shared_ptr<CE::ITransform> trans_principal,std::shared_ptr<CE::ITransform> trans_target, float velocidadDefault);
	[[maybe_unused]] bool SistemaSaltar_Target(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt, CE::IControl *c_principal,CE::IControl *c_target,std::shared_ptr<CE::ITransform> trans_principal,std::shared_ptr<CE::ITransform> trans_target, float velocidadDefault);
	[[maybe_unused]] bool SistemaMover_Original(std::shared_ptr<IVJ::Entidad> principal, std::shared_ptr<IVJ::Entidad> target, float dt, CE::IControl *c_principal,CE::IControl *c_target,std::shared_ptr<CE::ITransform> trans_principal,std::shared_ptr<CE::ITransform> trans_target, float velocidadDefault);

    [[maybe_unused]] bool SistemaIAJefes(std::shared_ptr<Entidad> actual, std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt);
	[[maybe_unused]] bool SistemaIAJefes_P(std::shared_ptr<Entidad> actual, std::vector<std::shared_ptr<IVJ::Entidad>> player, std::vector<std::shared_ptr<IVJ::Entidad>> enemigos, float dt);
}