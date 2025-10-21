#pragma once
#include "FSM.hpp"
#include "../Componentes/IJComponentes.hpp"

namespace IVJ
{
	class IdleFSM : public FSM
	{
		public:
			explicit IdleFSM();
			~IdleFSM() override {};
			FSM* onInputs(const CE::IControl& control) override;
			void onEntrar(const Entidad& obj) override;
			void onSalir(const Entidad& obj) override;
			void onUpdate(const Entidad& obj,float dt) override;
		private:
			CE::Vector2D ani_frames[20]{};
			float tiempo{};
			int id_actual{};
			float max_tiempo{};
			int max_frames{};
			//sprite ref
			sf::Sprite *sprite {nullptr};
			int s_w{};
			int s_h{};
	};
}
