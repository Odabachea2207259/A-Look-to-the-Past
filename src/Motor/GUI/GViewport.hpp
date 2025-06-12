#pragma once

#include "../GUI/GLayer.hpp"
#include <imgui.h>
namespace CE
{
    class GViewport : public GLayer
    {
        public:
            ~GViewport(){};
            void OnInit(const MotorConfig& des) override;
            void OnUpdate(float dt) override;
            void OnRender(void) override;
        private:
            unsigned int vw;
            unsigned int vh;
	    unsigned int vw_prev;
	    unsigned int vh_prev;
            MotorConfig motor_info;
            ImGuiID id;
    };
}
