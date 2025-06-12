#pragma once
#include "FSM.hpp"

namespace IVJ
{
	class BuffFSM : public FSM
	{
		public:
			explicit BuffFSM();
			~BuffFSM() override{};
			FSM* onInputs(const CE::IControl& control) override;
			void onEntrar(const Entidad& obj) override;
			void onSalir(const Entidad& obj) override;
			void onUpdate(const Entidad& obj, float dt) override;
		private:
			void flipSprite(const Entidad& obj);
		private:
			bool flip{};
			CE::Vector2D ani_frames[9]{};
			float tiempo{};
			int id_actual{};
			float max_tiempo{};

			sf::Sprite *sprite{nullptr};
			int s_w{};
			int s_h{};

			bool termino;
			int frame;
	};
}
