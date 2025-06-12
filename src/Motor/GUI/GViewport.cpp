#include "GViewport.hpp"
#include <Motor/Render/Render.hpp>
#include <Motor/Utils/Vector2D.hpp>
#include<imgui_internal.h>
#include<imgui-SFML.h>
#include<iostream>
namespace CE
{

    void GViewport::OnInit(const MotorConfig& des) 
    {
        vw=0;
        vh=0;
        motor_info = des;
    }
    void GViewport::OnUpdate(float dt) {}
    void GViewport::OnRender(void)
    {
#if DEBUG
        ImGui::Begin("GViewPort",nullptr,ImGuiWindowFlags_NoCollapse);
#else
        ImGui::Begin("GViewPort",nullptr,ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoDecoration |
                ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
#endif
        vw = (unsigned int)ImGui::GetContentRegionAvail().x;
        vh = (unsigned int)ImGui::GetContentRegionAvail().y;

//#if DEBUG
//        if(vw==0 || vh == 0)
//        {
//            vw = motor_info.vW - motor_info.vW*0.25f;
//            vh = motor_info.vH - motor_info.vH*0.25f;
//        }
//#endif

#if DEBUG
	//INTENTO
        ImVec2 image_pos = ImGui::GetCursorScreenPos();
	ImVec2 mouse_pos = ImGui::GetMousePos();
	ImVec2 window_pos = ImGui::GetWindowPos();
	//std::cout << "vw " << vw << " vh " << vh << std::endl;
	//std::cout << "Motor vw " << motor_info.vW << " Motor vh " << motor_info.vH << std::endl;
        
        float original_w = static_cast<float>(motor_info.vW);
        float original_h = static_cast<float>(motor_info.vH);

        float drawn_w = static_cast<float>(vw);
        float drawn_h = static_cast<float>(vh);

        float local_x = mouse_pos.x - image_pos.x;
        float local_y = mouse_pos.y - image_pos.y;

        float tex_x = (local_x / drawn_w) * original_w;
        float tex_y = (local_y / drawn_h) * original_h;
        Vector2D relative_pos(tex_x,tex_y);
	Render::Get().setMousePos(relative_pos);
#endif

	//std::cout << relative_pos.x << " " << relative_pos.y << std::endl;
        
        ImGui::Image(Render::Get().GetTextura(),
                    sf::Vector2f(vw,vh), 
                    sf::Color::White, 
                    sf::Color::Transparent);
        Render::Get().AutoResizeTextura(vw,vh);
        ImGui::End();
    }
}
