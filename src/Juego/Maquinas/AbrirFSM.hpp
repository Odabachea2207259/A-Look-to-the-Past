#pragma once
#include "FSM.hpp"

namespace IVJ
{
	class AbrirFSM : public FSM
	{
		public:
			explicit AbrirFSM();
			~AbrirFSM() override{};
			FSM* onInputs(const CE::IControl& control) override;
			void onEntrar(const Entidad& obj) override;
			void onSalir(const Entidad& obj) override;
			void onUpdate(const Entidad& obj, float dt) override;
		private:
			bool der{};
            bool termino{};
            int frame;

			CE::Vector2D ani_frames[11]{};
			float tiempo{};
			int id_actual{};
			float max_tiempo{};

			sf::Sprite *sprite{nullptr};
			int s_w{};
			int s_h{};
	};
}
