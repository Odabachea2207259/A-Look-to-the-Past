#include<iostream>
#include<Motor/Motor.hpp>
#include<Motor/Utils/Utils.hpp>
#include<Juego/Juego.hpp>
#include<memory>
#include<SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
    //Crear objeto del motor
    CE::MotorConfig config;
    config.vW=1080;
    config.vH=720;
    config.titulo="CimaEngine";
    std::cout<<"Iniciando "<<config.titulo<<"\n";

    CE::Motor motor{config,std::make_unique<IVJ::Juego>()};
    //ejecutar

    return motor.OnRun();
}
