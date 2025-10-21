#include "Escena_Zombie.hpp"

#include "../../Motor/Render/Render.hpp"
#include "../../Motor/Camaras/CamarasGestor.hpp"
#include "../Sistemas/Sistemas.hpp"
#include "../Figuras/Figuras.hpp"

namespace IVJ
{
    void Escena_Zombie::onInit()
    {
        if(!inicializar) return;

		CE::GestorAssets::Get().agregarTextura("hoja_yellow",ASSETS "/sprites_aliens/alienYellow.png",CE::Vector2D{0,0},CE::Vector2D{256,512});
		CE::GestorAssets::Get().agregarTextura("hoja_pink",ASSETS "/sprites_aliens/alienPink.png",CE::Vector2D{0,0},CE::Vector2D{256,512});
		CE::GestorAssets::Get().agregarTextura("hoja_blue",ASSETS "/sprites_aliens/alienBlue.png",CE::Vector2D{0,0},CE::Vector2D{256,512});
        
        //Registrar los botones
        registrarBotones(sf::Keyboard::Scancode::Escape,"pausa");

        int w,sa,h;

        auto path_test_obj = std::make_shared<Entidad>();
        path_test_obj->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("hoja_blue"),
            68,91,
            1.f
        ))
        .addComponente(std::make_shared<CE::IPaths>(600))
        .getStats()->hp=100;
        path_test_obj->setPosicion(300.f,200.f);
        objetos.agregarPool(path_test_obj);

        auto path = path_test_obj->getComponente<CE::IPaths>();
        path->addCurva(CE::Vector2D{700.f,200.f},CE::Vector2D{600.f,500.f},CE::Vector2D{500.f,200.f});
        path->addCurva(CE::Vector2D{500.f,200.f},CE::Vector2D{400.f,0.f},CE::Vector2D{300.f,200.f});

        auto objeto_muestra = std::make_shared<Entidad>();
        objeto_muestra->addComponente(std::make_shared<CE::ISprite>(
            CE::GestorAssets::Get().getTextura("hoja_pink"),
            68,91,
            1.f
        ))
        .addComponente(std::make_shared<CE::IPaths>(600))
        .getStats()->hp=1;
        objeto_muestra->setPosicion(-1000.f,-1000.f);
        objetos.agregarPool(objeto_muestra);

        h = CE::Render::Get().GetVentana().getSize().y;

        for(int i = 0; i < 3; i++){
            auto p = std::make_shared<IVJ::Entidad>();
            p->getStats()->hp = 100;

            p->addComponente(std::make_shared<CE::ISprite>(
                CE::GestorAssets::Get().getTextura("hoja_yellow"),
                68,85,
                1.0f
            ));

            w = p->getComponente<CE::ISprite>()->width;
            sa = p->getComponente<CE::ISprite>()->height;

            p->setPosicion(w*2,h*0.333334*(i+1)-1.5*sa);

            auto wventana = CE::Render::Get().GetVentana().getSize().x;

            auto linea = std::make_shared<IVJ::Rectangulo>(
                wventana,50,
                sf::Color{255,255,255,255},
                sf::Color{0,255,0,255}
            );

            linea->getStats()->hp = 100;
            float posX = w*3+wventana/2;
            float posY = h*0.33334*(i+1)-1.5*sa;
            linea->setPosicion(posX,posY);

            auto respawn = std::make_shared<Rectangulo>(100,200,sf::Color{255,0,0,255},sf::Color{0,0,0,255});
            respawn->getStats()->hp=1;
            respawn->setPosicion(wventana-50,h*0.333334*(i+1)-1.5*sa);

            respawn->addComponente(std::make_shared<CE::IRespawn>(
                120+(i*60/2),100,200,
                path_test_obj.get()
            ));

            objetos.agregarPool(linea);
            objetos.agregarPool(respawn);
            objetos.agregarPool(p);
        }

        objetos.agregarPool(objeto_muestra);

        //Crear las entidades
        //Inicializar las variables

        CE::GestorCamaras::Get().setCamaraActiva(0);
        //CE::GestorCamaras::Get().getCamaraActiva().lockEnObjeto(objetos.getPool()[0]);

    }
	void Escena_Zombie::onFinal()
    {

    }
	void Escena_Zombie::onUpdate(float dt)
    {   
        SistemaPaths(objetos.getPool());
        SistemaSpawn(objetos.getPool());
        for(auto &obj : objetos.getPool())
        {
            obj->onUpdate(dt);
        }
        
        SistemaMover(objetos.getPool(),dt);

        objetos.borrarPool();
    }
	void Escena_Zombie::onInputs(const CE::Botones& accion)
    {}
	void Escena_Zombie::onRender()
    {
        for(auto &obj : objetos.getPool())
            CE::Render::Get().AddToDraw(*obj);
    } 
}
